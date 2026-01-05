#include "mp3.h"
#include "ovl_80.h"

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

extern s16 mp3_D_80105588_1191A8_shared_board[];
extern s32 mp3_D_80101944_115564_shared_board[]; //mainFS ids for character images
extern s32 mp3_D_801019D0_1155F0_shared_board[];
void mp3_PushItemCountToGP(s32 itemTotal); //must be 3 or 5

#define BASE_X -30
#define BASE_Y 24
#define BASE_Y_INVERTED -24
#define ITEM_SPACING 16

s16 item0XY[] = {3, 5};
s16 item1XY[] = {21, -5};
s16 item2XY[] = {39, 5};
s16 item3XY[] = {57, -5};
s16 item4XY[] = {75, 5};

extern s16 D_801018E4_115504_shared_board[][2]; //original player icon positions + item icons

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
//player0 and player1 items xy positions
{BASE_X + (ITEM_SPACING * 0), BASE_Y}, //item 0
{BASE_X + (ITEM_SPACING * 1), BASE_Y}, //item 1
{BASE_X + (ITEM_SPACING * 2), BASE_Y}, //item 2
{BASE_X + (ITEM_SPACING * 3), BASE_Y}, //item 3
{BASE_X + (ITEM_SPACING * 4), BASE_Y}, //item 4

//player2 and player3 items xy positions
{BASE_X + (ITEM_SPACING * 0), BASE_Y_INVERTED}, //item 0
{BASE_X + (ITEM_SPACING * 1), BASE_Y_INVERTED}, //item 1
{BASE_X + (ITEM_SPACING * 2), BASE_Y_INVERTED}, //item 2
{BASE_X + (ITEM_SPACING * 3), BASE_Y_INVERTED}, //item 3
{BASE_X + (ITEM_SPACING * 4), BASE_Y_INVERTED}, //item 4
};

s16 (*iconPosList)[2] = NULL;
s32 mp3_GetItemCount(void);

f32 itemScale = 0.70f;
s32 itemXSpacing = 12;
s32 itemYSpacing = 5;

//create sprite IDs for hud elements
void func_800F4190_107DB0_shared_board(void) {
    void* temp_v0;
    s32 i;
    s16* spriteIDs;
    s32 sp10[2] = {0x130112, 0x130111};

    spriteIDs = mp3_D_80105588_1191A8_shared_board;
    //unk sprite id
    temp_v0 = mp3_DataRead(0x13010F);
    spriteIDs[0] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);
    
    //create player sprite ids
    for (i = 0; i < MAX_PLAYERS; i++) {
        temp_v0 = mp3_DataRead(mp3_D_80101944_115564_shared_board[mp3_GwPlayer[i].chr]);
        spriteIDs[i + 1] = mp3_func_80055810_56410(temp_v0);
        mp3_HuFreeFilePerm(temp_v0);
    }

    //create coin and star sprite ids
    for (i = 0; i < ARRAY_COUNT(sp10); i++) {
        temp_v0 = mp3_DataRead(sp10[i]);
        spriteIDs[i + 5] = mp3_func_80055810_56410(temp_v0);
        mp3_HuFreeFilePerm(temp_v0);
    }

    //create placement sprite id
    temp_v0 = mp3_DataRead(0x130110);
    spriteIDs[8] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);

    //create COM text sprite id
    temp_v0 = mp3_DataRead(0x1300D1);
    spriteIDs[9] = mp3_func_80055810_56410(temp_v0);
    mp3_HuFreeFilePerm(temp_v0);

    //create item sprite ids
    for (i = 0; i < ITEMS_END; i++) {
        temp_v0 = mp3_DataRead(mp3_D_801019D0_1155F0_shared_board[i]);
        spriteIDs[i + 10] = mp3_func_80055810_56410(temp_v0);
        mp3_HuFreeFilePerm(temp_v0);
    }

    mp3_PushItemCountToGP(3); //set 3 items for players
    s32 itemCount = mp3_GetItemCount();

    //use original icon positions if 3 items, otherwise use extended list
    if (itemCount == 3) {
        iconPosList = D_801018E4_115504_shared_board;
        itemScale = 1.0f;
        itemXSpacing = 18;
    } else { //is 5
        iconPosList = PlayerIconPositions;
        itemScale = 0.7f;
        itemXSpacing = 12;
    }
}

