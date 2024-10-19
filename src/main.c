#include "marioparty.h"

#define MAIN_DRAM 0x80000400
#define MAIN_OFF 0x400
#define MAIN_SIZE 0xBE940 //main segment size
#define MAIN_CART 0x0001000

#define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP2 0x0D57F0
#define FOREIGN_CART_MP2 0x2001000 //ROM start addr + 0x1000

// #define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP1 0xCDA50
#define FOREIGN_CART_MP1 0x4001000 //ROM start addr + 0x1000

void System_DisableInterrupts(void);
NORETURN void ComboGameSwitch2ToMp2(void);
void System_InvalDCache(void* addr, u32 size);
void System_InvalICache(void* addr, u32 size);
void comboDma_NoCacheInval(void* dramAddr, u32 cartAddr, u32 size);
void ComboGameSwitch4(u32);
void ComboGameSwitch2ToMp3(void);
NORETURN void ComboGameSwitch2ToMp1(void);
void mp3_DrawDebugText(s32 xPos, s32 yPos, char* str);
void func_80108910_119290(s32, s32, char*);
void mp3_SetSpriteCenter(s32, s32, s32);
void mp3_HuObjCreate(s32, s32, s32, s32, s32);

s32 printTimer = 0;

extern s16 D_800CD0AA;
extern s32 mp2_MinigameIndexToLoad;

s32 mp2_base = MP2_BASE;
s32 eepromLoadFailed = 0;

//also prevents wacky watches from being found from this point on if not 0
s32 wackyWatchUsedCopy = 0;


void cBootFunction(void) {
    //crash_screen_init();
}

extern mp3_PlayerData mp3_PlayersCopy[4];
extern mp2_PlayerData mp2_PlayersCopy[4];

mp2_PlayerData mp2_gPlayerBlank = {0};

typedef struct omOvlHisData { //Object Manager History Data
/* 0x00 */ s32 overlayID;
/* 0x04 */ s16 event;
/* 0x06 */ u16 stat;
} omOvlHisData; //sizeof 0x08

//these are hardcoded to avoid them being written when mp3 boots
extern omOvlHisData mp3_omovlhis_copy[12];
extern s16 mp3_omovlhisidx_copy;

extern omOvlHisData mp3_omovlhis[12];
extern s16 mp3_omovlhisidx;

#define BOARD_STATE_STRUCT_SIZE 0x80

extern u8 mp3_BoardState[BOARD_STATE_STRUCT_SIZE];
u8 mp3_BoardStateCopy[BOARD_STATE_STRUCT_SIZE] = {0};

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

