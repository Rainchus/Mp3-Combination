#include "marioparty.h"

s16 mp1_InitSprite(s32);
void mp1_SetBasicSpritePos(s32, s32, s32);
void mp1_SetFadeInTypeAndTime(s32, s32);
void mp1_ShowBasicSprite(s32);
void mp1_func_80018D84(s32, s32);
s32 mp1_func_80019060(s16, s32, s32);
void mp1_func_800191F8(s32);
void mp1_func_80067704(s16);
void mp1_func_800726AC(s32, s32);
s32 mp1_func_80072718(void);
extern s16 mp1_D_800F5144;
void mp1_HuPrcVSleep(void);
void mp1_HuPrcSleep(s32);
extern s32 ForeignMinigameIndexToLoad;
extern s32 mp3_LoadBackFromMp2;
NORETURN void ComboSwitchGameToMp3(void);
s32 mp1_omOvlCallEx(s32 arg0, s16 arg1, u16 arg2);
extern u8 mp1_D_800ED5E3;
extern u16 mp1_D_800ED5DE;
void CopyMp3_gPlayerCopy_To_Mp1(void);
void mp1_omInitObjMan(s32, s32);
extern mp3_PlayerData mp3_PlayersCopy[4];
extern u32 mp1_rnd_seed;

//func_800F686C_LogosSequence
void mp1_OriginalBootLogos(void) {
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0_2;
    s32 temp_v0_4;

    temp_v0 = mp1_InitSprite(0x9006D);
    temp_v0_2 = mp1_func_80019060(temp_v0, 0, 1);
    temp_s0 = temp_v0_2 & 0xFFFF;
    mp1_SetBasicSpritePos(temp_s0, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0);
    mp1_func_80018D84(temp_s0, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 30);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(5);
    mp1_func_800726AC(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_func_800191F8(temp_v0_2 & 0xFFFF);
    mp1_func_80067704(temp_v0);
    mp1_HuPrcSleep(9);
    temp_v0_3 = mp1_InitSprite(0x9006E);
    temp_v0_4 = mp1_func_80019060(temp_v0_3, 0, 1);
    temp_s0_2 = temp_v0_4 & 0xFFFF;
    mp1_SetBasicSpritePos(temp_s0_2, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0_2);
    mp1_func_80018D84(temp_s0_2, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(5);
    mp1_func_800726AC(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_func_800191F8(temp_v0_4 & 0xFFFF);
    mp1_func_80067704(temp_v0_3);
    mp1_HuPrcSleep(9);
    temp_s0_3 = mp1_func_80019060(mp1_InitSprite(0x9006F), 0, 1) & 0xFFFF;
    mp1_SetBasicSpritePos(temp_s0_3, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0_3);
    mp1_func_80018D84(temp_s0_3, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 9);

    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(5);
    mp1_D_800F5144 = 1;
    
    while (1) {
        mp1_HuPrcVSleep();
    }
}

//func_80102AD8_36DC78_BootLogos
void mp1_newBootLogo(void) {
    //we need to initialize rng in a better way than vanilla's static value
    //TODO: push current count before swapping game, seed against that
    mp1_rnd_seed = mp1_osGetCount() ^ 0xD826BC89;

    if (ForeignMinigameIndexToLoad == -1) {
        mp1_OriginalBootLogos();
    } else if (ForeignMinigameIndexToLoad == -2) {
        s32 i;
        //copy over player changes
        for (i = 0; i < 4; i++) {
            s32 coinsEarned = mp1_gPlayers[i].coins - mp3_PlayersCopy[i].coins;
            mp3_PlayersCopy[i].coins += coinsEarned;
            if (mp3_PlayersCopy[i].coins < 0) {
                mp3_PlayersCopy[i].coins = 0;
            }
            
            mp3_PlayersCopy[i].minigameCoinsTotal += coinsEarned;
            if (mp3_PlayersCopy[i].coins > mp3_PlayersCopy[i].coinsPeak) {
                mp3_PlayersCopy[i].coinsPeak = mp3_PlayersCopy[i].coins;
            }
        }
        
        ComboSwitchGameToMp3();
    } else {
        // mp2__SetFlag(0x19); //no idea what this does, might be important might not
        CopyMp3_gPlayerCopy_To_Mp1();
        mp1_omInitObjMan(16, 4);
        mp1_D_800ED5E3 = 1; //minigame explanations off
        mp1_D_800ED5DE = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
        ForeignMinigameIndexToLoad = -2;
        mp3_LoadBackFromMp2 = TRUE;
        mp1_omOvlCallEx(0x6F, 0, 0x84); //load explanation screen overlay (might be skipped depending on mp1_D_800ED5E3)
        while (1) {
            mp1_HuPrcVSleep();
        }
    }
}