void func_800F6BC4_10A7E4_shared_board(s32 arg0) {
    BoardStatus* temp_s2;
    f32 var_f20;
    s32 i, j;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            temp_s2 = &D_801057E0_119400_shared_board[i];
            if (temp_s2->uiUpdatePaused == TRUE) {
                mp3_func_800F6A88_10A6A8_shared_board(temp_s2->playerIndex, 2);
                mp3_func_80054904_55504(temp_s2->playerIndex, 1, iconPosList[1][0], iconPosList[1][1]);
                if (mp3_GwPlayer[i].itemNo[0] != ITEM_NONE) {
                    s32 itemCount = mp3_GetItemCount();
                    //used for item positions when closing items screen
                    for (j = 0; j < itemCount; j++) {
                        switch (j) {
                        case 0:
                            mp3_func_80054904_55504(temp_s2->playerIndex, j + 2, item0XY[0], item0XY[1]);
                            break;
                        case 1:
                            //normally is -5 on the last arg to move item index 1 up a bit
                            mp3_func_80054904_55504(temp_s2->playerIndex, j + 2, item1XY[0], item1XY[1]);
                            break;
                        case 2:
                            mp3_func_80054904_55504(temp_s2->playerIndex, j + 2, item2XY[0], item2XY[1]);
                            break;
                        case 3:
                            mp3_func_80054904_55504(temp_s2->playerIndex, j + 2, item3XY[0], item3XY[1]);
                            break;
                        case 4:
                            mp3_func_80054904_55504(temp_s2->playerIndex, j + 2, item4XY[0], item4XY[1]);
                            break;
                        }
                    }
                } else {
                    mp3_func_80054904_55504(temp_s2->playerIndex, 2, 0x12, 0);
                }
            }
        }
    }
    
    for (var_f20 = 0.0f; var_f20 <= 90.0f; var_f20 += 15.0f) {
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (arg0 == CUR_PLAYER || arg0 == i) {
                newfunc_800F6AD0_10A6F0_shared_board(i, mp3_HuMathCos(var_f20), 1.0f);
            }            
        }
        mp3_HuPrcVSleep();
    }
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            newfunc_800F6AD0_10A6F0_shared_board(i, 0.0f, 0);
        }
    }
    mp3_HuPrcVSleep();
}

