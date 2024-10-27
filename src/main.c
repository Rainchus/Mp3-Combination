#include "marioparty.h"

#define BOARD_STATE_STRUCT_SIZE 0x80
#define COLD_BOOT 0
#define WARM_BOOT 1
#define osAppNmiBufferSize 64
#define N64_LOGO 0x00110000
#define NINTENO_LOGO 0x00110001
#define HUDSON_LOGO 0x00110002
#define CUSTOM_LOGO 0x00110013

s32 initialBoot = 0;

//in the eeprom, 0x2C0 through 0x400 is free to use

typedef struct omOvlHisData { //Object Manager History Data
/* 0x00 */ s32 overlayID;
/* 0x04 */ s16 event;
/* 0x06 */ u16 stat;
} omOvlHisData; //sizeof 0x08

typedef struct UnkCastleGroundMessage {
    s16 unk_00;
    char unk_02[2];
    s32 unk_04;
    char unk_06[4];
} UnkCastleGroundMessage;

void mp3_DrawDebugText(s32 xPos, s32 yPos, char* str);
void func_80108910_119290(s32, s32, char*);
void mp3_SetSpriteCenter(s32, s32, s32);
void mp3_HuObjCreate(s32, s32, s32, s32, s32);
void checkIfLoadingFromMp2Minigame(s32 overlayID, s16 event, s16 stat);
NORETURN void ComboSwitchGameToMp2(void);
void func_80019C00_1A800(s32);
void func_8005B43C_5C03C(s16, char*, s32, s32); //RefreshMsg
void func_8005D294_5DE94(s16);
u32 func_80106B38_4F9028(s32);
void mp3_HuPrcSleep(s32 frames);
void mp3_HuPrcVSleep(void);
void mp3_HuWipeFadeIn(s32, s32);
void HuWipeFadeOut(s32, s32);
s32 HuWipeStatGet(void);
s32 InitEspriteSlot(s16, s32, s32);
u16 func_8000B838_C438(s32);
void func_8000BB54_C754(s32);
void func_8000BBD4_C7D4(s32, s32, s32);
void func_8000BCC8_C8C8(s32, s32);
void func_8000C184_CD84(s32);
void func_80055670_56270(s16);
void ComboSwitchGameToMp1(void);
void mp3_HuPrcExit(void);

s32 printTimer = 0;
s32 eepromLoadFailed = 0;
//also prevents wacky watches from being found from this point on if not 0
s32 wackyWatchUsedCopy = 0;

extern s16 D_800CD0AA;
extern s32 ForeignMinigameIndexToLoad;
extern mp3_PlayerData mp3_PlayersCopy[4];
extern mp2_GW_PLAYER mp2_PlayersCopy[4];
extern omOvlHisData mp3_omovlhis_copy[12];
extern s16 mp3_omovlhisidx_copy;
extern omOvlHisData mp3_omovlhis[12];
extern s16 mp3_omovlhisidx;
extern u8 osAppNmiBuffer[osAppNmiBufferSize];
extern s32 mp3_LoadBackFromMp2;
extern s16 mp3_D_800CD2A2;
extern UnkCastleGroundMessage mp3_D_80110998[];
extern omOvlHisData mp2_omovlhis[12];
extern s16 mp2_omovlhisidx;
extern s16 D_800D530C;
extern s8 D_800B23B0;
extern s32 mp3_D_800B1A30;
extern s16 D_800D6B60;
extern omOvlHisData D_800D20F0[];
extern s16 mp3_D_800CDA7C[];

//mp3 board state and copy (BOARD_STATE_STRUCT_SIZE isn't known what exact size we need)
extern u8 mp3_BoardState[BOARD_STATE_STRUCT_SIZE];
u8 mp3_BoardStateCopy[BOARD_STATE_STRUCT_SIZE] = {0};

void cBootFunction(void) {
    //crash_screen_init();
}

void PushMp3OvlHis(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        mp3_omovlhis_copy[i] = mp3_omovlhis[i];
    }
    mp3_omovlhisidx_copy = mp3_omovlhisidx;
}

void PushMp3BoardState(void) {
    s32 i;

    for (i = 0; i < BOARD_STATE_STRUCT_SIZE; i++) {
        mp3_BoardStateCopy[i] = mp3_BoardState[i];
    }
}

void PopMp3BoardState(void) {
    s32 i;

    for (i = 0; i < BOARD_STATE_STRUCT_SIZE; i++) {
        mp3_BoardState[i] = mp3_BoardStateCopy[i];
    }
}

void PopMp3OvlHis(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        mp3_omovlhis[i] = mp3_omovlhis_copy[i];
    }
    mp3_omovlhisidx = mp3_omovlhisidx_copy;
}

