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

void originalfunc_800F4798_1083B8_shared_board(u32 playerIndex, s32 turnStatus) {
    if (playerIndex < MAX_PLAYERS) {
        func_80055420_56020(D_801057E0_119400_shared_board[playerIndex].playerIndex, 0, D_8010188C_1154AC_shared_board[turnStatus].r, D_8010188C_1154AC_shared_board[turnStatus].g, D_8010188C_1154AC_shared_board[turnStatus].b);
        D_801057E0_119400_shared_board[playerIndex].spaceType = turnStatus;
    }
}

void originalUpdatePlayerBoardStatus(s32 playerIndex) {
    UnkCoinThing coinDigits;
    BoardStatus* playerBoardStatus;
    s32 var_v1;
    s32 i;
    
    playerBoardStatus = &D_801057E0_119400_shared_board[playerIndex];
    if (playerBoardStatus->prevCoins != mp3_gPlayers[playerIndex].coins) {
        coinDigits.digits[HUNDREDS] = mp3_gPlayers[playerIndex].coins / 100;
        coinDigits.digits[TENS] = mp3_gPlayers[playerIndex].coins / 10 % 10;
        coinDigits.digits[ONES] = mp3_gPlayers[playerIndex].coins % 10;
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
    
        playerBoardStatus->prevCoins = mp3_gPlayers[playerIndex].coins;
    }

    if (playerBoardStatus->prevStars != mp3_gPlayers[playerIndex].stars) {
        if (mp3_gPlayers[playerIndex].stars > 99) {
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 9, 0);
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 9, 0);
        } else {
            if (mp3_gPlayers[playerIndex].stars > 9) {
                func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, (mp3_gPlayers[playerIndex].stars / 10), 0);
            } else {
                func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, DIGIT_X, 0);
            }
            func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, mp3_gPlayers[playerIndex].stars % 10, 0);
        }
        func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 1);
        func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 1);
    
        playerBoardStatus->prevStars = mp3_gPlayers[playerIndex].stars;
    }
    coinDigits.unk_08[0] = mp3_gPlayers[playerIndex].coins;
    coinDigits.unk_08[1] = mp3_gPlayers[playerIndex].stars;
    
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
    if (playerBoardStatus->prevRank != BoardPlayerRankCalc(playerIndex)) {
        func_80055140_55D40(playerBoardStatus->playerIndex, DIGIT_X, BoardPlayerRankCalc(playerIndex), 0);
        func_800550F4_55CF4(playerBoardStatus->playerIndex, DIGIT_X, 1);
        playerBoardStatus->prevRank = BoardPlayerRankCalc(playerIndex);
    }
}

