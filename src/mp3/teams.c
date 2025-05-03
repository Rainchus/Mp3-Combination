#include "marioparty.h"
#include "ovl_80.h"
#include "mp3.h"

#define HUNDREDS 0
#define TENS 1
#define ONES 2
#define DIGIT_X 10

#define COINS_HUNDREDS_DIGIT 4
#define COINS_TENS_DIGIT 5
#define COINS_ONES_DIGIT 6

#define STARS_TENS_DIGIT 7
#define STARS_ONES_DIGIT 8
#define COM_ICON 9

#define ITEMS_POS_OFFSET_X 56
#define ITEMS_POS_OFFSET_Y 19

#define X_OFFSET 35
#define Y_OFFSET 0

s32 GetMinigameCategoryForEndTurnMinigame(void);
void originalShowPlayerCoinChange(s32 player, s32 coins);

s16 PlayerIconPositions[][2] = {
{0x0000, 0x0000},
{0x0000, 0x0000},
{0x0026, 0x0007},
{0x0026, 0xFFF7},
{0x0033, 0x000A},
{0x003D, 0x000A},
{0x0047, 0x000A},
{0x0033, 0xFFFA},
{0x003D, 0xFFFA},
{0xFFEC, 0x000E},
{0xFFD3, 0x0000},

//items
//team0 items xy positions
{0x0003, 0x0017}, //item 0
{0x0014, 0x0017}, //item 1
{0x0025, 0x0017}, //item 2
{0x0036, 0x0017}, //item 3
{0x0047, 0x0017}, //item 4

//team1 items xy positions
{0x0003, 0x0017}, //item 0
{0x0014, 0x0017}, //item 1
{0x0025, 0x0017}, //item 2
{0x0036, 0x0017}, //item 3
{0x0047, 0x0017}, //item 4
};

s16 OriginalTeamRootPositions[][2] = {
    0x0018, 0x0010,
    0x00BF, 0x0010,
    0x0018, 0x00BA,
    0x00BF, 0x00BA
};

s16 newTeamRootPositions[][2] = {
    // 0x0018, 0x0010,
    // 0x00BF, 0x0010,
    // 0x0018, 0x00BA,
    // 0x00BF, 0x00BA
};

s16 newTeam0RootPositions[][2] = {
    0x0010, 0x0010, //team0 player 0
    0x001C, 0x0011, //team0 player 1
};

s16 newTeam1RootPositions[][2] = {
    0x00A0, 0x0010, //team1 player 0
    0x00AC, 0x0011, //team1 player 1
};

void checkSetTeamMode(void) {
    if (customEepromData.teamModeFlag == 1) {
        s32 i;
        //assign team 0
        for (i = 0; i < 2; i++) {
            mp3_gPlayers[i].flags1 |= 0x10;
        }

        for (i = 2; i < 4; i++) {
            mp3_gPlayers[i].flags1 |= 0x20;
        }

    }
}

s32 get_team_index(mp3_GW_PLAYER* player) {
    return (player->flags1 & 0x30) >> 5; //returns team index 0 or 1
}

s32 GetCurrentPlayerScore(s32 arg0) {
    return mp3_gPlayers[arg0].stars * 1000 + mp3_gPlayers[arg0].coins;
}

//i believe the code assumes that the first team0 member is player index 0. this should mask that problem
void setTeamsHack(void) {
    s32 i;
    if (mp3_gPlayers[0].flags1 & 0x30) {
        //if player index 0 is not on team0, flip the teams
        if (!(mp3_gPlayers[0].flags1 & 0x10)) {
            for (i = 0; i < 4; i++) {
                if ((mp3_gPlayers[i].flags1 & 0x10)) {
                    mp3_gPlayers[i].flags1 = (mp3_gPlayers[i].flags1 & ~0xF0) | 0x20; // Change 0x10 to 0x20
                } else if ((mp3_gPlayers[i].flags1 & 0x20)) {
                    mp3_gPlayers[i].flags1 = (mp3_gPlayers[i].flags1 & ~0xF0) | 0x10; // Change 0x20 to 0x10
                }
            }            
        }
    }
    mp3_func_800F453C();
}

void checkColorSet_C_2(u32 playerIndex, s32 turnStatus) {
    RGB team0Color = {0x00, 0x00, 0xC0}; //blue
    RGB team1Color = {0xC0, 0x00, 0x00}; //red
    //if not teams, do normal colors
    if ((mp3_gPlayers[0].flags1 & 0x30) == 0) {
        func_80055420_56020(D_801057E0_119400_shared_board[playerIndex].playerIndex, 0, D_8010188C_1154AC_shared_board[turnStatus].r, D_8010188C_1154AC_shared_board[turnStatus].g, D_8010188C_1154AC_shared_board[turnStatus].b);
        D_801057E0_119400_shared_board[playerIndex].spaceType = turnStatus;
        return;
    }

    if (playerIndex < MAX_PLAYERS) {
        s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
        if (curPlayerTeamIndex == 0) {
            func_80055420_56020(D_801057E0_119400_shared_board[playerIndex].playerIndex, 0, team0Color.r, team0Color.g, team0Color.b);
        } else {
            func_80055420_56020(D_801057E0_119400_shared_board[playerIndex].playerIndex, 0, team1Color.r, team1Color.g, team1Color.b);
        }
        D_801057E0_119400_shared_board[playerIndex].spaceType = turnStatus;
    }    
}

void checkColorSet_C_1(u32 playerIndex, s32 turnStatus) {
    //if teams is on, exit
    if (mp3_gPlayers[0].flags1 & 0x30) {
        return;
    }
    //otherwise it's normal 4p, allow color setting
    if (playerIndex < MAX_PLAYERS) {
        func_80055420_56020(D_801057E0_119400_shared_board[playerIndex].playerIndex, 0, D_8010188C_1154AC_shared_board[turnStatus].r, D_8010188C_1154AC_shared_board[turnStatus].g, D_8010188C_1154AC_shared_board[turnStatus].b);
        D_801057E0_119400_shared_board[playerIndex].spaceType = turnStatus;
    }    
}

void newfunc_800F4798_1083B8_shared_board(u32 playerIndex, s32 turnStatus) {
    // if (playerIndex < MAX_PLAYERS) {
    //     func_80055420_56020(D_801057E0_119400_shared_board[playerIndex].playerIndex, 0, D_8010188C_1154AC_shared_board[turnStatus].r, D_8010188C_1154AC_shared_board[turnStatus].g, D_8010188C_1154AC_shared_board[turnStatus].b);
    //     D_801057E0_119400_shared_board[playerIndex].spaceType = turnStatus;
    // }
}

//takes player index, gets players current team and scores against the other team
s32 GetCurrentTeamBonusStarScore(mp3_GW_PLAYER* player) {
    s32 curPlayerTeam = get_team_index(player);
    s32 i;
    mp3_GW_PLAYER* curPlayer1stTeammate = NULL;
    mp3_GW_PLAYER* otherTeam1stTeammate = NULL;
    s32 bonusStarsScore = 0;

    s32 team0Stat = -1;
    s32 team1Stat = -1;

    //find first player from each team
    for (i = 0; i < 4; i++) {
        if (get_team_index(&mp3_gPlayers[i]) == curPlayerTeam) {
            if (curPlayer1stTeammate == NULL) {
                curPlayer1stTeammate = &mp3_gPlayers[i];
            }
        } else {
            if (otherTeam1stTeammate == NULL) {
                otherTeam1stTeammate = &mp3_gPlayers[i];
            }
        }
        if (curPlayer1stTeammate != NULL && otherTeam1stTeammate != NULL) {
            break;
        }
    }

    //calculate each teams extra score
    team0Stat = curPlayer1stTeammate->mg_star_coins;
    team1Stat = otherTeam1stTeammate->mg_star_coins;
    if (team0Stat >= team1Stat) {
        bonusStarsScore += 1000;
    }


    team0Stat = curPlayer1stTeammate->coins_total;
    team1Stat = otherTeam1stTeammate->coins_total;
    if (team0Stat >= team1Stat) {
        bonusStarsScore += 1000;
    }

    team0Stat = curPlayer1stTeammate->happeningSpacesLandedOn;
    team1Stat = otherTeam1stTeammate->happeningSpacesLandedOn;
    if (team0Stat >= team1Stat) {
        bonusStarsScore += 1000;
    }

    return bonusStarsScore;
}

s32 newfunc_800EEA58_102678_shared_board(s32 player) {
    s32 i;

    if (mp3_GWBoardFlagCheck(0xF) == 0) {
        return BoardPlayerRankCalc(player);
    }

    s32 team0Score = 0;
    s32 team1Score = 0;

    s32 curPlayerTeam = get_team_index(&mp3_gPlayers[player]);
    mp3_GW_PLAYER* curPlayer1stTeammate = NULL;
    mp3_GW_PLAYER* otherTeam1stTeammate = NULL;

    //find first player from each team, calculate their score
    for (i = 0; i < 4; i++) {
        if (get_team_index(&mp3_gPlayers[i]) == curPlayerTeam) {
            if (curPlayer1stTeammate == NULL) {
                curPlayer1stTeammate = &mp3_gPlayers[i];
                team0Score += curPlayer1stTeammate->stars * 1000 + curPlayer1stTeammate->coins;
            }
        } else {
            if (otherTeam1stTeammate == NULL) {
                otherTeam1stTeammate = &mp3_gPlayers[i];
                team1Score += otherTeam1stTeammate->stars * 1000 + otherTeam1stTeammate->coins;
            }
        }
        if (curPlayer1stTeammate != NULL && otherTeam1stTeammate != NULL) {
            break;
        }
    }

    team0Score += GetCurrentTeamBonusStarScore(curPlayer1stTeammate);
    team1Score += GetCurrentTeamBonusStarScore(otherTeam1stTeammate);
    
    if (curPlayerTeam == 0) {
        return team0Score < team1Score;
    } else {
        return team1Score < team0Score;
    }
}

//used so the placement icon updates correctly
s32 BoardPlayerTeamRankCalc(s32 player) {
    s32 i;
    s32 curPlayerTeam = get_team_index(&mp3_gPlayers[player]);
    mp3_GW_PLAYER* curPlayer1stTeammate = NULL;
    mp3_GW_PLAYER* otherTeam1stTeammate = NULL;
    s32 team0Score = 0;
    s32 team1Score = 0;


    //find first player from each team, calculate their score
    for (i = 0; i < 4; i++) {
        if (get_team_index(&mp3_gPlayers[i]) == curPlayerTeam) {
            if (curPlayer1stTeammate == NULL) {
                curPlayer1stTeammate = &mp3_gPlayers[i];
                team0Score += mp3_gPlayers[i].stars * 1000 + mp3_gPlayers[i].coins;
            }
        } else {
            if (otherTeam1stTeammate == NULL) {
                otherTeam1stTeammate = &mp3_gPlayers[i];
                team1Score += mp3_gPlayers[i].stars * 1000 + mp3_gPlayers[i].coins;
            }
        }
        if (curPlayer1stTeammate != NULL && otherTeam1stTeammate != NULL) {
            break;
        }
    }

    return team0Score < team1Score;
}