void originalUpdatePlayerBoardStatus(s32 playerIndex) {
    UnkCoinThing coinDigits;
    BoardStatus* playerBoardStatus;
    s32 var_v1;
    s32 i;
    
    playerBoardStatus = &D_801057E0_119400_shared_board[playerIndex];
    if (playerBoardStatus->prevCoins != mp3_GwPlayer[playerIndex].coin) {
        coinDigits.digits[HUNDREDS] = mp3_GwPlayer[playerIndex].coin / 100;
        coinDigits.digits[TENS] = mp3_GwPlayer[playerIndex].coin / 10 % 10;
        coinDigits.digits[ONES] = mp3_GwPlayer[playerIndex].coin % 10;
        if (coinDigits.digits[HUNDREDS] == 0 && coinDigits.digits[TENS] == 0) {
            var_v1 = 1;
        } else if (coinDigits.digits[HUNDREDS] == 0 && coinDigits.digits[TENS] != 0) {
            var_v1 = 2;
        } else {
            var_v1 = 3;
        }
        
        if (var_v1 == 1) {
            mp3_SprAttrSet(playerBoardStatus->playerIndex, COINS_ONES_DIGIT, 0x8000);
            coinDigits.digits[TENS] = coinDigits.digits[ONES];
        } else {
            mp3_SprAttrReset(playerBoardStatus->playerIndex, COINS_ONES_DIGIT, 0x8000);
        }
    
        if (coinDigits.digits[HUNDREDS] == 0) {
            coinDigits.digits[HUNDREDS] = DIGIT_X;
        }
        for (i = 0; i < ARRAY_COUNT(coinDigits.digits); i++) {
            mp3_func_80055140_55D40(playerBoardStatus->playerIndex, i + COINS_HUNDREDS_DIGIT, coinDigits.digits[i], 0);
            mp3_func_800550F4_55CF4(playerBoardStatus->playerIndex, i + COINS_HUNDREDS_DIGIT, 1);
        }
    
        playerBoardStatus->prevCoins = mp3_GwPlayer[playerIndex].coin;
    }

    if (playerBoardStatus->prevStars != mp3_GwPlayer[playerIndex].star) {
        if (mp3_GwPlayer[playerIndex].star > 99) {
            mp3_func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 9, 0);
            mp3_func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 9, 0);
        } else {
            if (mp3_GwPlayer[playerIndex].star > 9) {
                mp3_func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, (mp3_GwPlayer[playerIndex].star / 10), 0);
            } else {
                mp3_func_80055140_55D40(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, DIGIT_X, 0);
            }
            mp3_func_80055140_55D40(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, mp3_GwPlayer[playerIndex].star % 10, 0);
        }
        mp3_func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_TENS_DIGIT, 1);
        mp3_func_800550F4_55CF4(playerBoardStatus->playerIndex, STARS_ONES_DIGIT, 1);
    
        playerBoardStatus->prevStars = mp3_GwPlayer[playerIndex].star;
    }
    coinDigits.unk_08[0] = mp3_GwPlayer[playerIndex].coin;
    coinDigits.unk_08[1] = mp3_GwPlayer[playerIndex].star;
    
    for (i = 0; i < ARRAY_COUNT(coinDigits.unk_08); i++) {
        if ((i != 0 && playerBoardStatus->counts[i] != coinDigits.unk_08[i]) || (i == 0 && mp3_D_801055E8_119208_shared_board[playerIndex] != 0)) {
            if (playerBoardStatus->unk2[i] == 0) {
                mp3_func_800550B4_55CB4(playerBoardStatus->playerIndex, i + 2, 1.0f);
                playerBoardStatus->unk2[i] = 0xF;
            }
        }

        if (playerBoardStatus->unk2[i] != 0) {
            playerBoardStatus->unk2[i]--;
            if (playerBoardStatus->unk2[i] == 0) {
                if (i != 0 || mp3_D_801055E8_119208_shared_board[playerIndex] == 0) {
                    mp3_func_80055140_55D40(playerBoardStatus->playerIndex, i + 2, 0, 0);
                    mp3_func_800550B4_55CB4(playerBoardStatus->playerIndex, i + 2, 0.0f);
                    mp3_func_800550F4_55CF4(playerBoardStatus->playerIndex, i + 2, 1);                       
                }
            }
        }
        playerBoardStatus->counts[i] = coinDigits.unk_08[i];
    }
    if (playerBoardStatus->unk1 != -1) {
        mp3_func_80055140_55D40(playerBoardStatus->playerIndex, DIGIT_X, playerBoardStatus->unk1, 0);
        mp3_func_800550F4_55CF4(playerBoardStatus->playerIndex, DIGIT_X, 1);
        return;
    }
    if (playerBoardStatus->prevRank != mp3_BoardPlayerRankCalc(playerIndex)) {
        mp3_func_80055140_55D40(playerBoardStatus->playerIndex, DIGIT_X, mp3_BoardPlayerRankCalc(playerIndex), 0);
        mp3_func_800550F4_55CF4(playerBoardStatus->playerIndex, DIGIT_X, 1);
        playerBoardStatus->prevRank = mp3_BoardPlayerRankCalc(playerIndex);
    }
}

