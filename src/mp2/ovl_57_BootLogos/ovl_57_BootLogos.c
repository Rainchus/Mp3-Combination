#include "marioparty.h"
#include "mp3.h"
#include "mp2.h"

#define N64_LOGO 0x00090000
#define NINTENO_LOGO 0x00090001
#define HUDSON_LOGO 0x00090002

typedef struct UnkBoardStatus {
    char unk0[2];
    s16 unk_02;
    char unk4[0x1A];
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
} UnkBoardStatus; //sizeof 0x28

extern u16 mp2_D_801011FC_101DFC;
extern s32 ForeignMinigameIndexToLoad;
extern UnkBoardStatus mp2_D_800F93A8;
extern s8 mp2_D_800F93CD_F9FCD;
extern s32 mp3_LoadBackFromMp2;
extern u8 mp3_BoardStateCopy[BOARD_STATE_STRUCT_SIZE];

s16 mp2_func_8001A2F8_1AEF8(s32);
u16 mp2_func_8001AAAC_1B6AC(s16, s16, u16);
void mp2_espPosSet(u16, s16, s16);
void mp2_espDispOn(u16);
void mp2_func_8001A788_1B388(u16, u16);
void mp2_InitFadeIn(s32, s32);
s32 mp2_func_8008F618_90218(void);
void mp2_HuPrcVSleep(void);
void mp2_HuPrcSleep(s32);
void mp2_InitFadeOut(s32, s32);
void mp2_func_8001AC44_1B844(u16);
void mp2_SprAnimKill(s16);
void mp2__SetFlag(s32 input);
void CopyMp3_gPlayerCopy_To_Mp2(void);
void mp2_omInitObjMan(s32, s32);
void mp2_func_80026D28_27928(s32);
void mp2_func_80026DAC_279AC(s32, s32, s32, s32);
void mp2_func_80026E00_27A00(s32, f32, f32, f32);
NORETURN void ComboSwitchGameToMp3(void);
extern u32 mp2_rnd_seed;
extern u16 mp2_BattleMinigameCoins;
extern u16 mp3_BattleMinigameCoins;
extern u16 mp3_BattleMinigameCoins_Copy;
extern u8 newBattleMinigameListNormalMp3[];
s32 isBattleMinigame = 0;

void mp2_OriginalBootLogos(void) {
    s16 temp_v0;
    u16 temp_s0;

    temp_v0 = mp2_func_8001A2F8_1AEF8(N64_LOGO);
    temp_s0 = mp2_func_8001AAAC_1B6AC(temp_v0, 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, 0xFFFF);
    mp2_InitFadeIn(0, 30);

    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }

    mp2_HuPrcSleep(5);
    mp2_InitFadeOut(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_func_8001AC44_1B844(temp_s0);
    mp2_SprAnimKill(temp_v0);
    mp2_HuPrcSleep(9);
    temp_v0 = mp2_func_8001A2F8_1AEF8(NINTENO_LOGO);
    temp_s0 = mp2_func_8001AAAC_1B6AC(temp_v0, 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, -1);
    mp2_InitFadeIn(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }

    mp2_HuPrcSleep(5);
    mp2_InitFadeOut(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_func_8001AC44_1B844(temp_s0);
    mp2_SprAnimKill(temp_v0);
    mp2_HuPrcSleep(9);
    temp_s0 = mp2_func_8001AAAC_1B6AC(mp2_func_8001A2F8_1AEF8(HUDSON_LOGO), 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, -1);
    mp2_InitFadeIn(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_HuPrcSleep(5);
    mp2_D_801011FC_101DFC = 1;

    while (1) {
        mp2_HuPrcVSleep();
    }
}

//func_80102AD8_36DC78_BootLogos
void mp2_newBootLogo(void) {
    //we need to initialize rng in a better way than vanilla's static value
    //TODO: push current count before swapping game, seed against that
    mp2_rnd_seed = mp2_osGetCount() ^ 0xD826BC89;

    if (ForeignMinigameIndexToLoad == -1) {
        mp2_OriginalBootLogos();
    } else if (ForeignMinigameIndexToLoad == -2) {
        s32 i;
        //copy over player changes
        for (i = 0; i < 4; i++) {
            s32 coinsEarned = mp2_gPlayers[i].coins - mp3_PlayersCopy[i].coins;
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
        mp2__SetFlag(0x19); //no idea what this does, might be important might not
        CopyMp3_gPlayerCopy_To_Mp2();
        mp2_omInitObjMan(16, 4);
        //i dont believe this is needed
        // mp2_func_80026D28_27928(1);
        // mp2_func_80026DAC_279AC(0, 0x80, 0x80, 0x80);
        // mp2_func_80026DAC_279AC(1, 0x60, 0x60, 0x10);
        // mp2_func_80026E00_27A00(1, 100.0f, -100.0f, 100.0f);
        //otherwise, load into minigame from boot
        mp2_D_800F93CD_F9FCD = mp3_BoardStateCopy[0x13]; //minigame explanations on/off depending on mp3 settings
        mp2_D_800F93A8.unk_20 = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
        mp2_D_800F93A8.unk_22 = 0x55;
        // isBattleMinigame = 0;
        // s32 i;
        // for (i = 0; newBattleMinigameListNormalMp3[i] != 0xFF; i++) {
        //     if (ForeignMinigameIndexToLoad == newBattleMinigameListNormalMp3[i]) {
        //         mp2_BattleMinigameCoins = mp3_BattleMinigameCoins_Copy;
        //         isBattleMinigame = 1;
        //         break;
        //     }
        // }

        ForeignMinigameIndexToLoad = -2;
        mp3_LoadBackFromMp2 = MP2_FOREIGN_MINIGAME;
        
        mp2_omOvlCallEx(func_8003F6F0_402F0(mp2_D_800F93A8.unk_20), 0, 0x84);
        while (1) {
            mp2_HuPrcVSleep();
        }
    }
}