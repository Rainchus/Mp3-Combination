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

typedef struct mp1_PlayerData {
/* 0x00 */ u8 group;
/* 0x01 */ u8 cpuDifficulty;
/* 0x02 */ u8 cpuDifficultyCopy;
/* 0x03 */ u8 controller_port;
/* 0x04 */ u8 characterID;
/* 0x05 */ char unk_05;
/* 0x06 */ u16 flags; //including CPU flag
/* 0x08 */ s16 coinAmount;
/* 0x0A */ s16 miniGameCoins; //coins to give to player after minigame
/* 0x0C */ s16 starAmount;
/* 0x0E */ s16 curChainIndex;
/* 0x10 */ u16 curSpaceIndex;
/* 0x12 */ u16 nextChainIndex;
/* 0x14 */ u16 nextSpaceIndex;
/* 0x16 */ u8 poisonedFlag;
/* 0x17 */ u8 turn_status; //space type player landed on
/* 0x18 */ u8 playerIndex; //0, 1, 2, or 3
/* 0x19 */ char unk_19[3]; //likely padding
/* 0x1C */ void* process; //some heap instance
/* 0x20 */ void* playerObj; //ptr to playerObj on heap
/* 0x24 */ u16 totalMinigameCoins;
/* 0x26 */ s16 coinPeak;
/* 0x28 */ u8 happeningSpacesTotal;
/* 0x29 */ u8 redSpacesTotal;
/* 0x2A */ u8 blueSpacesTotal;
/* 0x2B */ u8 minigameSpacesTotal;
/* 0x2C */ u8 chanceSpacesTotal;
/* 0x2D */ u8 mushroomSpacesTotal;
/* 0x2E */ u8 bowserSpacesTotal;
/* 0x2F */ char unk_2F;
} mp1_PlayerData; //sizeof 0x30
//P1 800F32B0, P2 800F32E0, P3 800F3310, P4 800F3340

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