void newfunc_800F3400_107020_shared_board(mp3_omObjData* arg0) {
    BoardStatus* temp_s2;
    s32 var_v1;
    s32 i, k;
    s32 itemCount = mp3_GetItemCount();
    s32 iconLoopCount = 11 + itemCount; //14 icons for 3 items, 16 for 5 items

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
                        for (k = 0; k < iconLoopCount; k++) {
                            mp3_SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                        }
                        continue;
                    }

                    for (k = 0; k < iconLoopCount; k++) {
                        switch (k) {
                        case COM_ICON:
                            if (mp3_GwPlayer[i].stat & 1) {
                                break;
                            }
                            continue;
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                        case 15:
                            if (mp3_GwPlayer[i].itemNo[k - 11] == ITEM_NONE) {
                                continue;
                            }

                            mp3_func_80055024_55C24(temp_s2->playerIndex, k, D_8010559C_1191BC_shared_board[mp3_GwPlayer[i].itemNo[k - 11]], 0);
                            mp3_func_800550F4_55CF4(temp_s2->playerIndex, k, 0);
                            mp3_SprPriSet(temp_s2->playerIndex, k, (i * 5) + 0x478E);
                            mp3_SprAttrSet(temp_s2->playerIndex, k, 0);
                            var_v1 = k;
                            if (i >= 2) {
                                if (itemCount == 3) {
                                    var_v1 = k + 3;
                                } else {
                                    var_v1 = k + 5;
                                }
                            }
                            mp3_func_80054904_55504(temp_s2->playerIndex, k, iconPosList[var_v1][0], iconPosList[var_v1][1]);
                            mp3_SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                            if (D_80101790_1153B0_shared_board != 0) {
                                break;
                            }
                            continue;
                        case 6:
                            if (mp3_GwPlayer[i].coin < 10) {
                                continue;
                            }
                            break;
                        }
                        mp3_SprAttrReset(temp_s2->playerIndex, k, 0x8000);
                    }
                    originalUpdatePlayerBoardStatus(i);
                } else {
                    if (temp_s2->uiVisible & 1) {
                        for (k = 0; k < 5; k++) {
                            mp3_SprAttrSet(temp_s2->playerIndex, k, 0x8000);
                        }
                        mp3_SprAttrSet(temp_s2->playerIndex, 9, 0x8000);
                        continue;
                    }

                    for (k = 0; k < 2; k++) {
                        mp3_SprAttrReset(temp_s2->playerIndex, k, 0x8000);
                    }

                    for (k = 0; k < 3; k++) {
                        if (temp_s2->unk_40[k] != -1) {
                            mp3_SprAttrReset(temp_s2->playerIndex, (k + 2), 0x8000);
                        }
                    }

                    if ((mp3_GwPlayer[i].stat & 1) && !(temp_s2->uiVisible & 1)) {
                        mp3_SprAttrReset(temp_s2->playerIndex, 9, 0x8000);
                    } else {
                        mp3_SprAttrSet(temp_s2->playerIndex, 9, 0x8000);
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
                mp3_func_80054904_55504(temp_s2->playerIndex, 0,
                                    (s16)((s32)(temp_s2->xPos + 0.5f) + ITEMS_POS_OFFSET_X),
                                    (s16)((s32)(temp_s2->yPos + 0.5f) + ITEMS_POS_OFFSET_Y));
            }

            if (D_801055C2_1191E2_shared_board != -1) {
                D_801055C8_1191E8_shared_board += 0.1f;
                if (D_801055C8_1191E8_shared_board > 1.0f) {
                    D_801055C8_1191E8_shared_board = 1.0f;
                }
                mp3_HuSprScaleSet(D_801055C2_1191E2_shared_board, 0, D_801055C8_1191E8_shared_board, D_801055C8_1191E8_shared_board);
                if (D_801055E4_119204_shared_board > 0) {
                    D_801055E4_119204_shared_board--;
                    D_801055CC_1191EC_shared_board.x += D_801055D4_1191F4_shared_board.x;
                    D_801055CC_1191EC_shared_board.y += D_801055D4_1191F4_shared_board.y;
                    D_801055D4_1191F4_shared_board.x += D_801055DC_1191FC_shared_board.x;
                    D_801055D4_1191F4_shared_board.y += D_801055DC_1191FC_shared_board.y;
                    mp3_func_80054904_55504(D_801055C2_1191E2_shared_board, 0,
                                        D_801055CC_1191EC_shared_board.x,
                                        D_801055CC_1191EC_shared_board.y);
                }
            }
        }
        mp3_HuPrcVSleep();
    }
}

void newfunc_800F3D70_107990_shared_board(s32 arg0) {
    BoardStatus* temp_s0;
    s16 temp_v0;
    s32 itemCount = mp3_GetItemCount();
    s32 iconCount = 11 + itemCount;  //14 total icons for 3 items, 16 for 5 items

    temp_s0 = &D_801057E0_119400_shared_board[arg0];
    temp_v0 = mp3_func_8005279C_5339C(iconCount, 2);
    
    temp_s0->playerIndex = temp_v0;
    mp3_func_80055024_55C24(temp_v0, 0, mp3_D_80105588_1191A8_shared_board[0], 0);
    mp3_SprPriSet(temp_v0, 0, ((arg0 * 5) + 0x4790));
    mp3_SprAttrSet(temp_v0, 0, 0x1000);
    mp3_func_80054904_55504(temp_v0, 0, 0, 0);
}