void newUpdatePlayerBoardStatus(s32 playerIndex, s32 teamIndex) {
    UnkCoinThing coinDigits;
    BoardStatus* playerBoardStatus;
    s32 var_v1;
    s32 i;
    mp3_GW_PLAYER* curPlayer = &mp3_gPlayers[playerIndex];
    
    playerBoardStatus = &D_801057E0_119400_shared_board[playerIndex];
    //s32 combinedCoins = curPlayer->coins + teammate->coins;
    if (playerBoardStatus->prevCoins != curPlayer->coins) {
        coinDigits.digits[HUNDREDS] = curPlayer->coins / 100;
        coinDigits.digits[TENS] = curPlayer->coins / 10 % 10;
        coinDigits.digits[ONES] = curPlayer->coins % 10;
        if (coinDigits.digits[HUNDREDS] == 0 && coinDigits.digits[TENS] == 0) {
            var_v1 = 1;
        } else if (coinDigits.digits[HUNDREDS] == 0 && coinDigits.digits[TENS] != 0) {
            var_v1 = 2;
        } else {
            var_v1 = 3;
        }
        
        if (var_v1 == 1) {
            SprAttrSet(playerBoardStatus->playerIndex, COINS_ONES_DIGIT, 0x8000);
            coinDigits.digits[TENS] = coinDigits.digits[ONES];
        } else {
            SprAttrReset(playerBoardStatus->playerIndex, COINS_ONES_DIGIT, 0x8000);
        }
    
        if (coinDigits.digits[HUNDREDS] == 0) {
            coinDigits.digits[HUNDREDS] = DIGIT_X;
        }
        for (i = 0; i < ARRAY_COUNT(coinDigits.digits); i++) {
            func_80055140_55D40(playerBoardStatus->playerIndex, i + COINS_HUNDREDS_DIGIT, coinDigits.digits[i], 0);
            func_800550F4_55CF4(playerBoardStatus->playerIndex, i + COINS_HUNDREDS_DIGIT, 1);
        }
    
        playerBoardStatus->prevCoins = curPlayer->coins;
    }

    if (playerBoardStatus->prevStars != curPlayer->stars) {
        if (curPlayer->stars > 99) {
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 9, 0);
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 9, 0);
        } else {
            if (curPlayer->stars > 9) {
                func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, curPlayer->stars, 0);
            } else {
                func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, DIGIT_X, 0);
            }
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, curPlayer->stars % 10, 0);
        }
        func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 1);
        func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 1);
    
        playerBoardStatus->prevStars = curPlayer->stars;
    }
    coinDigits.unk_08[0] = curPlayer->coins;
    coinDigits.unk_08[1] = curPlayer->stars;
    
    for (i = 0; i < ARRAY_COUNT(coinDigits.unk_08); i++) {
        if ((i != 0 && playerBoardStatus->counts[i] != coinDigits.unk_08[i]) || (i == 0 && D_801055E8_119208_shared_board[playerIndex] != 0)) {
            if (playerBoardStatus->unk2[i] == 0) {
                func_800550B4_55CB4(playerBoardStatus->playerIndex, i + 2, 1.0f);
                playerBoardStatus->unk2[i] = 0xF;
            }
        }

        if (playerBoardStatus->unk2[i] != 0) {
            playerBoardStatus->unk2[i]--;
            if (playerBoardStatus->unk2[i] == 0) {
                if (i != 0 || D_801055E8_119208_shared_board[playerIndex] == 0) {
                    func_80055140_55D40(playerBoardStatus->playerIndex, i + 2, 0, 0);
                    func_800550B4_55CB4(playerBoardStatus->playerIndex, i + 2, 0.0f);
                    func_800550F4_55CF4(playerBoardStatus->playerIndex, i + 2, 1);                       
                }
            }
        }
        playerBoardStatus->counts[i] = coinDigits.unk_08[i];
    }
    if (playerBoardStatus->unk1 != -1) {
        func_80055140_55D40(playerBoardStatus->playerIndex, DIGIT_X, playerBoardStatus->unk1, 0);
        func_800550F4_55CF4(playerBoardStatus->playerIndex, DIGIT_X, 1);
        return;
    }
    if (playerBoardStatus->prevRank != BoardPlayerTeamRankCalc(playerIndex)) {
        func_80055140_55D40(playerBoardStatus->playerIndex, DIGIT_X, BoardPlayerTeamRankCalc(playerIndex), 0);
        func_800550F4_55CF4(playerBoardStatus->playerIndex, DIGIT_X, 1);
        playerBoardStatus->prevRank = BoardPlayerTeamRankCalc(playerIndex);
    }
}

void newfunc_800F3D70_107990_shared_board(s32 arg0) {
    BoardStatus* temp_s0;
    s16 temp_v0;
    
    temp_s0 = &D_801057E0_119400_shared_board[arg0];
    if (mp3_gPlayers[0].flags1 & 0x30) {
        temp_v0 = func_8005279C_5339C(16, 2); //14 -> 16 for drawing 2 extra items in teams
    } else {
        temp_v0 = func_8005279C_5339C(14, 2); //14
    }
    
    temp_s0->playerIndex = temp_v0;
    func_80055024_55C24(temp_v0, 0, mp3_D_80105588_1191A8_shared_board[0], 0);
    SprPriSet(temp_v0, 0, ((arg0 * 5) + 0x4790));
    SprAttrSet(temp_v0, 0, 0x1000);
    func_80054904_55504(temp_v0, 0, 0, 0);
}

void newfunc_800F3400_107020_shared_board(mp3_omObjData* arg0) {
    BoardStatus* temp_s2;
    s32 var_v1;
    s32 i, k;
    u8 teams[2] = {0, 0};
    u8 teams2[2] = {0, 0};

    while (1) {
        if (D_800D20B1_D2CB1 == 0) {
            teams[0] = 0;
            teams[1] = 0;
            teams2[0] = 0;
            teams2[1] = 0;
            for (i = 0; i < MAX_PLAYERS; i++) {
                if (D_80101780_1153A0_shared_board != -1 &&
                    D_80101784_1153A4_shared_board != -1 &&
                    i != D_80101780_1153A0_shared_board &&
                    i != D_80101784_1153A4_shared_board) {
                    continue;
                }

                temp_s2 = &D_801057E0_119400_shared_board[i];

                if (temp_s2->uiUpdatePaused == FALSE) {
                    if (temp_s2->uiVisible & 1) {
                        for (k = 0; k < 16; k++) {
                            SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                        }
                        continue;
                    }

                    for (k = 0; k < 16; k++) {
                        switch (k) {
                        case 9:
                            if (mp3_gPlayers[i].flags1 & 1) {
                                break;
                            }
                            continue;
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                        case 15:
                            if (mp3_gPlayers[i].items[k - 11] == ITEM_NONE) {
                                continue;
                            }

                            func_80055024_55C24(temp_s2->playerIndex, k, D_8010559C_1191BC_shared_board[mp3_gPlayers[i].items[k - 11]], 0);
                            func_800550F4_55CF4(temp_s2->playerIndex, k, 0);
                            SprPriSet(temp_s2->playerIndex, k, (i * 5) + 0x800);
                            SprAttrSet(temp_s2->playerIndex, k, 0);
                            var_v1 = k;
                            //if player is index 2 or 3
                            // if (i >= 2) {
                            //     var_v1 = k + 5; //for 5 items, usually is +3 for 3 items
                            // }
                            s32 teamIndex = get_team_index(&mp3_gPlayers[i]);
                            var_v1 = (teamIndex * 5) + var_v1;
                            
                            func_80054904_55504(temp_s2->playerIndex, k, PlayerIconPositions[var_v1][0], PlayerIconPositions[var_v1][1]);
                            SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                            if (D_80101790_1153B0_shared_board != 0) {
                                break;
                            }
                            continue;
                        case 6:
                            if (mp3_gPlayers[i].coins < 10) {
                                continue;
                            }
                            break;
                        }
                        SprAttrReset(temp_s2->playerIndex, k, 0x8000);
                    }
                    s32 j;
                    s32 teamIndex = get_team_index(&mp3_gPlayers[i]);

                    
                    if (teams[teamIndex] == 0) {
                        teams[teamIndex] = 1;
                        newUpdatePlayerBoardStatus(i, teamIndex);
                    } else {
                        //it's the second person encountered in this team, only draw face
                        //turn all sprites off
                        for (j = 0; j < 11; j++) {
                            //if face sprite, dont turn sprite off and set high priority
                            if (j == 1) {
                                SprPriSet(temp_s2->playerIndex, j, 0x1000);
                                continue;
                            }
                            //dont hide COM text if it's needed
                            if (j == 9) {
                                SprPriSet(temp_s2->playerIndex, j, 0xFFF);
                                continue;
                            }
                            //turn sprite off
                            SprAttrSet(temp_s2->playerIndex, j, 0x8000);
                        }
                    }
                } else {
                    if (temp_s2->uiVisible & 1) {
                        for (k = 0; k < 5; k++) {
                            SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                        }
                        SprAttrSet(temp_s2->playerIndex, 9, 0x8000);
                        continue;
                    }

                    for (k = 0; k < 2; k++) {
                        SprAttrReset(temp_s2->playerIndex, k, 0x8000);
                    }

                    for (k = 0; k < 3; k++) {
                        if (temp_s2->unk_40[k] != -1) {
                            SprAttrReset(temp_s2->playerIndex, (k + 2), 0x8000);
                        }
                    }

                    if ((mp3_gPlayers[i].flags1 & 1) && !(temp_s2->uiVisible & 1)) {
                        SprAttrReset(temp_s2->playerIndex, 9, 0x8000);
                    } else {
                        SprAttrSet(temp_s2->playerIndex, 9, 0x8000);
                    }
                    s32 j;
                    s32 teamIndex = get_team_index(&mp3_gPlayers[i]);

                    //it's the second person encountered in this team, only draw face
                    if (teams2[teamIndex] != 0) {
                        //turn all sprites off
                        for (j = 0; j < 11; j++) {
                            //if face sprite, dont turn sprite off
                            if (j == 1) {
                                SprPriSet(temp_s2->playerIndex, j, 0x1000);
                                SprAttrSet(temp_s2->playerIndex, j, 0x8000);
                            }
                            //turn sprite off
                            SprAttrSet(temp_s2->playerIndex, j, 0x8000);
                        }
                    } else {
                        teams2[teamIndex] = 1;
                    }
                }
                if (temp_s2->unkE > 0) {
                    temp_s2->unkE--;
                    temp_s2->xPos += temp_s2->unk_20;
                    temp_s2->yPos += temp_s2->unk_24;
                    temp_s2->unk_20 += temp_s2->unk_28;
                    temp_s2->unk_24 += temp_s2->unk_2C;
                } else if (temp_s2->unkE == -1) {
                    temp_s2->unkE = -2;
                } else if (temp_s2->unkE != -2) {
                    temp_s2->xPos = temp_s2->unk_18;
                    temp_s2->yPos = temp_s2->unk_1C;
                    temp_s2->unkE = -1;
                }
                func_80054904_55504(temp_s2->playerIndex, 0,
                                    (s16)((s32)(temp_s2->xPos + 0.5f) + ITEMS_POS_OFFSET_X),
                                    (s16)((s32)(temp_s2->yPos + 0.5f) + ITEMS_POS_OFFSET_Y));
            }

            if (D_801055C2_1191E2_shared_board != -1) {
                D_801055C8_1191E8_shared_board += 0.1f;
                if (D_801055C8_1191E8_shared_board > 1.0f) {
                    D_801055C8_1191E8_shared_board = 1.0f;
                }
                SprScale(D_801055C2_1191E2_shared_board, 0, D_801055C8_1191E8_shared_board, D_801055C8_1191E8_shared_board);
                if (D_801055E4_119204_shared_board > 0) {
                    D_801055E4_119204_shared_board--;
                    D_801055CC_1191EC_shared_board.x += D_801055D4_1191F4_shared_board.x;
                    D_801055CC_1191EC_shared_board.y += D_801055D4_1191F4_shared_board.y;
                    D_801055D4_1191F4_shared_board.x += D_801055DC_1191FC_shared_board.x;
                    D_801055D4_1191F4_shared_board.y += D_801055DC_1191FC_shared_board.y;
                    func_80054904_55504(D_801055C2_1191E2_shared_board, 0,
                                        D_801055CC_1191EC_shared_board.x,
                                        D_801055CC_1191EC_shared_board.y);
                }
            }
        }
        mp3_HuPrcVSleep();
    }
}

