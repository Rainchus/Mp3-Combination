#ifndef _MP_H_
#define _MP_H_

#include "ultra64.h"
#include "functions.h"
#include "macros.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

/* Buttons */

#define CONT_A      0x8000
#define CONT_B      0x4000
#define CONT_G	    0x2000
#define CONT_START  0x1000
#define CONT_UP     0x0800
#define CONT_DOWN   0x0400
#define CONT_LEFT   0x0200
#define CONT_RIGHT  0x0100
#define CONT_L      0x0020
#define CONT_R      0x0010
#define CONT_E      0x0008
#define CONT_D      0x0004
#define CONT_C      0x0002
#define CONT_F      0x0001

/* Nintendo's official button names */

#define A_BUTTON	CONT_A
#define B_BUTTON	CONT_B
#define L_TRIG		CONT_L
#define R_TRIG		CONT_R
#define Z_TRIG		CONT_G
#define START_BUTTON	CONT_START
#define U_JPAD		CONT_UP
#define L_JPAD		CONT_LEFT
#define R_JPAD		CONT_RIGHT
#define D_JPAD		CONT_DOWN
#define U_CBUTTONS	CONT_E
#define L_CBUTTONS	CONT_C
#define R_CBUTTONS	CONT_F
#define D_CBUTTONS	CONT_D

typedef struct mp2_PlayerData {
/* 0x00 */ u8  group; //for which group you belong to in a minigame
/* 0x01 */ u8 cpu_difficulty;
/* 0x02 */ u8 cpu_difficulty2; //copied from 0x01 for some reason..?
/* 0x03 */ u8 controller_port;
/* 0x04 */ u8 characterID;
/* 0x05 */ char padding_05;
/* 0x06 */ s16 flags;
/* 0x08 */ s16 coins;
/* 0x0A */ s16 extra_coins_collected_during_minigame;
/* 0x0C */ s16 minigameCoinsWon; //coins won on current minigame, also stores battle placement briefly
/* 0x0E */ s16 stars;
/* 0x10 */ s16 cur_chain_index;
/* 0x12 */ s16 cur_space_index;
/* 0x14 */ s16 next_chain_index;
/* 0x16 */ s16 next_space_index;
/* 0x18 */ char unk_18;
/* 0x19 */ s8 item;
/* 0x1A */ s8 turn_status;
/* 0x1B */ s8 player_space_color; //(color for minigame dividing)
/* 0x1C */ char unk_1C[0x0C];
/* 0x28 */ s16 minigame_coins_collected;
/* 0x2A */ s16 coinPeak; //used for coin star
/* 0x2C */ u8 happening_spaces_landed_on;
/* 0x2D */ u8 red_spaces_landed_on;
/* 0x2E */ u8 blue_spaces_landed_on;
/* 0x2F */ u8 chance_spaces_landed_on;
/* 0x30 */ u8 bowser_spaces_landed_on;
/* 0x31 */ u8 battle_spaces_landed_on;
/* 0x32 */ u8 item_spaces_landed_on;
/* 0x33 */ u8 bank_spaces_landed_on;
} mp2_PlayerData; //sizeof 0x34
//P1 - 800FD2C0
//P2 - 800FD2F4
//P3 - 800FD328
//P4 - 800FD35C

typedef struct mp3_PlayerData {
/* 0x00 */ u8  group; //for which group you belong to in a minigame
/* 0x01 */ u8  cpu_difficulty;
/* 0x02 */ u8  controller_port;
/* 0x03 */ u8  characterID;
/* 0x04 */ u8  flags1; //value & 1 == Player is CPU
/* 0x05 */ char unk_05;
/* 0x06 */ s16 minigameCoinsWon; //extra coins collected in minigames
/* 0x08 */ s16 minigameCoins; //coins for winning current minigame
/* 0x0A */ s16 coins; //referenced as u16 and s16 (usually if u16 it's casted to s16)
/* 0x0C */ char unk_0C[2];
/* 0x0E */ s8  stars;
/* 0x0F */ u8  chainIndexCur;
/* 0x10 */ u8  spaceIndexCur;
/* 0x11 */ u8  chainIndexNext;
/* 0x12 */ u8  spaceIndexNext;
/* 0x13 */ u8  unk_13; //(Chain Index?)
/* 0x14 */ u8  unk_14; //(Space Index?)
/* 0x15 */ u8  chainIndexPrevious;
/* 0x16 */ u8  spaceIndexPrevious;
/* 0x17 */ u8  flags2;
/* 0x18 */ u8  items[3];
/* 0x1B */ u8  bowser_suit_flags;
/* 0x1C */ u8  turn_status; //space type landed on (blue, red, etc.)
/* 0x1D */ s8 	playerIndex;
/* 0x1E */ char unk_1E[2]; //likely padding
/* 0x20 */ void* unk_20;
/* 0x24	*/ void* player_obj; //ptr to struct 0x48 in size (things like model position, rotation, etc.)
/* 0x28 */ s16 minigameCoinsTotal; //for minigame star
/* 0x2A */ s16 coinsPeak; //most coins held at once for coin star
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
} mp3_PlayerData; //sizeof 0x38
//P1 = 0x800D1108
//P2 = 0x800D1140
//P3 = 0x800D1178
//P4 = 0x800D11B0