//for giving an item after an item minigame
void newfunc_800F3FF4_107C14_shared_board(s32 arg0) {
    s32 temp_s3;
    s16 var_s1;
    s32 i;
    s32 curItem;
    s32 itemCount = mp3_GetItemCount();
    s32 baseIconOffset = 0xB;

    temp_s3 = D_801057E0_119400_shared_board[arg0].playerIndex;

    for (i = 0; i < itemCount; i++) {
        curItem = mp3_GwPlayer[arg0].itemNo[i];
        curItem = (curItem == -1) ? 0 : curItem;
        mp3_func_80055024_55C24(temp_s3, i + 0xB, D_8010559C_1191BC_shared_board[curItem], 0);
        mp3_func_800550F4_55CF4(temp_s3, i + 0xB, 0);
        mp3_SprPriSet(temp_s3, i + 0xB, ((arg0 * 5) + 0x478E));
        mp3_SprAttrSet(temp_s3, i + 0xB, 0);
        var_s1 = i + 0xB;
        if (arg0 >= 2) {
            var_s1 = i + baseIconOffset + itemCount;
        }
        mp3_func_80054904_55504(temp_s3, i + 0xB, iconPosList[var_s1][0], iconPosList[var_s1][1]);
        if (mp3_GwPlayer[arg0].itemNo[i] == -1) {
            mp3_SprAttrSet(temp_s3, i + 0xB, 0x8000);
        }
    }
}

void newfunc_800F6ECC_10AAEC_shared_board(s32 arg0) {
    s32 sp10;
    s32 sp14;
    BoardStatus* temp_s2;
    f32 var_f20;
    s32 i, j;
    s32 itemCount = mp3_GetItemCount();
    
    for (var_f20 = 90.0f; var_f20 >= 0.0f; var_f20 -= 15.0f) {
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (arg0 == CUR_PLAYER || arg0 == i) {
                newfunc_800F6AD0_10A6F0_shared_board(i, mp3_HuMathCos(var_f20), 1.0f);
            }            
        }
        mp3_HuPrcVSleep();
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (arg0 == CUR_PLAYER || arg0 == i) {
            newfunc_800F6AD0_10A6F0_shared_board(i, 1.0f, 1.0f);
            temp_s2 = &D_801057E0_119400_shared_board[i];
            if (temp_s2->uiUpdatePaused == TRUE) {
                mp3_func_800F6A88_10A6A8_shared_board(temp_s2->playerIndex, 0);
                sp10 = mp3_PlayerBoardStatusRootPosition[i][0] + ITEMS_POS_OFFSET_X;
                sp14 = mp3_PlayerBoardStatusRootPosition[i][1] + ITEMS_POS_OFFSET_Y;
                mp3_func_80054904_55504(temp_s2->playerIndex, 1, sp10, sp14);
                if (mp3_GwPlayer[i].itemNo[0] != ITEM_NONE) {
                    for (j = 0; j < itemCount; j++) {
                        mp3_func_800F6E4C_10AA6C_shared_board(i, j, &sp10, &sp14);

                        mp3_HuSprScaleSet(temp_s2->playerIndex, j + 2, itemScale, itemScale);

                        mp3_func_80054904_55504(temp_s2->playerIndex, j + 2, sp10, sp14);
                    }
                } else {
                    mp3_func_80054904_55504(temp_s2->playerIndex, 2, (sp10 + 0x12), sp14);
                }
            }
        }
    }
    mp3_HuPrcVSleep();
}

f32 HuMathSin(f32);
void func_800F696C_10A58C_shared_board(s32, s32, f32, f32);

//does pulsing effect of item when hovering over it as an item to use
void newMBItemScaleEff(void) {
    f32 temp_f0;
    f32 var_f20;
    s32* temp_s0;
    s32 prev;

    temp_s0 = mp3_HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    prev = *temp_s0;
    while (*temp_s0 != -1) {
        if (*temp_s0 != prev) {
            mp3_func_800F696C_10A58C_shared_board(mp3_GwSystem.current_player_index, prev, itemScale, itemScale);
            var_f20 = 0.0f;
            prev = *temp_s0;
        }
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }
        temp_f0 = (mp3_HuMathSin(var_f20) * 0.2f) + 1.0f;
        mp3_func_800F696C_10A58C_shared_board(mp3_GwSystem.current_player_index, *temp_s0, temp_f0, temp_f0);
        mp3_HuPrcVSleep();
        var_f20 += 13.0f;
        
    }
    mp3_func_800F696C_10A58C_shared_board(mp3_GwSystem.current_player_index, prev, itemScale, itemScale);
    mp3_omDelPrcObj(0);
}