//initialize player UIs
void newfunc_800F4874_108494_shared_board(s32 playerIndex, s16 arg1, s16 arg2) {
    BoardStatus* boardStatus;

    boardStatus = &D_801057E0_119400_shared_board[playerIndex];
    boardStatus->unk_18 = arg1;
    boardStatus->xPos = arg1;
    boardStatus->unk_1C = arg2;
    boardStatus->yPos = arg2;
    boardStatus->unk_20 = boardStatus->unk_24 = 0;
    boardStatus->unkE = -2;
    func_80054904_55504(boardStatus->playerIndex, 0, arg1 + ITEMS_POS_OFFSET_X, arg2 + ITEMS_POS_OFFSET_Y);
}

//create sprite IDs for hud elements
//also assign pointer to first teammate in variable

// mp3_GW_PLAYER* team0Player0 = NULL;
// mp3_GW_PLAYER* team1Player0 = NULL;

mp3_GW_PLAYER* firstPlayerEachTeam[2] = {NULL, NULL};

void SetMinigamePositions(void) {
    s32 i;
    
    //where player icons move before minigame
    s16 newBeforeMinigamePositions[4][2] = {
        {0x10, 0x4C}, //player team0 index0
        {0x1C, 0x4D}, //player team0 index1
        {0xA0, 0x4C}, //player team1 index0
        {0xAC, 0x4D}, //player team1 index1
    };

    //when player icons separate for 4p
    s16 newBeforeMinigamePositions2[4][2] = {
        {0x0C, 0x5C}, //player team0 index0
        {0x18, 0x5D}, //player team0 index1
        {0xA8, 0x5C}, //player team1 index0
        {0xB4, 0x5D}, //player team1 index1
    };

    //when player icons separate for 1v3
    s16 newBeforeMinigamePositions3[4][2] = {
        {0x0C, 0x5C}, //player team0 index0
        {0x18, 0x5D}, //player team0 index1
        {0xA8, 0x5C}, //player team1 index0
        {0xB4, 0x5D}, //player team1 index1
    };

    //when player icons separate for 2v2
    s16 newBeforeMinigamePositions4[4][2] = {
        {0x0C, 0x5C}, //player team0 index0
        {0x18, 0x5D}, //player team0 index1
        {0xA8, 0x5C}, //player team1 index0
        {0xB4, 0x5D}, //player team1 index1
    };

    //when a 1p minigame (item) is landed on player 0
    s16 newBeforeMinigamePositions5[4][2] = {
        {0x0C, 0x5C}, //player team0 index0
        {0x18, 0x5D}, //player team0 index1
        {0xA8, 0x5C}, //player team1 index0
        {0xB4, 0x5D}, //player team1 index1
    };

    // //when a 1p minigame (item) is landed on player 1
    // s16 newBeforeMinigamePositions6[4][2] = {
    //     {0x0C, 0x5C}, //player team0 index0
    //     {0x18, 0x5D}, //player team0 index1
    //     {0xA8, 0x5C}, //player team1 index0
    //     {0xB4, 0x5D}, //player team1 index1
    // };


    // //set x and y position
    // PlayerBoardStatusRootPosition[8][0] = 0x30;
    // PlayerBoardStatusRootPosition[8][1] = 0x4C;
    
    // PlayerBoardStatusRootPosition[9][0] = 0xA0;
    // PlayerBoardStatusRootPosition[9][1] = 0x4C;

    // PlayerBoardStatusRootPosition[10][0] = 0x30;
    // PlayerBoardStatusRootPosition[10][1] = 0x7E;

    // PlayerBoardStatusRootPosition[11][0] = 0xA0;
    // PlayerBoardStatusRootPosition[11][1] = 0x7E;

    //surely there's a better way to do this...
    s32 team0Count = 0;
    s32 team1Count = 0;

    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[i]);
        if (curPlayerTeamIndex == 0) {
            if (team0Count == 0) {
                //
                PlayerBoardStatusRootPosition[i + 8][0] = newBeforeMinigamePositions[0][0];
                PlayerBoardStatusRootPosition[i + 8][1] = newBeforeMinigamePositions[0][1];

                D_8010184C_11546C_shared_board[i][0] = newBeforeMinigamePositions2[0][0];
                D_8010184C_11546C_shared_board[i][1] = newBeforeMinigamePositions2[0][1];
                D_8010185C_11547C_shared_board[i][0] = newBeforeMinigamePositions3[0][0];
                D_8010185C_11547C_shared_board[i][1] = newBeforeMinigamePositions3[0][1];
                D_8010186C_11548C_shared_board[i][0] = newBeforeMinigamePositions4[0][0];
                D_8010186C_11548C_shared_board[i][1] = newBeforeMinigamePositions4[0][1];
                //set 1p minigame positions
                D_801017C4_1153E4_shared_board[i][0] = newBeforeMinigamePositions5[0][0];
                D_801017C4_1153E4_shared_board[i][1] = newBeforeMinigamePositions5[0][1];
                D_801017C4_1153E4_shared_board[i+4][0] = newBeforeMinigamePositions5[0][0];
                D_801017C4_1153E4_shared_board[i+4][1] = newBeforeMinigamePositions5[0][1];
                D_801017C4_1153E4_shared_board[i+8][0] = newBeforeMinigamePositions5[0][0];
                D_801017C4_1153E4_shared_board[i+8][1] = newBeforeMinigamePositions5[0][1];
                team0Count = 1;
            } else {
                PlayerBoardStatusRootPosition[i + 8][0] = newBeforeMinigamePositions[1][0];
                PlayerBoardStatusRootPosition[i + 8][1] = newBeforeMinigamePositions[1][1];

                D_8010184C_11546C_shared_board[i][0] = newBeforeMinigamePositions2[1][0];
                D_8010184C_11546C_shared_board[i][1] = newBeforeMinigamePositions2[1][1];
                D_8010185C_11547C_shared_board[i][0] = newBeforeMinigamePositions3[1][0];
                D_8010185C_11547C_shared_board[i][1] = newBeforeMinigamePositions3[1][1];
                D_8010186C_11548C_shared_board[i][0] = newBeforeMinigamePositions4[1][0];
                D_8010186C_11548C_shared_board[i][1] = newBeforeMinigamePositions4[1][1];
                //set 1p minigame positions
                D_801017C4_1153E4_shared_board[i][0] = newBeforeMinigamePositions5[1][0];
                D_801017C4_1153E4_shared_board[i][1] = newBeforeMinigamePositions5[1][1];
                D_801017C4_1153E4_shared_board[i+4][0] = newBeforeMinigamePositions5[1][0];
                D_801017C4_1153E4_shared_board[i+4][1] = newBeforeMinigamePositions5[1][1];
                D_801017C4_1153E4_shared_board[i+8][0] = newBeforeMinigamePositions5[1][0];
                D_801017C4_1153E4_shared_board[i+8][1] = newBeforeMinigamePositions5[1][1];
            }
        } else {
            if (team1Count == 0) {
                PlayerBoardStatusRootPosition[i + 8][0] = newBeforeMinigamePositions[2][0];
                PlayerBoardStatusRootPosition[i + 8][1] = newBeforeMinigamePositions[2][1];

                D_8010184C_11546C_shared_board[i][0] = newBeforeMinigamePositions2[2][0];
                D_8010184C_11546C_shared_board[i][1] = newBeforeMinigamePositions2[2][1];
                D_8010185C_11547C_shared_board[i][0] = newBeforeMinigamePositions3[2][0];
                D_8010185C_11547C_shared_board[i][1] = newBeforeMinigamePositions3[2][1];
                D_8010186C_11548C_shared_board[i][0] = newBeforeMinigamePositions4[2][0];
                D_8010186C_11548C_shared_board[i][1] = newBeforeMinigamePositions4[2][1];
                //set 1p minigame positions
                D_801017C4_1153E4_shared_board[i][0] = newBeforeMinigamePositions5[2][0];
                D_801017C4_1153E4_shared_board[i][1] = newBeforeMinigamePositions5[2][1];
                D_801017C4_1153E4_shared_board[i+4][0] = newBeforeMinigamePositions5[2][0];
                D_801017C4_1153E4_shared_board[i+4][1] = newBeforeMinigamePositions5[2][1];
                D_801017C4_1153E4_shared_board[i+8][0] = newBeforeMinigamePositions5[2][0];
                D_801017C4_1153E4_shared_board[i+8][1] = newBeforeMinigamePositions5[2][1];
                team1Count = 1;
            } else {
                PlayerBoardStatusRootPosition[i + 8][0] = newBeforeMinigamePositions[3][0];
                PlayerBoardStatusRootPosition[i + 8][1] = newBeforeMinigamePositions[3][1];
                D_8010184C_11546C_shared_board[i][0] = newBeforeMinigamePositions2[3][0];
                D_8010184C_11546C_shared_board[i][1] = newBeforeMinigamePositions2[3][1];
                D_8010185C_11547C_shared_board[i][0] = newBeforeMinigamePositions3[3][0];
                D_8010185C_11547C_shared_board[i][1] = newBeforeMinigamePositions3[3][1];
                D_8010186C_11548C_shared_board[i][0] = newBeforeMinigamePositions4[3][0];
                D_8010186C_11548C_shared_board[i][1] = newBeforeMinigamePositions4[3][1];
                //set 1p minigame positions
                D_801017C4_1153E4_shared_board[i][0] = newBeforeMinigamePositions5[3][0];
                D_801017C4_1153E4_shared_board[i][1] = newBeforeMinigamePositions5[3][1];
                D_801017C4_1153E4_shared_board[i+4][0] = newBeforeMinigamePositions5[3][0];
                D_801017C4_1153E4_shared_board[i+4][1] = newBeforeMinigamePositions5[3][1];
                D_801017C4_1153E4_shared_board[i+8][0] = newBeforeMinigamePositions5[3][0];
                D_801017C4_1153E4_shared_board[i+8][1] = newBeforeMinigamePositions5[3][1];
            }
        }
    }
}