void originalfunc_800F3400_107020_shared_board(mp3_omObjData* arg0) {
    BoardStatus* temp_s2;
    s32 var_v1;
    s32 i, k;

    while (1) {
        if (D_800D20B1_D2CB1 == 0) {
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
                        case COM_ICON:
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
                            SprPriSet(temp_s2->playerIndex, k, (i * 5) + 0x478E);
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
                    originalUpdatePlayerBoardStatus(i);
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
void originalfunc_800F4874_108494_shared_board(s32 playerIndex, s16 arg1, s16 arg2) {
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
void originalfunc_800F4190_107DB0_shared_board(void) {
    void* temp_v0;
    s32 i;
    s16* spriteIDs;
    s32 sp10[2] = {0x130112, 0x130111};

    spriteIDs = mp3_D_80105588_1191A8_shared_board;
    //unk sprite id
    temp_v0 = mp3_ReadMainFS(0x13010F);
    spriteIDs[0] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);
    
    //create player sprite ids
    for (i = 0; i < MAX_PLAYERS; i++) {
        temp_v0 = mp3_ReadMainFS(mp3_D_80101944_115564_shared_board[mp3_gPlayers[i].characterID]);
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

    //if teams, set gp to 5 for item cap
    if (mp3_gPlayers[0].flags1 & 0x30) {
        SetItemCountToGP(5); //5 items for teams
    } else {
        SetItemCountToGP(3); //3 items for teams
    }
}

void originalfunc_800F3A80_1076A0_shared_board(s32 arg0) {
    s16 temp_s2;
    s32 i;

    temp_s2 = D_801057E0_119400_shared_board[arg0].playerIndex;

    for (i = 0; i < 2; i++) {
        func_80055024_55C24(temp_s2, i + 2, D_80105592_1191B2_shared_board[i], 0);
        SprPriSet(temp_s2, i + 2, ((arg0 * 5) + 0x4790));
        SprAttrReset(temp_s2, i + 2, 0xFFFF);
        SprAttrSet(temp_s2, i + 2, 0x1000);
        func_800552DC_55EDC(temp_s2, i + 2, 0.0f);
        func_80054904_55504(temp_s2, i + 2, D_801018E4_115504_shared_board[i + 2][0], D_801018E4_115504_shared_board[i + 2][1]);
        func_800550B4_55CB4(temp_s2, i + 2, 0.0f);
        func_80055458_56058(temp_s2, i + 2, 0x100);
    }
}

void originalfunc_800F3F0C_107B2C_shared_board(s32 arg0) {
    s16 temp_s2;

    temp_s2 = D_801057E0_119400_shared_board[arg0].playerIndex;
    func_80055024_55C24(temp_s2, 9, D_8010559A_1191BA_shared_board, 0);
    func_800550F4_55CF4(temp_s2, 9, 0);
    SprPriSet(temp_s2, 9, ((arg0 * 5) + 0x478E) & 0xFFFF);
    SprAttrSet(temp_s2, 9, 0);
    func_80054904_55504(temp_s2, 9, D_80101908_115528_shared_board[0], D_80101908_115528_shared_board[1]);
    if (!(mp3_gPlayers[arg0].flags1 & 1)) {
        SprAttrSet(temp_s2, 9, 0x8000);
    }
}

s32 originalfunc_800EEA58_102678_shared_board(s32 arg0) {
    s32 var_a0_2;
    s32 var_a0;
    s32 i;
    s32 score[4];

    if (mp3_GWBoardFlagCheck(0xF) == 0) {
        return BoardPlayerRankCalc(arg0);
    }
    
    for (i = 0; i < 4; i++) {
        score[i] = func_800EECB0_1028D0_shared_board(i);
    }

    //calc what the highest mg coin total is
    for (i = 0, var_a0_2 = -100000; i < 4; i++) {
        if (var_a0_2 < mp3_gPlayers[i].mg_star_coins) {
            var_a0_2 = mp3_gPlayers[i].mg_star_coins;
        }
    }

    //award players 1000 points (a star) for having the highest mg coin total
    for (i = 0; i < 4; i++) {
        if (mp3_gPlayers[i].mg_star_coins == var_a0_2) {
            score[i] += 1000;
        }
    }

    //calc what the highest amount of coins collected was
    for (i = 0, var_a0_2 = -100000; i < 4; i++) {
        if (var_a0_2 < mp3_gPlayers[i].coins_total) {
            var_a0_2 = mp3_gPlayers[i].coins_total;
        }
    }

    //award players 1000 points (a star) for having the highest amount of coins
    for (i = 0; i < 4; i++) {
        if (mp3_gPlayers[i].coins_total == var_a0_2) {
            score[i] += 1000;
        }
    }

    //calc what the highest amount of happening spaces landed on was
    for (i = 0, var_a0_2 = -100000; i < 4; i++) {
        if (var_a0_2 < mp3_gPlayers[i].happeningSpacesLandedOn) {
            var_a0_2 =  mp3_gPlayers[i].happeningSpacesLandedOn;
        }
    }

    //award players 1000 points (a star) for landing on the most happening spaces
    for (i = 0; i < 4; i++) {
        if (mp3_gPlayers[i].happeningSpacesLandedOn == var_a0_2) {
            score[i] += 1000;
        }
    }

    for (i = 0, var_a0 = 0; i < 4; i++) {
        if (i != arg0) {
            var_a0 += score[arg0] < score[i];
        }
    }

    return var_a0;
}

void originalfunc_800F39C0_1075E0_shared_board(s32 playerIndex) {
    s16 temp_s1;

    temp_s1 = D_801057E0_119400_shared_board[playerIndex].playerIndex;
    func_80055024_55C24(temp_s1, 1, mp3_D_80105588_1191A8_shared_board[playerIndex+1], 0);
    func_800550F4_55CF4(temp_s1, 1, 0);
    SprPriSet(temp_s1, 1, ((playerIndex * 5) + 0x4790));
    SprAttrSet(temp_s1, 1, 0);
    func_80054904_55504(temp_s1, 1, D_801018E4_115504_shared_board[1][0], D_801018E4_115504_shared_board[1][1]);
}

void originalfunc_800F3BD0_1077F0_shared_board(s32 arg0) {
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
        func_80054904_55504(temp_s2, i + 4, D_801018E4_115504_shared_board[i + 4][0], D_801018E4_115504_shared_board[i + 4][1]);
        func_80055420_56020(temp_s2, i + 4, 0xFFU, 0xFFU, 0xFF);
        func_80055458_56058(temp_s2, i + 4, 0x100U);
        func_800552DC_55EDC(temp_s2, i + 4, 0.0f);        
    }
    mp3_HuFreeFilePerm(temp_v0);
}

void originalfunc_800F3E34_107A54_shared_board(s32 arg0) {
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
    func_80054904_55504(temp_s0, 0xA, D_801018E4_115504_shared_board[10][0], D_801018E4_115504_shared_board[10][1]);
}

void originalfunc_800F3FF4_107C14_shared_board(s32 arg0) {
    s32 temp_s3;
    s16 var_s1;
    s32 i;
    s32 curItem;
    temp_s3 = D_801057E0_119400_shared_board[arg0].playerIndex;

    for (i = 0; i < NORMAL_ITEM_COUNT; i++) {
        curItem = mp3_gPlayers[arg0].items[i];
        curItem = (curItem == -1) ? 0 : curItem;
        func_80055024_55C24(temp_s3, i + 0xB, D_8010559C_1191BC_shared_board[curItem], 0);
        func_800550F4_55CF4(temp_s3, i + 0xB, 0);
        SprPriSet(temp_s3, i + 0xB, ((arg0 * 5) + 0x478E));
        SprAttrSet(temp_s3, i + 0xB, 0);
        var_s1 = i + 0xB;
        if (arg0 >= 2) {
            var_s1 = i + 0xE;
        }
        func_80054904_55504(temp_s3, i + 0xB, D_801018E4_115504_shared_board[var_s1][0], D_801018E4_115504_shared_board[var_s1][1]);
        if (mp3_gPlayers[arg0].items[i] == -1) {
            SprAttrSet(temp_s3, i + 0xB, 0x8000);
        }
    }
}

void originalfunc_800F6BC4_10A7E4_shared_board(s32 arg0) {
    BoardStatus* temp_s2;
    f32 var_f20;
    s32 i, j;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            temp_s2 = &D_801057E0_119400_shared_board[i];
            if (temp_s2->uiUpdatePaused == TRUE) {
                func_800F6A88_10A6A8_shared_board(temp_s2->playerIndex, 2);
                func_80054904_55504(temp_s2->playerIndex, 1, D_801018E4_115504_shared_board[1][0], D_801018E4_115504_shared_board[1][1]);
                if (mp3_gPlayers[i].items[0] != ITEM_NONE) {
                    //used for item positions when closing items screen
                    for (j = 0; j < NORMAL_ITEM_COUNT; j++) {
                        switch (j) {
                        case 0:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, j * 0x12 + 3, 5);
                            break;
                        case 1:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, j * 0x12 + 3, -5);
                            break;
                        case 2:
                            func_80054904_55504(temp_s2->playerIndex, j + 2, j * 0x12 + 3, 5);
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

void originalfunc_800F3370_106F90_shared_board(void) {
    s32 i, j;

    for (i = 0; i < MAX_PLAYERS; i++) {
        BoardStatus* boardStatus = &D_801057E0_119400_shared_board[i];
        for (j = 0; j < 14; j++) {
            SprAttrSet(boardStatus->playerIndex, j, 0x8000);
        }
    }
}

void originalfunc_800F6ECC_10AAEC_shared_board(s32 arg0) {
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
                    for (j = 0; j < NORMAL_ITEM_COUNT; j++) {
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

void originalfunc_800F6AD0_10A6F0_shared_board(s32 arg0, f32 xScale, f32 yScale) {
    BoardStatus* temp_s1;
    s32 i;

    temp_s1 = &D_801057E0_119400_shared_board[arg0];
    switch(temp_s1->uiUpdatePaused) {
    case FALSE:
        for (i = 0; i < 14; i++) {
            SprScale(temp_s1->playerIndex, i, xScale, yScale);
        }
        break;
    case TRUE:
        for (i = 0; i < 5; i++) {
            SprScale(temp_s1->playerIndex, i, xScale, yScale);
        }
        SprScale(temp_s1->playerIndex, 9, xScale, yScale);
        break;
    }
}

//sets item positions when pressing B and you have control of hand cursor
void originalfunc_800F6E4C_10AA6C_shared_board(s32 playerIndex, s32 itemIndex, s32* xPos, s32* yPos) {
    s32 xPosTemp;
    
    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    *xPos = PlayerBoardStatusRootPosition[playerIndex][0] + ITEMS_POS_OFFSET_X;
    *yPos = PlayerBoardStatusRootPosition[playerIndex][1] + ITEMS_POS_OFFSET_Y;

    xPosTemp = *xPos + 3;
    *xPos = xPosTemp + (itemIndex * 18);
    //if item index is 1, move item up on the screen 5 units
    //if item index 0 or 2, move down on the screen 5 units
    if (itemIndex == 1) {
        *yPos -= 5;
    } else {
        *yPos += 5;
    }
}

void originalfunc_800F5F98_109BB8_shared_board(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    BoardStatus* temp_s7;
    s16 temp_s5;
    s16 i;
    void* var_s2;

    temp_s7 = &D_801057E0_119400_shared_board[arg0];
    temp_s5 = temp_s7->playerIndex;
    var_s2 = NULL;
    for (i = 0; i < NORMAL_ITEM_COUNT; i++) {
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

void originalfunc_800E35F8_F7218_shared_board(void) {
    f32 temp_f0;
    f32 var_f20;
    s32* temp_s0;
    s32 prev;

    temp_s0 = mp3_HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    prev = *temp_s0;
    while (*temp_s0 != -1) {
        if (*temp_s0 != prev) {
            func_800F696C_10A58C_shared_board(mp3_GwSystem.current_player_index, prev, 1.0f, 1.0f);
            var_f20 = 0.0f;
            prev = *temp_s0;
        }
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }
        temp_f0 = (mp3_HuMathSin(var_f20) * 0.2f) + 1.0f;
        func_800F696C_10A58C_shared_board(mp3_GwSystem.current_player_index, *temp_s0, temp_f0, temp_f0);
        mp3_HuPrcVSleep();
        var_f20 += 13.0f;
        
    }
    func_800F696C_10A58C_shared_board(mp3_GwSystem.current_player_index, prev, 1.0f, 1.0f);
    mp3_omDelPrcObj(0);
}

void originalfunc_800F59B4_1095D4_shared_board(mp3_omObjData* arg0) {
    s32 var_s1;

    var_s1 = 0;
    while (arg0->scale.y <= 0.0f) {
        if (arg0->trans.x > 0.0f) {
            mp3_AdjustPlayerCoins(arg0->work[0], 1);
            if (((arg0->work[3] != 0) & (var_s1 == 0)) && (arg0->scale.z >= 3.0f)) {
                mp3_PlaySound(0x106);
                var_s1 = 1;
                arg0->scale.z -= 3.0f;
            }
            arg0->trans.x -= 1.0f;

        } else {
            mp3_AdjustPlayerCoins(arg0->work[0], -1);
            arg0->trans.x += 1.0f;
            if (arg0->work[3] != 0) {
                if ((var_s1 == 0) && (arg0->scale.z >= 3.0f)) {
                    mp3_PlaySound(0x109);
                    var_s1 = 1;
                    arg0->scale.z -= 3.0f;
                }
                if ((arg0->trans.x == 0.0f) || (mp3_gPlayers[arg0->work[0]].coins == 0)) {
                    mp3_PlaySound(0x10A);
                }
            }
        }
        
        if ((arg0->trans.x == 0.0f) || (mp3_gPlayers[arg0->work[0]].coins == 0)) {
            D_801055E8_119208_shared_board[arg0->work[0]] = NULL;
            mp3_omDelObj(arg0);
            return;
        }
        arg0->scale.y += arg0->scale.x;
    }

    arg0->scale.y -= 1.0f;
    arg0->scale.z += 2.0f;
}

void originalfunc_800F7610_10B230_shared_board(void) {
    s32 prevItem = -1;
    s32 i = 0;
    s32* boardItemIds = D_80105630_119250_shared_board;
    
    for (; i < NORMAL_ITEM_COUNT; i++) {
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

//decide what type of minigame will be played
s32 originalfunc_800F52C4_108EE4_shared_board(void) {
    u8 type1Indices[4];
    u8 type2Indices[4];
    u8 otherCount = 0;
    u8 type2Count = 0;
    u8 type1Count = 0;
    s32 i;

    for (i = 0; i < MAX_PLAYERS; i++) {
        switch (D_801057E0_119400_shared_board[i].spaceType) {
        case 1:
            type1Indices[type1Count++] = i;
            break;
        case 2:
            type2Indices[type2Count++] = i;
            break;
        default:
            otherCount++;
        }
    }

    // Determine result based on counts
    if (otherCount > 0) {
        return -1;
    }

    if (type1Count == 0 || type1Count == 4) {
        return 0;
    }

    if (type1Count == 1) {
        D_801055F8_119218_shared_board = type1Indices[0];
        return 1;
    }

    if (type1Count == 3) {
        D_801055F8_119218_shared_board = type2Indices[0];
        return 1;
    }

    return 2;
}

/////////

void originalShowPlayerCoinChange(s32 player, s32 coins) {
    D_80102C48_116868_shared_board = 1;
    func_800E1934_F5554_shared_board(player, coins);
}

s32 originalPlayerHasItem(s32 playerIndex, s32 itemID) {
    s32 i;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    for (i = 0; i < NORMAL_ITEM_COUNT; i++) {
        if (mp3_gPlayers[playerIndex].items[i] == itemID) {
            break;
        }
    }

    if (i == 3) {
        return -1;
    } else {
        return i;
    }
}

void originalPlayerHasEmptyItemSlot(s32 arg0) {
    if (arg0 == CUR_PLAYER) {
        arg0 = mp3_GwSystem.current_player_index;
    }
    
    mp3_PlayerHasItem(arg0, -1);
}

void originalFixUpPlayerItemSlots(s32 arg0) {
    s8* playerItems;
    s32 i;


    if (arg0 == -1) {
        arg0 = mp3_GwSystem.current_player_index;
    }

    playerItems = mp3_gPlayers[arg0].items;

    for (i = 0; i < 2; i++) {
        if (playerItems[i] == -1) {
            playerItems[i] = playerItems[i+1];
            playerItems[i+1] = -1;
        }
    }
}

void originalAdjustPlayerCoins(s32 arg0, s32 arg1) {
    mp3_GW_PLAYER* player;

    player = mp3_GetPlayerStruct(arg0);
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

s32 originalPlayerHasCoins(s32 playerIndex, s32 requiredCoins) {
    return mp3_GetPlayerStruct(playerIndex)->coins >= requiredCoins;
}

s32 originalfunc_800E29E8_F6608_shared_board(void) {
    mp3_GW_PLAYER* player;
    mp3_GW_SYSTEM* system = &mp3_GwSystem;

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
    mp3_gPlayers[mp3_GwSystem.current_player_index].items[D_80100F90_114BB0_shared_board] = -1;
    originalFixUpPlayerItemSlots(mp3_GwSystem.current_player_index);
    func_800DE9AC_F25CC_shared_board(mp3_GwSystem.current_player_index, 2);
    func_800FF900_113520_shared_board(-1, 2);
    func_800DC128_EFD48_shared_board(mp3_GwSystem.current_player_index);
    mp3_HuPrcSleep(0xF);
    return 1;
}

//Baby bowser gives warp blocks from item space
void originalfunc_800F7F7C_10BB9C_shared_board(void) {
    func_800EC590_1001B0_shared_board(5, 0x3C21);
    D_80105630_119250_shared_board[0] = D_80105630_119250_shared_board[1] = D_80105630_119250_shared_board[2] = ITEM_WARP_BLOCK;
    func_800F76A4_10B2C4_shared_board(0);
    func_800EC590_1001B0_shared_board(5, 0x3C1D);
}