#ifndef _MP_H_
#define _MP_H_

#define PREV_MINIGAMES_PLAYED_SIZE 0x3C
#define BOARD_STATE_STRUCT_SIZE 0x80
#define EEPROM_ABS_POS 0x2C0
#define EEPROM_BLOCK_POS EEPROM_ABS_POS / EEPROM_BLOCK_SIZE
#define EEPROM_BLOCK_VI_POS 0x300 / EEPROM_BLOCK_SIZE

#define CUR_PLAYER -1
#define MAX_PLAYERS 4
#define MB_MAX_PLAYERS MAX_PLAYERS //for decomp compatibility reasons
#define FOREIGN_MINIGAME_INDEX_BOOT_VAL -2
#define FOREIGN_MINIGAME_INVALID_ID -1

#include "ultra64.h"
#include "PR/mbi.h"
#include "macros.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
} Vec;

typedef struct OvlEntrypoint {
/* 0x00 */ s16 index;
/* 0x04 */ void (*fn)(void);
} OvlEntrypoint; //sizeof 0x08
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

#define PLAYERS_SPECIAL -1
#define PLAYERS_4P 0
#define PLAYERS_1V3 1
#define PLAYERS_2V2 2
#define PLAYERS_ITEM 3
#define PLAYERS_BATTLE 4
#define PLAYERS_DUEL 5
#define PLAYERS_GAME_GUY 6
#define PLAYERS_1P 7

//combined minigame ids
enum MinigameIDs {
    NONE = 0,
    HAND_LINE_AND_SINKER,
    COCONUT_CONK,
    SPOTLIGHT_SWIM,
    BOULDER_BALL,
    CRAZY_COGS,
    HIDE_AND_SNEAK,
    RIDICULOUS_RELAY,
    THWOMP_PULL,
    RIVER_RAIDERS,
    TIDAL_TOSS,
    EATSA_PIZZA,
    BABY_BOWSER_BROADSIDE,
    PUMP_PUMP_AND_AWAY,
    HYPER_HYDRANTS,
    PICKING_PANIC,
    COSMIC_COASTER,
    PUDDLE_PADDLE,
    ETCH_N_CATCH,
    LOG_JAM,
    SLOT_SYNC,
    TREADMILL_GRILL,
    TOADSTOOL_TITAN,
    ACES_HIGH,
    BOUNCE_N_TROUNCE,
    ICE_RINK_RISK,
    LOCKED_OUT,
    CHIP_SHOT_CHALLENGE,
    PARASOL_PLUMMET,
    MESSY_MEMORY,
    PICTURE_IMPERFECT,
    MARIOS_PUZZLE_PARTY,
    THE_BEAT_GOES_ON,
    MPIQ,
    CURTAIN_CALL,
    WATER_WHIRLED,
    FRIGID_BRIDGES,
    AWFUL_TOWER,
    CHEEP_CHEEP_CHASE,
    PIPE_CLEANERS,
    SNOWBALL_SUMMIT,
    ALL_FIRED_UP,
    STACKED_DECK,
    THREE_DOOR_MONTY,
    ROCKIN_RACEWAY,
    MERRY_GO_CHOMP,
    SLAP_DOWN,
    STORM_CHASERS,
    EYE_SORE,
    VINE_WITH_ME,
    POPGUN_PICK_OFF,
    END_OF_THE_LINE,
    BOWSER_TOSS,
    BABY_BOWSER_BONKERS,
    MOTOR_ROOTER,
    SILLY_SCREWS,
    CROWD_COVER,
    TICK_TOCK_HOP,
    FOWL_PLAY,
    WINNERS_WHEEL,
    HEY_BATTER_BATTER,
    BOBBING_BOW_LOONS,
    DORRIE_DIP,
    SWINGING_WITH_SHARKS,
    SWING_N_SWIPE,
    MP3_CHANCE_TIME,
    STARDUST_BATTLE,
    GAME_GUYS_ROULETTE,
    GAME_GUYS_LUCKY_7,
    GAME_GUYS_MAGIC_BOXES,
    GAME_GUYS_SWEET_SURPRISE,
    DIZZY_DINGHIES,
    MARIO_PUZZLE_PARTY_PRO,
    //mp2 0
    BOWSER_SLOTS, //mp2 1
    ROLL_OUT_THE_BARRELS, //mp2 2
    COFFIN_CONGESTION, //mp2 3
    HAMMER_SLAMMER, //mp2 4
    GIVE_ME_A_BRAKE, //mp2 5
    MALLET_GO_ROUND, //mp2 6
    MP2_GRAB_BAG, //mp2 7
    BUMPER_BALLOON_CARS, //mp2 8
    RAKIN_EM_IN, //mp2 9
    //mp2 10
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
    //mp2 25
    TOAD_BANDSTAND, //mp2 26
    MP2_BOBSLED_RUN, //mp2 27
    MP2_HANDCAR_HAVOC, //mp2 28
    //mp2 29
    MP2_BALLOON_BURST, //mp2 30
    SKY_PILOTS, //mp2 31
    SPEED_HOCKEY, //mp2 32
    CAKE_FACTORY, //mp2 33
    //mp2 34
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
    //mp2 47
    MP2_BOMBS_AWAY, //mp2 48
    MP2_TIPSY_TOURNEY, //mp2 49
    HONEYCOMB_HAVOC, //mp2 50
    HEXAGON_HEAT, //mp2 51
    MP2_SKATEBOARD_SCAMPER, //mp2 52
    MP2_SLOT_CAR_DERBY, //mp2 53
    MP2_SHY_GUY_SAYS, //mp2 54
    SNEAK_N_SNORE, //mp2 55
    //mp2 56
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
    //mp1 0
    #ifdef MP1
    MEMORY_MATCH, //mp1 0
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
    //BUMPER_BALL_MAZE_0, //mp1 27
    //BUMPER_BALL_MAZE_1, //mp1 36
    //BUMPER_BALL_MAZE_2, //mp1 48
    //BUMPER_BALL_MAZE_3, //mp1 53
    #endif
    #ifdef MK64
    MARIO_RACEWAY,
    CHOCO_MOUNTAIN,
    BOWSER_CASTLE,
    BANSHEE_BOARDWALK,
    YOSHI_VALLEY,
    FRAPPE_SNOWLAND,
    KOOPA_BEACH,
    ROYAL_RACEWAY,
    LUIGI_RACEWAY,
    MOO_MOO_FARM,
    TOADS_TURNPIKE,
    KALAMARI_DESERT,
    SHERBET_LAND,
    RAINBOW_ROAD,
    WARIO_STADIUM,
    BLOCK_FORT,
    SKYSCRAPER,
    DOUBLE_DECK,
    DK_JUNGLE,
    BIG_DONUT,
    #endif
    MINIGAME_END
};