void newfunc_800F4190_107DB0_shared_board(void) {
    void* temp_v0;
    s32 i;
    s16* spriteIDs;
    s32 sp10[2] = {0x130112, 0x130111};
    s32 team0Set = 0;
    s32 team1Set = 0;

    firstPlayerEachTeam[0] = NULL;
    firstPlayerEachTeam[1] = NULL;

    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[i]);
        if (teamIndex == 0) { 
            if (firstPlayerEachTeam[0] == NULL) {
                firstPlayerEachTeam[0] = &mp3_gPlayers[i];
            }
        } else {
            if (firstPlayerEachTeam[1] == NULL) {
                firstPlayerEachTeam[1] = &mp3_gPlayers[i];
            }
        }
    }

    //player icon with "page" background
    s32 originalPlayerHUDIDs[] = {
        0x00130272,
        0x00130273,
        0x00130274,
        0x00130275,
        0x00130276,
        0x00130277,
        0x00130278,
        0x00130279,
    };

    //just the players' face
    s32 PlayerFaceOnlyHUDIDs[] = {
        0x0013026A,
        0x0013026B,
        0x0013026C,
        0x0013026D,
        0x0013026E,
        0x0013026F,
        0x00130270,
        0x00130271,
    };

    spriteIDs = mp3_D_80105588_1191A8_shared_board;
    //if teams, use extended graphic
    if (mp3_gPlayers[0].flags1 & 0x30) {
        PushItemCountToGP(5); //5 items for teams
        temp_v0 = mp3_ReadMainFS(0x13027A); //extended background graphic
    } else {
        PushItemCountToGP(3); //3 items for teams
        temp_v0 = mp3_ReadMainFS(0x13010F); //normal background graphic
    }
    
    spriteIDs[0] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);
    
    //create player sprite ids
    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 team = mp3_gPlayers[i].flags1 & 0x30;
        if (team == 0x10) {
            if (team0Set == 0) {
                temp_v0 = mp3_ReadMainFS(originalPlayerHUDIDs[mp3_gPlayers[i].characterID]);
            } else {
                temp_v0 = mp3_ReadMainFS(PlayerFaceOnlyHUDIDs[mp3_gPlayers[i].characterID]);
            }
            team0Set = 1;
            
        } else {
            if (team1Set == 0) {
                temp_v0 = mp3_ReadMainFS(originalPlayerHUDIDs[mp3_gPlayers[i].characterID]);
            } else {
                temp_v0 = mp3_ReadMainFS(PlayerFaceOnlyHUDIDs[mp3_gPlayers[i].characterID]);
            }
            team1Set = 1;
        }
        
        spriteIDs[i + 1] = mp3_func_80055810_56410(temp_v0);
        mp3_HuFreeFilePerm(temp_v0);
    }

    //create coin and star sprite ids
    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        temp_v0 = mp3_ReadMainFS(sp10[i]);
        spriteIDs[i + 5] = mp3_func_80055810_56410(temp_v0);
        mp3_HuFreeFilePerm(temp_v0);
    }

    //create placement sprite id
    temp_v0 = mp3_ReadMainFS(0x130110);
    spriteIDs[8] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);

    //create COM text sprite id
    temp_v0 = mp3_ReadMainFS(0x1300D1);
    spriteIDs[9] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);

    //create item sprite ids
    for (i = 0; i < ITEMS_END; i++) {
        temp_v0 = mp3_ReadMainFS(mp3_D_801019D0_1155F0_shared_board[i]);
        spriteIDs[i + 10] = mp3_func_80055810_56410(temp_v0);
        mp3_HuFreeFilePerm(temp_v0);
    }

    s32 team0 = 0;
    s32 team1 = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
        //if team0, else team1
        if (mp3_gPlayers[i].flags1 & 0x10) {
            //team0
            PlayerBoardStatusRootPosition[i][0] = newTeam0RootPositions[team0][0];
            PlayerBoardStatusRootPosition[i][1] = newTeam0RootPositions[team0][1];
            team0++;
        } else {
            //team1
            PlayerBoardStatusRootPosition[i][0] = newTeam1RootPositions[team1][0];
            PlayerBoardStatusRootPosition[i][1] = newTeam1RootPositions[team1][1];
            team1++;
        }
    }
    
    SetMinigamePositions();

    team0 = 0;
    team1 = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[i]);
        //if team0, else team1
        if (mp3_gPlayers[i].flags1 & 0x10) {
            //team0
            PlayerBoardStatusRootPosition[i][0] = newTeam0RootPositions[teamIndex + team0][0];
            PlayerBoardStatusRootPosition[i][1] = newTeam0RootPositions[teamIndex + team0][1];
            team0++;
        } else {
            //team1
            PlayerBoardStatusRootPosition[i][0] = newTeam1RootPositions[team1][0];
            PlayerBoardStatusRootPosition[i][1] = newTeam1RootPositions[team1][1];
            team1++;
        }
    }
}

void newfunc_800F3A80_1076A0_shared_board(s32 arg0) {
    s16 temp_s2;
    s32 i;

    temp_s2 = D_801057E0_119400_shared_board[arg0].playerIndex;

    for (i = 0; i < 2; i++) {
        func_80055024_55C24(temp_s2, i + 2, D_80105592_1191B2_shared_board[i], 0);
        SprPriSet(temp_s2, i + 2, ((arg0 * 5) + 0x4790));
        SprAttrReset(temp_s2, i + 2, 0xFFFF);
        SprAttrSet(temp_s2, i + 2, 0x1000);
        func_800552DC_55EDC(temp_s2, i + 2, 0.0f);
        func_80054904_55504(temp_s2, i + 2, PlayerIconPositions[i + 2][0], PlayerIconPositions[i + 2][1]);
        func_800550B4_55CB4(temp_s2, i + 2, 0.0f);
        func_80055458_56058(temp_s2, i + 2, 0x100);
    }
}



void newfunc_800F3F0C_107B2C_shared_board(s32 arg0) {
    s32 x;
    s32 y;
    s16 temp_s2;
    s32 i;
    s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[arg0]);
    s32 posIndex = -1;

    s16 newCOM_TextPos[4][2] = {
        {-20, 15}, //player team0 index0
        {0, 14}, //player team0 index1
        {-20, 15}, //player team1 index0
        {0, 14}, //player team1 index1
    };

    //get player team is on, then get the index of the player
    for (i = 0; i < MAX_PLAYERS; i++) {
        //is current player
        if (arg0 == i) {
            posIndex = 0;
            break;
        }
        //if 2 players are on the same team and it wasn't the current player
        if (curPlayerTeamIndex == get_team_index(&mp3_gPlayers[i])) {
            posIndex = 1;
            break;
        }
    }

    x = newCOM_TextPos[curPlayerTeamIndex * 2 + posIndex][0];
    y = newCOM_TextPos[curPlayerTeamIndex * 2 + posIndex][1];

    temp_s2 = D_801057E0_119400_shared_board[arg0].playerIndex;
    func_80055024_55C24(temp_s2, 9, D_8010559A_1191BA_shared_board, 0);
    func_800550F4_55CF4(temp_s2, 9, 0);
    SprPriSet(temp_s2, 9, ((arg0 * 5) + 0x478E) & 0xFFFF);
    SprAttrSet(temp_s2, 9, 0);
    
    func_80054904_55504(temp_s2, 9, x, y);
    if (!(mp3_gPlayers[arg0].flags1 & 1)) {
        SprAttrSet(temp_s2, 9, 0x8000);
    }
}

void newfunc_800F39C0_1075E0_shared_board(s32 playerIndex) {
    s16 temp_s1;

    temp_s1 = D_801057E0_119400_shared_board[playerIndex].playerIndex;
    func_80055024_55C24(temp_s1, 1, mp3_D_80105588_1191A8_shared_board[playerIndex+1], 0);
    func_800550F4_55CF4(temp_s1, 1, 0);
    SprPriSet(temp_s1, 1, ((playerIndex * 5) + 0x4790));
    SprAttrSet(temp_s1, 1, 0);
    func_80054904_55504(temp_s1, 1, PlayerIconPositions[1][0], PlayerIconPositions[1][1]);
}

void newfunc_800F3BD0_1077F0_shared_board(s32 arg0) {
    BoardStatus* temp_s4;
    s16 temp_s2;
    void* temp_v0;
    s32 i;

    temp_s4 = &D_801057E0_119400_shared_board[arg0];
    temp_s4->prevCoins = -1;
    temp_s4->prevStars = -1;
    temp_v0 = mp3_ReadMainFS(0x1300CF);
    temp_s4->unk_3A = mp3_func_80055810_56410(temp_v0);
    temp_s2 = temp_s4->playerIndex;
    for (i = 0; i < 5; i++) {
        func_80055024_55C24(temp_s2, i + 4, temp_s4->unk_3A, 0);
        func_800550F4_55CF4(temp_s2, i + 4, 1);
        func_80055140_55D40(temp_s2, i + 4, 0xAU, 0);
        SprPriSet(temp_s2, i + 4, ((arg0 * 5) + 0x4790) & 0xFFFF);
        SprAttrReset(temp_s2, i + 4, 0xFFFFU);
        SprAttrSet(temp_s2, i + 4, 0U);
        func_80054904_55504(temp_s2, i + 4, PlayerIconPositions[i + 4][0], PlayerIconPositions[i + 4][1]);
        func_80055420_56020(temp_s2, i + 4, 0xFFU, 0xFFU, 0xFF);
        func_80055458_56058(temp_s2, i + 4, 0x100U);
        func_800552DC_55EDC(temp_s2, i + 4, 0.0f);        
    }
    mp3_HuFreeFilePerm(temp_v0);
}

void newfunc_800F3E34_107A54_shared_board(s32 arg0) {
    BoardStatus* temp_v0;
    s16 temp_s0;

    temp_v0 = &D_801057E0_119400_shared_board[arg0];
    temp_v0->prevRank = -1;
    temp_s0 = temp_v0->playerIndex;
    func_80055024_55C24(temp_s0, 0xA, mp3_D_80105598_1191B8_shared_board, 0);
    func_800550F4_55CF4(temp_s0, 0xA, 1);
    func_80055140_55D40(temp_s0, 0xA, 0, 0);
    SprPriSet(temp_s0, 0xA, ((arg0 * 5) + 0x478F) & 0xFFFF);
    SprAttrSet(temp_s0, 0xA, 0);
    func_80054904_55504(temp_s0, 0xA, PlayerIconPositions[10][0], PlayerIconPositions[10][1]);
}

//for giving an item after an item minigame
void newfunc_800F3FF4_107C14_shared_board(s32 arg0) {
    s32 temp_s3;
    s16 var_s1;
    s32 i;
    s32 curItem;
    s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
        if (teamIndex == curPlayerTeam) {
            arg0 = i;
            break;
        }
    }
    
    
    temp_s3 = D_801057E0_119400_shared_board[arg0].playerIndex;

    for (i = 0; i < EXTENDED_ITEM_COUNT; i++) {
        curItem = mp3_gPlayers[arg0].items[i];
        curItem = (curItem == -1) ? 0 : curItem;
        func_80055024_55C24(temp_s3, i + 0xB, D_8010559C_1191BC_shared_board[curItem], 0);
        func_800550F4_55CF4(temp_s3, i + 0xB, 0);
        SprPriSet(temp_s3, i + 0xB, ((arg0 * 5) + 0x478E));
        SprAttrSet(temp_s3, i + 0xB, 0);
        var_s1 = i + 0xB;
        if (arg0 >= 2) {
            //should this be changed?
            var_s1 = i + 0x10;
        }
        func_80054904_55504(temp_s3, i + 0xB, PlayerIconPositions[var_s1][0], PlayerIconPositions[var_s1][1]);
        if (mp3_gPlayers[arg0].items[i] == -1) {
            SprAttrSet(temp_s3, i + 0xB, 0x8000);
        }
    }
}

s16 item0XY[] = {3, 5};
s16 item1XY[] = {21, -5};
s16 item2XY[] = {39, 5};
s16 item3XY[] = {57, -5};
s16 item4XY[] = {75, 5};

void newfunc_800F6BC4_10A7E4_shared_board(s32 arg0) {
    BoardStatus* temp_s2;
    f32 var_f20;
    s32 i, j;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            temp_s2 = &D_801057E0_119400_shared_board[i];
            if (temp_s2->uiUpdatePaused == TRUE) {
                func_800F6A88_10A6A8_shared_board(temp_s2->playerIndex, 2);
                func_80054904_55504(temp_s2->playerIndex, 1, PlayerIconPositions[1][0], PlayerIconPositions[1][1]);
                if (mp3_gPlayers[i].items[0] != ITEM_NONE) {
                    //used for item positions when closing items screen
                    for (j = 0; j < EXTENDED_ITEM_COUNT; j++) {
                        switch (j) {
                        case 0:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, item0XY[0], item0XY[1]);
                            break;
                        case 1:
                            //normally is -5 on the last arg to move item index 1 up a bit
                            func_80054904_55504(temp_s2->playerIndex, j + 2, item1XY[0], item1XY[1]);
                            break;
                        case 2:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, item2XY[0], item2XY[1]);
                            break;
                        case 3:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, item3XY[0], item3XY[1]);
                            break;
                        case 4:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, item4XY[0], item4XY[1]);
                            break;
                        }
                    }
                } else {
                    func_80054904_55504(temp_s2->playerIndex, 2, 0x12, 0);
                }
            }
        }
    }
    
    for (var_f20 = 0.0f; var_f20 <= 90.0f; var_f20 += 15.0f) {
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (arg0 == CUR_PLAYER || arg0 == i) {
                func_800F6AD0_10A6F0_shared_board(i, mp3_HuMathCos(var_f20), 1.0f);
            }            
        }
        mp3_HuPrcVSleep();
    }
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            func_800F6AD0_10A6F0_shared_board(i, 0.0f, 0);
        }
    }
    mp3_HuPrcVSleep();
}

void newfunc_800F3370_106F90_shared_board(void) {
    s32 i, j;

    for (i = 0; i < MAX_PLAYERS; i++) {
        BoardStatus* boardStatus = &D_801057E0_119400_shared_board[i];
        for (j = 0; j < 16; j++) {
            SprAttrSet(boardStatus->playerIndex, j, 0x8000);
        }
    }
}

