#include "marioparty.h"
#include "mp3.h"
#include "mp2.h"
#include "mp1.h"

enum {
    OPT_RACE_MODE = 0, //works
    OPT_GP_CUP,   //works
    OPT_GP_ROUND, //works but game doesn't init properly
    OPT_COURSE,   //only works in TT; pause screen shows Luigi Raceway
    OPT_PLAYERS,  //works
    OPT_DRIVER1,  //works
    OPT_DRIVER2,
    OPT_DRIVER3,
    OPT_DRIVER4,
    OPT_CLASS,  //works
    OPT_MIRROR, //works
    OPT_ITEMS,  //not implemented (need to patch item box loader)
    OPT_MUSIC,  //not implemented
    OPT_DEBUG,  //works
    NUM_OPTIONS
};

enum {
    SCREEN_MODE_1P,
    SCREEN_MODE_2P_HORZ, //normal 2P mode
    SCREEN_MODE_2P_VERT, //unused vertical 2P mode
    SCREEN_MODE_4P //also used for 3P, the 4th part shows map
} ScreenModes;

typedef enum {
    /* 0x00 */ COURSE_MARIO_RACEWAY = 0,
    /* 0x01 */ COURSE_CHOCO_MOUNTAIN,
    /* 0x02 */ COURSE_BOWSER_CASTLE,
    /* 0x03 */ COURSE_BANSHEE_BOARDWALK,
    /* 0x04 */ COURSE_YOSHI_VALLEY,
    /* 0x05 */ COURSE_FRAPPE_SNOWLAND,
    /* 0x06 */ COURSE_KOOPA_BEACH,
    /* 0x07 */ COURSE_ROYAL_RACEWAY,
    /* 0x08 */ COURSE_LUIGI_RACEWAY,
    /* 0x09 */ COURSE_MOO_MOO_FARM,
    /* 0x0A */ COURSE_TOADS_TURNPIKE,
    /* 0x0B */ COURSE_KALAMARI_DESERT,
    /* 0x0C */ COURSE_SHERBET_LAND,
    /* 0x0D */ COURSE_RAINBOW_ROAD,
    /* 0x0E */ COURSE_WARIO_STADIUM,
    /* 0x0F */ COURSE_BLOCK_FORT,
    /* 0x10 */ COURSE_SKYSCRAPER,
    /* 0x11 */ COURSE_DOUBLE_DECK,
    /* 0x12 */ COURSE_DK_JUNGLE,
    /* 0x13 */ COURSE_BIG_DONUT,
    /* 0x14 */ COURSE_AWARD_CEREMONY,
    /* 0x15 */ NUM_COURSES
} COURSES;

#define NUM_RACERS  8
#define MAX_PLAYERS 4

#define RACE_GP 0
#define RACE_TIME_TRIAL 1
#define RACE_VS 2
#define RACE_BATTLE 3

enum MK64Players {
    MK_PLAYER_MARIO = 0,
    MK_PLAYER_LUIGI = 1,
    MK_PLAYER_YOSHI = 2,
    MK_PLAYER_TOAD = 3,
    MK_PLAYER_DK = 4,
    MK_PLAYER_WARIO = 5,
    MK_PLAYER_PEACH = 6,
    MK_PLAYER_BOWSER = 7,
};

enum Mp64Players {
    MP_PLAYER_MARIO = 0,
    MP_PLAYER_LUIGI = 1,
    MP_PLAYER_PEACH = 2,
    MP_PLAYER_YOSHI = 3,
    MP_PLAYER_WARIO = 4,
    MP_PLAYER_DK = 5,
    MP_PLAYER_WALUIGI = 6,
    MP_PLAYER_DAISY = 7,
};

typedef struct MpToMkMapping {
    u8 mpCharacterIndex; //mario party character ID
    u8 mkCharacterIndex; //mario kart 64 character ID
} MpToMkMapping;

MpToMkMapping playersMapping[] = {
    {MP_PLAYER_MARIO,   MK_PLAYER_MARIO},
    {MP_PLAYER_LUIGI,   MK_PLAYER_LUIGI},
    {MP_PLAYER_PEACH,   MK_PLAYER_PEACH},
    {MP_PLAYER_YOSHI,   MK_PLAYER_YOSHI},
    {MP_PLAYER_WARIO,   MK_PLAYER_WARIO},
    {MP_PLAYER_DK,      MK_PLAYER_DK},
    //these characters are impossible to be selected by a player
    {MP_PLAYER_WALUIGI, -1},
    {MP_PLAYER_DAISY,   -1},
};

enum RaceClass {
    RACE_50_CC = 0,
    RACE_100_CC = 1,
    RACE_150_CC = 2,
    RACE_EXTRA = 3
};


extern int numPlayers;
extern int screenMode;
extern int screenSplitMode;
extern s8 debugMenuScreenMode;
extern s8 debugMenuNumPlayers;
extern int raceType; //0=GP 1=Time Trial 2=VS 3=Battle
extern int gpMode_currentCupDisp;
extern s16 gpMode_currentCup;
extern s16 gpMode_currentRound; //0 to 3; also cup selected in menu
extern s16 curCourse;
extern s8 playerCharacter[MAX_PLAYERS];
extern int raceClass; //0=50cc 1=100cc 2=150cc 3=Extra
extern s16 isMirrorMode;
extern u16 debugMode; //1=on
extern s16 debugCoordDisplay; //1=on, requires debug mode
extern s16 debugResourceMeters; //1=on, requires debug mode
extern int mainThreadTask;