//we only want to copy the necessary data so that the mp2 results screen is correct,
//and the human/cpu flags and characters are copied over
void CopyMp3_gPlayerCopy_To_Mp2(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mp2_gPlayers[i].group = mp3_PlayersCopy[i].group;
        mp2_gPlayers[i].cpu_difficulty = mp3_PlayersCopy[i].cpu_difficulty;
        mp2_gPlayers[i].cpu_difficulty2 = mp3_PlayersCopy[i].cpu_difficulty;
        mp2_gPlayers[i].port = mp3_PlayersCopy[i].controller_port;
        mp2_gPlayers[i].character = mp3_PlayersCopy[i].characterID;
        mp2_gPlayers[i].flags = mp3_PlayersCopy[i].flags1;
        mp2_gPlayers[i].coins = mp3_PlayersCopy[i].coins;
        mp2_gPlayers[i].stars = mp3_PlayersCopy[i].stars;
    }
}

void CopyMp3_gPlayerCopy_To_Mp1(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mp1_gPlayers[i].group = mp3_PlayersCopy[i].group;
        mp1_gPlayers[i].cpu_difficulty = mp3_PlayersCopy[i].cpu_difficulty;
        mp1_gPlayers[i].cpu_difficulty_copy = mp3_PlayersCopy[i].cpu_difficulty;
        mp1_gPlayers[i].port = mp3_PlayersCopy[i].controller_port;
        mp1_gPlayers[i].character = mp3_PlayersCopy[i].characterID;
        mp1_gPlayers[i].flags = mp3_PlayersCopy[i].flags1;
        mp1_gPlayers[i].coins = mp3_PlayersCopy[i].coins;
        mp1_gPlayers[i].stars = mp3_PlayersCopy[i].stars;
    }
}

void SaveMp2PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp2_PlayersCopy[i] = mp2_gPlayers[i];
    }
}

void SaveMp3PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp3_PlayersCopy[i] = mp3_gPlayers[i];
    }
    wackyWatchUsedCopy = D_800CD0AA;
}

void LoadMp3PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp3_gPlayers[i] = mp3_PlayersCopy[i];
    }
}

void checkosAppNmiBufferReset(s32 resetType) {
    s32 i;

    if (resetType == COLD_BOOT) {
        for (i = 0; i < osAppNmiBufferSize; i++) {
            osAppNmiBuffer[i] = 0;
        }        
    }
}

omOvlHisData last5Turns[] = {
    {0x7A, 0x0002, 0x0092},
    {0x7A, 0x0002, 0x0092},
    {0x77, 0x0000, 0x0091},
    {0x47, 0x0001, 0x0192},
    {0x71, 0x0000, 0x0012},
    {0x01, 0x0000, 0x0014},
};

s32 D_80101B40_115760_Copy[] = {
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x48
};

void func_800F8610_10C230_Copy(s32 arg0, s16 arg1, s16 arg2, s32 curBoardIndex) {
    omOvlHisData* temp_v1;

    temp_v1 = &D_800D20F0[D_800D6B60++];
    if (arg0 != -2) {
        if (arg0 == -1) {
            arg0 = mp3_omovlhis[mp3_omovlhisidx].overlayID;
            temp_v1->overlayID = arg0;
        } else {
            temp_v1->overlayID = arg0;
        }
    } else {
        arg0 = D_80101B40_115760_Copy[curBoardIndex];
        temp_v1->overlayID = arg0;
    }
    temp_v1->event = arg1;
    temp_v1->stat = arg2;
    if (D_800D6B60 >= 5) {
        D_800D6B60 = 4;
    }
}

void checkIfLoadingFromMp2Minigame(s32 overlayID, s16 event, s16 stat) {
    s8 curTurn;
    s8 totalTurns;
    s8 curBoardIndex;
    
    if (eepromLoadFailed == 1) {
        mp3_omOvlCallEx(0, 0, 0);
        return;
    }

    if (mp3_LoadBackFromMp2 == TRUE) {
        mp3_LoadBackFromMp2 = FALSE;
        PopMp3BoardState();
        LoadMp3PlayerStructs();

        
        if (wackyWatchUsedCopy == 3) {
            //set turns as if wacky watch was used
            mp3_BoardState[3] = mp3_BoardState[2] - 4;
        }

        D_800CD0AA = wackyWatchUsedCopy;

        curTurn = mp3_BoardState[3];
        totalTurns = mp3_BoardState[2];
        curBoardIndex = mp3_BoardState[1];

        mp3_D_800B1A30 = 1; //set that there is at least 1 controller active
        D_800B23B0 = 1; //is party mode
        if (curTurn > totalTurns) {
            PopMp3OvlHis();
            mp3_omovlhisidx--;
            mp3_omOvlCallEx(0x4F, 0, 0x4190); //go to end of game scene
            return;
        } else if ((totalTurns - curTurn) == 4) {
            //there's probably a better way to do this over hardcoding the ovl history
            //set last 5 turns event
            // PopMp3OvlHis();
            s32 i;
            for (i = 0; i < ARRAY_COUNT(last5Turns); i++) {
                mp3_omovlhis[i] = last5Turns[i];
            }
            mp3_omovlhisidx = 3;
            mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
            // func_800F8610_10C230_Copy(0x48, 2, 0x192, curBoardIndex);
            mp3_omOvlCallEx(0x51, 2, 0x192); //last 5 turns
            return;
        }

        PopMp3OvlHis();
        mp3_omovlhisidx--;
        mp3_omOvlCallEx(0x48 + curBoardIndex, 2, 0x192); //load back into board
        
        mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
    } else {
        mp3_omOvlCallEx(overlayID, event, stat);
    }
}