void newfunc_800F6ECC_10AAEC_shared_board(s32 arg0) {
    s32 sp10;
    s32 sp14;
    BoardStatus* temp_s2;
    f32 var_f20;
    s32 i, j;
    
    for (var_f20 = 90.0f; var_f20 >= 0.0f; var_f20 -= 15.0f) {
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (arg0 == CUR_PLAYER || arg0 == i) {
                func_800F6AD0_10A6F0_shared_board(i, mp3_HuMathCos(var_f20), 1.0f);
            }            
        }
        mp3_HuPrcVSleep();
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            func_800F6AD0_10A6F0_shared_board(i, 1.0f, 1.0f);
            temp_s2 = &D_801057E0_119400_shared_board[i];
            if (temp_s2->uiUpdatePaused == TRUE) {
                func_800F6A88_10A6A8_shared_board(temp_s2->playerIndex, 0);
                sp10 = PlayerBoardStatusRootPosition[i][0] + ITEMS_POS_OFFSET_X;
                sp14 = PlayerBoardStatusRootPosition[i][1] + ITEMS_POS_OFFSET_Y;
                func_80054904_55504(temp_s2->playerIndex, 1, sp10, sp14);
                if (mp3_gPlayers[i].items[0] != ITEM_NONE) {
                    for (j = 0; j < EXTENDED_ITEM_COUNT; j++) {
                        func_800F6E4C_10AA6C_shared_board(i, j, &sp10, &sp14);
                        func_80054904_55504(temp_s2->playerIndex, j + 2, sp10, sp14);
                    }
                } else {
                    func_80054904_55504(temp_s2->playerIndex, 2, (sp10 + 0x12), sp14);
                }
            }
        }
    }
    mp3_HuPrcVSleep();
}

void newfunc_800F6AD0_10A6F0_shared_board(s32 arg0, f32 xScale, f32 yScale) {
    BoardStatus* temp_s1;
    s32 i;

    temp_s1 = &D_801057E0_119400_shared_board[arg0];
    switch(temp_s1->uiUpdatePaused) {
    case FALSE:
        for (i = 0; i < 16; i++) {
            SprScale(temp_s1->playerIndex, i, xScale, yScale);
        }
        break;
    case TRUE:
        for (i = 0; i < 7; i++) { //was i < 5, is now i < 7 for 2 extra items
            SprScale(temp_s1->playerIndex, i, xScale, yScale);
        }
        SprScale(temp_s1->playerIndex, 9, xScale, yScale);
        break;
    }
}

//sets item positions when pressing B and you have control of hand cursor
void newfunc_800F6E4C_10AA6C_shared_board(s32 playerIndex, s32 itemIndex, s32* xPos, s32* yPos) {
    s32 xPosTemp;
    
    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    *xPos = PlayerBoardStatusRootPosition[playerIndex][0] + ITEMS_POS_OFFSET_X;
    *yPos = PlayerBoardStatusRootPosition[playerIndex][1] + ITEMS_POS_OFFSET_Y;

    xPosTemp = *xPos + 3;
    *xPos = xPosTemp + (itemIndex * 18);
    //if item index is 1 or 3 move item up on the screen 5 units
    //if item index 0, 2, or 4 move down on the screen 5 units
    if (itemIndex == 1 || itemIndex == 3) {
        *yPos -= 5;
    } else {
        *yPos += 5;
    }
}

void newfunc_800F5F98_109BB8_shared_board(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    BoardStatus* temp_s7;
    s16 temp_s5;
    s16 i;
    void* var_s2;
    s32 temp = 0;

    temp_s7 = &D_801057E0_119400_shared_board[arg0];
    temp_s5 = temp_s7->playerIndex;
    var_s2 = NULL;

    s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);

    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
        if (teamIndex == curPlayerTeam) {
            temp = i;
            break;
        }
    }

    for (i = 0; i < EXTENDED_ITEM_COUNT; i++) {
        var_s2 = NULL;
        if (mp3_gPlayers[temp].items[i] != -1) {
            var_s2 = mp3_ReadMainFS(D_8010197C_11559C_shared_board[mp3_gPlayers[arg0].items[i]]);
        } else {
            if (i == 0) {
                var_s2 = mp3_ReadMainFS(0x13025E);
            }
        }

        if (var_s2 != NULL) {
            temp_s7->unk_40[i] = mp3_func_80055810_56410(var_s2);
            mp3_HuFreeFilePerm(var_s2);
            func_80055024_55C24(temp_s5, i + 2, temp_s7->unk_40[i], 0);
            if (i != 0) {
                SprPriSet(temp_s5, i + 2, (arg0 * 5) + 0x4790);
            } else {
                SprPriSet(temp_s5, i + 2, ((arg0 * 5) + 0x478F) & 0xFFFF);
            }
            SprAttrSet(temp_s5, i + 2, 0x180CU);
            SprAttrReset(temp_s5, i + 2, 0x8000U);
            func_800552DC_55EDC(temp_s5, i + 2, 0.0f);
            if (mp3_gPlayers[arg0].items[0] != -1) {
                if (arg1 != 0) {
                    func_800F6E4C_10AA6C_shared_board(arg0, i, &sp10, &sp14);
                    func_80054904_55504(temp_s7->playerIndex, i + 2, sp10, sp14);
                } else {
                    switch (i) {
                    case 0:
                        func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, 5);
                        break;
                    case 1:
                        func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, -5);
                        break;
                    case 2:
                        func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, 5);
                        break;
                    //add case 3 and 4 for 4th and 5th item
                    case 3:
                        func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, -5);
                        break;
                    case 4:
                        func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, 5);
                        break;
                    }                    
                }
            } else {
                if (arg1 != 0) {
                    f32 xPos, yPos;
                    xPos = (PlayerBoardStatusRootPosition[arg0][0] + 0x38);
                    yPos = (PlayerBoardStatusRootPosition[arg0][1] + 0x13);
                    xPos = xPos + 22.0f;
                    xPos = xPos - 4.0f;
                    
                    func_80054904_55504(temp_s7->playerIndex, 2, xPos, yPos);
                } else {
                    func_80054904_55504(temp_s5, 2, 0x12, 0);
                }
            }
            SprScale(temp_s5, i + 2, 1.0f, 1.0f);
            func_800550B4_55CB4(temp_s5, i + 2, 0.0f);
            s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
            s32 teamIndex2 = get_team_index(&mp3_gPlayers[mp3_GwSystem.current_player_index]);
            if (teamIndex == teamIndex2) {
                func_80055458_56058(temp_s5, i + 2, 0x100U);
            } else {
                func_80055458_56058(temp_s5, i + 2, 0x80U);
            }
            
        } else {
            temp_s7->unk_40[i] = -1;
        }
    }
}

void func_800F6848_10A468_shared_board(s32 arg0, s32 arg1, f32* arg2, f32* arg3);

void itemHandCursor2(s32 arg0, s32 arg1, f32* arg2, f32* arg3) {
    s32 i;
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
        func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
    } else {
        func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
    } 
}

void itemHandCursor3(s32 arg0, s32 arg1, f32* arg2, f32* arg3) {
    s32 i;
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
    }
    //related to where you drag an item
    func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
}

void itemHandCursor(s32 arg0, s32 arg1, f32* arg2, f32* arg3) {
    s32 i;
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
        func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
    } else {
        func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
    } 
}

s32 GetTeamCaptainCurrentIndex(s32 playerIndex) {
    s32 i;
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                break;
            }
        }
        return i;
    } else {
        return mp3_GwSystem.current_player_index;
    }   
}

void newfunc_800E35F8_F7218_shared_board(void) {
    f32 temp_f0;
    f32 var_f20;
    s32* temp_s0;
    s32 prev;
    s32 teamIndex = get_team_index(&mp3_gPlayers[mp3_GwSystem.current_player_index]);
    s32 i;

    for (i = 0; i < MAX_PLAYERS; i++) {
        s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[i]);
        if (teamIndex == curPlayerTeamIndex) {
            break;
        }
    }

    temp_s0 = mp3_HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    prev = *temp_s0;
    while (*temp_s0 != -1) {
        if (*temp_s0 != prev) {
            func_800F696C_10A58C_shared_board(i, prev, 1.0f, 1.0f);
            var_f20 = 0.0f;
            prev = *temp_s0;
        }
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }
        temp_f0 = (mp3_HuMathSin(var_f20) * 0.2f) + 1.0f;
        func_800F696C_10A58C_shared_board(i, *temp_s0, temp_f0, temp_f0);
        mp3_HuPrcVSleep();
        var_f20 += 13.0f;
        
    }
    func_800F696C_10A58C_shared_board(i, prev, 1.0f, 1.0f);
    mp3_omDelPrcObj(0);
}

void func_800F6848_10A468_shared_board(s32 arg0, s32 arg1, f32* arg2, f32* arg3);
void func_800F688C_10A4AC_shared_board(s32 arg0, s32 arg1, s16 arg2, s16 arg3);

void chillyWatersSkeletonKeyThing2(s32 arg0, s32 arg1, f32* arg2, f32* arg3) {
    s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
    s32 i;

    if (mp3_gPlayers[0].flags1 & 0x30) {
        // //get first player of team (this needs a different approach)
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
        func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
    } else {
        func_800F6848_10A468_shared_board(arg0, arg1, arg2, arg3);
    }
}

void chillyWatersSkeletonKeyThing3(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
    s32 i;

    if (mp3_gPlayers[0].flags1 & 0x30) {
        // //get first player of team (this needs a different approach)
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
        func_800F688C_10A4AC_shared_board(arg0, arg1, arg2, arg3);
    } else {
        func_800F688C_10A4AC_shared_board(arg0, arg1, arg2, arg3);
    }
}

//TODO: hopefully the array D_80105630_119250_shared_board can hold 5 items (I believe it does)
void newfunc_800F7610_10B230_shared_board(void) {
    s32 prevItem = -1;
    s32 i = 0;
    s32* boardItemIds = D_80105630_119250_shared_board;
    
    for (; i < EXTENDED_ITEM_COUNT; i++) {
        boardItemIds = &D_80105630_119250_shared_board[i];
        while (1) {
            *boardItemIds = D_80101A50_115670_shared_board[func_800EEF80_102BA0_shared_board(9.0f)];
            if (*boardItemIds != prevItem) {
                prevItem = *boardItemIds;
                break;
            }
        }
    }
}

void newfunc_800F7F30_10BB50_shared_board(void) {
    func_800EC590_1001B0_shared_board(5, 0x3C20);
    D_80105630_119250_shared_board[0] =
    D_80105630_119250_shared_board[1] =
    D_80105630_119250_shared_board[2] =
    D_80105630_119250_shared_board[3] =
    D_80105630_119250_shared_board[4] = ITEM_SKELETON_KEY;
    func_800F76A4_10B2C4_shared_board(0);
    func_800EC590_1001B0_shared_board(5, 0x3C1D);    
}

//Toad gives all skeleton keys
void newfunc_800F7D4C_10B96C_shared_board(void) {
    func_800EC590_1001B0_shared_board(3, 0x3C0B);
    D_80105630_119250_shared_board[0] =
    D_80105630_119250_shared_board[1] =
    D_80105630_119250_shared_board[2] = 
    D_80105630_119250_shared_board[3] = 
    D_80105630_119250_shared_board[4] = 
    ITEM_SKELETON_KEY;
    func_800F76A4_10B2C4_shared_board(0);
    func_800EC590_1001B0_shared_board(3, 0x3C0A);
}

//Baby bowser gives warp blocks from item space
void newfunc_800F7F7C_10BB9C_shared_board(void) {
    func_800EC590_1001B0_shared_board(5, 0x3C21);
    D_80105630_119250_shared_board[0] =
    D_80105630_119250_shared_board[1] =
    D_80105630_119250_shared_board[2] =
    D_80105630_119250_shared_board[3] =
    D_80105630_119250_shared_board[4] =
    ITEM_WARP_BLOCK;
    func_800F76A4_10B2C4_shared_board(0);
    func_800EC590_1001B0_shared_board(5, 0x3C1D);
}

