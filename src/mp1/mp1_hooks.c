#include "ultra64.h"
#include "PR/os_eeprom.h"
#include "macros.h"
#include "marioparty.h"
#include "mp1.h"

#define NEW_EEP_OFFSET 0x400
#define EEP_BLOCK_OFFSET NEW_EEP_OFFSET / EEPROM_BLOCK_SIZE

typedef struct UnkEep {
/* 0x00 */ u16 dest;
/* 0x04 */ u8* src;
/* 0x08 */ u16 size;
} UnkEep;

extern u8 mp1_D_800D1B20[];
extern u8 mp1_D_800D1B28[];
extern OSMesgQueue mp1_D_800EE960;
extern u8 mp1_D_800C30B0[];
extern u8 MarioParty1CompletedSaveData[];

s32 mp1_func_800195E0(void);
s32 mp1_func_80019540(UnkEep* arg0);
s32 mp1_func_80019438(UnkEep* arg0);
s32 mp1_GetEepType(s8** arg0);

s32 mp1__InitEeprom(s8** arg0) {
    // s32 eepromProbeResult;
    s32 var_s1;
    s16 i;

    var_s1 = 0;
    mp1_osEepromProbe(&mp1_D_800EE960);
    // eepromProbeResult = mp1_osEepromProbe(&mp1_D_800EE960);

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
                    mp1_D_800D1B20[i] = MarioParty1CompletedSaveData[i];
                    //mp1_D_800D1B20[i] = 0;
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

#define HUDSON_HEADER_SIZE 8

s32 mp1__ReadEeprom(UnkEep* arg0) {
    if (mp1_osEepromLongRead(&mp1_D_800EE960, EEP_BLOCK_OFFSET, mp1_D_800D1B20, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        return 2;
    }
    mp1_bcopy(&mp1_D_800D1B20[arg0->dest], arg0->src, arg0->size);
    return 0;
}

s32 mp1__WriteEeprom(UnkEep* arg0) {
    u8 eepromBlockOffset;
    s16 i;
    s32 startOffset;

    if (arg0->dest >= 8) {
        for (i = 0; i < arg0->size; i++) {
            if (arg0->dest + i >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
                break;
            }
            mp1_D_800D1B20[arg0->dest + i] = arg0->src[i];
        }
        
        eepromBlockOffset = (arg0->dest / EEPROM_BLOCK_SIZE);
        startOffset = ((u8)arg0->size + ((u8)arg0->dest & 7) + 7) & 0xF8;
        return (mp1_osEepromLongWrite(&mp1_D_800EE960, eepromBlockOffset + EEP_BLOCK_OFFSET, &mp1_D_800D1B20[eepromBlockOffset * EEPROM_BLOCK_SIZE], startOffset) != 0) * 2;
    }
    return 2;
}

void func_800F9440_MinigameInstructions(mp1_omObjData*);
extern mp1_omObjData* mp1_D_8010F404_MinigameInstructions;
extern Vec3f mp1_CRot;
extern Vec3f mp1_Center;
extern s8 mp1_omSysPauseEnableFlag;
extern f32 mp1_CZoom;
extern u16 mp1_D_8010F766_MinigameInstructions;
extern s16 mp1_D_8010F760_MinigameInstructions;
typedef struct Unk_D_8010E4F4_MinigameInstructions {
    u8 unk_00;
    char unk_01[0x13];
} Unk_D_8010E4F4_MinigameInstructions;

extern Unk_D_8010E4F4_MinigameInstructions mp1_D_8010E4F4_MinigameInstructions[];

extern s16 mp1_D_8010F4E0_MinigameInstructions;
void func_800F92D4_MinigameInstructions(mp1_omObjData*);
s32 mp1_CheckFlag(s32);

void func_800F692C_MinigameInstructions(mp1_omObjData*);
void func_800F6B14_MinigameInstructions(void);
void func_800FA470_MinigameInstructions(void);
extern s16 mp1_D_8010F400_MinigameInstructions;
extern s16 mp1_D_8010F402_MinigameInstructions;
extern s16 mp1_D_8010F764_MinigameInstructions;
extern s16 mp1_D_8010F408_MinigameInstructions;
extern s16 mp1_D_8010F4E2_MinigameInstructions;
extern s16 mp1_D_8010F772_MinigameInstructions;
void func_800F9110_MinigameInstructions(void);
extern u8 mp1_D_8010F050_MinigameInstructions;
extern void* mp1_D_8010F4E4_MinigameInstructions;
void mp1_func_8007FAC0(void);
void mp1_func_8007B168(u8* arg0, u8 arg1);
void mp1_InitCameras(s16 count);
void func_80029090(s32);
void func_8001DE70(s16);
void func_80060088(void);
void func_8006CEA0(void);
void func_8010E090_MinigameInstructions(s16);
void func_800F9E64_MinigameInstructions(s16);
void func_800593AC(s16 arg0);
void func_800F6990_MinigameInstructions(void);
mp1_omObjData* mp1_omAddObj(s16, u16, u16, s16, void*);
void mp1_omSetStatBit(mp1_omObjData*, s32);
void func_8001D494(s16, f32, f32, f32);
void func_80023448(s32);
void func_800234B8(u8, u8, u8, u8);
void func_80023504(s32, f32, f32, f32);

typedef struct mp1_jmp_buf
{
    void *sp;
    void *func;
    u32 regs[21];
} mp1_jmp_buf;
typedef void (*mp1_process_func)();
typedef struct mp1_Process {
           struct mp1_Process *next;
           struct mp1_Process *youngest_child;
           struct mp1_Process *oldest_child;
           struct mp1_Process *relative;
           struct mp1_Process *parent_oldest_child;
           struct mp1_Process *new_process;
           void *heap;
           u16 exec_mode;
           u16 stat;
           u16 priority;
           s16 dtor_idx;
           s32 sleep_time;
           void *base_sp;
           mp1_jmp_buf prc_jump;
           mp1_process_func destructor;
           void *user_data;
} mp1_Process;

mp1_Process* mp1_omAddPrcObj(mp1_process_func func, u16 priority, s32 stack_size, s32 extra_data_size);
void* func_80023684(s32, s16);


//check if we need to swap games from currentl being in mp1
void CheckIfShouldSwapGames(void) {
    if (mp1_GwSystem.curMinigame >= HAND_LINE_AND_SINKER && mp1_GwSystem.curMinigame <= MARIO_PUZZLE_PARTY_PRO) { //mp3
        SaveMp1PlayerStructs();
        PushMp1BoardState();
        PushMp1MinigamesPlayedList();
        ForeignMinigameIndexToLoad = mp1_GwSystem.curMinigame;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp1OvlHis();
        ComboSwitchGameToMp3();
    } else if (mp1_GwSystem.curMinigame >= BOWSER_SLOTS && mp1_GwSystem.curMinigame <= DEEP_SEA_SALVAGE) { //mp3 { //mp2
        SaveMp1PlayerStructs();
        PushMp1BoardState();
        PushMp1MinigamesPlayedList();
        ForeignMinigameIndexToLoad = mp1_GwSystem.curMinigame;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp1OvlHis();
        ComboSwitchGameToMp2();
    }
    //else is mp1, do nothing and exit
}


//coin shower flower is trying to load bumper balls maze?
//TODO: top priority to fix ^

void newfunc_800F6610_MinigameInstructions(void) {
    #ifdef MP1
    mp1_omObjData* obj;
    s32 i;

    mp1_InitCameras(1);
    func_80029090(1);
    func_8001DE70(0x19);
    mp1_omInitObjMan(0x32, 0x14);
    func_80060088();
    func_8006CEA0();
    mp1_omSysPauseEnableFlag = 1;
    CheckIfShouldSwapGames();
    mp1_GwSystem.curMinigame = ForeignMinigameIDToGame(mp1_GwSystem.curMinigame);
    mp1_D_8010F766_MinigameInstructions = mp1_GwSystem.curMinigame;
    mp1_D_8010F760_MinigameInstructions = mp1_D_8010E4F4_MinigameInstructions[mp1_GwSystem.curMinigame].unk_00;
    if (mp1_CheckFlag(0x2B) != 0) {
        func_8010E090_MinigameInstructions(mp1_D_8010F766_MinigameInstructions);
    } else {
        func_800F9E64_MinigameInstructions(mp1_D_8010F766_MinigameInstructions);
    }
    func_800593AC(-1);
    mp1_D_8010F4E0_MinigameInstructions = mp1_CheckFlag(0x45);
    if (mp1_GwSystem.minigameExplanation == 1) {
        func_800F6990_MinigameInstructions();
        return;
    }
    obj = mp1_omAddObj(0x7FDA, 0U, 0U, -1, func_800F92D4_MinigameInstructions);
    mp1_omSetStatBit(obj, 0xA0);
    mp1_omAddObj(0x2710, 0U, 0U, -1, &func_800F9440_MinigameInstructions);
    mp1_CRot.x = 0.0f;
    mp1_CRot.y = 0.0f;
    mp1_CRot.z = 0.0f;
    mp1_CZoom = 2000.0f;
    mp1_Center.x = mp1_Center.y = mp1_Center.z = 0.0f;
    func_8001D494(0, 10.0f, 80.0f, 8000.0f);
    func_800F92D4_MinigameInstructions(obj);
    func_80023448(3);
    func_800234B8(0U, 0x78U, 0x78U, 0x78U);
    func_800234B8(1U, 0x40U, 0x40U, 0x60U);
    func_80023504(1, -100.0f, 100.0f, 100.0f);
    func_800234B8(2U, 0U, 0U, 0U);
    func_800234B8(3U, 0U, 0U, 0U);
    mp1_D_8010F404_MinigameInstructions = mp1_omAddObj(0x3E8, 0xAU, 0xAU, -1, &func_800F692C_MinigameInstructions);
    mp1_omAddPrcObj(func_800F6B14_MinigameInstructions, 0x3F00U, 0x800, 0);
    mp1_omAddPrcObj(func_800FA470_MinigameInstructions, 0x3F00U, 0x800, 0);
    mp1_D_8010F400_MinigameInstructions = 0;
    mp1_D_8010F402_MinigameInstructions = 0;
    mp1_D_8010F764_MinigameInstructions = -1;
    mp1_D_8010F408_MinigameInstructions = -1;
    mp1_D_8010F4E2_MinigameInstructions = -1;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (mp1_gPlayers[i].group == 0) {
            break;
        }
    }
    mp1_D_8010F772_MinigameInstructions = i;
    mp1_omAddPrcObj(func_800F9110_MinigameInstructions, 0x3F00, 0x800, 0);
    mp1_func_8007B168(&mp1_D_8010F050_MinigameInstructions, 0);
    mp1_func_8007FAC0();
    mp1_D_8010F4E4_MinigameInstructions = func_80023684(0x1040, 0x7918);
    #endif
}