typedef struct MinigameIndexTable {
    u8 minigameIndex; //index for string look up and id tracking
    char* minigameStr;
    u8 gameOverlayID; //actual overlay index in the game
    u8 minigameType;
    u8 gameIndex; //0 mp1, 1 mp2, 2 mp3
} MinigameIndexTable;

extern MinigameIndexTable minigameLUT[];

typedef struct mp1_GW_PLAYER {
/* 0x00 */ u8 group;
/* 0x01 */ u8 cpu_difficulty;
/* 0x02 */ u8 cpu_difficulty_copy;
/* 0x03 */ u8 port; //controller port
/* 0x04 */ u8 character;
/* 0x05 */ char unk_05; //likely padding
/* 0x06 */ u16 flags; // (flags) including CPU flag
/* 0x08 */ s16 coins; //player's current coins
/* 0x0A */ s16 coins_mg; //coins to give to player after minigame
/* 0x0C */ s16 stars;
/* 0x0E */ s16 cur_chain;
/* 0x10 */ u16 cur_space;
/* 0x12 */ u16 next_chain;
/* 0x14 */ u16 next_space;
/* 0x16 */ u8 poisoned_flag;
/* 0x17 */ u8 turn_status; //space type player landed on
/* 0x18 */ u8 player_index; //0, 1, 2, or 3
/* 0x19 */ char unk_19[3]; //likely padding
/* 0x1C */ void* process; //some heap instance
/* 0x20 */ void* player_obj; //ptr to player_obj on heap
/* 0x24 */ s16 mg_star_coins; //used for mg star
/* 0x26 */ s16 coins_total; //used for coin star
/* 0x28 */ u8 happening_count;
/* 0x29 */ u8 red_count;
/* 0x2A */ u8 blue_count;
/* 0x2B */ u8 minigame_count;
/* 0x2C */ u8 chance_count;
/* 0x2D */ u8 mushroom_count;
/* 0x2E */ u8 bowser_count;
/* 0x2F */ char unk_2F;
} mp1_GW_PLAYER; //sizeof 0x30
//P1 800F32B0, P2 800F32E0, P3 800F3310, P4 800F3340