void teamCheck6_C(s32 arg0, s32 arg1, s32 arg2) {
    s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
    s32 i;

    if (mp3_gPlayers[0].flags1 & 0x30) {   
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
    }

    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void func_800F6780_10A3A0_shared_board(s32 arg0, s32 arg1, f32 arg2, f32 arg3);

void teamCheck11_C(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
    s32 i;

    if (mp3_gPlayers[0].flags1 & 0x30) {   
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
    }

    func_800F6780_10A3A0_shared_board(arg0, arg1, arg2, arg3);
}

//if team is in second, return that they are in 4th for item pool
s32 GetPlayerPlacementForTeamShop(s32 playerIndex) {
    //if teams are not on, do normal rank calc
    if (!(mp3_gPlayers[0].flags1 & 0x30)) {
        return BoardPlayerRankCalc(playerIndex);
    }

    s32 teamRank = BoardPlayerTeamRankCalc(playerIndex);

    if (teamRank > 0) {
        teamRank = 3; //give last place items
    }
    return teamRank;
}

s32 storeTeamIndex(void) {
    s32 teamIndex = get_team_index(&mp3_gPlayers[mp3_GwSystem.current_player_index]);
    s32 i;

    if (mp3_gPlayers[0].flags1 & 0x30) {   
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                return i;
            }
        }
    } else {
        return mp3_GwSystem.current_player_index;
    }
    //should never be reached
    return -1;
}

#define MINIGAME_4P 0
#define MINIGAME_1V3 1
#define MINIGAME_2V2 2
#define MINIGAME_ITEM 3
#define MINIGAME_BATTLE 4
#define MINIGAME_1V1 5

s32 findUniqueIndex(void) {
    // Check for the unique value
    if (D_801057E0_119400_shared_board[0].spaceType == D_801057E0_119400_shared_board[1].spaceType) {
        // If the first two values are the same, check the rest
        if (D_801057E0_119400_shared_board[0].spaceType == D_801057E0_119400_shared_board[2].spaceType) {
            // If the first three values are the same, the last one is unique
            return 3;
        } else {
            // If the third value is different, it's unique
            return 2;
        }
    } else {
        // If the first two values are different, one of them is unique
        // Compare with the third value to identify
        if (D_801057E0_119400_shared_board[0].spaceType == D_801057E0_119400_shared_board[2].spaceType) {
            return 1; // Second value is unique
        } else {
            return 0; // First value is unique
        }
    }
}

void SetTeamsTo2v2Minigame(void) {
    s32 i;
    for (i = 0; i < MAX_PLAYERS; i++) {
        BoardStatus* playerStatus = &D_801057E0_119400_shared_board[i];
        s32 teamIndex = get_team_index(&mp3_gPlayers[i]);
        //if team 0 set to blue space. otherwise, set to red
        if (teamIndex == 0) {
            playerStatus->spaceType = 1; //blue
        } else {
            playerStatus->spaceType = 2; //red
        }
    }
}

void CustomMinigameSetCheck(void) {
    //if teams off, run normal function, exit
    if (!(mp3_gPlayers[0].flags1 & 0x30)) {
        func_800F52C4_108EE4_shared_board();
        return;
    }

    SetMinigamePositions();

    s32 minigameCategory = GetMinigameCategoryForEndTurnMinigame();

    //if force 2v2 is on or players landed on 2 red and 2 blue, force correct teams
    if (customEepromData.force2v2Minigame == TRUE || minigameCategory == MINIGAME_2V2) {
        SetTeamsTo2v2Minigame();
        func_800F52C4_108EE4_shared_board();
        return;
    }

    //if 1v3
    if (minigameCategory == MINIGAME_1V3) {
        s32 playerOn1Team = findUniqueIndex();
        s32 playerWantedColor;
        s32 randVal = func_800EEF80_102BA0_shared_board(100.0f);

        //50/50 between 4p and 2v2
        if (randVal > 50) {
            //1v3
            //copy any player that's not the unique player to get the color
            if (playerOn1Team == 0) {
                playerWantedColor = D_801057E0_119400_shared_board[1].spaceType;
            } else {
                playerWantedColor = D_801057E0_119400_shared_board[0].spaceType;
            }
            //set player to team with rest of players
            D_801057E0_119400_shared_board[playerOn1Team].spaceType = playerWantedColor;
        } else {
            //2v2
            SetTeamsTo2v2Minigame();
        }
    }
    func_800F52C4_108EE4_shared_board();
}

s32 GetMinigameCategoryForEndTurnMinigame(void) {
    #define BLUE_SPACE 1
    #define RED_SPACE 2
    u8 otherCount = 0;
    u8 redCount = 0;
    u8 blueCount = 0;
    s32 i;

    for (i = 0; i < MAX_PLAYERS; i++) {
        switch (D_801057E0_119400_shared_board[i].spaceType) {
        case BLUE_SPACE:
            blueCount++;
            break;
        case RED_SPACE:
            redCount++;
            break;
        default:
            otherCount++;
        }
    }

    // Determine result based on counts
    if (otherCount > 0) {
        return -1;
    }

    if (blueCount == 0 || blueCount == 4) {
        return 0;
    }

    if (blueCount == 1) {
        return 1;
    }

    if (blueCount == 3) {
        return 1;
    }

    return 2;
}

//decide what type of minigame will be played
s32 newfunc_800F52C4_108EE4_shared_board(void) {
    #define BLUE_SPACE 1
    #define RED_SPACE 2
    u8 blueSpaceIndices[4];
    u8 type2Indices[4];
    u8 otherCount = 0;
    u8 redCount = 0;
    u8 blueCount = 0;
    s32 i;

    for (i = 0; i < MAX_PLAYERS; i++) {
        switch (D_801057E0_119400_shared_board[i].spaceType) {
        case BLUE_SPACE:
            blueSpaceIndices[blueCount++] = i;
            break;
        case RED_SPACE:
            type2Indices[redCount++] = i;
            break;
        default:
            otherCount++;
        }
    }

    // Determine result based on counts
    if (otherCount > 0) {
        return -1;
    }

    if (blueCount == 0 || blueCount == 4) {
        return 0;
    }

    if (blueCount == 1) {
        D_801055F8_119218_shared_board = blueSpaceIndices[0];
        return 1;
    }

    if (blueCount == 3) {
        D_801055F8_119218_shared_board = type2Indices[0];
        return 1;
    }

    return 2;
}

//AdjustPlayerCoinsGradual
void newfunc_800F5D44_109964_shared_board(s32 arg0, s32 arg1) {
    func_800F5BF4_109814_shared_board(arg0, arg1, 1);
}

void newShowPlayerCoinChange(s32 player, s32 coins) {
    D_80102C48_116868_shared_board = 1;

    //always want to pass 0 or 1 for HUD display (so pass team index)
    func_800E1934_F5554_shared_board(player, coins);
}

s32 newPlayerHasItem(s32 playerIndex, s32 itemID) {
    s32 i;
    s32 teamIndex;
    mp3_GW_PLAYER* player0Team0 = NULL;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
    player0Team0 = firstPlayerEachTeam[teamIndex];

    //search first player's inventory (all 5 items)
    for (i = 0; i < EXTENDED_ITEM_COUNT; i++) {
        if (player0Team0->items[i] == itemID) {
            return i;
        }
    }

    //wasn't found, return -1
    return -1;
}

void newPlayerHasEmptyItemSlot(s32 arg0) {
    if (arg0 == CUR_PLAYER) {
        arg0 = mp3_GwSystem.current_player_index;
    }
    
    mp3_PlayerHasItem(arg0, -1);
}

void newFixUpPlayerItemSlots(s32 playerIndex) {
    s8* playerItems;
    s32 i;
    mp3_GW_PLAYER* player0Team0 = NULL;
    s32 teamIndex;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
    player0Team0 = firstPlayerEachTeam[teamIndex];
    playerItems = player0Team0->items;

    for (i = 0; i < EXTENDED_ITEM_COUNT - 1; i++) {
        if (playerItems[i] == -1) {
            playerItems[i] = playerItems[i+1];
            playerItems[i+1] = -1;
        }
    }
}

void newAdjustPlayerCoins(s32 playerIndex, s32 arg1) {
    mp3_GW_PLAYER* player = NULL;
    s32 teamIndex;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
    player = firstPlayerEachTeam[teamIndex];

    // player = mp3_GetPlayerStruct(arg0);
    player->coins = player->coins + arg1;
    if (player->coins >= 1000) {
        player->coins = 999;
    }
    if (player->coins < 0) {
        player->coins = 0;
    }
    if (player->coins_total <= player->coins) {
        player->coins_total = player->coins;
    }
}

s32 newPlayerHasCoins(s32 playerIndex, s32 requiredCoins) {
    mp3_GW_PLAYER* player = NULL;
    s32 teamIndex;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
    player = firstPlayerEachTeam[teamIndex];

    return player->coins >= requiredCoins;
}

void newfunc_800F59B4_1095D4_shared_board(mp3_omObjData* arg0) {
    s32 var_s1;
    s32 playerIndex = arg0->work[0];
    s32 teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
    mp3_GW_PLAYER* player = firstPlayerEachTeam[teamIndex];
    s32 teamPlayerIndex = player->playerIndex;

    var_s1 = 0;
    while (arg0->scale.y <= 0.0f) {
        if (arg0->trans.x > 0.0f) {
            mp3_AdjustPlayerCoins(teamPlayerIndex, 1);
            if (((arg0->work[3] != 0) & (var_s1 == 0)) && (arg0->scale.z >= 3.0f)) {
                mp3_PlaySound(0x106);
                var_s1 = 1;
                arg0->scale.z -= 3.0f;
            }
            arg0->trans.x -= 1.0f;

        } else {
            mp3_AdjustPlayerCoins(teamPlayerIndex, -1);
            arg0->trans.x += 1.0f;
            if (arg0->work[3] != 0) {
                if ((var_s1 == 0) && (arg0->scale.z >= 3.0f)) {
                    mp3_PlaySound(0x109);
                    var_s1 = 1;
                    arg0->scale.z -= 3.0f;
                }
                if ((arg0->trans.x == 0.0f) || (mp3_gPlayers[teamPlayerIndex].coins == 0)) {
                    mp3_PlaySound(0x10A);
                }
            }
        }
        
        if ((arg0->trans.x == 0.0f) || (mp3_gPlayers[teamPlayerIndex].coins == 0)) {
            D_801055E8_119208_shared_board[playerIndex] = NULL;
            mp3_omDelObj(arg0);
            return;
        }
        arg0->scale.y += arg0->scale.x;
    }

    arg0->scale.y -= 1.0f;
    arg0->scale.z += 2.0f;
}

//AdjustPlayerCoinsGradualInternal
void newfunc_800F5BF4_109814_shared_board(s32 playerIndex, s32 coinAmount, s32 arg2) {
    s32 teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
    s32 i;
    s32 teamPlayerIndex = playerIndex;

    //if teams mode is active
    if (mp3_gPlayers[0].flags1 & 0x30) {
        // //get first player of team (this needs a different approach)
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                teamPlayerIndex = i;
                break;
            }
        }
    }
    if (coinAmount != 0) {
        if (D_801055E8_119208_shared_board[playerIndex] != NULL) {
            mp3_AdjustPlayerCoins(teamPlayerIndex, coinAmount);
            return;
        }
        
        //if player has no coins and more are attempted to be taken, exit
        if ((mp3_gPlayers[teamPlayerIndex].coins == 0) && (coinAmount < 0)) {
            return;
        }
        
        D_801055E8_119208_shared_board[playerIndex] = mp3_omAddObj(-0x8000, 0, 0, -1, func_800F59B4_1095D4_shared_board);
        D_801055E8_119208_shared_board[playerIndex]->work[0] = playerIndex;
        D_801055E8_119208_shared_board[playerIndex]->trans.x = coinAmount;

        D_801055E8_119208_shared_board[playerIndex]->scale.x = coinAmount > 0.0f ? (30.0f / coinAmount) : (30.0f / (0.0f - coinAmount));
        
        (D_801055E8_119208_shared_board[playerIndex])->scale.y = 0.0f;
        (D_801055E8_119208_shared_board[playerIndex])->scale.z  = 3.0f;
        (D_801055E8_119208_shared_board[playerIndex])->work[3] = arg2;
    }
}