void SetInvalidEepromFound(void) {
    eepromLoadFailed = 1;
}

void InvalidEep2(s32 arg0, s32 arg1, s32 arg2) {
    if (eepromLoadFailed == 1) {
        arg1 = 0x01BC; //draw coin off screen
    }
    mp3_SetSpriteCenter(arg0, arg1, arg2);
}

void InvalidEep3(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (eepromLoadFailed == 0) {
        mp3_HuObjCreate(arg0, arg1, arg2, arg3, arg4);
    }
}

void drawMessageOnBootLogos(void) {
    //TODO: this should only be possible on initial boot, or players might accidentally enter these menus
    //if R is held on boot, load mp2
    if ((printTimer == 0) && mp3_D_800CDA7C[0] & 0x10) {
        ForeignMinigameIndexToLoad = -1;
        ComboSwitchGameToMp2();
        return;
    }
    // if L is held on boot, load mp1
    if ((printTimer == 0) && mp3_D_800CDA7C[0] & 0x20) {
        ForeignMinigameIndexToLoad = -1;
        ComboSwitchGameToMp1();
        return;
    }
    // if Z is held on boot, load minigame selection screen
    if ((printTimer == 0) && mp3_D_800CDA7C[0] & 0x2000) {
        ForeignMinigameIndexToLoad = -1;
        mp3_omOvlCallEx(0, 0, 0);
        return;
    }
    if (printTimer < 90) {
        printTimer++;
        // mp3_DrawDebugText(20, 210, "MOD BY: RAINCHUS");
        // mp3_DrawDebugText(20, 220, "IF YOU WOULD LIKE TO SUPPORT MY WORK:");
        // mp3_DrawDebugText(20, 230, "HTTPS://KO-FI.COM/RAINCHUS");
    }
}

void func_80107730_4F9C20_Copy(s32 arg0, s32 messageID) {
    //i wanted to make this a choice textbox, but that's tricky
    //for now, it will say loading mario party 2 and then sleep for 1 second and load

    char newMessage[] = {"\x0B""Loading Mario Party 2""\xFF"};
    //char newMessage[] = {"\x0B""Huh""\xC3"" Do you want to swap to Mario Party 2""\xC3""\xFF"};
    //char newMessage[] = {"\x0B""Huh" "\xC3" " Do you want to swap to\nMario Party 2" "\xC3" "\x0C Yes\x0D   \x0C No\x0D"};
    u32 temp_v0; //pointer to message

    //Huh? My suggestion? textbox
    if (messageID == 0x3125) {
        func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, newMessage, -1, -1);
        ForeignMinigameIndexToLoad = -1;
        mp3_HuPrcSleep(30);
        ComboSwitchGameToMp2();
        return;
    }

    func_8005D294_5DE94(mp3_D_80110998[arg0].unk_00);

    if (mp3_D_80110998[arg0].unk_04 != 0) {
        func_80019C00_1A800(mp3_D_80110998[arg0].unk_04);
        mp3_D_80110998[arg0].unk_04 = 0;
    }

    temp_v0 = func_80106B38_4F9028(messageID);

    //pointer check
    if (temp_v0 > 0x80000000U) {
        mp3_D_80110998[arg0].unk_04 = temp_v0;
    }

    func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, (char*)temp_v0, -1, -1);
}

void mp2BootOverlaySwapCheck(s32 overlayID, s16 event, s16 stat) {
    if (ForeignMinigameIndexToLoad == -2) {
        s32 i;
        //load directly into title screen
        omOvlHisData titleScreen[] = {
            {0x62, 0x0000, 0x192},
            {0x62, 0x0001, 0x193}
        };

        for (i = 0; i < ARRAY_COUNT(titleScreen); i++) {
            mp2_omovlhis[i] = titleScreen[i];
        }

        mp2_omovlhisidx = 1;
        mp2_omOvlCallEx(0x5B, 0, 0x1081); //load mode select
    } else { //otherwise, load debug overlay
        mp2_omOvlCallEx(0, event, stat);
    }
}

