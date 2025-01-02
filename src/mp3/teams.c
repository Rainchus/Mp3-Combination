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

void SetItemCountToGP(s32 itemCount);

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

s32 get_team_index(mp3_GW_PLAYER* player) {
    return (player->flags1 & 0x30) >> 5; //returns team index 0 or 1
}

s32 GetCurrentPlayerScore(s32 arg0) {
    return mp3_gPlayers[arg0].stars * 1000 + mp3_gPlayers[arg0].coins;
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
    s32 score[4];

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
    mp3_GW_PLAYER* teammate;
    mp3_GW_PLAYER* curPlayer = &mp3_gPlayers[playerIndex];

    //find current player's teammate
    for (i = 0; i < 4; i++) {
        teammate = &mp3_gPlayers[i];
        if (i == playerIndex) {
            continue;
        }
        s32 curPlayerTeam = get_team_index(teammate);
        if (curPlayerTeam == teamIndex) {
            break;
        }
    }
    
    playerBoardStatus = &D_801057E0_119400_shared_board[playerIndex];
    s32 combinedCoins = curPlayer->coins + teammate->coins;
    if (playerBoardStatus->prevCoins != combinedCoins) {
        coinDigits.digits[HUNDREDS] = combinedCoins / 100;
        coinDigits.digits[TENS] = combinedCoins / 10 % 10;
        coinDigits.digits[ONES] = combinedCoins % 10;
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
    
        playerBoardStatus->prevCoins = combinedCoins;
    }

    s32 combinedStars = curPlayer->stars + teammate->stars;

    if (playerBoardStatus->prevStars != combinedStars) {
        if (combinedStars > 99) {
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 9, 0);
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 9, 0);
        } else {
            if (combinedStars > 9) {
                func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, combinedStars, 0);
            } else {
                func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, DIGIT_X, 0);
            }
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, combinedStars % 10, 0);
        }
        func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 1);
        func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 1);
    
        playerBoardStatus->prevStars = combinedStars;
    }
    coinDigits.unk_08[0] = combinedCoins;
    coinDigits.unk_08[1] = combinedStars;
    
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

void newfunc_800F4190_107DB0_shared_board(void) {
    void* temp_v0;
    s32 i;
    s16* spriteIDs;
    s32 sp10[2] = {0x130112, 0x130111};
    s32 team0Set = 0;
    s32 team1Set = 0;

    firstPlayerEachTeam[0] = NULL;
    firstPlayerEachTeam[1] = NULL;

    for (i = 0; i < 4; i++) {
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
        SetItemCountToGP(5); //5 items for teams
        temp_v0 = mp3_ReadMainFS(0x13027A); //extended background graphic
    } else {
        SetItemCountToGP(3); //3 items for teams
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

    // //set x and y position
    // PlayerBoardStatusRootPosition[8][0] = 0x30;
    // PlayerBoardStatusRootPosition[8][1] = 0x4C;
    
    // PlayerBoardStatusRootPosition[9][0] = 0xA0;
    // PlayerBoardStatusRootPosition[9][1] = 0x4C;

    // PlayerBoardStatusRootPosition[10][0] = 0x30;
    // PlayerBoardStatusRootPosition[10][1] = 0x7E;

    // PlayerBoardStatusRootPosition[11][0] = 0xA0;
    // PlayerBoardStatusRootPosition[11][1] = 0x7E;
    

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

void newfunc_800F3FF4_107C14_shared_board(s32 arg0) {
    s32 temp_s3;
    s16 var_s1;
    s32 i;
    s32 curItem;
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

    temp_s7 = &D_801057E0_119400_shared_board[arg0];
    temp_s5 = temp_s7->playerIndex;
    var_s2 = NULL;
    for (i = 0; i < EXTENDED_ITEM_COUNT; i++) {
        var_s2 = NULL;
        if (mp3_gPlayers[arg0].items[i] != -1) {
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
            if (arg0 == mp3_GwSystem.current_player_index) {
                func_80055458_56058(temp_s5, i + 2, 0x100U);
            } else {
                func_80055458_56058(temp_s5, i + 2, 0x80U);
            }
            
        } else {
            temp_s7->unk_40[i] = -1;
        }
    }
}

/////
//AdjustPlayerCoinsGradual
void newfunc_800F5D44_109964_shared_board(s32 arg0, s32 arg1) {
    // s32 i;

    // //if teams is on, replace playerIndex with team's player index
    // if (mp3_gPlayers[0].flags1 & 0x30) {
    //     s32 teamIndex = get_team_index(&mp3_gPlayers[arg0]);
    //     for (i = 0; i < MAX_PLAYERS; i++) {
    //         s32 curPlayerTeam = get_team_index(&mp3_gPlayers[i]);
    //         if (teamIndex == curPlayerTeam) {
    //             arg0 = i;
    //             break;
    //         }
    //     }
    // }
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
    s8* teammateItems;
    s32 i;
    mp3_GW_PLAYER* player0Team0 = NULL;
    mp3_GW_PLAYER* player1Team0 = NULL;
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
    s32 i;

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
    s32 i;

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
