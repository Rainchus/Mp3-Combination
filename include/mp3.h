#ifndef _MP3_H_
#define _MP3_H_

#include "ultra64.h"
#include "marioparty.h"
#include "mp3/game/object.h"

enum ITEMS {
    ITEM_NONE = -1,
    ITEM_MUSHROOM = 0,
    ITEM_SKELETON_KEY = 1,
    ITEM_POISON_MUSHROOM = 2,
    ITEM_REVERSE_MUSHROOM = 3,
    ITEM_CELLULAR_SHOPPER = 4,
    ITEM_WARP_BLOCK = 5,
    ITEM_PLUNDER_CHEST = 6,
    ITEM_BOWSER_PHONE = 7,
    ITEM_DUEL_GLOVE = 8,
    ITEM_LUCKY_LAMP = 9,
    ITEM_GOLDEN_MUSHROOM = 10,
    ITEM_BOO_BELL = 11,
    ITEM_BOO_REPELLENT = 12,
    ITEM_BOWSER_SUIT = 13,
    ITEM_MAGIC_LAMP = 14,
    ITEM_KOOPA_KARD = 15,
    ITEM_BARTER_BOX = 16,
    ITEM_LUCKY_CHARM = 17,
    ITEM_WACKY_WATCH = 18,
    ITEMS_END
};

//original struct
// typedef struct mp3_GW_PLAYER {
// /* 0x00 */ u8 group; //for which group you belong to in a minigame
// /* 0x01 */ u8 cpu_difficulty;
// /* 0x02 */ u8 controller_port;
// /* 0x03 */ u8 characterID;
// /* 0x04 */ u8 flags1; //value & 1 == Player is CPU
// /* 0x05 */ char unk_05;
// /* 0x06 */ s16 coins_mg_bonus; //extra coins collected in minigames
// /* 0x08 */ s16 minigameCoins; //coins for winning current minigame
// /* 0x0A */ s16 coins; //referenced as u16 and s16 (usually if u16 it's casted to s16)
// /* 0x0C */ char unk_0C[2];
// /* 0x0E */ s8 stars;
// /* 0x0F */ u8 chainIndexCur;
// /* 0x10 */ u8 spaceIndexCur;
// /* 0x11 */ u8 chainIndexNext;
// /* 0x12 */ u8 spaceIndexNext;
// /* 0x13 */ u8 unk_13; //(Chain Index?)
// /* 0x14 */ u8 unk_14; //(Space Index?)
// /* 0x15 */ u8 chainIndexPrevious;
// /* 0x16 */ u8 spaceIndexPrevious;
// /* 0x17 */ u8 flags2;
// /* 0x18 */ s8 items[3];
// /* 0x1B */ u8 bowser_suit_flags;
// /* 0x1C */ u8 turn_status; //space type landed on (blue, red, etc.)
// /* 0x1D */ s8 playerIndex;
// /* 0x1E */ char unk_1E[2]; //likely padding
// /* 0x20 */ void* unk_20;
// /* 0x24	*/ void* player_obj; //ptr to struct 0x48 in size (things like model position, rotation, etc.)
// /* 0x24 */ s16 mg_star_coins; //used for mg star
// /* 0x26 */ s16 coins_total; //used for coin star
// /* 0x2C */ s8 happeningSpacesLandedOn;
// /* 0x2D */ s8 redSpacesLandedOn;
// /* 0x2E */ s8 blueSpacesLandedOn;
// /* 0x2F */ s8 chanceSpacesLandedOn;
// /* 0x30 */ s8 bowserSpacesLandedOn;
// /* 0x31 */ s8 battleSpacesLandedOn;
// /* 0x32 */ s8 itemSpacesLandedOn;
// /* 0x33 */ s8 bankSpacesLandedOn;
// /* 0x34 */ s8 gameGuySpacesLandedOn;
// /* 0x35 */ char unk_35[3]; //likely padding
// } mp3_GW_PLAYER; //sizeof 0x38

//new struct with extended item array
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
/* 0x0F */ s8 chainIndexCur;
/* 0x10 */ s8 spaceIndexCur;
/* 0x11 */ s8 chainIndexNext;
/* 0x12 */ s8 spaceIndexNext;
/* 0x13 */ s8 unk_13; //(Chain Index?)
/* 0x14 */ s8 unk_14; //(Space Index?)
/* 0x15 */ u8 chainIndexPrevious;
/* 0x16 */ u8 spaceIndexPrevious;
/* 0x17 */ u8 flags2;
//some members moved around here to support 5 items
/* 0x18 */ s8 items[5];
/* 0x1D */ s8 playerIndex;
/* 0x1E */ u8 bowser_suit_flags;
/* 0x1F */ u8 turn_status; //space type landed on (blue, red, etc.)
/* 0x20 */ void* unk_20;
/* 0x24	*/ Object* player_obj; //ptr to struct 0x48 in size (things like model position, rotation, etc.)
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