// enum MinigameNameStringIDs {
//     STR_HAND_LINE_AND_SINKER = 0x4700,
//     STR_COCONUT_CONK = 0x4701,
//     STR_SPOTLIGHT_SWIM = 0x4702,
//     STR_BOULDER_BALL = 0x4703,
//     STR_CRAZY_COGS = 0x4704,
//     STR_HIDE_AND_SNEAK = 0x4705,
//     STR_RIDICULOUS_RELAY = 0x4706,
//     STR_THWOMP_PULL = 0x4707,
//     STR_RIVER_RAIDERS = 0x4708,
//     STR_TIDAL_TOSS = 0x4709,
//     STR_EATSA_PIZZA = 0x470A,
//     STR_BABY_BOWSER_BROADSIDE = 0x470B,
//     STR_PUMP_PUMP_AND_AWAY = 0x470C,
//     STR_HYPER_HYDRANTS = 0x470D,
//     STR_PICKING_PANIC = 0x470E,
//     STR_COSMIC_COASTER = 0x470F,
//     STR_PUDDLE_PADDLE = 0x4710,
//     STR_ETCH_N_CATCH = 0x4711,
//     STR_LOG_JAM = 0x4712,
//     STR_SLOT_SYNCH = 0x4713,
//     STR_TREADMILL_GRILL = 0x4714,
//     STR_TOADSTOOL_TITAN = 0x4715,
//     STR_ACES_HIGH = 0x4716,
//     STR_BOUNCE_N_TROUNCE = 0x4717,
//     STR_ICE_RINK_RISK = 0x4718,
//     STR_LOCKED_OUT = 0x4719,
//     STR_CHIP_SHOT_CHALLENGE = 0x471A,
//     STR_PARASOL_PLUMMET = 0x471B,
//     STR_MESSY_MEMORY = 0x471C,
//     STR_PICTURE_IMPERFECT = 0x471D,
//     STR_MARIOS_PUZZLE_PARTY = 0x471E,
//     STR_THE_BEAT_GOES_ON = 0x471F,
//     STR_MPIQ = 0x4720,
//     STR_CURTAIN_CALL = 0x4721,
//     STR_WATER_WHIRLED = 0x4722,
//     STR_FRIGID_BRIDGES = 0x4723,
//     STR_AWFUL_TOWER = 0x4724,
//     STR_CHEEP_CHEEP_CHASE = 0x4725,
//     STR_PIPE_CLEANERS = 0x4726,
//     STR_SNOWBALL_SUMMIT = 0x4727,
//     STR_ALL_FIRED_UP = 0x4728,
//     STR_STACKED_DECK = 0x4729,
//     STR_THREE_DOOR_MONTY = 0x472A,
//     STR_ROCKIN_RACEWAY = 0x472B,
//     STR_MERRY_GO_CHOMP = 0x472C,
//     STR_SLAP_DOWN = 0x472D,
//     STR_STORM_CHASERS = 0x472E,
//     STR_EYE_SORE = 0x472F,
//     STR_VINE_WITH_ME = 0x4730,
//     STR_POPGUN_PICK_OFF = 0x4731,
//     STR_END_OF_THE_LINE = 0x4732,
//     STR_BOWSER_TOSS = 0x4733,
//     STR_BABY_BOWSER_BONKERS = 0x4734,
//     STR_MOTOR_ROOTER = 0x4735,
//     STR_SILLY_SCREWS = 0x4736,
//     STR_CROWD_COVER = 0x4737,
//     STR_TICK_TOCK_HOP = 0x4738,
//     STR_FOWL_PLAY = 0x4739,
//     STR_WINNERS_WHEEL = 0x473A,
//     STR_HEY_BATTER_BATTER = 0x473B,
//     STR_BOBBING_BOW_LOONS = 0x473C,
//     STR_DORRIE_DIP = 0x473D,
//     STR_SWINGING_WITH_SHARKS = 0x473E,
//     STR_SWING_N_SWIPE = 0x473F,
//     STR_CHANCE_TIME = 0x4740,
//     STR_STARDUST_BATTLE = 0x4741,
//     STR_GAME_GUYS_ROULETTE = 0x4742,
//     STR_GAME_GUYS_LUCKY_7 = 0x4743,
//     STR_GAME_GUYS_MAGIC_BOXES = 0x4744,
//     STR_GAME_GUYS_SWEET_SURPRISE = 0x4745,
//     STR_DIZZY_DINGHIES = 0x4746,
//     STR_MARIO_PUZZLE_PARTY_PRO = 0x4747,
//     STR_QUESTION_MARKS = 0x4748,
// };

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
    MP3_CHANCE_TIME = 65,
    STARDUST_BATTLE = 66,
    GAME_GUYS_ROULETTE = 67,
    GAME_GUYS_LUCKY_7 = 68,
    GAME_GUYS_MAGIC_BOXES = 69,
    GAME_GUYS_SWEET_SURPRISE = 70,
    DIZZY_DINGHIES = 71,
    MARIO_PUZZLE_PARTY_PRO = 72,
    MP2_BASE = 73,
    BOWSER_SLOTS = 73, //mp2 1
    ROLL_OUT_THE_BARRELS = 74, //mp2 2
    COFFIN_CONGESTION = 75, //mp2 3
    HAMMER_SLAMMER = 76, //mp2 4
    GIVE_ME_A_BRAKE = 77, //mp2 5
    MALLET_GO_ROUND = 78, //mp2 6
    GRAB_BAG_MP2 = 79, //mp2 7
    BUMPER_BALLOON_CARS = 80, //mp2 8
    RAKIN_EM_IN = 81, //mp2 9
    NONE_0 = 82, //mp2 10
    DAY_AT_THE_RACES = 83, //mp2 11
    FACE_LIFT_MP2 = 84, //mp2 12
    CRAZY_CUTTERS = 85, //mp2 13
    HOT_BOB_OMB_MP2 = 86, //mp2 14
    BOWL_OVER_MP2 = 87, //mp2 15
    RAINBOW_RUN = 88, //mp2 16
    CRANE_GAME_MP2 = 89, //mp2 17
    MOVE_TO_THE_MUSIC = 90, //mp2 18
    BOB_OMB_BARRAGE = 91, //mp2 19
    LOOK_AWAY = 92, //mp2 20
    SHOCK_DROP_OR_ROLL = 93, //mp2 21
    LIGHTS_OUT = 94, //mp2 22
    FILET_RELAY = 95, //mp2 23
    ARCHERIVAL = 96, //mp2 24
    NONE_1 = 97, //mp2 25
    TOAD_BANDSTAND = 98, //mp2 26
    BOBSLED_RUN = 98, //mp2 27
    HANDCAR_HAVOC_MP2 = 99, //mp2 28
    NONE_3 = 100, //mp2 29
    BALLOON_BURST_MP2 = 101, //mp2 30
    SKY_PILOTS = 102, //mp2 31
    SPEED_HOCKEY = 103, //mp2 32
    CAKE_FACTORY = 104, //mp2 33
    NONE_4 = 105, //mp2 34
    DUNGEON_DASH = 106, //mp2 35
    MAGNET_CARTA = 107, //mp2 36
    LAVA_TILE_ISLE = 108, //mp2 37
    HOT_ROPE_JUMP_MP2 = 109, //mp2 38
    SHELL_SHOCKED = 110, //mp2 39
    TOAD_IN_THE_BOX = 111, //mp2 40
    MECHA_MARATHON = 112, //mp2 41
    ROLL_CALL = 113, //mp2 42
    ABANDON_SHIP = 114, //mp2 43
    PLATFORM_PERIL_MP2 = 115, //mp2 44
    TOTEM_POLE_POUND = 116, //mp2 45
    BUMPER_BALLS_MP2 = 117, //mp2 46
    NONE_6 = 118, //mp2 47
    BOMBS_AWAY = 119, //mp2 48
    TIPSY_TOURNEY = 120, //mp2 49
    HONEYCOMB_HAVOC = 121, //mp2 50
    HEXAGON_HEAT = 122, //mp2 51
    SKATEBOARD_SCAMPER = 123, //mp2 52
    SLOT_CAR_DERBY = 124, //mp2 53
    SHY_GUY_SAYS_MP2 = 125, //mp2 54
    SNEAK_N_SNORE = 126, //mp2 55
    NONE_7 = 127, //mp2 56
    DRIVERS_ED = 128, //mp2 57
    MP2_CHANCE_TIME = 129, //mp2 58
    WESTERN_LAND_DUEL = 130, //mp2 59
    PIRATE_LAND_DUEL = 131, //mp2 60
    HORROR_LAND_DUEL = 132, //mp2 61
    SPACE_LAND_DUEL = 133, //mp2 62
    MYSTERY_LAND_DUEL = 134, //mp2 63
    KOOPA_LAND_DUEL = 135, //mp2 64
    BOWSERS_BIG_BLAST = 136, //mp2 65
    LOONEY_LUMBERJACKS = 137, //mp2 66
    TORPEDO_TARGETS = 138, //mp2 67
    DESTRUCTION_DUET = 139, //mp2 68
    DIZZY_DANCING = 140, //mp2 69
    TILE_DRIVER = 141, //mp2 70
    QUICKSAND_CACHE = 141, //mp2 71
    DEEP_SEA_SALVAGE = 142, //mp2 72
    MP1_BASE = 143,
    MEMORY_MATCH = 143, //mp1 0
    MP1_CHANCE_TIME = 144, //mp1 1
    SLOT_MACHINE = 145, //mp1 2
    BURIED_TREASURE = 146, //mp1 3
    TREASURE_DIVERS = 147, //mp1 4
    SHELL_GAME = 148, //mp1 5
};

typedef struct mp2_omObjData {
/* 0x00 */ u16 stat;
/* 0x02 */ s16 next_idx_alloc;
/* 0x04 */ s16 prio;
/* 0x06 */ s16 prev;
/* 0x08 */ s16 next;
/* 0x0A */ s16 next_idx;
/* 0x0C */ s16 group;
/* 0x0E */ s16 group_idx;
/* 0x10 */ s32 unk_10;
/* 0x14 */ void* func_ptr;
/* 0x18 */ Vec3f trans;
/* 0x24 */ Vec3f rot;
/* 0x30 */ Vec3f scale;
/* 0x3C */ u16 mdlcnt;
// /* 0x3E */ char unk_3E[2];
/* 0x40 */ s16* model;
/* 0x44 */ u16 mtncnt;
// /* 0x46 */ char unk_46[2];
/* 0x48 */ s16* motion;
/* 0x4C */ u8 work[4];
/* 0x50 */ void* unk_50;
} mp2_omObjData; //sizeof 0x54

extern mp3_PlayerData mp3_gPlayers[4];
extern mp2_PlayerData mp2_gPlayers[4];
extern mp1_PlayerData mp1_gPlayers[4];

extern u8 mp2_debugMode;

#endif //_MP_H_