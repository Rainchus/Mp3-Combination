#ifndef MP3_PLAYER_H
#define MP3_PLAYER_H

#include "marioparty.h"
#include "game/process.h"
#include "math.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define    OS_K0_TO_PHYSICAL(x)    (u32)(((char *)(x)-0x80000000))
#define    OS_PHYSICAL_TO_K0(x)    (void *)(((u32)(x)+0x80000000))

typedef struct Vec2f {
/* 0x00 */ f32 x;
/* 0x04 */ f32 y;
} Vec2f;

typedef struct objectIndirect3t {
/* 0x00 */ struct objectt *unk0;
/* 0x04 */ f32 unk4;
} objectIndirect3;

typedef struct DiceInstance {
    char unk_00[0x4C];
    s32 unk_4C;
} DiceInstance; //unk size

typedef struct UnkDiceRelatedInner {
    /* 0x00 */ char unk_00[0x28];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[10];
    /* 0x34 */ DiceInstance* dice;
    /* 0x38 */ char unk_38[12];
} UnkDiceRelatedInner;

typedef struct UnkDiceRelated {
/* 0x00 */ s16 unk_00;
/* 0x02 */ char unk_02[6];
/* 0x08 */ UnkDiceRelatedInner UnkDiceInner;
} UnkDiceRelated; //sizeof 0x4C


// typedef struct GwPlayer_s {
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
// /* 0x13 */ s8 unk_13; //(Chain Index?)
// /* 0x14 */ s8 unk_14; //(Space Index?)
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
// } GW_PLAYER __attribute__((aligned(4))); //sizeof 0x38;

typedef struct SpaceData {
/* 0x00 */ s8 unk_00;
/* 0x01 */ u8 space_type; // enum board_space_type
/* 0x02 */ s16 unk_02;
/* 0x04 */ s32 unk_04;
/* 0x08 */ Vec coords;
/* 0x14 */ Vec rot;
/* 0x20 */ void* event_list;
} SpaceData; //sizeof 0x24

// typedef struct omOvlHisData { //Object Manager History Data
// /* 0x00 */ s32 overlayID;
// /* 0x04 */ s16 event;
// /* 0x06 */ u16 stat;
// } omOvlHisData; //sizeof 0x08

typedef struct GW_SYSTEM {
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
    /* 0x58 - 800CD0B0 */ char unk_58[2];
    /* 0x5A - 800CD0B2 */ s16 unk_5A;
    /* 0x5C - 800CD0B4 */ u16 bank_coins;
    /* 0x5E - 800CD0B6 */ u8 data_flags[8]; //unknown what this is, unknown size
    /* 0x66 - 800CD0B8 */ u8 unk_66[0x3E];
} GW_SYSTEM; //sizeof 0xA4

typedef struct GwCommon_s {
/* 0x00 */ u8 unk_00;
/* 0x01 */ char unk_01;
/* 0x02 */ u16 mgRecord[8]; //is this still 8 in length like mp1?
/* 0x12 */ char unk_12[4];
/* 0x16 */ u8 mgUnlock[7]; //is this still 7 in length like mp1?
/* 0x1D */ char unk_1D[0x6E];
/* 0x8B */ u8 flag[12]; //is this still 12 in length like mp1?
/* 0x97 */ char unk_9D[0xD];
} GW_COMMON; //sizeof 0xA4?

typedef struct GW_STORY {
    char unk_00[0x74];
} GW_STORY; //sizeof 0x74

typedef struct RectF {
/* 0x00 */ f32 x1;
/* 0x04 */ f32 y1;
/* 0x08 */ f32 x2;
/* 0x0C */ f32 y2;
} RectF; //sizeof 0x10

typedef struct board_overlay_entrypoint {
/* 0x00 */ s16 index;
/* 0x04 */ void* fn;
} board_overlay_entrypoint; //sizeof 0x08

typedef struct RGB {
/* 0x00 */ u8 r;
/* 0x01 */ u8 g;
/* 0x02 */ u8 b;
} RGB; //sizeof 0x3

typedef struct ESprite2 {
    char unk_00[0x14];
    u16 unk_14;
    char unk_18[0x30];
    f32 unk_48;
    f32 unk_4C;
    char unk_50[0x34];
    s32 unk_84;
} ESprite2; //unknown size

typedef struct ESprite {
    char unk_00[8];
    s16 unk_08;
    s16 unk_0A;
    char unk_0C[4];
    ESprite2* unk_10[4]; //unknown size
} ESprite; //unknown size

#endif