void newfunc_800F6AD0_10A6F0_shared_board(s32 arg0, f32 xScale, f32 yScale) {
    BoardStatus* temp_s1;
    s32 itemCount = mp3_GetItemCount();
    s32 baseIconOffset = 0xB;
    s32 anotherBaseOffset = 2;
    s32 i;

    temp_s1 = &D_801057E0_119400_shared_board[arg0];
    switch(temp_s1->uiUpdatePaused) {
    case FALSE:
        for (i = 0; i < baseIconOffset + itemCount; i++) {
            mp3_HuSprScaleSet(temp_s1->playerIndex, i, xScale, yScale);
        }
        break;
    case TRUE:
        for (i = 0; i < anotherBaseOffset + itemCount; i++) {
            mp3_HuSprScaleSet(temp_s1->playerIndex, i, xScale, yScale);
        }
        mp3_HuSprScaleSet(temp_s1->playerIndex, 9, xScale, yScale);
        break;
    }
}

//sets item positions when pressing B and you have control of hand cursor
void newfunc_800F6E4C_10AA6C_shared_board(s32 playerIndex, s32 itemIndex, s32* xPos, s32* yPos) {
    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    *xPos = mp3_PlayerBoardStatusRootPosition[playerIndex][0] + ITEMS_POS_OFFSET_X;
    *yPos = mp3_PlayerBoardStatusRootPosition[playerIndex][1] + ITEMS_POS_OFFSET_Y;

    *xPos = *xPos + 3 + (itemIndex * itemXSpacing);
    //if item index is 1 or 3 move item up on the screen 5 units
    //if item index 0, 2, or 4 move down on the screen 5 units
    if (itemIndex == 1 || itemIndex == 3) {
        *yPos -= itemYSpacing;
    } else {
        *yPos += itemYSpacing;
    }
}

void newfunc_800F5F98_109BB8_shared_board(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    BoardStatus* temp_s7;
    s16 temp_s5;
    s16 i;
    void* var_s2;
    s32 itemCount = mp3_GetItemCount();

    temp_s7 = &D_801057E0_119400_shared_board[arg0];
    temp_s5 = temp_s7->playerIndex;
    var_s2 = NULL;

    for (i = 0; i < itemCount; i++) {
        var_s2 = NULL;
        if (mp3_GwPlayer[arg0].itemNo[i] != -1) {
            var_s2 = mp3_DataRead(mp3_D_8010197C_11559C_shared_board[mp3_GwPlayer[arg0].itemNo[i]]);
        } else {
            if (i == 0) {
                var_s2 = mp3_DataRead(0x13025E);
            }
        }

        if (var_s2 != NULL) {
            temp_s7->unk_40[i] = mp3_func_80055810_56410(var_s2);
            mp3_HuFreeFilePerm(var_s2);
            mp3_func_80055024_55C24(temp_s5, i + 2, temp_s7->unk_40[i], 0);
            if (i != 0) {
                mp3_SprPriSet(temp_s5, i + 2, (arg0 * 5) + 0x4790);
            } else {
                mp3_SprPriSet(temp_s5, i + 2, ((arg0 * 5) + 0x478F) & 0xFFFF);
            }
            mp3_SprAttrSet(temp_s5, i + 2, 0x180CU);
            mp3_SprAttrReset(temp_s5, i + 2, 0x8000U);
            mp3_func_800552DC_55EDC(temp_s5, i + 2, 0.0f);
            if (mp3_GwPlayer[arg0].itemNo[0] != -1) {
                if (arg1 != 0) {
                    mp3_func_800F6E4C_10AA6C_shared_board(arg0, i, &sp10, &sp14);
                    mp3_func_80054904_55504(temp_s7->playerIndex, i + 2, sp10, sp14);
                } else {
                    switch (i) {
                    case 0:
                        mp3_func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, 5);
                        break;
                    case 1:
                        mp3_func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, -5);
                        break;
                    case 2:
                        mp3_func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, 5);
                        break;
                    //add case 3 and 4 for 4th and 5th item
                    case 3:
                        mp3_func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, -5);
                        break;
                    case 4:
                        mp3_func_80054904_55504(temp_s5, i + 2, (i * 0x12) + 3, 5);
                        break;
                    }                    
                }
            } else {
                if (arg1 != 0) {
                    f32 xPos, yPos;
                    xPos = (mp3_PlayerBoardStatusRootPosition[arg0][0] + 0x38);
                    yPos = (mp3_PlayerBoardStatusRootPosition[arg0][1] + 0x13);
                    xPos = xPos + 22.0f;
                    xPos = xPos - 4.0f;
                    
                    mp3_func_80054904_55504(temp_s7->playerIndex, 2, xPos, yPos);
                } else {
                    mp3_func_80054904_55504(temp_s5, 2, 0x12, 0);
                }
            }
            mp3_HuSprScaleSet(temp_s5, i + 2, itemScale, itemScale);
            mp3_func_800550B4_55CB4(temp_s5, i + 2, 0.0f);
            if (arg0 == mp3_GwSystem.current_player_index) {
                mp3_func_80055458_56058(temp_s5, i + 2, 0x100U);
            } else {
                mp3_func_80055458_56058(temp_s5, i + 2, 0x80U);
            }
            
        } else {
            temp_s7->unk_40[i] = -1;
        }
    }
}

