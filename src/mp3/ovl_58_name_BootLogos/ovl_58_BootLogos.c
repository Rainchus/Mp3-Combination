#include "marioparty.h"
#include "mp3.h"
#include "mp2.h"
#include "mp1.h"

#define N64_LOGO 0x00110000
#define NINTENO_LOGO 0x00110001
#define HUDSON_LOGO 0x00110002
#define CUSTOM_LOGO 0x00110013

void mp3_HuWipeFadeOut(s32, s32);
void CopyMp2_gPlayerCopy_To_Mp3(void);
void CopyMp1_gPlayerCopy_To_Mp3(void);
void mp3_omInitObjMan(s32, s32);
void mp3_PlaySound(s16);

extern s32 shouldShowKofiText;
s32 shouldShowCustomSplashScreen = 0;

void NewInitialSplashScreen(void) {
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_s0;

    temp_v0 = func_8000B838_C438(CUSTOM_LOGO);
    temp_v0_2 = InitEspriteSlot(temp_v0, 0, 1);
    temp_s0 = temp_v0_2 & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0, 210, 0x78);
    mp3_func_8000BB54_C754(temp_s0);
    mp3_func_8000BCC8_C8C8(temp_s0, 0xFFFF);

    mp3_HuWipeFadeIn(0xB, 15);
    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    //check for button inputs
    while (1) {
        if (mp3_D_800CDA7C[0] == -1) {
            mp3_HuPrcVSleep();
            continue;
        }
        if (mp3_D_800CDA7C[0] & 0x10) { //if R is pressed, load mario party 2
            mp3_osResetType = 1;
            CurBaseGame = MP2_BASE;
            mp3_PlaySound(2);
            mp3_HuWipeFadeOut(0xB, 12);

            while (mp3_HuWipeStatGet() != 0) {
                mp3_HuPrcVSleep();
            }
            ComboSwitchGameToMp2();
        }
        #ifdef MP1
        else if (mp3_D_800CDA7C[0] & 0x20) { //if L is pressed, load mario party 1
            mp3_osResetType = 1;
            CurBaseGame = MP1_BASE;
            mp3_PlaySound(2);
            mp3_HuWipeFadeOut(0xB, 12);

            while (mp3_HuWipeStatGet() != 0) {
                mp3_HuPrcVSleep();
            }
            ComboSwitchGameToMp1();
        }
        #endif
        else if (mp3_D_800CDA7C[0] & 0x2000) { //if Z is pressed, load minigame selection
            mp3_osResetType = 1;
            ForeignMinigameIndexToLoad = -1;
            shouldShowCustomSplashScreen = 0;
            mp3_PlaySound(2);
            mp3_HuWipeFadeOut(0xB, 12);

            while (mp3_HuWipeStatGet() != 0) {
                mp3_HuPrcVSleep();
            }
            mp3_omOvlCallEx(0, 0, 0);
            mp3_HuPrcExit();
        } else if (mp3_D_800CDA7C[0] & 0x8000) { //if A is pressed, load mario party 3
            mp3_osResetType = 1;
            shouldShowCustomSplashScreen = 1;
            CurBaseGame = MP3_BASE;
            mp3_PlaySound(2);
            mp3_HuWipeFadeOut(0xB, 12);
            break;
        }
        mp3_HuPrcVSleep();
    }

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }
    
}

void mp3_OriginalBootLogos(void) {
    s16 temp_v0_copy;
    s16 temp_v0_3;
    s32 temp_s0_copy;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0_2_copy;
    s32 temp_v0_4;

    shouldShowKofiText = 1;

    temp_v0_copy = func_8000B838_C438(N64_LOGO);
    temp_v0_2_copy = InitEspriteSlot(temp_v0_copy, 0, 1);
    temp_s0_copy = temp_v0_2_copy & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0_copy, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_copy);
    mp3_func_8000BCC8_C8C8(temp_s0_copy, 0xFFFF);

    mp3_HuWipeFadeIn(0xB, 5);
    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    mp3_HuWipeFadeOut(0xB, 5);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    temp_v0_3 = func_8000B838_C438(NINTENO_LOGO);
    temp_v0_4 = InitEspriteSlot(temp_v0_3, 0, 1);
    temp_s0_2 = temp_v0_4 & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0_2, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_2);
    mp3_func_8000BCC8_C8C8(temp_s0_2, 0xFFFF);
    mp3_HuWipeFadeIn(0xB, 5);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    mp3_HuWipeFadeOut(0xB, 5);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_func_8000C184_CD84(temp_v0_4 & 0xFFFF);
    mp3_func_80055670_56270(temp_v0_3);
    mp3_HuPrcSleep(5);
    temp_s0_3 = InitEspriteSlot(func_8000B838_C438(HUDSON_LOGO), 0, 1) & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0_3, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_3);
    mp3_func_8000BCC8_C8C8(temp_s0_3, 0xFFFF);
    mp3_HuWipeFadeIn(0xB, 5);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    mp3_D_800D530C = 1;

    while (1) {
        mp3_HuPrcVSleep();
    }
}

//80047160,code,InitObjSys

//func_80105C80_3D7430
void mp3_newBootLogos(void) {
    if (shouldShowCustomSplashScreen == 0) {
        shouldShowCustomSplashScreen = 1;
        NewInitialSplashScreen();
        return;
    }

    if (ForeignMinigameAlreadyLoaded == TRUE) {
        if (CurBaseGame == MP3_BASE) {
            //TODO: load back into mp3 board
            
        } else if (CurBaseGame == MP2_BASE) {
            s32 i;
            //copy over player changes
            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp3_gPlayers[i].coins - mp2_PlayersCopy[i].coins;
                mp2_PlayersCopy[i].coins += coinsEarned;
                // if (mp2_PlayersCopy[i].coins < 0) {
                //     mp2_PlayersCopy[i].coins = 0;
                // }
                
                mp2_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp2_PlayersCopy[i].coins > mp2_PlayersCopy[i].coins_total) {
                    mp2_PlayersCopy[i].coins_total = mp2_PlayersCopy[i].coins;
                }
            }
            
            ComboSwitchGameToMp2();
        } else if (CurBaseGame == MP1_BASE) {
            s32 i;
            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp3_gPlayers[i].coins - mp1_PlayersCopy[i].coins;
                mp1_PlayersCopy[i].coins += coinsEarned;
                // if (mp1_PlayersCopy[i].coins < 0) {
                //     mp1_PlayersCopy[i].coins = 0;
                // }
                
                mp1_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp1_PlayersCopy[i].coins > mp1_PlayersCopy[i].coins_total) {
                    mp1_PlayersCopy[i].coins_total = mp1_PlayersCopy[i].coins;
                }
            }
            
            ComboSwitchGameToMp1();
            return;
        }
    }

    if (CurBaseGame == MP3_BASE) {
        mp3_OriginalBootLogos();
    } else if (CurBaseGame == MP2_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp2_gPlayerCopy_To_Mp3();
        mp3_BoardState[0x13] = mp2_BoardStateCopy.minigameExplanations; //minigame explanations on/off
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp1_gPlayerCopy_To_Mp3();
        //TODO: fill in mp1
        //mp3_BoardState[0x13] = mp2_BoardStateCopy.minigameExplanations; //minigame explanations on/off
    }

    mp3_omInitObjMan(16, 4);
    ForeignMinigameAlreadyLoaded = TRUE;
    mp3_BoardState[0x10] = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    mp3_omOvlCallEx(0x70, 0, 0x192);

    while (1) {
        mp3_HuPrcVSleep();
    }
}