enum MinigameNameStringIDs {
    STR_HAND_LINE_AND_SINKER = 0x4700,
    STR_COCONUT_CONK = 0x4701,
    STR_SPOTLIGHT_SWIM = 0x4702,
    STR_BOULDER_BALL = 0x4703,
    STR_CRAZY_COGS = 0x4704,
    STR_HIDE_AND_SNEAK = 0x4705,
    STR_RIDICULOUS_RELAY = 0x4706,
    STR_THWOMP_PULL = 0x4707,
    STR_RIVER_RAIDERS = 0x4708,
    STR_TIDAL_TOSS = 0x4709,
    STR_EATSA_PIZZA = 0x470A,
    STR_BABY_BOWSER_BROADSIDE = 0x470B,
    STR_PUMP_PUMP_AND_AWAY = 0x470C,
    STR_HYPER_HYDRANTS = 0x470D,
    STR_PICKING_PANIC = 0x470E,
    STR_COSMIC_COASTER = 0x470F,
    STR_PUDDLE_PADDLE = 0x4710,
    STR_ETCH_N_CATCH = 0x4711,
    STR_LOG_JAM = 0x4712,
    STR_SLOT_SYNCH = 0x4713,
    STR_TREADMILL_GRILL = 0x4714,
    STR_TOADSTOOL_TITAN = 0x4715,
    STR_ACES_HIGH = 0x4716,
    STR_BOUNCE_N_TROUNCE = 0x4717,
    STR_ICE_RINK_RISK = 0x4718,
    STR_LOCKED_OUT = 0x4719,
    STR_CHIP_SHOT_CHALLENGE = 0x471A,
    STR_PARASOL_PLUMMET = 0x471B,
    STR_MESSY_MEMORY = 0x471C,
    STR_PICTURE_IMPERFECT = 0x471D,
    STR_MARIOS_PUZZLE_PARTY = 0x471E,
    STR_THE_BEAT_GOES_ON = 0x471F,
    STR_MPIQ = 0x4720,
    STR_CURTAIN_CALL = 0x4721,
    STR_WATER_WHIRLED = 0x4722,
    STR_FRIGID_BRIDGES = 0x4723,
    STR_AWFUL_TOWER = 0x4724,
    STR_CHEEP_CHEEP_CHASE = 0x4725,
    STR_PIPE_CLEANERS = 0x4726,
    STR_SNOWBALL_SUMMIT = 0x4727,
    STR_ALL_FIRED_UP = 0x4728,
    STR_STACKED_DECK = 0x4729,
    STR_THREE_DOOR_MONTY = 0x472A,
    STR_ROCKIN_RACEWAY = 0x472B,
    STR_MERRY_GO_CHOMP = 0x472C,
    STR_SLAP_DOWN = 0x472D,
    STR_STORM_CHASERS = 0x472E,
    STR_EYE_SORE = 0x472F,
    STR_VINE_WITH_ME = 0x4730,
    STR_POPGUN_PICK_OFF = 0x4731,
    STR_END_OF_THE_LINE = 0x4732,
    STR_BOWSER_TOSS = 0x4733,
    STR_BABY_BOWSER_BONKERS = 0x4734,
    STR_MOTOR_ROOTER = 0x4735,
    STR_SILLY_SCREWS = 0x4736,
    STR_CROWD_COVER = 0x4737,
    STR_TICK_TOCK_HOP = 0x4738,
    STR_FOWL_PLAY = 0x4739,
    STR_WINNERS_WHEEL = 0x473A,
    STR_HEY_BATTER_BATTER = 0x473B,
    STR_BOBBING_BOW_LOONS = 0x473C,
    STR_DORRIE_DIP = 0x473D,
    STR_SWINGING_WITH_SHARKS = 0x473E,
    STR_SWING_N_SWIPE = 0x473F,
    STR_CHANCE_TIME = 0x4740,
    STR_STARDUST_BATTLE = 0x4741,
    STR_GAME_GUYS_ROULETTE = 0x4742,
    STR_GAME_GUYS_LUCKY_7 = 0x4743,
    STR_GAME_GUYS_MAGIC_BOXES = 0x4744,
    STR_GAME_GUYS_SWEET_SURPRISE = 0x4745,
    STR_DIZZY_DINGHIES = 0x4746,
    STR_MARIO_PUZZLE_PARTY_PRO = 0x4747,
    STR_QUESTION_MARKS = 0x4748,
};

