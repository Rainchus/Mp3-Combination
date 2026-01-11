#include "mp1.h"

typedef struct Unk_D_8010E4F4_MinigameInstructions {
    u8 unk_00;
    char unk_01[0x13];
} Unk_D_8010E4F4_MinigameInstructions;

extern Unk_D_8010E4F4_MinigameInstructions mp1_D_8010E4F4_MinigameInstructions[];

void mp1_func_8007FAC0(void);
void func_800F6990_MinigameInstructions(void);
void mp1_func_800F6B14_MinigameInstructions(void);
void mp1_func_800F9110_MinigameInstructions(void);
void mp1_func_800F92D4_MinigameInstructions(mp1_omObjData*);
void mp1_func_800F9E64_MinigameInstructions(s16);
void mp1_func_800FA470_MinigameInstructions(void);
void mp1_func_8010E090_MinigameInstructions(s16);
extern s8 mp1_omSysPauseEnableFlag;
extern u8 mp1_D_8010F050_MinigameInstructions;
extern s16 mp1_D_8010F400_MinigameInstructions;
extern s16 mp1_D_8010F402_MinigameInstructions;
extern mp1_omObjData* mp1_D_8010F404_MinigameInstructions;
extern s16 mp1_D_8010F408_MinigameInstructions;
extern s16 mp1_D_8010F4E0_MinigameInstructions;
extern s16 mp1_D_8010F4E2_MinigameInstructions;
extern void* mp1_D_8010F4E4_MinigameInstructions;
extern s16 mp1_D_8010F760_MinigameInstructions;
extern s16 mp1_D_8010F764_MinigameInstructions;
extern s16 mp1_D_8010F766_MinigameInstructions;
extern s16 mp1_D_8010F772_MinigameInstructions;
void mp1_func_800F692C_MinigameInstructions(mp1_omObjData*);
void mp1_func_800F9440_MinigameInstructions(mp1_omObjData*);
void mp1_func_80029090(s32);
void mp1_func_8001DE70(s32);
void mp1_func_80060088(void);
void mp1_func_8006CEA0(void);
s32 mp1__CheckFlag(s32);
void mp1_func_80023448(s32);
void mp1_func_800234B8(s32, s32, s32, s32);
void mp1_func_80023504(s32, f32, f32, f32);
void mp1_func_8001D494(s16, f32, f32, f32);
void* mp1_func_80023684(s32, s32);
void SaveMp1PlayerToMp1PlayerCopy(void);
void LoadMp3PlayerCopyToMp1(void);
void LoadMp2PlayerCopyToMp1(void);

extern f32 mp1_CZoom;
extern Vec3f mp1_CRot;
extern Vec3f mp1_Center;

void Mp1SwapGameIfNeeded(void) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

    //determine if we are loading a mp2 or mp3 minigame
    if (ForeignMinigameIndexToLoad >= BOWSER_SLOTS && ForeignMinigameIndexToLoad <= DEEP_SEA_SALVAGE) { //mp2
        //save necessary data, swap to mp2
        //TODO: implement these functions
        // PushMp1BoardState();
        // PushMp1MinigamesPlayedList();
        // mp1_StoreBattleMinigameCoins();
        SaveMp1PlayerToMp1PlayerCopy();
        ComboSwitchGameToMp2();
    } else if (ForeignMinigameIndexToLoad >= HAND_LINE_AND_SINKER && ForeignMinigameIndexToLoad <= MARIO_PUZZLE_PARTY_PRO) { //mp3
        //save necessary data, swap to mp3
        //TODO: implement these functions
        // PushMp1BoardState();
        // PushMp1MinigamesPlayedList();
        // mp1_StoreBattleMinigameCoins();
        SaveMp1PlayerToMp1PlayerCopy();
        ComboSwitchGameToMp3();
    }
    //is mp1 minigame, load it
    mp1_GwSystem.curMinigame = localOverlayID;
    ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
}