void mp3_newBootLogos(void) {
    s16 temp_v0;
    s16 temp_v0_copy;
    s16 temp_v0_3;
    s32 temp_s0;
    s32 temp_s0_copy;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0_2;
    s32 temp_v0_2_copy;
    s32 temp_v0_4;

    // temp_v0 = func_8000B838_C438(N64_LOGO);
    // temp_v0_2 = InitEspriteSlot(temp_v0, 0, 1);
    // temp_s0 = temp_v0_2 & 0xFFFF;
    // func_8000BBD4_C7D4(temp_s0, 0xA0, 0x78);
    // func_8000BB54_C754(temp_s0);
    // func_8000BCC8_C8C8(temp_s0, 0xFFFF);

    if (initialBoot == 0) {
        initialBoot = 1;
        temp_v0 = func_8000B838_C438(CUSTOM_LOGO);
        temp_v0_2 = InitEspriteSlot(temp_v0, 0, 1);
        temp_s0 = temp_v0_2 & 0xFFFF;
        func_8000BBD4_C7D4(temp_s0, 210, 0x78);
        func_8000BB54_C754(temp_s0);
        func_8000BCC8_C8C8(temp_s0, 0xFFFF);

        mp3_HuWipeFadeIn(0xB, 0x1E);
        while (HuWipeStatGet() != 0) {
            mp3_HuPrcVSleep();
        }

        //check for button inputs
        while (1) {
            if (mp3_D_800CDA7C[0] & 0x10) { //if R is pressed, load mario party 2
                HuWipeFadeOut(0xB, 9);

                while (HuWipeStatGet() != 0) {
                    mp3_HuPrcVSleep();
                }
                ComboSwitchGameToMp2();
            }
            #ifdef MP1
            else if (mp3_D_800CDA7C[0] & 0x20) { //if L is pressed, load mario party 1
                HuWipeFadeOut(0xB, 9);

                while (HuWipeStatGet() != 0) {
                    mp3_HuPrcVSleep();
                }
                ComboSwitchGameToMp1();
            }
            #endif
            else if (mp3_D_800CDA7C[0] & 0x2000) { //if Z is pressed, load minigame selection
                ForeignMinigameIndexToLoad = -1;
                HuWipeFadeOut(0xB, 9);

                while (HuWipeStatGet() != 0) {
                    mp3_HuPrcVSleep();
                }
                mp3_omOvlCallEx(0, 0, 0);
                mp3_HuPrcExit();
            } else if (mp3_D_800CDA7C[0] & 0x8000) { //if A is pressed, load mario party 3
                break;
            }
            mp3_HuPrcVSleep();
        }
        HuWipeFadeOut(0xB, 9);

        while (HuWipeStatGet() != 0) {
            mp3_HuPrcVSleep();
        }
    }


    temp_v0_copy = func_8000B838_C438(N64_LOGO);
    temp_v0_2_copy = InitEspriteSlot(temp_v0_copy, 0, 1);
    temp_s0_copy = temp_v0_2_copy & 0xFFFF;
    func_8000BBD4_C7D4(temp_s0_copy, 0xA0, 0x78);
    func_8000BB54_C754(temp_s0_copy);
    func_8000BCC8_C8C8(temp_s0_copy, 0xFFFF);

    mp3_HuWipeFadeIn(0xB, 0x1E);
    while (HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    HuWipeFadeOut(0xB, 9);

    while (HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    temp_v0_3 = func_8000B838_C438(NINTENO_LOGO);
    temp_v0_4 = InitEspriteSlot(temp_v0_3, 0, 1);
    temp_s0_2 = temp_v0_4 & 0xFFFF;
    func_8000BBD4_C7D4(temp_s0_2, 0xA0, 0x78);
    func_8000BB54_C754(temp_s0_2);
    func_8000BCC8_C8C8(temp_s0_2, 0xFFFF);
    mp3_HuWipeFadeIn(0xB, 9);

    while (HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    HuWipeFadeOut(0xB, 9);

    while (HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    func_8000C184_CD84(temp_v0_4 & 0xFFFF);
    func_80055670_56270(temp_v0_3);
    mp3_HuPrcSleep(9);
    temp_s0_3 = InitEspriteSlot(func_8000B838_C438(HUDSON_LOGO), 0, 1) & 0xFFFF;
    func_8000BBD4_C7D4(temp_s0_3, 0xA0, 0x78);
    func_8000BB54_C754(temp_s0_3);
    func_8000BCC8_C8C8(temp_s0_3, 0xFFFF);
    mp3_HuWipeFadeIn(0xB, 9);

    while (HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    D_800D530C = 1;

    while (1) {
        mp3_HuPrcVSleep();
    }
}