//TODO: hopefully the array D_80105630_119250_shared_board can hold 5 items (I believe it does)
void newfunc_800F7610_10B230_shared_board(void) {
    s32 prevItem = -1;
    s32 i = 0;
    s32* boardItemIds = mp3_D_80105630_119250_shared_board;
    s32 itemCount = mp3_GetItemCount();
    
    for (; i < itemCount; i++) {
        boardItemIds = &mp3_D_80105630_119250_shared_board[i];
        while (1) {
            *boardItemIds = mp3_D_80101A50_115670_shared_board[mp3_func_800EEF80_102BA0_shared_board(9.0f)];
            if (*boardItemIds != prevItem) {
                prevItem = *boardItemIds;
                break;
            }
        }
    }
}

void newfunc_800F7F30_10BB50_shared_board(void) {
    s32 itemCount = mp3_GetItemCount();
    s32 i;

    mp3_func_800EC590_1001B0_shared_board(5, 0x3C20);

    for (i = 0; i < itemCount; i++) {
        mp3_D_80105630_119250_shared_board[i] = ITEM_SKELETON_KEY;
    }

    mp3_func_800F76A4_10B2C4_shared_board(0);
    mp3_func_800EC590_1001B0_shared_board(5, 0x3C1D);    
}

//Toad gives all skeleton keys
void newfunc_800F7D4C_10B96C_shared_board(void) {
    s32 itemCount = mp3_GetItemCount();
    s32 i;

    mp3_func_800EC590_1001B0_shared_board(3, 0x3C0B);

    for (i = 0; i < itemCount; i++) {
        mp3_D_80105630_119250_shared_board[i] = ITEM_SKELETON_KEY;
    }

    mp3_func_800F76A4_10B2C4_shared_board(0);
    mp3_func_800EC590_1001B0_shared_board(3, 0x3C0A);
}

//Baby bowser gives warp blocks from item space
void newfunc_800F7F7C_10BB9C_shared_board(void) {
    s32 itemCount = mp3_GetItemCount();
    s32 i;

    mp3_func_800EC590_1001B0_shared_board(5, 0x3C21);

    for (i = 0; i < itemCount; i++) {
        mp3_D_80105630_119250_shared_board[i] = ITEM_WARP_BLOCK;
    }

    mp3_func_800F76A4_10B2C4_shared_board(0);
    mp3_func_800EC590_1001B0_shared_board(5, 0x3C1D);
}

s32 newPlayerHasItem(s32 playerIndex, s32 itemID) {
    s32 itemCount = mp3_GetItemCount();
    s32 i;

    if (playerIndex == CUR_PLAYER) {
        playerIndex = mp3_GwSystem.current_player_index;
    }

    for (i = 0; i < itemCount; i++) {
        if (mp3_GwPlayer[playerIndex].itemNo[i] == itemID) {
            break;
        }
    }

    if (i == itemCount) {
        return -1;
    } else {
        return i;
    }
}

void newFixUpPlayerItemSlots(s32 arg0) {
    s32 itemCount = mp3_GetItemCount();
    s32 i;
    s8* playerItems;

    if (arg0 == CUR_PLAYER) {
        arg0 = mp3_GwSystem.current_player_index;
    }

    playerItems = mp3_GwPlayer[arg0].itemNo;

    for (i = 0; i < itemCount - 1; i++) {
        if (playerItems[i] == -1) {
            playerItems[i] = playerItems[i+1];
            playerItems[i+1] = -1;
        }
    }
}