//we only want to copy the necessary data so that the mp2 results screen is correct
void CopyMp3_gPlayerCopy_To_Mp2(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mp2_gPlayers[i].group = mp3_PlayersCopy[i].group;
        mp2_gPlayers[i].cpu_difficulty = mp3_PlayersCopy[i].cpu_difficulty;
        mp2_gPlayers[i].cpu_difficulty2 = mp3_PlayersCopy[i].cpu_difficulty;
        mp2_gPlayers[i].controller_port = mp3_PlayersCopy[i].controller_port;
        mp2_gPlayers[i].characterID = mp3_PlayersCopy[i].characterID;
        mp2_gPlayers[i].flags = mp3_PlayersCopy[i].flags1;
        mp2_gPlayers[i].coins = mp3_PlayersCopy[i].coins;
        mp2_gPlayers[i].extra_coins_collected_during_minigame = mp3_PlayersCopy[i].minigameCoinsWon;
        mp2_gPlayers[i].minigameCoinsWon = mp3_PlayersCopy[i].minigameCoins;
        mp2_gPlayers[i].stars = mp3_PlayersCopy[i].stars;
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

//start loading into Mp3
NORETURN void ComboSwitchGameToMp3(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp3(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboSwitchGame3ToMp3(void) {
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    comboDma_NoCacheInval((void*)MAIN_OFF, MAIN_CART, MAIN_SIZE);
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    ComboGameSwitch4(MAIN_DRAM);
    __builtin_unreachable();
}

//start loading into Mp2
NORETURN void ComboSwitchGameToMp2(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp2(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboSwitchGame3ToMp2(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP2, FOREIGN_SIZE_MP2);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
    __builtin_unreachable();
}

NORETURN void ComboSwitchGameToMp1(void) {
    //SaveMp3PlayerStructs();
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp1(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboSwitchGame3ToMp1(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP1, FOREIGN_SIZE_MP1);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
    __builtin_unreachable();
}

#define COLD_BOOT 0
#define WARM_BOOT 1
#define osAppNmiBufferSize 64

extern u8 osAppNmiBuffer[osAppNmiBufferSize];
void checkIfLoadingFromMp2Minigame(s32 overlayID, s16 event, s16 stat);
extern s32 mp3_LoadBackFromMp2;

void checkosAppNmiBufferReset(s32 resetType) {
    s32 i;

    if (resetType == COLD_BOOT) {
        for (i = 0; i < osAppNmiBufferSize; i++) {
            osAppNmiBuffer[i] = 0;
        }        
    }
}

extern s16 mp3_D_800CD2A2;

// omOvlHisData endgameScene[] = {
//     {0x7A, 0x0002, 0x0092},
//     {0x7A, 0x0002, 0x0092},
//     {0x77, 0x0000, 0x0091},
//     {0x47, 0x0001, 0x0192},
//     {0x71, 0x0000, 0x0012},
//     {0x02, 0x0000, 0x0014},
// };

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

extern s16 D_800D6B60;
extern omOvlHisData D_800D20F0[];

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

        if (curTurn > totalTurns) {
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
            mp3_omOvlCallEx(0x51, 2, 0x192); //hardcoded load chilly waters atm
            return;
        }

        PopMp3OvlHis();
        mp3_omOvlCallEx(0x48 + curBoardIndex, 2, 0x192); //hardcoded load chilly waters atm
        
        mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
    } else {
        mp3_omOvlCallEx(overlayID, event, stat);
    }
}

void SetInvalidEepromFound(void) {
    eepromLoadFailed = 1;
}

void InvalidEepCheck(s32 arg0, s32 arg1, char* arg2) {
    if (eepromLoadFailed == 1) {
        mp3_DrawDebugText(20, 20, "INVALID SAVE TYPE FOUND");
        mp3_DrawDebugText(20, 30, "PLEASE SET THE SAVE TYPE TO");
        mp3_DrawDebugText(20, 40, "EEPROM 16KBIT");
    } else {
        func_80108910_119290(arg0, arg1, arg2);
    }
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

extern s16 mp2_D_800CDA7C[];

void drawMessageOnBootLogos(void) {
    //if R is held on boot, load mp2
    if ((printTimer == 0) && mp2_D_800CDA7C[0] & 0x10) {
        mp2_MinigameIndexToLoad = -2;
        ComboSwitchGameToMp2();
        return;
    }
    if (printTimer < 150) {
        printTimer++;
        mp3_DrawDebugText(20, 210, "MOD BY: RAINCHUS");
        mp3_DrawDebugText(20, 220, "IF YOU WOULD LIKE TO SUPPORT MY WORK:");
        mp3_DrawDebugText(20, 230, "HTTPS://KO-FI.COM/RAINCHUS");
    }
}

typedef struct UnkCastleGroundMessage {
    s16 unk_00;
    char unk_02[2];
    s32 unk_04;
    char unk_06[4];
} UnkCastleGroundMessage;

void func_80019C00_1A800(s32);
void func_8005B43C_5C03C(s16, u32, s32, s32); //RefreshMsg
void func_8005D294_5DE94(s16);
u32 func_80106B38_4F9028(s32);
extern UnkCastleGroundMessage mp3_D_80110998[];
void mp3_HuPrcSleep(s32 frames);

extern omOvlHisData mp2_omovlhis[12];
extern s16 mp2_omovlhisidx;

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
        mp2_MinigameIndexToLoad = -2;
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
    func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, temp_v0, -1, -1);
}

void mp2BootOverlaySwapCheck(s32 overlayID, s16 event, s16 stat) {
    if (mp2_MinigameIndexToLoad == -2) {
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