typedef struct mp2_GW_PLAYER {
/* 0x00 */ u8 group; //for which group you belong to in a minigame
/* 0x01 */ u8 cpu_difficulty;
/* 0x02 */ u8 cpu_difficulty2; //copied from 0x01 for some reason..?
/* 0x03 */ u8 port;
/* 0x04 */ u8 character;
/* 0x05 */ char unk_05; //likely padding
/* 0x06 */ s16 flags;
/* 0x08 */ s16 coins;
/* 0x0A */ s16 coins_mg_bonus; //extra coins collected in minigame
/* 0x0C */ s16 coins_mg; //coins for winning current minigame
/* 0x0E */ s16 stars;
/* 0x10 */ s16 cur_chain_index;
/* 0x12 */ s16 cur_space_index;
/* 0x14 */ s16 next_chain_index;
/* 0x16 */ s16 next_space_index;
/* 0x18 */ char unk_18;
/* 0x19 */ s8 item;
/* 0x1A */ s8 turn_status;
/* 0x1B */ s8 player_space_color; //(color for minigame dividing)
/* 0x1C */ char unk_1C[4];
/* 0x20 */ void* unk_20;
/* 0x24 */ void* unk_24;
/* 0x28 */ s16 mg_star_coins; //used for mg star
/* 0x2A */ s16 coins_total; //used for coin star
/* 0x2C */ u8 happening_spaces_landed_on;
/* 0x2D */ u8 red_spaces_landed_on;
/* 0x2E */ u8 blue_spaces_landed_on;
/* 0x2F */ u8 chance_spaces_landed_on;
/* 0x30 */ u8 bowser_spaces_landed_on;
/* 0x31 */ u8 battle_spaces_landed_on;
/* 0x32 */ u8 item_spaces_landed_on;
/* 0x33 */ u8 bank_spaces_landed_on;
} mp2_GW_PLAYER; //sizeof 0x34
//P1 - 800FD2C0
//P2 - 800FD2F4
//P3 - 800FD328
//P4 - 800FD35C


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

typedef struct mp1_omObjData {
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
/* 0x18 */ Vec trans;
/* 0x24 */ Vec rot;
/* 0x30 */ Vec scale;
/* 0x3C */ u16 mdlcnt;
// /* 0x3E */ char unk_3E[2];
/* 0x40 */ s16* model;
/* 0x44 */ u16 mtncnt;
// /* 0x46 */ char unk_46[2];
/* 0x48 */ s16* motion;
/* 0x4C */ u8 work[4];
/* 0x50 */ void* unk_50;
} mp1_omObjData; //sizeof 0x54

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

typedef struct omOvlHisData { //Object Manager History Data
/* 0x00 */ s32 overlayID;
/* 0x04 */ s16 event;
/* 0x06 */ u16 stat;
} omOvlHisData; //sizeof 0x08

extern mp2_GW_PLAYER mp2_GwPlayer[4];
extern mp1_GW_PLAYER mp1_GwPlayer[4];

typedef struct EepData {
/* 0x00 */ u8 minigameFlags[0x18];
/* 0x18 */ u8 teamModeFlag; //used for setting bits in player structs on board start for team mode (TODO: implement)
/* 0x19 */ u8 force2v2Minigame; //if teams mode is active, this will force 2v2 minigames every turn from all 3 mario parties
/* 0x1A */ u8 preventMinigameCoinLoss; //for mp1. in games where coins are the focus (ex bash n cash) coins will still be lost
/* 0x1B */ u8 mp3UnlockedPartyBoards;
/* 0x1C */ u8 mp3UnlockedDuelBoards;
/* 0x1D */ char pad[0x123];
} EepData __attribute__((aligned(16))); //sizeof 0x140

extern EepData customEepromData;

extern u8 mp2_debugMode;
extern s32 eepromLoadFailed;
extern s32 isMidTurnMinigame;
extern s32 ForeignMinigameIndexToLoad;

s32 ForeignMinigameIsMidTurnMinigame(s32);
u16 func_8000B838_C438(s32);
s16 mp3_InitEspriteSlot(s16, s32, s32);                     /* extern */
void crash_screen_init(void);
void infiniteLoop(void);
void WaitForSubSystems(void);
s32 ForeignMinigameIDToGame(s32 minigameCombinedIndex);
NORETURN void ComboSwitchGameToMp2(void);
NORETURN void ComboSwitchGameToMp1(void);
extern s32 ForeignMinigameAlreadyLoaded;
extern s32 GetMinigameFlag(s32 arg0);
extern s32 CurBaseGame;

enum {
    MP1_BASE = 0,
    MP2_BASE = 1,
    MP3_BASE = 2,
};

NORETURN void ComboSwitchGameToMp3(void);
void LoadMp3PlayerCopyToMp2(void);

//static symbols get stripped from the map file which is annoying
#ifdef DEBUG
#define STATIC
#else
#define STATIC static
#endif

#endif //_MP_H_