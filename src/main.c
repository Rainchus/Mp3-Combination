#include "marioparty.h"
#include "mp3.h"

#define COLD_BOOT 0
#define WARM_BOOT 1
#define osAppNmiBufferSize 64

//in the eeprom, 0x2C0 through 0x400 is free to use
u16 mp3_BattleMinigameCoins_Copy = 0;

u8 CustomMinigamesEepromBytes[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F
};

void func_80108910_119290(s32, s32, char*);
void checkIfLoadingFromMp2Minigame(s32 overlayID, s16 event, s16 stat);
s32 WriteEepromCustom(void);
void func_8005D294_5DE94(s16);
u32 func_80106B38_4F9028(s32);
u16 func_8000B838_C438(s32);
extern s32 GetMinigameFlag(s32 arg0);

extern u16 mp2_BattleMinigameCoins;
extern s32 isBattleMinigame;
s32 printTimer = 0;
s32 eepromLoadFailed = 0;
//also prevents wacky watches from being found from this point on if not 0
s32 wackyWatchUsedCopy = 0;
extern mp3MinigameIndexTable minigameLUT[];
extern s16 D_800CD0AA;

extern mp2_GW_PLAYER mp2_PlayersCopy[4];
extern u8 osAppNmiBuffer[osAppNmiBufferSize];

extern omOvlHisData mp2_omovlhis[12];
extern s16 mp2_omovlhisidx;
extern s8 D_800B23B0;

extern s16 D_800D6B60;
extern omOvlHisData D_800D20F0[];



//mp3 board state and copy (BOARD_STATE_STRUCT_SIZE isn't known what exact size we need)
u8 mp3_BoardStateCopy[BOARD_STATE_STRUCT_SIZE] = {0};
u8 mp3_prevMinigamesPlayedCopy[PREV_MINIGAMES_PLAYED_SIZE] = {0};

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

void PushMp3MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp3_prevMinigamesPlayedCopy[i] = mp3_prevMinigamesPlayed[i];
    }
}

void PopMp3MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp3_prevMinigamesPlayed[i] = mp3_prevMinigamesPlayedCopy[i];
    }
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
        mp2_gPlayers[i].turn_status = mp3_PlayersCopy[i].turn_status;
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
    //wackyWatchUsedCopy = D_800CD0AA;
    //800F9310 sets D_800CD0AA to 3 when a watch has been used and when loading into a minigame
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