void checkIfHideItemIcons(void) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        D_80101790_1153B0_shared_board = 1; //leave item icons on during 1p minigame hud movement
    } else {
        D_80101790_1153B0_shared_board = 0; //vanilla code, hide item icons
    }
}

s32 func_800DEB2C_F274C_shared_board(s32);
void func_800EC590_1001B0_shared_board(s32, s32);

s32 newfunc_800E29E8_F6608_shared_board(void) {
    mp3_GW_PLAYER* player;
    mp3_GW_SYSTEM* system = &mp3_GwSystem;
    s32 arg0 = 0;

    player = mp3_GetPlayerStruct(CUR_PLAYER);
    if (func_800DEB2C_F274C_shared_board(system->current_player_index) == 3 && player->flags2 & 0x80) {
        player->flags2 &= ~0x80;
        func_800EC590_1001B0_shared_board(-1, 0x3A2B);
    } else {
        if (func_800DEB2C_F274C_shared_board(system->current_player_index) == 3) {
            func_800EC590_1001B0_shared_board(-1, 0x3A27);
        }
        if (player->flags2 & 0x80) {
            player->flags2 &= ~0x80;
            func_800EC590_1001B0_shared_board(-1, 0x3A29);
        }        
    }

    func_800DCA64_F0684_shared_board(mp3_GwSystem.current_player_index);
    (*D_80102C70_116890_shared_board)();
    s32 teamIndex = get_team_index(&mp3_gPlayers[mp3_GwSystem.current_player_index]);

    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 i;
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                arg0 = i;
                break;
            }
        }
    }

    mp3_gPlayers[arg0].items[D_80100F90_114BB0_shared_board] = -1;
    newFixUpPlayerItemSlots(mp3_GwSystem.current_player_index);
    func_800DE9AC_F25CC_shared_board(mp3_GwSystem.current_player_index, 2);
    func_800FF900_113520_shared_board(-1, 2);
    func_800DC128_EFD48_shared_board(mp3_GwSystem.current_player_index);
    mp3_HuPrcSleep(0xF);
    return 1;
}

//bowser checks if you have any coins at all, and if not gives you some (this is the check part only)
s32 bowserCoinCheck(void) {
    //if teams are on, poke player index in coin check to team captain's index
    if (mp3_gPlayers[0].flags1 & 0x30) {
        return GetTeamCaptainCurrentIndex(D_801094F4_3C6314_name_50);
    } else {
        return D_801094F4_3C6314_name_50;
    }
}

s32 bowserPhoneGiveEvent(void) {
    //if teams are on, poke player index in bowser event to team captain's index
    if (mp3_gPlayers[0].flags1 & 0x30) {
        D_801094F4_3C6314_name_50 = GetTeamCaptainCurrentIndex(D_801094F4_3C6314_name_50);
    }
    return PlayerHasEmptyItemSlot(D_801094F4_3C6314_name_50);
}

void bowserPhoneGiveEvent2(void) {
    // //if teams are on, poke player index back to current player
    if (mp3_gPlayers[0].flags1 & 0x30) {
        D_801094F4_3C6314_name_50 = mp3_GwSystem.current_player_index;
    }
    func_800EC3C0_FFFE0_shared_board(D_801094F4_3C6314_name_50);
}

s32 bowserSuitGiveEvent(void) {
    //if teams are on, poke player index in bowser event to team captain's index
    if (mp3_gPlayers[0].flags1 & 0x30) {
        D_801094F4_3C6314_name_50 = GetTeamCaptainCurrentIndex(D_801094F4_3C6314_name_50);
    }
    return PlayerHasEmptyItemSlot(D_801094F4_3C6314_name_50);
}

void bowserSuitGiveEvent2(void) {
    // //if teams are on, poke player index back to current player
    if (mp3_gPlayers[0].flags1 & 0x30) {
        D_801094F4_3C6314_name_50 = mp3_GwSystem.current_player_index;
    }
    func_800EC3C0_FFFE0_shared_board(D_801094F4_3C6314_name_50);
}

//do coin check on team captain
s32 coinsForBowserEvent(void) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        return GetTeamCaptainCurrentIndex(mp3_GwSystem.current_player_index);
    } else {
        return D_801094F4_3C6314_name_50;
    }
}

//steal coins from team captain (or give coins if player/team had 0 coins coming into bowser event?)
void coinsForBowserEvent2(void) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        func_800F5E24_109A44_shared_board(GetTeamCaptainCurrentIndex(mp3_GwSystem.current_player_index));
    } else {
        func_800F5E24_109A44_shared_board(D_801094F4_3C6314_name_50);
    }
}

void newfunc_801059A0_4E6DC0_name_71(void) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 team0PlayersFound = 0;
        s32 team1PlayersFound = 0;
        s32 i;
        mp3_GW_PLAYER* player0TeamCaptain = NULL;
        mp3_GW_PLAYER* player1TeamCaptain = NULL;

        //move dummy character coins to team captain
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[i]);
            if (curPlayerTeamIndex == 0) {
                if (team0PlayersFound == 0) {
                    player0TeamCaptain = &mp3_gPlayers[i];
                    team0PlayersFound++;
                } else {
                    //is second player on team 0, merge coins collected into team captain
                    player0TeamCaptain->minigameCoins += mp3_gPlayers[i].minigameCoins;
                    player0TeamCaptain->minigameCoins += mp3_gPlayers[i].coins_mg_bonus;
                    mp3_gPlayers[i].minigameCoins = 0;
                    mp3_gPlayers[i].coins_mg_bonus = 0;
                }
                
            } else {
                if (team1PlayersFound == 0) {
                    player1TeamCaptain = &mp3_gPlayers[i];
                    team1PlayersFound++;
                } else {
                    //is second player on team 0, merge coins collected into team captain
                    player1TeamCaptain->minigameCoins += mp3_gPlayers[i].minigameCoins;
                    player1TeamCaptain->minigameCoins += mp3_gPlayers[i].coins_mg_bonus;
                    mp3_gPlayers[i].minigameCoins = 0;
                    mp3_gPlayers[i].coins_mg_bonus = 0;
                }
            }
        }
    }
    mp3_omInitObjMan(0x1E, 0x1E);
}

void itemDragFadeCheck(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void itemDragFadeCheck2(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void newfunc_800F641C_10A03C_shared_board(s32 playerIndex) {
    BoardStatus* temp_s2;
    s32 i;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    if (mp3_gPlayers[0].flags1 & 0x30) {
        playerIndex = GetTeamCaptainCurrentIndex(playerIndex);
    }
    
    temp_s2 = &D_801057E0_119400_shared_board[playerIndex];
    
    for (i = 0; i < ARRAY_COUNT(temp_s2->unk_40); i++) {
        if (temp_s2->unk_40[i] != -1) {
            func_800F6AA4_10A6C4_shared_board(temp_s2->playerIndex, i + 2);
            mp3_func_80055670_56270(temp_s2->unk_40[i]);
            temp_s2->unk_40[i] = -1;
        }
    }

    newfunc_800F5F98_109BB8_shared_board(playerIndex, 1);
}

//used when the item should disappear, needs to have team captain index if teams are active
void ReverseMushroomVanishHook(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }    
    func_800F696C_10A58C_shared_board(arg0, arg1, arg2, arg3);
}

void newPlunderChest3(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }   
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void func_800F69B0_10A5D0_shared_board(s32 arg0, s32 arg1, s32 arg2);

void newPlunderChest4(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }       
    func_800F69B0_10A5D0_shared_board(arg0, arg1, arg2);
}

void newDuelGlove2(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    } 
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void newDuelGlove4(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    } 
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

s32 newDuelCheck(s32 arg0) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        //get player index of captain on opposite team
        s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
        return firstPlayerEachTeam[teamIndex]->playerIndex;
    } else {
        return arg0;
    }
}

s32 newDuelCheck2(s32 playerBeingDueledIndex) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        return GetTeamCaptainCurrentIndex(mp3_GwSystem.current_player_index);
    } else {
        return mp3_GwSystem.current_player_index;
    }
}

//replaces "you already have 3 items" with "you already have 5 items"
s32 toadShopTooManyItemsTeamsText[] = {
    0x0B1A1A1A, 0x1A57656C, 0x636F6D65, 0x20746F0F,
    0x2016020F, 0x546F6164, 0x5C731619, 0x0A1A1A1A,
    0x1A020F54, 0x72616469, 0x6E672050, 0x6F737416,
    0x19C22085, 0x85855761, 0x69740A1A, 0x1A1A1A61,
    0x20736563, 0x6F6E6485, 0x85852059, 0x6F752061,
    0x6C726561, 0x64790A68, 0x61766520, 0x66697665,
    0x20697465, 0x6D738520, 0x436F6D65, 0x20626163,
    0x6B0A6166, 0x74657220, 0x796F7520, 0x75736520,
    0x6F6E6585, 0x19FF0000
};

//replaces "You already have 3 items?" with "You already have 5 items?"
s32 babyBowserShopTooManyItemsTeamsText[] = {
0x0B1A1A1A, 0x1A486182, 0x20686182, 0x20686168,
0xC2205765, 0x6C636F6D, 0x650A1A1A, 0x1A1A746F,
0x20030F42, 0x61627920, 0x426F7773, 0x65725C73,
0x204A6F69, 0x6E741619, 0xC20A1A1A, 0x1A1A8585,
0x85576861, 0x745C7320, 0x74686973, 0xC3C2C30A,
0x596F7520, 0x616C7265, 0x61647920, 0x68617665,
0x20666976, 0x65206974, 0x656D73C3, 0x0A546865,
0x6E206765, 0x74206C6F, 0x7374C219, 0xFF000000
};

void func_800EC4E4_100104_shared_board(s16, s32, s32);

void newfunc_800EC590_1001B0_shared_board(s16 arg0, s32 arg1) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        if (arg1 == 0x3B02) {
            arg1 = (s32)toadShopTooManyItemsTeamsText;
        } else if (arg1 == 0x3D02) {
            arg1 = (s32)babyBowserShopTooManyItemsTeamsText;
        }
    }
    //display shop message
    func_800EC4E4_100104_shared_board(arg0, arg1, -1);
}

s32 gameGuyCoinCheck(s32 playerIndex) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
        return firstPlayerEachTeam[teamIndex]->coins;
    } else {
        return mp3_gPlayers[playerIndex].coins;
    }
}

void wackyWatchMovementCheck1(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void wackyWatchMovementCheck2(s32 arg0, s32 arg1, s32* arg2, s32* arg3) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0);
    }
    func_800F6E4C_10AA6C_shared_board(arg0, arg1, arg2, arg3);
}

//make it so player cant duel teammate in last 5 turns
s16 newfunc_800FA818_10E438_shared_board(s32 arg0) {
    mp3_GW_SYSTEM* system =  &mp3_GwSystem;
    s16 temp_s3;
    s32 var_s2;
    s32 i;

    var_s2 = 0;
    if ((system->total_turns - system->current_turn) >= 5) {
        return 0;
    }

    temp_s3 = func_800EB184_FEDA4_shared_board(mp3_GetPlayerStruct(CUR_PLAYER)->chainIndexCur, mp3_GetPlayerStruct(CUR_PLAYER)->spaceIndexCur);
    s32 teamIndex = get_team_index(&mp3_gPlayers[mp3_GetPlayerStruct(CUR_PLAYER)->playerIndex]);

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (i != mp3_GetPlayerStruct(CUR_PLAYER)->playerIndex) {
            //if player being checked is on cur player's team, skip
            s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[i]);
            if (teamIndex == curPlayerTeamIndex) {
                continue;
            }

            if (temp_s3 == func_800EB184_FEDA4_shared_board(mp3_GetPlayerStruct(i)->chainIndexCur, mp3_GetPlayerStruct(i)->spaceIndexCur)) {
                var_s2 |= 1 << i;
                if (arg0 != 0) {
                    func_800FF900_113520_shared_board(i, 3);
                }
            }
        }    
    }
    return var_s2;
}