//will need to make mario party IDs to mk64 IDs. this is the list order
static const char *characterNames[] = {
    "Mario", "Luigi", "Yoshi", "Toad", "DK", "Wario", "Peach", "Bowser"
};

static struct {
    int min, max;
    int value;
    u8 dispModes; //bitmask: 01=GP 02=TT 04=VS 08=Battle
    const char *text;
    const char **names;
} options[] = {
    {0,  3, 0, 0xF, "Race Mode",   NULL},
    {0,  3, 0, 0x1, "GP Cup",      NULL},
    {0,  3, 0, 0x0, "GP Round",    NULL}, //XXX
    {0, 19, 0, 0xE, "Course",      NULL},
    {0,  4, 0, 0xD, "Players",     NULL},
    {0,  7, 0, 0xF, "Player 1",    NULL},
    {0,  7, 1, 0xD, "Player 2",    NULL},
    {0,  7, 2, 0xC, "Player 3",    NULL},
    {0,  7, 3, 0xC, "Player 4",    NULL},
    {0,  3, 2, 0xF, "Class",       NULL}, //default to 150cc
    {0,  1, 0, 0xF, "Mirror Mode", NULL},
    {0,  1, 1, 0x0, "Items",       NULL}, //XXX (patch item box function?)
    {0,  1, 1, 0x0, "Music",       NULL}, //XXX
    {0,  1, 0, 0xF, "Debug Mode",  NULL},
    //XXX other settings from that competition hack
    //L to reset/quit
    {0,  0, NULL, NULL, NULL}
};

extern s32 gGlobalTimer;

s32 GetHumanPlayerTotal(void) {
    s32 i;
    s32 totalHumanPlayers = 0;
    
    //if not CPU, add to totalPlayers
    if (CurBaseGame == MP1_BASE) {
        for (i = 0; i < 4; i++) {
            if (!(mp1_PlayersCopy[i].flags & 1)) {
                totalHumanPlayers++;
            }
        }
    } else if (CurBaseGame == MP2_BASE) {
        for (i = 0; i < 4; i++) {
            if (!(mp2_PlayersCopy[i].flags & 1)) {
                totalHumanPlayers++;
            }
        }
    } else if (CurBaseGame == MP3_BASE) {
        for (i = 0; i < 4; i++) {
            if (!(mp3_PlayersCopy[i].flags1 & 1)) {
                totalHumanPlayers++;
            }
        }
    }
    return totalHumanPlayers;
}

u8 GetMkCharacterEquivalent(s32 mpCharacterID) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (playersMapping[i].mpCharacterIndex == mpCharacterID) {
            return playersMapping[i].mkCharacterIndex;
        }
    }
    return 0xFF; //character not found, this should never happen
}

//map mp character IDs -> mk64 character IDs
//is there a better way to do this?
void SetMk64Players(void) {
    u8 convertedCharacterIDs[4] = {0, 0, 0, 0};
    s32 i;

    if (CurBaseGame == MP1_BASE) {
        for (i = 0; i < 4; i++) {
            convertedCharacterIDs[i] = GetMkCharacterEquivalent(mp1_PlayersCopy[i].character);
        }
    } else if (CurBaseGame == MP2_BASE) {
        for (i = 0; i < 4; i++) {
            convertedCharacterIDs[i] = GetMkCharacterEquivalent(mp2_PlayersCopy[i].character);
        }
    } else if (CurBaseGame == MP3_BASE) {
        for (i = 0; i < 4; i++) {
            convertedCharacterIDs[i] = GetMkCharacterEquivalent(mp3_PlayersCopy[i].characterID);
        }
    }

    //write mk64 equivalent of mario party character IDs
    for (i = 0; i < 4; i++) {
        playerCharacter[i] = convertedCharacterIDs[i];
    }
}

void checkCourseLoadFromBoot(void) {
    //only run this a single time, check the frame counter to make sure of that
    if (gGlobalTimer > 15) {
        return;
    }

    //numPlayers = GetHumanPlayerTotal();
    numPlayers = 4;

    //set numPlayers and screenMode
    switch(numPlayers) {
        case 0: //requires at least 1 human player. if 0 valid players are found, default to 1
        case 1:
            numPlayers = 1;
            screenMode = SCREEN_MODE_1P;
            break;
        case 2:
            numPlayers = 2;
            screenMode = SCREEN_MODE_2P_HORZ;
            break;
        // case 2:
        //     numPlayers = 2;
        //     screenMode = SCREEN_MODE_2P_VERT;
        //     break;
        case 3:
            numPlayers = 3;
            screenMode = SCREEN_MODE_4P;
            break;
        case 4:
            numPlayers = 4;
            screenMode = SCREEN_MODE_4P;
            break;
    }

    //set other game parameters
    screenSplitMode       = screenMode;
    debugMenuScreenMode   = screenMode; //this might be the actual screen mode...
    //numPlayers2           = numPlayers;
    debugMenuNumPlayers   = numPlayers;
    raceType              = RACE_VS;
    gpMode_currentCupDisp = options[OPT_GP_CUP   ].value; //shown at race start
    gpMode_currentCup     = options[OPT_GP_CUP   ].value; //actually selects cup
    gpMode_currentRound   = options[OPT_GP_ROUND ].value;
    curCourse             = options[OPT_COURSE   ].value;
    SetMk64Players();

    raceClass             = RACE_150_CC;
    isMirrorMode          = FALSE;
    //XXX items, music
    debugMode             = options[OPT_DEBUG    ].value;
    debugCoordDisplay     = debugMode;
    debugResourceMeters   = debugMode;

    if (gGlobalTimer == 2) {
        mainThreadTask = 4; //start game
    }
}