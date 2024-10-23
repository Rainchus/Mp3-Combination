#include "ultra64.h"
#include "PR/os_eeprom.h"
#include "macros.h"
#include "marioparty.h"

#define NEW_EEP_OFFSET 0x400
#define EEP_BLOCK_OFFSET NEW_EEP_OFFSET / EEPROM_BLOCK_SIZE

typedef struct UnkEep {
    u16 unk0;
    char unk2[2];
    u8* unk4;
    u16 unk8;
} UnkEep;

s32 mp1_func_800195E0(void);
s32 mp1_func_80019540(UnkEep* arg0);
s32 mp1_func_80019438(UnkEep* arg0);
s32 mp1_GetEepType(s8** arg0);

extern u8 mp1_D_800D1B20[];
extern u8 mp1_D_800D1B28[];
extern OSMesgQueue mp1_D_800EE960;
extern u8 mp1_D_800C30B0[];

s32 mp1_func_800195E0(void);
s32 mp1_func_80019540(UnkEep* arg0);
s32 mp1_func_80019438(UnkEep* arg0);
s32 mp1_GetEepType(s8** arg0);

s32 mp1_func_80019438_New(UnkEep* arg0) {
    u8 eepromBlockCount;
    s16 i;
    s32 alignmentOffset;
    s32 startOffset;

    if (arg0->unk0 >= 8) {
        for (i = 0; i < arg0->unk8; i++) {
            if (arg0->unk0 + i >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
                break;
            }
            mp1_D_800D1B20[arg0->unk0 + i] = arg0->unk4[i];
        }
        
        eepromBlockCount = (arg0->unk0 / EEPROM_BLOCK_SIZE) + EEP_BLOCK_OFFSET;
        startOffset = (((u8)arg0->unk8 + ((u8)arg0->unk0 & 7) + 7) & 0xF8);
        return (mp1_osEepromLongWrite(&mp1_D_800EE960, eepromBlockCount, &mp1_D_800D1B20[eepromBlockCount * EEPROM_BLOCK_SIZE], startOffset) != 0) * 2;
    }
    return 2;
}

s32 mp1_GetEepType_New(s8** arg0) {
    s32 eepromProbeResult;
    s32 var_s1;
    s16 i;

    var_s1 = 0;
    eepromProbeResult = mp1_osEepromProbe(&mp1_D_800EE960);

    // if (!(eepromProbeResult)) {
    //     return EEPROM_TYPE_4K;
    // }

    if (mp1_osEepromLongRead(&mp1_D_800EE960, EEP_BLOCK_OFFSET, mp1_D_800D1B20, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        //return EEPROM_TYPE_16K;
    }

    i = 0;
    if (mp1_D_800C30B0[i] != 0) {
        while (1) {
            if (mp1_D_800D1B20[i] != mp1_D_800C30B0[i]) {
                var_s1 = 1;
                //Write "HUDSON\0\0" header
                for (i = 0; i < 8; i++) {
                    mp1_D_800D1B20[i] = mp1_D_800C30B0[i];
                }

                for (i = 8; i < EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE; i++) {
                    mp1_D_800D1B20[i] = 0;
                }

                if (mp1_osEepromLongWrite(&mp1_D_800EE960, EEP_BLOCK_OFFSET + 1, &mp1_D_800D1B20[8], (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - EEPROM_BLOCK_SIZE) != 0) {
                    //return EEPROM_TYPE_16K;
                }

                if (mp1_osEepromLongWrite(&mp1_D_800EE960, EEP_BLOCK_OFFSET, &mp1_D_800D1B20[0], EEPROM_BLOCK_SIZE) == 0) {
                    **arg0 = var_s1;
                    return 0;
                }
                //return EEPROM_TYPE_16K;
            }      
            i++;
            if (mp1_D_800C30B0[i] == 0) {
                break;
            }
        }
    }
    **arg0 = var_s1;
    return 0;
}

s32 mp1_GetSaveFileChecksum_New(u16 checksumAddrOffset, u16 size) {
    u16 offset;
    u16 checksumTotal;

    checksumTotal = 0;
    checksumAddrOffset += 8;

    while (size--) {
        offset = checksumAddrOffset;
        checksumAddrOffset++;
        checksumTotal += mp1_D_800D1B20[offset];
        if ((checksumAddrOffset) >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
            break;
        }
    }
    return checksumTotal;
}

u16 mp1_func_8005AFC8_New(void) {
    return mp1_GetSaveFileChecksum_New(NEW_EEP_OFFSET, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - 0x10);
}