typedef struct mp3_GW_SYSTEM {
    /* 0x00 - 800CD058 */ s8 playMode; //0x01 - Lite Play pause screen, 0x04 - Story Play pause screen
    /* 0x01 - 800CD059 */ s8 current_board_index;
    /* 0x02 - 800CD05A */ s8 total_turns;
    /* 0x03 - 800CD05B */ s8 current_turn;
    /* 0x04 - 800CD05C */ s8 current_game_length; // 00=Lite Play,01=Standard Play,02=Full Play,03=Custom Play
    /* 0x05 - 800CD05D */ s8 current_star_spawn; // Index of star space (index into star_spawn_indices)
    /* 0x06 - 800CD05E */ s8 star_spawn_indices[7];
    /* 0x0D - 800CD065 */ s8 unk_0D;
    /* 0x0E - 800CD066 */ s8 unk_0E;
    /* 0x0F - 800CD067 */ s8 current_player_index;
    /* 0x10 - 800CD068 */ s8 minigame_index;
    /* 0x11 - 800CD069 */ s8 current_space_index;
    /* 0x12 - 800CD06A */ s8 save_mode; //00 - Save every turn, 01 - Save this turn, 02 - Don't save
    /* 0x13 - 800CD06B */ s8 show_minigame_explanations; //00 - show, 01 - hide
    /* 0x14 - 800CD06C */ s8 message_speed; //00 - Fast, 01 - Normal, 02 - Slow
    /* 0x15 - 800CD06D */ s8 walk_speed; //00 - Fast, 01 - Normal, 02 - Slow
    /* 0x16 - 800CD06E */ s8 show_com_minigames; //00 - Show COM minigame, 01 - Hide COM minigame
    /* 0x17 - 800CD06F */ char unk_17[0x26]; //unknown
    /* 0x3E - 800CD096 */ s8 board_bytes[0x13]; //bytes related to storing information for each board
    /* 0x51 - 800CD0A9 */ u8 cur_player_used_item; //1 if player already used an item this turn
    /* 0x52 - 800CD0AA */ char unk_52[5];
    /* 0x57 - 800CD0AF */ s8 slow_dice_flags;
    /* 0x58 - 800CD0B0 */ s16 unk_58;                           /* inferred */
    /* 0x5A - 800CD0B2 */ s16 playerIndexVisitingBowser;
    /* 0x5C - 800CD0B4 */ u16 bank_coins;
    /* 0x5E - 800CD0B6 */ u8 data_flags; //unknown what this is, but star spawns are included in this
    /* 0x5F - 800CD0B7 */ u8 unk_flags;
    /* 0x60 - 800CD0B8 */ u8 unk_60[0x44];
} mp3_GW_SYSTEM; //sizeof 0xA4

extern mp3_GW_PLAYER mp3_gPlayers[4];
extern mp3_GW_PLAYER mp3_PlayersCopy[4];
extern omOvlHisData mp3_omovlhis_copy[12];
extern omOvlHisData mp2_omovlhis_copy[12];
extern s16 mp3_omovlhisidx_copy;
extern omOvlHisData mp3_omovlhis[12];
extern s16 mp3_omovlhisidx;
extern s16 mp3_D_800CD2A2;
extern UnkCastleGroundMessage mp3_D_80110998[];
extern s32 mp3_D_800B1A30;
extern s16 mp3_D_800CDA7C[];
extern u32 mp3_debug_font_color;
extern mp3_GW_SYSTEM mp3_GwSystem;
extern mp3_GW_SYSTEM mp3_GwSystemCopy;
extern OSMesgQueue mp3_D_800CE1A0;
extern s32 ForeignMinigameIndexToLoad;
extern s16 mp3_BattleMinigameCoins;
extern s16 mp3_D_800D530C;
extern u8 mp3_prevMinigamesPlayed[PREV_MINIGAMES_PLAYED_SIZE];
extern s32 mp3_D_800A12C0;
extern s32 mp3_D_800A12C4;
extern Gfx* mp3_gMainGfxPos;

void mp3_omDelPrcObj(s32); 
f32 mp3_HuMathSin(f32);
void mp3_PlaySound(s16);
f32 mp3_HuMathCos(f32);
void mp3_HuFreeFilePerm(void*);
s16 mp3_func_80055810_56410(void*);
void* mp3_ReadMainFS(s32);
void mp3_LoadMinigameList(void);
void LoadBackIntoMp3Board(void);
void mp3_HuPrcEnd(void);
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
s32 mp3_RequestSIFunction(void* siMessg, void* func, void* arg, s32 type);
s32 func_800EECB0_1028D0_shared_board(s32);
mp3_GW_PLAYER* mp3_GetPlayerStruct(s32 playerIndex);
s32 mp3_GWBoardFlagCheck(s32);
void func_800E1934_F5554_shared_board(s32, s32);
s32 mp3_PlayerHasItem(s32 playerIndex, s32 itemID);
void mp3_AdjustPlayerCoins(s32 arg0, s32 arg1);
extern int		mp3_sprintf(char *s, const char *fmt, ...);

#endif
