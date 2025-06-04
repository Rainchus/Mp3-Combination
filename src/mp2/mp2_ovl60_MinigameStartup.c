#include "mp2.h"

void mp2_func_80102A14_3BE174_name_60(void);
void mp2_func_80102AF0_3BE250_name_60(void);
void func_801085A0_3C3D00_name_60(s32); //exist within the file, dont call mp2 variant
void mp2_func_80105B94_3C12F4_name_60(void);

extern s16 mp2_D_801148F2_3D0052_name_60;
extern s16 mp2_D_801148F4_3D0054_name_60;
extern s16 mp2_D_80114AC2_3D0222_name_60;

void Mp2SwapGameIfNeeded(void) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

    //determine if we are loading a mp3 or mp1 minigame
    if (ForeignMinigameIndexToLoad >= HAND_LINE_AND_SINKER && ForeignMinigameIndexToLoad <= MARIO_PUZZLE_PARTY_PRO) { //mp2
        //save necessary data
        //SaveMp2PlayerStructs();
        PushMp2BoardState();
        PushMp2MinigamesPlayedList();
        mp2_StoreBattleMinigameCoins();
        ComboSwitchGameToMp3();
    } else if (ForeignMinigameIndexToLoad >= MEMORY_MATCH && ForeignMinigameIndexToLoad <= PADDLE_BATTLE) { //mp3 { //mp2
        //save necessary data
        //SaveMp2PlayerStructs();
        PushMp2BoardState();
        PushMp2MinigamesPlayedList();
        mp2_StoreBattleMinigameCoins();
        ComboSwitchGameToMp1();
    }
    //is mp2 minigame, load it
    mp2_GwSystem.chosenMinigameIndex = localOverlayID;
    ForeignMinigameIndexToLoad = -1;
}

void mp2_func_80102830_3BDF90_name_60(void) {
    s16 var_v0_2;
    s32 temp_s0;
    s32 i;

    Mp2SwapGameIfNeeded();
    if (CurBaseGame == MP3_BASE) {
        LoadMp3PlayerCopyToMp2();
    }
    mp2_func_80102A14_3BE174_name_60();
    if ((mp2_GwSystem.minigameExplanations == 1)) {
        func_801085A0_3C3D00_name_60(0);
        return;
    }

    switch (mp2_D_801148F2_3D0052_name_60) {
    case 6:
    case 7:
        func_801085A0_3C3D00_name_60(0);
        return;
    }

    mp2_PlayMusic(0x16);
    mp2_omSetStatBit(mp2_omAddObj(0x7FDA, 0U, 0U, -1, &mp2_func_80079E60_7AA60), 0xA0);
    mp2_func_80018E30_19A30(1);
    temp_s0 = mp2_func_80018E78_19A78();
    mp2_ScissorSet(temp_s0, 0.0f, 0.0f, 320.0f, 240.0f);
    mp2_ViewportSet(temp_s0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    mp2_func_800202DC_20EDC(0, 10.0f, 500.0f, 5000.0f);
    mp2_D_800FA610_FB210 = 2500.0f;

    mp2_D_800FD474_FE074.x = 0;
    mp2_D_800FD474_FE074.y = 0;
    mp2_D_800FD474_FE074.z = 0;

    mp2_D_8010274C_10334C.x = 0;
    mp2_D_8010274C_10334C.y = 0;
    mp2_D_8010274C_10334C.z = 0;
    
    mp2_func_80102AF0_3BE250_name_60();
    mp2_omAddPrcObj(&mp2_func_80105B94_3C12F4_name_60, 0x1001U, 0x800, 0);
    
    for (i = 0; i < 4; i++) {
        if (mp2_GwPlayer[i].group == 0) {
            break;
        }
    }

    mp2_D_801148F4_3D0054_name_60 = mp2_D_80114AC2_3D0222_name_60 = i;
    mp2_InitFadeIn(0, 0x10);
}

extern s16 mp2_D_801148F0_3D0050_name_60;
extern s16 mp2_D_801148F2_3D0052_name_60;
extern s16 mp2_D_8011497A_3D00DA_name_60;
extern s32 mp2_D_8011497C_3D00DC_name_60;
extern s32 mp2_D_80114980_3D00E0_name_60;
extern s32 mp2_D_80114984_3D00E4_name_60;

void mp2_func_8008CE5C_8DA5C(void);
void mp2_func_800727F0_733F0(void);
void mp2_func_80067EF8_68AF8(s32);
void mp2_func_80017800_18400(s32);
void mp2_omOvlKill(void);
void mp2_omOvlHisChg(s16 arg0, s32 overlay, s16 event, s16 stat);

void func_801085A0_3C3D00_name_60(s32 arg0) {
    mp2_func_8008CE5C_8DA5C();
    if (CurBaseGame == MP2_BASE) {
        mp2_func_800727F0_733F0(); //clears coins
    }
    mp2_func_80067EF8_68AF8(-1);
    
    if (arg0 != 0) {
        mp2_func_80017800_18400(mp2_D_80114984_3D00E4_name_60);
        mp2_func_80017800_18400(mp2_D_8011497C_3D00DC_name_60);
        mp2_func_80017800_18400(mp2_D_80114980_3D00E0_name_60);
        mp2_omOvlKill();
    }
    
    if (mp2_D_8011497A_3D00DA_name_60 != 0) {
        mp2_omOvlCallEx(mp2_D_800CAD90[mp2_D_801148F0_3D0050_name_60].unk_00, 0, 0x14);
        mp2_omOvlHisChg(1, mp2_func_8003F6F0_402F0(mp2_GwSystem.chosenMinigameIndex), 0, 0x14);
        return;
    } 
    
    mp2__ClearFlag(0x15);
    if ((mp2__CheckFlag(0x13) != 0) || !(mp2__CheckFlag(0xC) == 0)) {
        mp2_omOvlGotoEx(mp2_D_800CAD90[mp2_D_801148F0_3D0050_name_60].unk_00, 0, 0x14);
        return;
    }
    
    switch (mp2_D_801148F2_3D0052_name_60) {
        case 6:
        case 5:
        case 4:
            mp2_omOvlGotoEx(mp2_D_800CAD90[mp2_D_801148F0_3D0050_name_60].unk_00, 0, 0x14);
            return;
        case 7:
            mp2_GwSystem.current_board_index = mp2_D_801148F0_3D0050_name_60 - 0x3A;
            mp2_D_800F8D18[2] = 1;
            mp2_D_800F8D18[1] = 0xE;
            mp2_omOvlGotoEx(mp2_D_800CAD90[mp2_D_801148F0_3D0050_name_60].unk_00, 0, 0x12);
            return;
            
        case 3:
            mp2_omOvlCallEx(mp2_D_800CAD90[mp2_D_801148F0_3D0050_name_60].unk_00, 0, 0x14);
            if (CurBaseGame == MP2_BASE) {
                mp2_omOvlHisChg(1, 0x6F, 0, 0x14); //original code; push results scene to history
            } else {
                mp2_omOvlHisChg(1, 0, 0, 0x14); //push debug overlay (has logic for returning to original game)
            }
            return;
    }
    mp2_omOvlCallEx(mp2_D_800CAD90[mp2_D_801148F0_3D0050_name_60].unk_00, 0, 0x14);
    if (CurBaseGame == MP2_BASE) {
        mp2_omOvlHisChg(1, 0x70, 0, 0x14);
    } else {
        mp2_omOvlHisChg(1, 0, 0, 0x14); //push debug overlay (has logic for returning to original game)
    }
}
