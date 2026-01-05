#include "marioparty.h"
#include "mp3.h"

#define COLD_BOOT 0
#define WARM_BOOT 1
#define osAppNmiBufferSize 64

extern u8 mp3_osAppNmiBuffer[osAppNmiBufferSize];
extern u32 rnd_seed_shared;

s32 AddToDisplayQueue(void* imageData);

void checkosAppNmiBufferReset(s32 resetType) {
    s32 i;

    if (resetType == COLD_BOOT) {
        for (i = 0; i < osAppNmiBufferSize; i++) {
            mp3_osAppNmiBuffer[i] = 0;
        }        
    }
}

//used for all 3 games sharing the same seed address
u8 rand8_Shared(void) {
    rnd_seed_shared = rnd_seed_shared * 0x41C64E6D + 0x3039;
    return ((rnd_seed_shared + 1) >> 16);
}

// Structure for RGBA pixel
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBAPixel;

void mp3_func_8006A370_6AF70(s32);
void mp3_func_80069E68_6AA68(void*);
void mp3_func_800698E8_6A4E8(void*, u16*, s32, void*);

// Function to convert HVQS texture to RGBA32
void* ConvertHVQSToRGBA(void* hvqmCompressed, void* hvqmData, void* alphaData) {
    u16* srcTexture;
    RGBAPixel* destTexture;
    void* tempBuffer;
    int pixelIndex;
    int x, y;
    u16 pixel16;
    u8* alphaPtr = (u8*)alphaData;
    u32 alphaOffset;
    
    // Allocate source texture buffer (16-bit, 128x96 = 24576 bytes)
    srcTexture = (u16*)mp3_HuMemMemoryAllocPerm(0x6000);
    
    // Setup HVQM decoding
    mp3_func_8006A370_6AF70(0xFF);
    mp3_func_80069E68_6AA68(hvqmCompressed);
    
    // Allocate temporary buffer for HVQM decoding
    tempBuffer = mp3_HuMemMemoryAllocPerm(0xC00);
    
    // Decode HVQM texture data into 16-bit format
    mp3_func_800698E8_6A4E8(hvqmData, srcTexture, 0x80, tempBuffer);
    
    // Free temporary buffer
    mp3_HuMemMemoryFreePerm(tempBuffer);
    
    // Allocate destination texture buffer (32-bit RGBA, 128x96x4 = 49152 bytes)
    destTexture = (RGBAPixel*)mp3_HuMemMemoryAllocPerm(0xC000);
    
    // Calculate alpha data offset
    // Original: arg3 + ((arg3->unkA << 0x10) + arg3->unkB)
    // This looks like it's reading a 32-bit offset from the alpha data header
    alphaOffset = *(u16*)((u8*)alphaData + 0xA);
    alphaPtr = (u8*)alphaData + alphaOffset;
    
    // Convert 16-bit RGB to 32-bit RGBA
    pixelIndex = 0;
    for (y = 0; y < 96; y++) {
        for (x = 0; x < 128; x++) {
            // Read 16-bit pixel
            pixel16 = srcTexture[pixelIndex];
            
            // Extract and expand RGB components (RGB555 format)
            destTexture[pixelIndex].r = (pixel16 >> 8) & 0xF8;
            destTexture[pixelIndex].g = (pixel16 >> 3) & 0xF8;
            destTexture[pixelIndex].b = (pixel16 << 2) & 0xF8;
            
            // Get alpha from separate alpha data
            destTexture[pixelIndex].a = alphaPtr[pixelIndex];
            
            pixelIndex++;
        }
    }
    
    // Free source texture
    mp3_HuMemMemoryFreePerm(srcTexture);
    
    return destTexture;
}

extern u16 mp3_player1pressedbuttons;

s32 frameCountWait = 0x0013;
s32 drawImages = 0;

void SetDrawImages(void) {
    drawImages = 1;
}

void newVoteSystem(void) {
    void* image0;
    void* image1;
    void* image2;
    void* converted[4];
    s32 i;
    s32 mainFS_ID = 0x00170048;
    
    drawImages = 0;

    image2 = mp3_DataRead(0x170007);
    for (i = 0; i < 4; i++, mainFS_ID+= 2) {
        image0 = mp3_DataRead(mainFS_ID);
        image1 = mp3_DataRead(mainFS_ID+1);
        converted[i] = ConvertHVQSToRGBA(image1, image0, image2);
    }

    while (drawImages == 0) {
        mp3_HuPrcVSleep();
    }

    for (i = 0; i < frameCountWait; i++) {
        mp3_HuPrcVSleep();
    }

    for (i = 0; i < 4; i++) {
        AddToDisplayQueue(converted[i]);
    }


    while (1) {
        mp3_HuPrcVSleep();
    }
}