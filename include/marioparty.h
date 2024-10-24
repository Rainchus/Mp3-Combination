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
    MP2_DEBUG = 73,
    BOWSER_SLOTS, //mp2 1
    ROLL_OUT_THE_BARRELS, //mp2 2
    COFFIN_CONGESTION, //mp2 3
    HAMMER_SLAMMER, //mp2 4
    GIVE_ME_A_BRAKE, //mp2 5
    MALLET_GO_ROUND, //mp2 6
    MP2_GRAB_BAG, //mp2 7
    BUMPER_BALLOON_CARS, //mp2 8
    RAKIN_EM_IN, //mp2 9
    NONE_0, //mp2 10
    DAY_AT_THE_RACES, //mp2 11
    MP2_FACE_LIFT, //mp2 12
    MP2_CRAZY_CUTTERS, //mp2 13
    MP2_HOT_BOB_OMB, //mp2 14
    MP2_BOWL_OVER, //mp2 15
    RAINBOW_RUN, //mp2 16
    MP2_CRANE_GAME, //mp2 17
    MOVE_TO_THE_MUSIC, //mp2 18
    BOB_OMB_BARRAGE, //mp2 19
    LOOK_AWAY, //mp2 20
    SHOCK_DROP_OR_ROLL, //mp2 21
    LIGHTS_OUT, //mp2 22
    FILET_RELAY, //mp2 23
    ARCHERIVAL, //mp2 24
    NONE_1, //mp2 25
    TOAD_BANDSTAND, //mp2 26
    MP2_BOBSLED_RUN, //mp2 27
    MP2_HANDCAR_HAVOC, //mp2 28
    NONE_3, //mp2 29
    MP2_BALLOON_BURST, //mp2 30
    SKY_PILOTS, //mp2 31
    SPEED_HOCKEY, //mp2 32
    CAKE_FACTORY, //mp2 33
    NONE_4, //mp2 34
    DUNGEON_DASH, //mp2 35
    MAGNET_CARTA, //mp2 36
    LAVA_TILE_ISLE, //mp2 37
    MP2_HOT_ROPE_JUMP, //mp2 38
    SHELL_SHOCKED, //mp2 39
    TOAD_IN_THE_BOX, //mp2 40
    MECHA_MARATHON, //mp2 41
    ROLL_CALL, //mp2 42
    ABANDON_SHIP, //mp2 43
    MP2_PLATFORM_PERIL, //mp2 44
    TOTEM_POLE_POUND, //mp2 45
    MP2_BUMPER_BALLS, //mp2 46
    NONE_6, //mp2 47
    MP2_BOMBS_AWAY, //mp2 48
    MP2_TIPSY_TOURNEY, //mp2 49
    HONEYCOMB_HAVOC, //mp2 50
    HEXAGON_HEAT, //mp2 51
    MP2_SKATEBOARD_SCAMPER, //mp2 52
    MP2_SLOT_CAR_DERBY, //mp2 53
    MP2_SHY_GUY_SAYS, //mp2 54
    SNEAK_N_SNORE, //mp2 55
    NONE_7, //mp2 56
    DRIVERS_ED, //mp2 57
    MP2_CHANCE_TIME, //mp2 58
    WESTERN_LAND_DUEL, //mp2 59
    PIRATE_LAND_DUEL, //mp2 60
    HORROR_LAND_DUEL, //mp2 61
    SPACE_LAND_DUEL, //mp2 62
    MYSTERY_LAND_DUEL, //mp2 63
    KOOPA_LAND_DUEL, //mp2 64
    BOWSERS_BIG_BLAST, //mp2 65
    LOONEY_LUMBERJACKS, //mp2 66
    TORPEDO_TARGETS, //mp2 67
    DESTRUCTION_DUET, //mp2 68
    DIZZY_DANCING, //mp2 69
    TILE_DRIVER, //mp2 70
    QUICKSAND_CACHE, //mp2 71
    DEEP_SEA_SALVAGE, //mp2 72

    MP1_BASE = 146,
    MEMORY_MATCH = 146, //mp1 0
    MP1_CHANCE_TIME, //mp1 1
    SLOT_MACHINE, //mp1 2
    BURIED_TREASURE, //mp1 3
    TREASURE_DIVERS, //mp1 4
    SHELL_GAME, //mp1 5
    SAME_GAME, //mp1 6
    MP1_HOT_BOB_OMB, //mp1 7
    YOSHIS_TONGUE_MEETING, //mp1 8
    PIPE_MAZE, //mp1 9
    GHOST_GUESS, //mp1 10
    MUSICAL_MUSHROOM, //mp1 11
    PEDAL_POWER, //mp1 12
    MP1_CRAZY_CUTTER, //mp1 13
    MP1_FACE_LIFT, //mp1 14
    WHACKA_A_PLANT, //mp1 15
    BASH_N_CASH, //mp1 16
    MP1_BOWL_OVER, //mp1 17
    GROUND_POUND, //mp1 18
    MP1_BALLOON_BURST, //mp1 19
    COIN_BLOCK_BLITZ, //mp1 20
    COIN_BLOCK_BASH, //mp1 21
    MP1_SKATEBOARD_SCAMPER, //mp1 22
    BOX_MOUNTAIN_MAYHEM, //mp1 23
    MP1_PLATFORM_PERIL, //mp1 24
    TEETERING_TOWER, //mp1 25
    MUSHROOM_MIXUP, //mp1 26
    HAMMER_DROP, //mp1 27
    MP1_GRAB_BAG, //mp1 28
    MP1_BOBSLED_RUN, //mp1 29
    MP1_BUMPER_BALLS, //mp1 30
    TIGHTROPE_TREACHERY, //mp1 31
    KNOCK_BLOCK_TOWER, //mp1 32
    MP1_TIPSY_TOURNEY, //mp1 33
    MP1_BOMBS_AWAY, //mp1 34
    MP1_CRANE_GAME, //mp1 35
    COIN_SHOWER_FLOWER, //mp1 36
    MP1_SLOT_CAR_DERBY, //mp1 37
    MARIO_BANDSTAND, //mp1 38
    DESERT_DASH, //mp1 39
    MP1_SHY_GUY_SAYS, //mp1 40
    LIMBO_DANCE, //mp1 41
    BOMBSKETBALL, //mp1 42
    CAST_AWAYS, //mp1 43
    KEY_PA_WAY, //mp1 44
    RUNNING_OF_THE_BULB, //mp1 45
    MP1_HOT_ROPE_JUMP, //mp1 46
    MP1_HANDCAR_HAVOC, //mp1 47
    DEEP_SEA_DIVERS, //mp1 48
    PIRANHA_PURSUIT, //mp1 49
    TUG_O_WAR, //mp1 50
    PADDLE_BATTLE, //mp1 51
    BUMPER_BALL_MAZE_0, //mp1 52
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