//related to how CPUs decide who to duel?
s32 newfunc_800F9D1C_10D93C_shared_board(void) {
    s32 i;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 sp10[MAX_PLAYERS];
    mp3_GW_SYSTEM* system = &mp3_GwSystem;

    s32 teamIndex = get_team_index(&mp3_gPlayers[system->current_player_index]);

    for (i = 0, var_s2 = 99; i < MAX_PLAYERS; i++) {
        if ((i != system->current_player_index) && ((mp3_GwSystem.unk_58 >> i) & 1) && (BoardPlayerRankCalc(i) < var_s2) && mp3_gPlayers[i].coins != 0) {
            //add team check
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[system->current_player_index]);
            if (teamIndex == curPlayerTeam) {
                continue;
            }
            var_s2 = BoardPlayerRankCalc(i);
        }
    }
    
    var_s1 = 0;
    
    for (i = 0; i < MAX_PLAYERS; i++) {
        if ((i != system->current_player_index) && ((mp3_GwSystem.unk_58 >> i) & 1) && (BoardPlayerRankCalc(i) == var_s2)) {
            //add team check
            s32 curPlayerTeam = get_team_index(&mp3_gPlayers[system->current_player_index]);
            if (teamIndex == curPlayerTeam) {
                continue;
            }            
            sp10[var_s1] = i;
            var_s1 += 1;
        }        
    }
    
    if (mp3_GetPlayerStruct(CUR_PLAYER)->coins >= 20) {
        if (mp3_GetPlayerStruct(sp10[0])->coins < 20) {
            for (i = 0, var_s2 = 99, var_s3 = 0; i < MAX_PLAYERS; i++) {
                if ((i != system->current_player_index) && (mp3_GetPlayerStruct(i)->coins >= 20)) {
                    //add team check
                    s32 curPlayerTeam = get_team_index(&mp3_gPlayers[system->current_player_index]);
                    if (teamIndex == curPlayerTeam) {
                        continue;
                    }
                    var_s3 = 1;
                    if (BoardPlayerRankCalc(i) < var_s2) {
                        var_s2 = BoardPlayerRankCalc(i);
                    }
                }
            }
            
            if (var_s3 != 0) {
                for (i = 0, var_s1 = 0; i < MAX_PLAYERS; i++) {
                    if ((i != system->current_player_index) && ((mp3_GwSystem.unk_58 >> i) & 1) && (BoardPlayerRankCalc(i) == var_s2) && mp3_gPlayers[i].coins != 0) {
                        //add team check
                        s32 curPlayerTeam = get_team_index(&mp3_gPlayers[system->current_player_index]);
                        if (teamIndex == curPlayerTeam) {
                            continue;
                        }
                        sp10[var_s1] = i;
                        var_s1++;
                    }
                }
            }
        }
    }
    i = sp10[func_800EEF80_102BA0_shared_board(var_s1)];
    if (mp3_gPlayers[i].coins == 0) {
        i = 4;
    }
    return i;
}

void mp3_ShowPlayerCoinChange(s32, s32);

void BankShowPlayerCoinChangeHook(s32 playerIndex) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 captainIndex = GetTeamCaptainCurrentIndex(playerIndex);
        mp3_GW_PLAYER* captain = mp3_GetPlayerStruct(captainIndex);
        mp3_ShowPlayerCoinChange(playerIndex, -captain->coins);
    } else {
        mp3_ShowPlayerCoinChange(playerIndex, -mp3_gPlayers[playerIndex].coins);
    }
}

//replaces "You already have three items" with "You already have five items"
s32 itemSpaceTooManyItemsTeamsText[] = {
0x0B596F75, 0x20616C72, 0x65616479, 0x20686176,
0x65206669, 0x76652069, 0x74656D73, 0x8220736F,
0x20796F75, 0x0A646F6E, 0x5C742067, 0x65742074,
0x6F20706C, 0x61792066, 0x6F722061, 0x6E79206D,
0x6F7265C2, 0x19FF0000
};

void messageReplacementCheck(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        //strID 0x3C00: You already have three items. so you.don\t get to play for any more
        if (arg1 == 0x3C00) {
            arg1 = (s32)itemSpaceTooManyItemsTeamsText;
        }
        mp3_func_8005B43C_5C03C(arg0, (char*)arg1, arg2, arg3);
    } else {
        mp3_func_8005B43C_5C03C(arg0, (char*)arg1, arg2, arg3);
    }
}


void GameGuyTakePlayerCoinsChangeHook(s32 playerIndex) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 captainIndex = GetTeamCaptainCurrentIndex(playerIndex);
        mp3_GW_PLAYER* captain = mp3_GetPlayerStruct(captainIndex);
        mp3_ShowPlayerCoinChange(playerIndex, -captain->coins);
    } else {
        mp3_ShowPlayerCoinChange(playerIndex, -mp3_gPlayers[playerIndex].coins);
    }
}

void checkTeamCoinsForGameGuy2(s32 playerIndex) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        s32 teamIndex = get_team_index(&mp3_gPlayers[playerIndex]);
        mp3_GW_PLAYER* curPlayerTeamCaptain = firstPlayerEachTeam[teamIndex];
        mp3_gPlayers[playerIndex].coins_mg_bonus = curPlayerTeamCaptain->coins;
    } else {
        mp3_gPlayers[playerIndex].coins_mg_bonus = mp3_gPlayers[playerIndex].coins;
    }
}

s32 FindCurPlayerTeammate(s32 curPlayerIndex) {
    s32 i;
    s32 teamIndex = get_team_index(&mp3_gPlayers[curPlayerIndex]);

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (i == curPlayerIndex) {
            continue;
        }
        s32 curPlayerTeamIndex = get_team_index(&mp3_gPlayers[i]);
        if (curPlayerTeamIndex == teamIndex) {
            return i;
        }
    }
    return -1;
}

void teamCheck12(s32 arg0, s32 arg1, s32 arg2) {
    if (mp3_gPlayers[0].flags1 & 0x30) {
        arg0 = GetTeamCaptainCurrentIndex(arg0); //remove teammates icon when using items from the screen
    }
    func_800F68E0_10A500_shared_board(arg0, arg1, arg2);
}

void ShowPlayerCoinChange(s32 player, s32 coins);
void func_800DB884_EF4A4_shared_board(s32);
s32 func_800DBEC0_EFAE0_shared_board(s32);
void func_800E1F28_F5B48_shared_board(s32, s32);
void func_800E48F4_F8514_shared_board(void);
void func_800E6420_FA040_shared_board(s32, s32);
s16 func_800EB184_FEDA4_shared_board(u16 arg0, u16 arg1);
void func_800EC6C8_1002E8_shared_board(void);
void func_800EC6EC_10030C_shared_board(void);
void func_800EC8EC_10050C_shared_board(s32, s32, s32, char*, s32, s32, s32);
void func_800ECC0C_10082C_shared_board(char*);
void func_800ED128_100D48_shared_board(Vec*, char*, Vec*, s32);
void func_800F5D44_109964_shared_board(s32, s32);
extern s32 D_800D41B0_D4DB0[];
extern s32 D_801014A0_1150C0_shared_board[];
void func_8004ACE0_4B8E0(s32, s16);

void func_800E455C_F817C_shared_board(void) {
    s8 sp20[MAX_PLAYERS];
    char sp28[16]; //unk type
    char sp38[16];
    s32 sp4C;
    mp3_GW_PLAYER* curPlayer;
    s16 absSpace;
    s32 temp_s0_2;
    s32 coinsToLose;
    s32 totalCoinsToLose;
    s32 playerPassed;
    s32 curPlayerIndex;
    s32 i;


    curPlayerIndex = mp3_GwSystem.current_player_index;
    curPlayer = mp3_GetPlayerStruct(CUR_PLAYER);
    if (mp3_gPlayers[curPlayerIndex].bowser_suit_flags != 0) {
        for (playerPassed = 0, i = 0; i < MAX_PLAYERS; i++) {
            //skip current player
            if (i == curPlayerIndex) {
                continue;
            }
            //if teams are active skip teammate in checks
            if (mp3_gPlayers[0].flags1 & 0x30) {
                s32 teamIndex = get_team_index(&mp3_gPlayers[curPlayerIndex]);
                s32 playerLoopTeamIndex = get_team_index(&mp3_gPlayers[i]);
                if (teamIndex == playerLoopTeamIndex) {
                    continue;
                }
            }
            absSpace = func_800EB184_FEDA4_shared_board(mp3_gPlayers[curPlayerIndex].chainIndexCur, mp3_gPlayers[curPlayerIndex].spaceIndexCur);
            if (absSpace == func_800EB184_FEDA4_shared_board(mp3_gPlayers[i].chainIndexCur, mp3_gPlayers[i].spaceIndexCur)) {
                sp20[playerPassed++] = i;
            }
        }
        if (playerPassed != 0) {
            sp4C = func_800DBEC0_EFAE0_shared_board(curPlayerIndex);
            func_800E6420_FA040_shared_board(-1, 2);
            func_800ECC0C_10082C_shared_board(sp28);
            func_800ED128_100D48_shared_board(&curPlayer->player_obj->unk18, sp28, &curPlayer->player_obj->unk18, 8);
            mp3_HuPrcSleep(8);
            totalCoinsToLose = 0;

            for (i = 0; i < playerPassed; i++) {
                if (mp3_gPlayers[sp20[i]].coins != 0) {
                    if (mp3_gPlayers[sp20[i]].coins < 20) {
                        coinsToLose = mp3_gPlayers[sp20[i]].coins;
                    } else {
                        coinsToLose = 20;
                    }
                    mp3_sprintf(sp38, "%2d", coinsToLose);
                    func_800EC8EC_10050C_shared_board(-1, 0x3A15, D_801014A0_1150C0_shared_board[mp3_gPlayers[sp20[i]].characterID], sp38, D_801014A0_1150C0_shared_board[mp3_gPlayers[curPlayerIndex].characterID], 0, 0);
                    temp_s0_2 = -coinsToLose;
                    func_800EC6C8_1002E8_shared_board();
                    totalCoinsToLose += coinsToLose;
                    func_800EC6EC_10030C_shared_board();
                    func_8004ACE0_4B8E0(0, sp20[i]);
                    func_800E1F28_F5B48_shared_board(sp20[i], temp_s0_2);
                    func_800F5D44_109964_shared_board(sp20[i], temp_s0_2);
                    mp3_HuPrcSleep(30);
                } else {
                    func_800EC8EC_10050C_shared_board(-1, 0x3A16, D_801014A0_1150C0_shared_board[mp3_gPlayers[sp20[i]].characterID], NULL, 0, 0, 0);
                    func_800EC6C8_1002E8_shared_board();
                    func_800EC6EC_10030C_shared_board();                        
                }
            }
            
            if (totalCoinsToLose != 0) {
                if (mp3_gPlayers[0].flags1 & 0x30) {
                    s32 teamIndex = get_team_index(&mp3_gPlayers[curPlayerIndex]);
                    newShowPlayerCoinChange(teamIndex, totalCoinsToLose); //display to either top left or top right
                } else {
                    originalShowPlayerCoinChange(curPlayerIndex, totalCoinsToLose);
                }
                
                func_800F5D44_109964_shared_board(curPlayerIndex, totalCoinsToLose);
                mp3_HuPrcSleep(30);
            }
            if (sp4C != 0) {
                func_800DB884_EF4A4_shared_board(mp3_GwSystem.current_player_index);
            }
            func_800E6420_FA040_shared_board(0, 2);
        }
    }
    
    if (D_800D41B0_D4DB0[4] == 0) {
        func_800E48F4_F8514_shared_board();
    }
}