//combined minigame ids
enum MinigameIDs {
    HAND_LINE_AND_SINKER = 1,
    COCONUT_CONK = 2,
    SPOTLIGHT_SWIM = 3,
    BOULDER_BALL = 4,
    CRAZY_COGS = 5,
    HIDE_AND_SNEAK = 6,
    RIDICULOUS_RELAY = 7,
    THWOMP_PULL = 8,
    RIVER_RAIDERS = 9,
    TIDAL_TOSS = 10,
    EATSA_PIZZA = 11,
    BABY_BOWSER_BROADSIDE = 12,
    PUMP_PUMP_AND_AWAY = 13,
    HYPER_HYDRANTS = 14,
    PICKING_PANIC = 15,
    COSMIC_COASTER = 16,
    PUDDLE_PADDLE = 17,
    ETCH_N_CATCH = 18,
    LOG_JAM = 19,
    SLOT_SYNC = 20,
    TREADMILL_GRILL = 21,
    TOADSTOOL_TITAN = 22,
    ACES_HIGH = 23,
    BOUNCE_N_TROUNCE = 24,
    ICE_RINK_RISK = 25,
    LOCKED_OUT = 26,
    CHIP_SHOT_CHALLENGE = 27,
    PARASOL_PLUMMET = 28,
    MESSY_MEMORY = 29,
    PICTURE_IMPERFECT = 30,
    MARIOS_PUZZLE_PARTY = 31,
    THE_BEAT_GOES_ON = 32,
    MPIQ = 33,
    CURTAIN_CALL = 34,
    WATER_WHIRLED = 35,
    FRIGID_BRIDGES = 36,
    AWFUL_TOWER = 37,
    CHEEP_CHEEP_CHASE = 38,
    PIPE_CLEANERS = 39,
    SNOWBALL_SUMMIT = 40,
    ALL_FIRED_UP = 41,
    STACKED_DECK = 42,
    THREE_DOOR_MONTY = 43,
    ROCKIN_RACEWAY = 44,
    MERRY_GO_CHOMP = 45,
    SLAP_DOWN = 46,
    STORM_CHASERS = 47,
    EYE_SORE = 48,
    VINE_WITH_ME = 49,
    POPGUN_PICK_OFF = 50,
    END_OF_THE_LINE = 51,
    BOWSER_TOSS = 52,
    BABY_BOWSER_BONKERS = 53,
    MOTOR_ROOTER = 54,
    SILLY_SCREWS = 55,
    CROWD_COVER = 56,
    TICK_TOCK_HOP = 57,
    FOWL_PLAY = 58,
    WINNERS_WHEEL = 59,
    HEY_BATTER_BATTER = 60,
    BOBBING_BOW_LOONS = 61,
    DORRIE_DIP = 62,
    SWINGING_WITH_SHARKS = 63,
    SWING_N_SWIPE = 64,
    CHANCE_TIME = 65,
    STARDUST_BATTLE = 66,
    GAME_GUYS_ROULETTE = 67,
    GAME_GUYS_LUCKY_7 = 68,
    GAME_GUYS_MAGIC_BOXES = 69,
    GAME_GUYS_SWEET_SURPRISE = 70,
    DIZZY_DINGHIES = 71,
    MARIO_PUZZLE_PARTY_PRO = 72,
    MP2_BASE = 73,
    BOWSER_SLOTS = 73, //test mp2 import
    ROLL_OUT_THE_BARRELS = 74,
    COFFIN_CONGESTION = 75,
    HAMMER_SLAMMER = 76,
    GIVE_ME_A_BRAKE = 77,
    MALLET_GO_ROUND = 78,
    GRAB_BAG_MP2 = 79,
    LAVA_TILE_ISLE = 80,
    BUMPER_BALLOON_CARS = 81,
    RAKIN_EM_IN = 82,
    DAY_AT_THE_RACES = 83,
    HOT_ROPE_JUMP_MP2 = 84,
    HOT_BOB_OMB_MP2 = 85,
    BOWL_OVER_MP2 = 86,
    RAINBOW_RUN = 87,
    CRANE_GAME = 88,
    MOVE_TO_THE_MUSIC = 89,
    BOB_OMB_BARRAGE = 90,
    LOOK_AWAY = 91,
    SHOCK_DROP_OR_ROLL = 92,
    LIGHTS_OUT = 93,
    FILET_RELAY = 94,
    ARCHER_IVAL = 95,
    TOAD_BANDSTAND = 96,
    BOBSLED_RUN = 97,
    HANDCAR_HAVOC = 98,
};


extern mp3_PlayerData mp3_gPlayers[4];
extern mp2_PlayerData mp2_gPlayers[4];

extern u8 mp2_debugMode;

#endif //_MP_H_