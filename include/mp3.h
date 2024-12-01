#ifndef _MP3_H_
#define _MP3_H_

#include "ultra64.h"
#include "marioparty.h"

typedef struct mp3_GW_PLAYER {
/* 0x00 */ u8 group; //for which group you belong to in a minigame
/* 0x01 */ u8 cpu_difficulty;
/* 0x02 */ u8 controller_port;
/* 0x03 */ u8 characterID;
/* 0x04 */ u8 flags1; //value & 1 == Player is CPU
/* 0x05 */ char unk_05;
/* 0x06 */ s16 coins_mg_bonus; //extra coins collected in minigames
/* 0x08 */ s16 minigameCoins; //coins for winning current minigame
/* 0x0A */ s16 coins; //referenced as u16 and s16 (usually if u16 it's casted to s16)
/* 0x0C */ char unk_0C[2];
/* 0x0E */ s8 stars;
/* 0x0F */ u8 chainIndexCur;
/* 0x10 */ u8 spaceIndexCur;
/* 0x11 */ u8 chainIndexNext;
/* 0x12 */ u8 spaceIndexNext;
/* 0x13 */ u8 unk_13; //(Chain Index?)
/* 0x14 */ u8 unk_14; //(Space Index?)
/* 0x15 */ u8 chainIndexPrevious;
/* 0x16 */ u8 spaceIndexPrevious;
/* 0x17 */ u8 flags2;
/* 0x18 */ u8 items[3];
/* 0x1B */ u8 bowser_suit_flags;
/* 0x1C */ u8 turn_status; //space type landed on (blue, red, etc.)
/* 0x1D */ s8 playerIndex;
/* 0x1E */ char unk_1E[2]; //likely padding
/* 0x20 */ void* unk_20;
/* 0x24	*/ void* player_obj; //ptr to struct 0x48 in size (things like model position, rotation, etc.)
/* 0x24 */ s16 mg_star_coins; //used for mg star
/* 0x26 */ s16 coins_total; //used for coin star
/* 0x2C */ s8 happeningSpacesLandedOn;
/* 0x2D */ s8 redSpacesLandedOn;
/* 0x2E */ s8 blueSpacesLandedOn;
/* 0x2F */ s8 chanceSpacesLandedOn;
/* 0x30 */ s8 bowserSpacesLandedOn;
/* 0x31 */ s8 battleSpacesLandedOn;
/* 0x32 */ s8 itemSpacesLandedOn;
/* 0x33 */ s8 bankSpacesLandedOn;
/* 0x34 */ s8 gameGuySpacesLandedOn;
/* 0x35 */ char unk_35[3]; //likely padding
} mp3_GW_PLAYER; //sizeof 0x38
//P1 = 0x800D1108
//P2 = 0x800D1140
//P3 = 0x800D1178
//P4 = 0x800D11B0

typedef struct UnkCastleGroundMessage {
    s16 unk_00;
    char unk_02[2];
    s32 unk_04;
    char unk_06[4];
} UnkCastleGroundMessage;

enum TEXT_COLORS {
    TEXT_BLACK,
    TEXT_DEFAULT,
    TEXT_RED,
    TEXT_PURPLE,
    TEXT_GREEN,
    TEXT_BLUE,
    TEXT_YELLOW,
    TEXT_WHITE
};

//in regards to the minigame wheel -
//these values have 1 added to them in relation to the actual text color values
enum TEXT_COLORS_ADJUSTED {
    TEXT_ADJUST_BLACK = 0,
    TEXT_ADJUST_DEFAULT,
    TEXT_ADJUST_RED,
    TEXT_ADJUST_PURPLE,
    TEXT_ADJUST_GREEN,
    TEXT_ADJUST_BLUE,
    TEXT_ADJUST_YELLOW,
    TEXT_ADJUST_WHITE
};

extern mp3_GW_PLAYER mp3_gPlayers[4];
extern mp3_GW_PLAYER mp3_PlayersCopy[4];
extern omOvlHisData mp3_omovlhis_copy[12];
extern omOvlHisData mp2_omovlhis_copy[12];
extern s16 mp3_omovlhisidx_copy;
extern omOvlHisData mp3_omovlhis[12];
extern s16 mp3_omovlhisidx;
extern s32 CurBaseGame;
extern s16 mp3_D_800CD2A2;
extern UnkCastleGroundMessage mp3_D_80110998[];
extern s32 mp3_D_800B1A30;
extern s16 mp3_D_800CDA7C[];
extern u32 mp3_debug_font_color;
extern u8 mp3_BoardState[BOARD_STATE_STRUCT_SIZE];
extern OSMesgQueue mp3_D_800CE1A0;
extern u8 customEepromData[0x140];
extern s32 ForeignMinigameIndexToLoad;
extern s16 mp3_BattleMinigameCoins;
extern s16 mp3_D_800D530C;
extern u8 mp3_prevMinigamesPlayed[PREV_MINIGAMES_PLAYED_SIZE];

void mp3_func_8000BBD4_C7D4(s32, s32, s32);
void mp3_DrawDebugText(s32 xPos, s32 yPos, char* str);
void mp3_SetSpriteCenter(s32, s32, s32);
void mp3_HuObjCreate(s32, s32, s32, s32, s32);
void mp3_HuPrcSleep(s32 frames);
void mp3_HuPrcVSleep(void);
void mp3_HuWipeFadeIn(s32, s32);
void mp3_HuPrcExit(void);
s32 mp3_osEepromProbe(OSMesgQueue *);
s32 mp3_osEepromRead(OSMesgQueue *, u8, u8 *);
s32 mp3_osEepromWrite(OSMesgQueue *, u8, u8 *);
s32 mp3_osEepromLongRead(OSMesgQueue *, u8, u8 *, int);
s32 mp3_osEepromLongWrite(OSMesgQueue *, u8, u8 *, int);
s32 mp3_omOvlCallEx(s32 overlayID, s16 event, s16 stat);
void mp3_func_80019C00_1A800(s32);
void mp3_func_8005B43C_5C03C(s16, char*, s32, s32); //RefreshMsg
void mp3_func_8000BB54_C754(s32);
void mp3_func_8000BCC8_C8C8(s32, s32);
s32 mp3_HuWipeStatGet(void);
void mp3_func_8000C184_CD84(s32);
void mp3_func_80055670_56270(s16);
void mp3_RequestSIFunction(char (*)[16], void*, void*, s32);

#endif
