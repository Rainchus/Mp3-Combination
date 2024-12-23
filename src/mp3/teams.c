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
    0x000D, 0x0002, //team0 player 1
};

s16 newTeam1RootPositions[][2] = {
    0x00A0, 0x0010, //team1 player 0
    0x009D, 0x0002, //team1 player 1
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

//used so the placement icon updates correctly
//in other instances, the game actually 
s32 BoardPlayerTeamRankCalc(s32 player) {
    s32 rank;
    s32 i;
    s32 score[4];

    s32 team0Score = 0;
    s32 team1Score = 0;

    s32 curPlayerTeam = get_team_index(&mp3_gPlayers[player]);


    for (i = 0; i < 4; i++) {
        s32 score = GetCurrentPlayerScore(i);
        if (mp3_gPlayers[i].flags1 & 0x10) {
            //is team index 0
            team0Score += score;
        } else {
            //else, team index 1
            team1Score += score;
        }
    }

    if (curPlayerTeam == 0) {
        return team0Score < team1Score;
    } else {
        return team1Score < team0Score;
    }
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
        if (i == playerIndex) {
            continue;
        }
        teammate = &mp3_gPlayers[i];
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



void newfunc_800F3400_107020_shared_board(omObjData* arg0) {
    BoardStatus* temp_s2;
    BoardStatus* temp_s3;
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
                        for (k = 0; k < 14; k++) {
                            SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                        }
                        continue;
                    }

                    for (k = 0; k < 14; k++) {
                        switch (k) {
                        case 9:
                            if (mp3_gPlayers[i].flags1 & 1) {
                                break;
                            }
                            continue;
                        case 11:
                        case 12:
                        case 13:
                            if (mp3_gPlayers[i].items[k - 11] == ITEM_NONE) {
                                continue;
                            }

                            func_80055024_55C24(temp_s2->playerIndex, k, D_8010559C_1191BC_shared_board[mp3_gPlayers[i].items[k - 11]], 0);
                            func_800550F4_55CF4(temp_s2->playerIndex, k, 0);
                            func_80055294_55E94(temp_s2->playerIndex, k, (i * 5) + 0x478E);
                            SprAttrSet(temp_s2->playerIndex, k, 0);
                            var_v1 = k;
                            if (i >= 2) {
                                var_v1 = k + 3;
                            }
                            func_80054904_55504(temp_s2->playerIndex, k, D_801018E4_115504_shared_board[var_v1][0], D_801018E4_115504_shared_board[var_v1][1]);
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
                        for (j = 0; j < 14; j++) {
                            //if face sprite, dont turn sprite off and set high priority
                            if (j == 1) {
                                func_80055294_55E94(temp_s2->playerIndex, j, 0x1000);
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
                        for (j = 0; j < 14; j++) {
                            //if face sprite, dont turn sprite off
                            if (j == 1) {
                                func_80055294_55E94(temp_s2->playerIndex, j, 0x1000);
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
    f32 temp_f0;
    f32 temp_f0_2;

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
void newfunc_800F4190_107DB0_shared_board(void) {
    BoardStatus* temp_s2;
    void* temp_v0;
    s32 i;
    s16* spriteIDs;
    s32 sp10[2] = {0x130112, 0x130111};
    s32 team0Set = 0;
    s32 team1Set = 0;
    u8 teams[2] = {0, 0};

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

    //set new player icon hud position
    D_801018E4_115504_shared_board[1][0] = 0;
    D_801018E4_115504_shared_board[1][1] = 0;

    spriteIDs = mp3_D_80105588_1191A8_shared_board;
    //if teams, use extended graphic
    if (mp3_gPlayers[0].flags1 & 0x30) {
        temp_v0 = mp3_ReadMainFS(0x13027A); //extended background graphic
    } else {
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

    for (i = 0; i < 7; i++) {
        s16 xPos = D_801018E4_115504_shared_board[i + 2][0];
        s16 yPos = D_801018E4_115504_shared_board[i + 2][1];

        xPos += X_OFFSET;
        yPos += Y_OFFSET;

        D_801018E4_115504_shared_board[i + 2][0] = xPos;
        D_801018E4_115504_shared_board[i + 2][1] = yPos;
    }

    s32 team0 = 0;
    s32 team1 = 0;
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

// 00000000 00000000 00030007 0003FFF7
// 0010000A 001A000A 0024000A 0010FFFA
// 001AFFFA FFEC000E FFD30000 00030017
// 00140017 00250017 0003FFE9 0014FFE9
// 0025FFE9 00040000

// 0x0030, 0x0007
// 0x0030, 0xFFF7

void newfunc_800F3A80_1076A0_shared_board(s32 arg0) {
    s16 temp_s2;
    s32 i;

    temp_s2 = D_801057E0_119400_shared_board[arg0].playerIndex;

    for (i = 0; i < 2; i++) {
        func_80055024_55C24(temp_s2, i + 2, D_80105592_1191B2_shared_board[i], 0);
        func_80055294_55E94(temp_s2, i + 2, ((arg0 * 5) + 0x4790));
        SprAttrReset(temp_s2, i + 2, 0xFFFF);
        SprAttrSet(temp_s2, i + 2, 0x1000);
        func_800552DC_55EDC(temp_s2, i + 2, 0.0f);
        func_80054904_55504(temp_s2, i + 2, D_801018E4_115504_shared_board[i + 2][0], D_801018E4_115504_shared_board[i + 2][1]);
        func_800550B4_55CB4(temp_s2, i + 2, 0.0f);
        func_80055458_56058(temp_s2, i + 2, 0x100);
    }
}