void StoreBattleMinigameCoins(void) {
    mp3_BattleMinigameCoins_Copy = mp3_BattleMinigameCoins;
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

// u8 new4PMinigameListNormalMp3[] = {
//     TREADMILL_GRILL,        TOADSTOOL_TITAN,    ACES_HIGH,      BOUNCE_N_TROUNCE,       ICE_RINK_RISK,
//     CHIP_SHOT_CHALLENGE,    PARASOL_PLUMMET,    MESSY_MEMORY,   PICTURE_IMPERFECT,      MARIOS_PUZZLE_PARTY,
//     THE_BEAT_GOES_ON,       MPIQ,               CURTAIN_CALL,   WATER_WHIRLED,          FRIGID_BRIDGES,
//     AWFUL_TOWER,            CHEEP_CHEEP_CHASE,  PIPE_CLEANERS,  SNOWBALL_SUMMIT,        ROCKIN_RACEWAY,
//     //mp2 minigame
//     LAVA_TILE_ISLE, MP2_HOT_ROPE_JUMP, SHELL_SHOCKED, TOAD_IN_THE_BOX, MECHA_MARATHON,
//     ROLL_CALL, ABANDON_SHIP, MP2_PLATFORM_PERIL, TOTEM_POLE_POUND, MP2_BUMPER_BALLS, 
//     MP2_BOMBS_AWAY, MP2_TIPSY_TOURNEY, HONEYCOMB_HAVOC, HEXAGON_HEAT, MP2_SKATEBOARD_SCAMPER,
//     MP2_SLOT_CAR_DERBY, MP2_SHY_GUY_SAYS, SNEAK_N_SNORE, DIZZY_DANCING, TILE_DRIVER,
//     DEEP_SEA_SALVAGE,
//     //mp1 minigames
//     #ifdef MP1
//     BURIED_TREASURE, TREASURE_DIVERS, MP1_HOT_BOB_OMB, MUSICAL_MUSHROOM, MP1_CRAZY_CUTTER,
//     MP1_FACE_LIFT, MP1_BALLOON_BURST, COIN_BLOCK_BLITZ, MP1_SKATEBOARD_SCAMPER, BOX_MOUNTAIN_MAYHEM,
//     MP1_PLATFORM_PERIL, MUSHROOM_MIXUP, MP1_GRAB_BAG, MP1_BUMPER_BALLS, MP1_TIPSY_TOURNEY,
//     MP1_BOMBS_AWAY, MARIO_BANDSTAND, MP1_SHY_GUY_SAYS, CAST_AWAYS, KEY_PA_WAY,
//     RUNNING_OF_THE_BULB, MP1_HOT_ROPE_JUMP, HAMMER_DROP, MP1_SLOT_CAR_DERBY,
//     #endif
//     0xFF
// };

// u8 new1v3MinigameListNormalMp3[] = {
//     HAND_LINE_AND_SINKER,   COCONUT_CONK,       SPOTLIGHT_SWIM, BOULDER_BALL,   CRAZY_COGS,
//     HIDE_AND_SNEAK,         RIDICULOUS_RELAY,   THWOMP_PULL,    RIVER_RAIDERS,  TIDAL_TOSS,
//     //mp2 minigames
//     MP2_BOWL_OVER, MP2_CRANE_GAME, MOVE_TO_THE_MUSIC, BOB_OMB_BARRAGE, LOOK_AWAY,
//     SHOCK_DROP_OR_ROLL, LIGHTS_OUT, FILET_RELAY, ARCHERIVAL, QUICKSAND_CACHE,
//     RAINBOW_RUN,
//     //mp1 minigames
//     #ifdef MP1
//     PIPE_MAZE, BASH_N_CASH, MP1_BOWL_OVER, COIN_BLOCK_BASH, TIGHTROPE_TREACHERY,
//     MP1_CRANE_GAME, PIRANHA_PURSUIT, TUG_O_WAR, PADDLE_BATTLE, COIN_SHOWER_FLOWER,
//     #endif
//     0xFF
// };
// u8 new2v2MinigameListNormalMp3[] = {
//     EATSA_PIZZA,    BABY_BOWSER_BROADSIDE,  PUMP_PUMP_AND_AWAY,     HYPER_HYDRANTS, PICKING_PANIC,
//     COSMIC_COASTER, PUDDLE_PADDLE,          ETCH_N_CATCH, LOG_JAM,  SLOT_SYNC,

//     //mp2 minigames
//     TOAD_BANDSTAND, MP2_BOBSLED_RUN, MP2_HANDCAR_HAVOC, MP2_BALLOON_BURST, SKY_PILOTS,
//     SPEED_HOCKEY, CAKE_FACTORY, MAGNET_CARTA, LOONEY_LUMBERJACKS, TORPEDO_TARGETS,
//     DESTRUCTION_DUET, DUNGEON_DASH,
//     //mp1 minigames
//     #ifdef MP1
//     MP1_BOBSLED_RUN, DESERT_DASH, BOMBSKETBALL, MP1_HANDCAR_HAVOC, DEEP_SEA_DIVERS,
//     #endif
//     0xFF
// };
// u8 newBattleMinigameListNormalMp3[] = {
//     LOCKED_OUT, ALL_FIRED_UP, STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP,
//     SLAP_DOWN, STORM_CHASERS, EYE_SORE,
//     //issues with mp2 battle minigames atm
//     // MP2_GRAB_BAG, BUMPER_BALLOON_CARS, RAKIN_EM_IN, DAY_AT_THE_RACES, MP2_FACE_LIFT,
//     // MP2_CRAZY_CUTTERS, MP2_HOT_BOB_OMB, BOWSERS_BIG_BLAST,
//     0xFF
// };
// u8 newItemMinigameListNormalMp3[] = {
//     //no mp2 minigames currently for these
//     WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS,
//     SWING_N_SWIPE,
//     //issues with mp2 item minigames atm
//     0xFF
// };
// u8 newDuelMinigameListNormalMp3[] = {
//     VINE_WITH_ME, POPGUN_PICK_OFF, END_OF_THE_LINE, BABY_BOWSER_BONKERS, SILLY_SCREWS,
//     CROWD_COVER, TICK_TOCK_HOP, BOWSER_TOSS, MOTOR_ROOTER, FOWL_PLAY,
//     0xFF
// };

u8 new4PMinigameListNormalMp3[66] = {0};
u8 new1v3MinigameListNormalMp3[32] = {0};
u8 new2v2MinigameListNormalMp3[28] = {0};
u8 newBattleMinigameListNormalMp3[17] = {0};
u8 newItemMinigameListNormalMp3[7] = {0};
u8 newDuelMinigameListNormalMp3[11] = {0};
u8 newCategoryAmountsNormal[6] = {0};

//the blacklisted minigames below are blacklisted due to having issues loading them...
//once this is fixed this can be removed
u8 battleMinigameBlacklist[] = {
    MP2_GRAB_BAG, BUMPER_BALLOON_CARS, RAKIN_EM_IN, DAY_AT_THE_RACES, MP2_FACE_LIFT,
    MP2_CRAZY_CUTTERS, MP2_HOT_BOB_OMB, BOWSERS_BIG_BLAST
};

u8 duelMinigameBlacklist[] = {
    PIRATE_LAND_DUEL, WESTERN_LAND_DUEL, SPACE_LAND_DUEL, MYSTERY_LAND_DUEL, HORROR_LAND_DUEL,
    KOOPA_LAND_DUEL
};

u8 itemMinigameBlacklist[] = {
    ROLL_OUT_THE_BARRELS, GIVE_ME_A_BRAKE, HAMMER_SLAMMER, MALLET_GO_ROUND, COFFIN_CONGESTION,
    BOWSER_SLOTS
};

u8 minigame4PBlacklist[] = {
    YOSHIS_TONGUE_MEETING
};

// u8 minigame1v3Blacklist[] = {
//     COIN_SHOWER_FLOWER
// };

//at 80100EEC originally (normal minigame list, amount of minigames in each category)
// u8 newCategoryAmountsNormal[] = {
//     ARRAY_COUNT(new4PMinigameListNormalMp3) -1,
//     ARRAY_COUNT(new1v3MinigameListNormalMp3) -1,
//     ARRAY_COUNT(new2v2MinigameListNormalMp3) -1,
//     ARRAY_COUNT(newItemMinigameListNormalMp3) -1,
//     ARRAY_COUNT(newBattleMinigameListNormalMp3) -1,
//     ARRAY_COUNT(newDuelMinigameListNormalMp3) -1,
// };

void checkIfLoadingFromMp2Minigame(s32 overlayID, s16 event, s16 stat) {
    mp3MinigameIndexTable* curMinigameData;
    s8 curTurn;
    s8 totalTurns;
    s8 curBoardIndex;
    s32 i, j;
    s32 eepromByteResults = 0;
    u8 minigame4PCount = 0;
    u8 minigame1v3Count = 0;
    u8 minigame2v2Count = 0;
    u8 minigameItemCount = 0;
    u8 minigameBattleCount = 0;
    u8 minigameDuelCount = 0;
    // u8 minigameGameGuyCount = 0;
    // u8 minigame1PCount = 0;
    s32 minigameIsBlacklisted;
    s32 eepresult = 0;

    for (i = 0; i < ARRAY_COUNT(newCategoryAmountsNormal); i++) {
        newCategoryAmountsNormal[i] = 0;
    }
    
    if (eepromLoadFailed == 1) {
        mp3_omOvlCallEx(0, 0, 0);
        return;
    }

    eepresult = mp3_osEepromLongRead(&mp3_D_800CE1A0, EEPROM_BLOCK_POS, customEepromData, sizeof(customEepromData));

    if (eepresult == CONT_NO_RESPONSE_ERROR) {
        while (1) {
            mp3_DrawDebugText(20, 212, "EEPROM CONT_NO_RESPONSE_ERROR");
            mp3_HuPrcVSleep();
        }
    } else if (eepresult == -1) {
        while (1) {
            mp3_DrawDebugText(20, 212, "EEPROM INVALID ADDRESS");
            mp3_HuPrcVSleep();
        }
    }

    //otherwise, result was zero and the eeprom read happened correctly
    mp3_HuPrcVSleep();
    for (i = 0; i < 0x18; i++) {
        eepromByteResults += customEepromData[i];
    }

    if (eepromByteResults == 0) {
        for (i = 0; i < 0x18; i++) {
            customEepromData[i] = CustomMinigamesEepromBytes[i];
        }
        //no idea what any of these args do
        char sp10[16] = {0};
        s16 temp = 0x20; 

        //why is it required you do this this way?
        //and why only when writing? reading works fine?
        mp3_RequestSIFunction(&sp10, &WriteEepromCustom, &temp, 1);
        mp3_HuPrcVSleep();
    }

    //load active minigames into lists
    for (i = 0; i < MINIGAME_END - 1; i++) {
        
        for (j = 0, curMinigameData = 0; j < MINIGAME_END - 1; j++) {
            if (i == minigameLUT[j].minigameIndex) {
                curMinigameData = &minigameLUT[j];
                break;
            }
        }

        //minigame was not found in list (??), continue loop
        if (curMinigameData == 0) {
            continue;
        }

        //else, minigame is active
        u8 minigameActiveFlag = GetMinigameFlag(curMinigameData->minigameIndex);
        if (minigameActiveFlag == 0) {
            continue;
        }

        switch(curMinigameData->minigameType) {
        case PLAYERS_4P:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(minigame4PBlacklist); j++) {
                if (curMinigameData->minigameIndex == minigame4PBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                new4PMinigameListNormalMp3[minigame4PCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormal[PLAYERS_4P]++;
            }
            break;
        case PLAYERS_1V3:
            // minigameIsBlacklisted = 0;
            // for (j = 0; j < ARRAY_COUNT(minigame1v3Blacklist); j++) {
            //     if (curMinigameData->minigameIndex == minigame1v3Blacklist[j]) {
            //         minigameIsBlacklisted = 1;
            //         break;
            //     }
            // }
            // if (minigameIsBlacklisted == 0) {
            //     new1v3MinigameListNormalMp3[minigame1v3Count++] = curMinigameData->minigameIndex;
            //     newCategoryAmountsNormal[PLAYERS_1V3]++;
            // }
            new1v3MinigameListNormalMp3[minigame1v3Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormal[PLAYERS_1V3]++;
            break;
        case PLAYERS_2V2:
            new2v2MinigameListNormalMp3[minigame2v2Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormal[PLAYERS_2V2]++;
            break;
        case PLAYERS_ITEM:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(itemMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == itemMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newItemMinigameListNormalMp3[minigameItemCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormal[PLAYERS_ITEM]++;
            }
            
            break;
        case PLAYERS_BATTLE:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(battleMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == battleMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newBattleMinigameListNormalMp3[minigameBattleCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormal[PLAYERS_BATTLE]++;
            }

            break;
        case PLAYERS_DUEL:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(duelMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == duelMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newDuelMinigameListNormalMp3[minigameDuelCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormal[PLAYERS_DUEL]++;
            }
            break;
        case PLAYERS_GAME_GUY:
            break;
        case PLAYERS_1P:
            break;
        }
    }

    if (mp3_LoadBackFromMp2 == TRUE) {
        mp3_LoadBackFromMp2 = FALSE;
        PopMp3BoardState();
        PopMp3MinigamesPlayedList();
        LoadMp3PlayerStructs();

        
        if (wackyWatchUsedCopy == 2) {
            wackyWatchUsedCopy = 3;
            //set turns as if wacky watch was used
            mp3_BoardState[3] = mp3_BoardState[2] - 4;
        }

        D_800CD0AA = wackyWatchUsedCopy;

        curTurn = mp3_BoardState[3];
        totalTurns = mp3_BoardState[2];
        curBoardIndex = mp3_BoardState[1];

        mp3_D_800B1A30 = 1; //set that there is at least 1 controller active
        D_800B23B0 = 1; //is party mode
        // if (isBattleMinigame == 1) {
        //     s32 i;
        //     isBattleMinigame = 0;

        //     omOvlHisData BattleResults[] = {
        //         {0x70, 0x0001, 0x0192},
        //         {0x53, 0x0000, 0x0192},
        //         {0x48, 0x0000, 0x0192},
        //     };
        //     for (i = 0; i < ARRAY_COUNT(BattleResults); i++) {
        //         mp3_omovlhis[i] = BattleResults[i];
        //     }
        //     mp3_omovlhisidx = 3;
        //     mp3_omOvlCallEx(0x74, 0, 0x12); //go to battle results scene
        //     return;
        // }
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
    // if ((printTimer == 0) && mp3_D_800CDA7C[0] & 0x10) {
    //     ForeignMinigameIndexToLoad = -1;
    //     ComboSwitchGameToMp2();
    //     return;
    // }
    // // if L is held on boot, load mp1
    // if ((printTimer == 0) && mp3_D_800CDA7C[0] & 0x20) {
    //     ForeignMinigameIndexToLoad = -1;
    //     ComboSwitchGameToMp1();
    //     return;
    // }
    // // if Z is held on boot, load minigame selection screen
    // if ((printTimer == 0) && mp3_D_800CDA7C[0] & 0x2000) {
    //     ForeignMinigameIndexToLoad = -1;
    //     mp3_omOvlCallEx(0, 0, 0);
    //     return;
    // }
    if (printTimer < 120) {
        printTimer++;
        
        mp3_debug_font_color = 4;
        mp3_DrawDebugText(20, 212, "MOD BY: RAINCHUS VERSION 0.1.7");
        mp3_DrawDebugText(20, 221, "IF YOU WOULD LIKE TO SUPPORT MY WORK:");
        mp3_DrawDebugText(20, 230, "HTTPS://KO-FI.COM/RAINCHUS");
    }
}

void func_80107730_4F9C20_Copy(s32 arg0, s32 messageID) {
    //i wanted to make this a choice textbox, but that's tricky
    //for now, it will say loading mario party 2 and then sleep for 1 second and load

    // char newMessage[] = {"\x0B""Loading Mario Party 2""\xFF"};
    // char newMessage[] = {"\x0B""Huh""\xC3"" Do you want to swap to Mario Party 2""\xC3""\xFF"};
    // char newMessage[] = {"\x0B""Huh" "\xC3" " Do you want to swap to\nMario Party 2" "\xC3" "\x0C Yes\x0D   \x0C No\x0D"};
    u32 temp_v0; //pointer to message

    //Huh? My suggestion? textbox
    // if (messageID == 0x3125) {
    //     mp3_func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, newMessage, -1, -1);
    //     ForeignMinigameIndexToLoad = -1;
    //     mp3_HuPrcSleep(30);
    //     ComboSwitchGameToMp2();
    //     return;
    // }

    func_8005D294_5DE94(mp3_D_80110998[arg0].unk_00);

    if (mp3_D_80110998[arg0].unk_04 != 0) {
        mp3_func_80019C00_1A800(mp3_D_80110998[arg0].unk_04);
        mp3_D_80110998[arg0].unk_04 = 0;
    }

    temp_v0 = func_80106B38_4F9028(messageID);

    //pointer check
    if (temp_v0 > 0x80000000U) {
        mp3_D_80110998[arg0].unk_04 = temp_v0;
    }

    mp3_func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, (char*)temp_v0, -1, -1);
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

