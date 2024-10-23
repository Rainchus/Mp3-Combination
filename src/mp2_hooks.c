#include "ultra64.h"
#include "PR/os_eeprom.h"
#include "macros.h"
#include "marioparty.h"

extern s32 loadingBackFromMinigame;
NORETURN void ComboSwitchGameToMp3(void);
void CopyMp3_gPlayerCopy_To_Mp2(void);
void func_800683BC_68FBC(s32);

#define NEW_EEP_OFFSET 0x600
#define EEP_BLOCK_OFFSET NEW_EEP_OFFSET / EEPROM_BLOCK_SIZE

extern u8 mp2_HUDSON_Header[];
// extern u8 eepromBuffer[(EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)];
extern u8 eepromBuffer[(EEP16K_MAXBLOCKS * EEPROM_BLOCK_SIZE)]; //extend this array
//u8 eepromBuffer[(EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)];
extern OSMesgQueue mp2_D_800FA5E0;

typedef struct unkfunc_8001AFD8 {
    s16 unk0;
    struct unkfunc_8001AFD8* unk4; //is this correct?
    s16 unk8;
} unkfunc_8001AFD8;

typedef struct unkfunc_8007EE0C {
    void* GetEepTypeFunc; //func pointer
    unkfunc_8001AFD8* unk4; //is this correct?
    s32 unk8;
    OSMesgQueue* mesgQueue;
} unkfunc_8007EE0C;

typedef struct UnkEep {
    u16 unk0;
    char unk2[2];
    u8* unk4;
    u16 unk8;
} UnkEep;

void mp2_bcopy(u8*, u8*, u16);

s32 GetEepType(s8** arg0) {
    s16 eepromProbeResult;
    s32 var_s1;
    s16 i;

    var_s1 = 0;
    eepromProbeResult = mp2_osEepromProbe(&mp2_D_800FA5E0);
    if ((eepromProbeResult) == 0) {
        for (i = 0; i < 4; i++) {
            eepromProbeResult = mp2_osEepromProbe(&mp2_D_800FA5E0);
            if (eepromProbeResult != 0) {
                break;
            }
        }

        if (i == 4) {
            return EEPROM_TYPE_4K;
        }
    }

    //ASSERT(eepromProbeResult == EEPROM_TYPE_4K);

    if (mp2_osEepromLongRead(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, eepromBuffer, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        //return EEPROM_TYPE_16K;
    }

    i = 1;
    if (mp2_HUDSON_Header[i] != 0) {
        while (1) {
            if (eepromBuffer[i] != mp2_HUDSON_Header[i]) {
                var_s1 = 1;
                //Write "HUDSON\0\0" header
                for (i = 0; i < 8; i++) {
                    eepromBuffer[i] = mp2_HUDSON_Header[i];
                }

                for (i = 8; i < EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE; i++) {
                    eepromBuffer[i] = 0;
                }

                //write actual save data (write all eeprom blocks except first)
                if (mp2_osEepromLongWrite(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET + 1, &eepromBuffer[8], (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - EEPROM_BLOCK_SIZE) != 0) {
                    //return EEPROM_TYPE_16K;
                }
                //write "HUDSON\0\0" header (only write 1 eeprom block)
                if (mp2_osEepromLongWrite(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, &eepromBuffer[0], EEPROM_BLOCK_SIZE) == 0) {
                    **arg0 = var_s1;
                    return 0;
                }
                //return EEPROM_TYPE_16K;
            }      
            i++;
            if (mp2_HUDSON_Header[i] == 0) {
                break;
            }
        }
    }
    **arg0 = var_s1;
    return 0;
}

s32 func_8001AEDC_1BADC(unkfunc_8001AFD8* arg0) {
    unkfunc_8007EE0C sp10;
    unkfunc_8001AFD8* sp20 = arg0; //?

    return mp2_func_8007ee0c_7fa0c(&sp10, &GetEepType, &sp20, 1);
}

s32 func_8001AF0C_1BB0C(UnkEep* arg0) {
    u8 eepromBlockOffset;
    u8 eepromBufferOffset;
    s16 i;
    s32 alignmentOffset;
    s32 size;

    if (arg0->unk0 >= 8) {
            for (i = 0; i < arg0->unk8; i++) {
                if (arg0->unk0 + i >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
                    break;
                }
                eepromBuffer[arg0->unk0 + i] = arg0->unk4[i];
            }
        
        
        eepromBlockOffset = (arg0->unk0 / EEPROM_BLOCK_SIZE);
        eepromBufferOffset = eepromBlockOffset;
        eepromBlockOffset = eepromBlockOffset + EEP_BLOCK_OFFSET;
        alignmentOffset = arg0->unk0 & 7;
        size = (arg0->unk8 + alignmentOffset + 7) & 0xFFF8;
        return (mp2_osEepromLongWrite(&mp2_D_800FA5E0, eepromBlockOffset, &eepromBuffer[eepromBufferOffset * EEPROM_BLOCK_SIZE], size) != 0) * 2;
    }
    return 2;
}

void func_8001AFD8_1BBD8(s32 arg0, unkfunc_8001AFD8* arg1, s16 arg2) {
    unkfunc_8007EE0C sp10;
    unkfunc_8001AFD8 sp20;

    sp20.unk0 = arg0 + 8;
    sp20.unk4 = arg1;
    sp20.unk8 = arg2;

    mp2_func_8007ee0c_7fa0c(&sp10, func_8001AF0C_1BB0C, &sp20, 1);
}

s32 func_8001B014_1BC14(UnkEep* arg0) {
    if (mp2_osEepromLongRead(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, eepromBuffer, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        return 2;
    }
    mp2_bcopy(&eepromBuffer[arg0->unk0], arg0->unk4, arg0->unk8);
    return 0;
}

void func_8001B078_1BC78(s32 arg0, unkfunc_8001AFD8* arg1, s16 arg2) {
    unkfunc_8007EE0C sp10;
    unkfunc_8001AFD8 sp20;

    sp20.unk0 = arg0 + 8;
    sp20.unk4 = arg1;
    sp20.unk8 = arg2;

    mp2_func_8007ee0c_7fa0c(&sp10, func_8001B014_1BC14, &sp20, 1);
}

s32 func_8001B0B4_1BCB4(void) {
    return (mp2_osEepromWrite(&mp2_D_800FA5E0, 0, &mp2_HUDSON_Header[1]) != 0) * 2;
}

s32 func_8001B0E8_1BCE8(unkfunc_8001AFD8* arg0) {
    unkfunc_8007EE0C sp10;

    return mp2_func_8007ee0c_7fa0c(&sp10, &func_8001B0B4_1BCB4, 0, 1);
}

s32 GetSaveFileChecksum(u16 checksumAddrOffset, u16 size) {
    u16 offset;
    u16 checksumTotal;

    checksumTotal = 0;
    checksumAddrOffset += 8;

    while (size--) {
        offset = checksumAddrOffset;
        checksumAddrOffset++;
        checksumTotal += eepromBuffer[offset];
        if ((checksumAddrOffset) >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
            break;
        }
    }
    return checksumTotal;
}

u16 func_8007DC50_7E850(void) {
    return GetSaveFileChecksum(NEW_EEP_OFFSET, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - 0x10);
}

u16 func_80068720_69320(void) {
    return GetSaveFileChecksum(NEW_EEP_OFFSET, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - 0x10);
}
