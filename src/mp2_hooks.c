#include "ultra64.h"
#include "PR/os_eeprom.h"
#include "macros.h"
#include "marioparty.h"

extern s32 loadingBackFromMinigame;
NORETURN void ComboSwitchGameToMp3(void);
void CopyMp3_gPlayerCopy_To_Mp2(void);
void func_800683BC_68FBC(s32);
void mp2_UnkCamThing(f32);

#define NEW_EEP_OFFSET 0x600
#define EEP_BLOCK_OFFSET NEW_EEP_OFFSET / EEPROM_BLOCK_SIZE

extern u8 mp2_HUDSON_Header[];
extern u8 eepromBuffer[(EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)];
extern OSMesgQueue mp2_D_800FA5E0;
extern u8 MarioParty2CompletedSaveData[];

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

s32 mp2__InitEeprom(s8** arg0) {
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
                    //eepromBuffer[i] = 0;
                    eepromBuffer[i] = MarioParty2CompletedSaveData[i];
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

s32 mp2__ReadEeprom(UnkEep* arg0) {
    if (mp2_osEepromLongRead(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, eepromBuffer, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        return 2;
    }
    mp2_bcopy(&eepromBuffer[arg0->unk0], arg0->unk4, arg0->unk8);
    return 0;
}

s32 mp2__WriteEeprom(UnkEep* arg0) {
    u8 eepromBlockOffset;
    s16 i;
    s32 alignmentOffset;
    s32 startOffset;

    if (arg0->unk0 >= 8) {
        for (i = 0; i < arg0->unk8; i++) {
            if (arg0->unk0 + i >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
                break;
            }
            eepromBuffer[arg0->unk0 + i] = arg0->unk4[i];
        }
        
        eepromBlockOffset = (arg0->unk0 / EEPROM_BLOCK_SIZE);
        alignmentOffset = arg0->unk0 & 7;
        startOffset = (arg0->unk8 + alignmentOffset + 7) & 0xFFF8;
        return (mp2_osEepromLongWrite(&mp2_D_800FA5E0, eepromBlockOffset + EEP_BLOCK_OFFSET, &eepromBuffer[eepromBlockOffset * EEPROM_BLOCK_SIZE], startOffset) != 0) * 2;
    }
    return 2;
}

void mp2_Unk_Camera_Function(f32 arg0) {
    if (arg0 == 0.0f) {
        arg0 = 1.0f;
    }
    mp2_UnkCamThing(arg0);
}