void func_800F6610_MinigameInstructions(void) {
    mp1_omObjData* obj;
    s32 i;

    Mp1SwapGameIfNeeded();
    if (CurBaseGame == MP3_BASE) {
        LoadMp3PlayerCopyToMp1();
    } else { //MP2_BASE
        LoadMp2PlayerCopyToMp1();
    }

    mp1_InitCameras(1);
    mp1_func_80029090(1);
    mp1_func_8001DE70(0x19);
    mp1_omInitObjMan(0x32, 0x14);
    mp1_func_80060088();
    mp1_func_8006CEA0();
    mp1_omSysPauseEnableFlag = 1;
    mp1_D_8010F766_MinigameInstructions = mp1_GwSystem.curMinigame;
    mp1_D_8010F760_MinigameInstructions = mp1_D_8010E4F4_MinigameInstructions[mp1_GwSystem.curMinigame].unk_00;
    if (mp1__CheckFlag(0x2B) != 0) {
        mp1_func_8010E090_MinigameInstructions(mp1_D_8010F766_MinigameInstructions);
    } else {
        mp1_func_800F9E64_MinigameInstructions(mp1_D_8010F766_MinigameInstructions);
    }
    mp1_func_800593AC(-1);
    mp1_D_8010F4E0_MinigameInstructions = mp1__CheckFlag(0x45);
    if (mp1_GwSystem.minigameExplanation == 1) {
        func_800F6990_MinigameInstructions();
        return;
    }
    obj = mp1_omAddObj(0x7FDA, 0U, 0U, -1, mp1_func_800F92D4_MinigameInstructions);
    mp1_omSetStatBit(obj, 0xA0);
    mp1_omAddObj(0x2710, 0U, 0U, -1, &mp1_func_800F9440_MinigameInstructions);
    mp1_CRot.x = 0.0f;
    mp1_CRot.y = 0.0f;
    mp1_CRot.z = 0.0f;
    mp1_CZoom = 2000.0f;
    mp1_Center.x = mp1_Center.y = mp1_Center.z = 0.0f;
    mp1_func_8001D494(0, 10.0f, 80.0f, 8000.0f);
    mp1_func_800F92D4_MinigameInstructions(obj);
    mp1_func_80023448(3);
    mp1_func_800234B8(0U, 0x78U, 0x78U, 0x78U);
    mp1_func_800234B8(1U, 0x40U, 0x40U, 0x60U);
    mp1_func_80023504(1, -100.0f, 100.0f, 100.0f);
    mp1_func_800234B8(2U, 0U, 0U, 0U);
    mp1_func_800234B8(3U, 0U, 0U, 0U);
    mp1_D_8010F404_MinigameInstructions = mp1_omAddObj(0x3E8, 0xAU, 0xAU, -1, &mp1_func_800F692C_MinigameInstructions);
    mp1_omAddPrcObj(mp1_func_800F6B14_MinigameInstructions, 0x3F00U, 0x800, 0);
    mp1_omAddPrcObj(mp1_func_800FA470_MinigameInstructions, 0x3F00U, 0x800, 0);
    mp1_D_8010F400_MinigameInstructions = 0;
    mp1_D_8010F402_MinigameInstructions = 0;
    mp1_D_8010F764_MinigameInstructions = -1;
    mp1_D_8010F408_MinigameInstructions = -1;
    mp1_D_8010F4E2_MinigameInstructions = -1;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (mp1_GwPlayer[i].group == 0) {
            break;
        }
    }
    mp1_D_8010F772_MinigameInstructions = i;
    mp1_omAddPrcObj(mp1_func_800F9110_MinigameInstructions, 0x3F00, 0x800, 0);
    mp1_func_8007B168(&mp1_D_8010F050_MinigameInstructions, 0);
    mp1_func_8007FAC0();
    mp1_D_8010F4E4_MinigameInstructions = mp1_func_80023684(0x1040, 0x7918);
}

typedef struct mp1_UnkomOvl {
    s32 unk_00;
    u16 unk_04;
    char unk_06[0xE]; //unused pad?
} mp1_UnkomOvl; //szieof 0x14

extern mp1_UnkomOvl mp1_D_8010E4F0_MinigameInstructions[];
extern s16 mp1_D_8010F4E0_MinigameInstructions;
extern s16 mp1_D_8010F766_MinigameInstructions;

void mp1_func_80070ED4(void);

void func_800F6990_MinigameInstructions(void) {
    mp1_func_80070ED4();
    if (mp1__CheckFlag(0x2B) != 0) {
        if (mp1__CheckFlag(0x2D) == 0) {
            mp1_omOvlCallEx(mp1_D_8010E4F0_MinigameInstructions[mp1_D_8010F766_MinigameInstructions].unk_00, 0, 0x14);
            mp1_omOvlHisChg(1, 0x7D, 0, 0x92); //minigame island miss?
            return;
        }
    } else if ((mp1__CheckFlag(0x2C) != 0) || (mp1__CheckFlag(0x30) != 0)) {
        if ((mp1_D_8010F4E0_MinigameInstructions == 0) && (mp1__CheckFlag(0x29) == 0)) {
            mp1_omOvlCallEx(mp1_D_8010E4F0_MinigameInstructions[mp1_D_8010F766_MinigameInstructions].unk_00, 0, 0x14);
            mp1_omOvlHisChg(1, 0x7B, 0, 0x92); //minigame stadium results scene
            return;
        }
    } else if ((mp1_D_8010F4E0_MinigameInstructions == 0) && (mp1__CheckFlag(0x29) == 0)) {
        mp1_omOvlCallEx(mp1_D_8010E4F0_MinigameInstructions[mp1_D_8010F766_MinigameInstructions].unk_00, 0, 0x14);

        if (CurBaseGame == MP1_BASE) {
            mp1_omOvlHisChg(1, 0x7C, 0, 0x14); //noraml results scene after minigame
        } else {
            mp1_omOvlHisChg(1, 0x67, 0, 0x14); //push boot logos which has swap logic for swapping back to main game
        }
        return;
    }
    mp1_omOvlGotoEx(mp1_D_8010E4F0_MinigameInstructions[mp1_D_8010F766_MinigameInstructions].unk_00, 0, 0x14);
}