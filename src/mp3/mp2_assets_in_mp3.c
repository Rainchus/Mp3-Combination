#include "mp3/malloc.h"
#include "macros.h"

/* Private MP2 filesystem state — completely separate from MP3's globals */
static u32  sMp2RomAddr = 0;
static s32 *sMp2DirTbl = 0;
static u32  sMp2DirMax = 0;
static u32  sMp2FileRomAddr = 0;
static s32 *sMp2FileTbl = 0;
static u32  sMp2FileMax = 0;

// 16 byte portion of a directory or file table, which is initially read from ROM.
typedef struct {
    s32 count;
    s32 offsets[3]; // Enough to pad to size 16
} HuArchive;

typedef enum
{
    DECODE_NONE = 0,
    DECODE_LZ,              // lzss
    DECODE_SLIDE,           // yaz0/szs
    DECODE_FSLIDE,          // yaz0/szs, no loopback
    DECODE_FSLIDE_2,        // yaz0/szs, no loopback
    DECODE_RLE              // custom rle variant
} EDecodeType;

s32 mp3_dmaRead(u32 src, u8 *dest, s32 size);
void mp3_DecodeData(u32 src, void *dest, s32 len, EDecodeType decodeType);
void* mp3_HuMemMemoryAllocTemp(u32 size);

/* Private header scratch (instead of sharing gArchive). 8-byte aligned for PI DMA. */
static HuArchive sMp2Archive __attribute__((aligned(8))) = {0};

typedef struct {
    u32 bytes;
    u32 size;
    u32 compType;
} Mp2FileInfo;

void Mp2DataInit(u32 fsRomAddr) {
    s32 tblSize;

    sMp2RomAddr = fsRomAddr;
    mp3_dmaRead(fsRomAddr, (u8 *)&sMp2Archive, 16);

    sMp2DirMax = sMp2Archive.count;
    tblSize    = sMp2DirMax * 4;
    sMp2DirTbl = mp3_HuMemMemoryAllocPerm(tblSize);
    mp3_dmaRead(fsRomAddr + 4, (u8 *)sMp2DirTbl, tblSize);

    sMp2FileRomAddr = sMp2RomAddr;
    sMp2FileMax     = sMp2DirMax;
    sMp2FileTbl     = sMp2DirTbl;
}

static void Mp2DataDirInit(s32 dir) {
    u32 tablePtr = sMp2RomAddr + sMp2DirTbl[dir];
    s32 tblSize;

    if (sMp2FileRomAddr == tablePtr) {
        return; /* already cached */
    }
    if (sMp2FileRomAddr != sMp2RomAddr) {
        mp3_HuMemMemoryFreePerm(sMp2FileTbl);
    }

    sMp2FileRomAddr = tablePtr;
    mp3_dmaRead(tablePtr, (u8 *)&sMp2Archive, 16);

    sMp2FileMax = sMp2Archive.count;
    tblSize     = sMp2FileMax * 4;
    sMp2FileTbl = mp3_HuMemMemoryAllocPerm(tblSize);
    mp3_dmaRead(tablePtr + 4, (u8 *)sMp2FileTbl, tblSize);
}

static void Mp2DataInfoRead(s32 file, Mp2FileInfo *info) {
    info->bytes = sMp2FileRomAddr + sMp2FileTbl[file];
    mp3_dmaRead(info->bytes, (u8 *)&sMp2Archive, 16);

    info->bytes   += 8;
    info->size     = sMp2Archive.count;
    info->compType = sMp2Archive.offsets[0];
}

/* heap: 0 = perm, 1 = temp, 2 = tagged */
static void *Mp2DataReadCommon(s32 dirAndFile, s32 heap, s32 tag) {
    u32 dir  = (u32)dirAndFile >> 16;
    u32 file = dirAndFile & 0xFFFF;
    Mp2FileInfo info;
    void *buf;
    u32 allocSize;

    if (dir >= sMp2DirMax) return NULL;
    Mp2DataDirInit(dir);
    if (file >= sMp2FileMax) return NULL;

    Mp2DataInfoRead(file, &info);
    allocSize = (info.size + 1) & ~1;

    switch (heap) {
        case 0:  buf = mp3_HuMemMemoryAllocPerm(allocSize); break;
        case 1:  buf = mp3_HuMemMemoryAllocTemp(allocSize); break;
        default: buf = mp3_HuMemAllocTag(allocSize, tag);   break;
    }

    if (buf != NULL) {
        mp3_DecodeData(info.bytes, buf, info.size, info.compType);
    }
    return buf;
}

void *Mp2DataRead(s32 id) {
    return Mp2DataReadCommon(id, 0, 0);
}

void *Mp2DataReadTemp(s32 id) {
    return Mp2DataReadCommon(id, 1, 0);
}
void *Mp2DataReadNum(s32 id, s32 tag)  {
    return Mp2DataReadCommon(id, 2, tag);
}

void Mp2DataClose(void *data) {
    if (data != NULL) {
        mp3_HuMemMemoryFreePerm(data); /* free is heap-independent, same as MP3 */
    }
}

s16 mp2_func_8000B838_main(s32 arg0) {
    void *temp_v0;
    s16 temp_s0;

    temp_v0 = Mp2DataRead(arg0);
    if (temp_v0 == NULL) {
        return -1;   // bad MP2 dir/file
    }
    temp_s0 = mp3_func_80055810_56410(temp_v0);
    mp3_HuMemMemoryFreePerm(temp_v0);
    return temp_s0;
}

extern u32 mp3_DataDirMax;
extern u32 mp3_DataFileMax; // Directory count (copy)

typedef enum
{
    ARCHIVE_CACHED = 0x2E,
    ARCHIVE_DIRECT,
} EArchiveType;

void mp3_DataDirInit(EArchiveType type, s32 dir);
void* mp3_DataDecode(EArchiveType type, s32 index);



typedef struct Mp2AssetToMp3 {
    s32 mp2ID;
    s32 unkMp2;
    s32 mp3ID;
    s32 unkMp3;
} Mp2AssetToMp3;

//maps hmf file from one game to another (vanilla mp3 yoshi to horror yoshi from mp2)
Mp2AssetToMp3 animReplacementLoop[] = {
    {0x000400D9, 0x6A9, 0x000400A0, 0x6A9}, //map yoshi to horror yoshi
    {0x000400D9, 0x6A9, 0x000400A1, 0x6A9}, //map yoshi to horror yoshi

    //map yoshi to horror yoshi (this requires 0xD8 not 0xD9 for horror land sprite because?? during party mode setup)
    {0x000400D8, 0x6A9, 0x000400A2, 0x6A9}, 
};

void *DataReadHook(s32 dirAndFile) {
    u32 dir;
    u32 file;
    s32 i;

    /* everything else: normal MP3 load */
    dir  = (u32)dirAndFile >> 16;
    file = dirAndFile & 0xFFFF;

    //if mario through daisy
    if (dir >= 2 && dir <= 7) {
        //swap out wanted mp3 IDs with mp2 models
        for (i = 0; i < ARRAY_COUNT(animReplacementLoop); i++) {
            if (dirAndFile == animReplacementLoop[i].mp3ID) {
                return Mp2DataRead(animReplacementLoop[i].mp2ID);
            }
        }
    }

    if (dir < mp3_DataDirMax) {
        mp3_DataDirInit(ARCHIVE_DIRECT, dir);
        if (file < mp3_DataFileMax) {
            return mp3_DataDecode(ARCHIVE_CACHED, file);
        }
    }
    
    return NULL;
}