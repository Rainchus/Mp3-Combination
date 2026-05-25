#include "mp3.h"
#include "ovl_80.h"
#include "mp3/mp3_mod.h"

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
extern u8 newCategoryAmountsNormalMp3[];
extern u8 new4PMinigameListNormalMp3[];
extern u8 new1v3MinigameListNormalMp3[];
extern u8 new2v2MinigameListNormalMp3[];
extern u8 newBattleMinigameListNormalMp3[];
extern u8 newItemMinigameListNormalMp3[];
extern u8 newDuelMinigameListNormalMp3[];
void mp3_GWMgNoSet(s8 arg0);
void mp3_PushItemCountToGP(s32 itemTotal); //must be 3 or 5

#define BASE_X -30
#define BASE_Y 24
#define BASE_Y_INVERTED -24
#define ITEM_SPACING 16

s32 mp3_DrawPrevMinigameList = 0;

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

    mp3_PushItemCountToGP(TOTAL_ITEM_SLOTS); //set 3 items for players
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
            *boardItemIds = mp3_D_80101A50_115670_shared_board[mp3_MBRand(ARRAY_COUNT(mp3_D_80101A50_115670_shared_board))];
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









////////////
typedef struct ItemRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ItemRect;

typedef struct DefinitelyNotItemRect {
    s8 x[100500];
} DefinitelyNotItemRect;

typedef struct ItemRectTable {
    ItemRect* rects[6];
} ItemRectTable; //sizeof 0x18

typedef struct DefinitelyNotItemRectTable {
    DefinitelyNotItemRect* notRects[6];
} DefinitelyNotItemRectTable; //sizeof 0x18

// typedef struct Sp18Struct {
//     ItemRectTable rectTable;
//     DefinitelyNotItemRectTable notRectTable1;
//     DefinitelyNotItemRectTable notRectTable2;
// } Sp18Struct;

typedef struct ItemSlotEntry {
/* 0x00 */ s16 obj;
/* 0x02 */ s16 x;
/* 0x04 */ s16 y;
/* 0x06 */ s16 w;
/* 0x08 */ s16 h;
} ItemSlotEntry; //sizeof 0xA

ItemRect D_80100E44_shared_board = {
/* x */ 60,
/* y */ 348,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E4C_shared_board = {
/* x */ 60,
/* y */ 368,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E54_shared_board = {
/* x */ 60,
/* y */ 388,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E5C_shared_board = {
/* x */ 60,
/* y */ 328,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E64_shared_board = {
/* x */ 60,
/* y */ 348,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E6C_shared_board = {
/* x */ 60,
/* y */ 368,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E74_shared_board = {
/* x */ 60,
/* y */ 388,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E7C_shared_board = {
/* x */ 60,
/* y */ 408,
/* w */ 200,
/* h */ 20
};

ItemRectTable D_801020B0_115CD0_shared_board = {
    &D_80100E5C_shared_board,
    &D_80100E44_shared_board,
    &D_80100E44_shared_board,
    &D_80100E44_shared_board,
    &D_80100E44_shared_board,
    &D_80100E5C_shared_board
};

//normal minigames, 4p?
u8 mp3Normal4pMinigames[] = {
    0x15, 0x16, 0x17, 0x18,
    0x19, 0x1B, 0x1C, 0x1D,
    0x1E, 0x1F, 0x20, 0x21,
    0x22, 0x23, 0x24, 0x25,
    0x26, 0x27, 0x28, 0x2C    
};

//easy minigames, 4p?
u8 mp3Easy4pMinigames[] = {
    TREADMILL_GRILL, 0x19, 0x1C, 0x1D,
    0x1E, 0x21, 0x22, 0x26,
    0x28, 0
};

//normal 1v3 minigames
u8 mp3Normal1v3Minigames[] = {
    HAND_LINE_AND_SINKER, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0
};

//easy 1v3 minigames
u8 mp3Easy1v3Minigames[] = {
    COCONUT_CONK, 3, 4, 5, 6, 9, 10, 0
};

//2v2
u8 mp3Normal2v2Minigames[] = {
    EATSA_PIZZA, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14
};

//item
u8 mp3NormalItemMinigames[] = {
    WINNERS_WHEEL, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
};

//battle
u8 mp3NormalBattleMinigames[] = {
    LOCKED_OUT, 0x29, 0x2A, 0x2B, 0x2D, 0x2E, 0x2F, 0x30
};

//battle
u8 mp3EasyBattleMinigames[] = {
    STACKED_DECK, 0x2B, 0x2D, 0x2E
};

//duel
u8 mp3NormalDuelMinigames[] = {
    VINE_WITH_ME, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A
};

//easy 2v2 minigames
u8 mp3Easy2v2Minigames[] = {
    EATSA_PIZZA, 0xC, 0x10, 0x11, 0x13
};

//game guy again?
u8 mp3EasyItemMinigames[] = {
    WINNERS_WHEEL, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
};

//easy duel
u8 mp3EasyDuelMinigames[] = {
    VINE_WITH_ME, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39
};

//noraml minigames
// u8* D_801020C8_115CE8_shared_board[] = {
//     mp3Normal4pMinigames,
//     mp3Normal1v3Minigames,
//     mp3Normal2v2Minigames,
//     mp3NormalItemMinigames,
//     mp3NormalBattleMinigames,
//     mp3NormalDuelMinigames
// };

u8* D_801020C8_115CE8_shared_board[] = {
    new4PMinigameListNormalMp3,
    new1v3MinigameListNormalMp3,
    new2v2MinigameListNormalMp3,
    newItemMinigameListNormalMp3,
    newBattleMinigameListNormalMp3,
    newDuelMinigameListNormalMp3
};

//easy minigames
u8* D_801020E0_115D00_shared_board[] = {
    mp3Easy4pMinigames,
    mp3Easy1v3Minigames,
    mp3Easy2v2Minigames,
    mp3EasyItemMinigames,
    mp3EasyBattleMinigames,
    mp3EasyDuelMinigames
};

// extern DefinitelyNotItemRectTable D_801020C8_115CE8_shared_board;
// extern DefinitelyNotItemRectTable D_801020E0_115D00_shared_board;

u8 D_80100EEC_114B0C_shared_board[] = {
    0x14,
    0xA,
    0xA,
    0x6,
    0x08,
    0xA,
    0,
    0
};

u8 D_80100EF4_114B14_shared_board[] = {
    9,
    7,
    5,
    6,
    4,
    7,
    0,
    0,
    0,
    0,
    0,
    0
};

extern u8 D_80100E20_114A40_shared_board[]; /* normal mode: recent minigame avoid count per category */
extern u8 D_80100E28_114A48_shared_board[]; /* hard mode: recent minigame avoid count per category */
extern u8 D_80100E30_114A50_shared_board[][3];
extern u16 D_80102BD4_1167F4_shared_board;
extern ItemSlotEntry D_80102BD0_1167F0_shared_board[];
// extern s8 D_80102C08_116828_shared_board[];
extern u8 D_80102C08_116828_shared_board[]; //changed to u8
extern s8 D_80102C0D_11682D_shared_board; //category index
extern u8 D_80100E18_114A38_shared_board[];
extern u8 D_80100EEC_114B0C_shared_board[];
extern u8 D_80100EF4_114B14_shared_board[];
extern u8 D_80100E20_114A40_shared_board[]; /* normal mode: recent minigame avoid count per category */
extern u8 D_80100E28_114A48_shared_board[]; /* hard mode: recent minigame avoid count per category */
extern u8 D_80100E9B_114ABB_shared_board[];
extern u8 D_80100E30_114A50_shared_board[][3];
extern s16 D_80102C12_116832_shared_board;
extern s8 D_80100E94_114AB4_shared_board[][2];
extern u8 D_80100E8C_114AAC_shared_board[];
extern u8 minigameTextColor[];

s16 mp3_func_8005A968_5B568(s16, s16, s16, s16, s32, s16);
void mp3_func_8005BE30_5CA30(s16, s32);
void mp3_func_8005BE30_5CA30(s16, s32);
void mp3_func_8005BE30_5CA30(s16, s32);
void mp3_func_80060144_60D44(s16);
void mp3_func_8005BCA4_5C8A4(s16, s16, s16);
void mp3_func_8005BEE0_5CAE0(s16, s32);
s32 mp3_BoardGetTurnTier(s32);
void mp3_func_8005D2D4_5DED4(s16);
extern mp3_omObjData* D_80102C04_116824_shared_board;
void mp3_func_8005C02C_5CC2C(s16, s32);
void mp3_func_8005BDFC_5C9FC(s16, s32);
void mp3_func_800DF9EC_F360C_shared_board(void);
extern s16 D_80102C0E_11682E_shared_board;
void SetMp3MultigameMinigameString(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_80100E84_114AA4_shared_board[];

void mp3_func_8005BA90_5C690(s16, s16, s16);
void mp3_func_8005BB18_5C718(s16, f32, f32);
void mp3_func_8005C154_5CD54(s16, s32, s32, s32);
void mp3_func_8005D2D4_5DED4(s16);
void mp3_func_800DECF0_F2910_shared_board(void);
void mp3_func_800DF8B4_F34D4_shared_board(void);
void mp3_func_800DFAD4_F36F4_shared_board(void);
void mp3_func_800E5B90_F97B0_shared_board(void);
void mp3_func_8005FBF8_607F8(s16, s32, s32, s32);
u8 rand8_Shared(void);
void mp3_HuAudFXPlay(s16);
void mp3_func_8005D294_5DE94(s16);

void newfunc_800DED3C_F295C_shared_board(mp3_omObjData* arg0) {
    ItemSlotEntry* entry = NULL;
    s32 i;
    s16 new_var;
    
    switch (arg0->work[0]) {
    case 3:
        break;
    case 0:
        if (arg0->work[1] == 0) {
            arg0->scale.y += 0.1f;
            if (arg0->scale.y > 1.0f) {
                arg0->scale.y = 1.0f;
            }
            for (i = 0; i < D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]; i++) {
                new_var = 0xE0;
                entry = &D_80102BD0_1167F0_shared_board[i];
                mp3_func_8005BA90_5C690(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                mp3_func_8005BB18_5C718(entry->obj, 0.0f, arg0->scale.y);
            }
   
            new_var = 0xE0;
            mp3_func_80054904_55504(D_80102C0E_11682E_shared_board, 0, 0xA0, (D_80102BD4_1167F4_shared_board + (D_80100E84_114AA4_shared_board[D_80102C0D_11682D_shared_board] - new_var)));
            
            
            mp3_HuSprScaleSet(D_80102C0E_11682E_shared_board, 0, mp3_HuMathSin(arg0->scale.x), arg0->scale.y);
            if (arg0->scale.y >= 1.0f) {
                arg0->work[0] = 4;
                arg0->work[1] = 5;
            }
        } else {
            arg0->work[1] -= 1;
        }
        break;
    case 4:
        if (arg0->work[1] != 0) {
            arg0->work[1] -= 1;
            break;
        }
        
        arg0->scale.x += 10.0f;
        if (arg0->scale.x > 90.0f) {
            arg0->scale.x = 90.0f;
        }

        for (i = 0; i < D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]; i++) {
            new_var = 0xE0;
            entry = &D_80102BD0_1167F0_shared_board[i];
            mp3_func_8005BA90_5C690(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
            mp3_func_8005BB18_5C718(entry->obj, mp3_HuMathSin(arg0->scale.x), arg0->scale.y);
        }
        
        new_var = 0xE0;    
        mp3_func_80054904_55504(D_80102C0E_11682E_shared_board, 0, 0xA0,
            (D_80102BD4_1167F4_shared_board + (D_80100E84_114AA4_shared_board[D_80102C0D_11682D_shared_board] - new_var)));
        
        
        mp3_HuSprScaleSet(D_80102C0E_11682E_shared_board, 0, mp3_HuMathSin(arg0->scale.x), arg0->scale.y);
        
        if (arg0->scale.x >= 90.0f) {
            mp3_func_800DECF0_F2910_shared_board();
            arg0->work[0] = 1;
            arg0->scale.x = 1.0f;
            arg0->scale.z = -1.0f;
            arg0->scale.y = 0.0f;
            arg0->work[1] = 0;
            arg0->work[2] = mp3_MBRand((f32) D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]);
            arg0->work[3] = 0;
            mp3_func_800DFAD4_F36F4_shared_board();
        }
        break;
    case 1:
        arg0->scale.z += arg0->scale.x;
        
        if (arg0->scale.z >= 1.0f) {
            if ((arg0->work[3] != 0) && (arg0->scale.x <= 0.08f)) {
                arg0->work[3]--;
            }
            arg0->scale.z -= 1.0f;
            if (arg0->scale.y == 0.0f) {
                arg0->work[1]++;
                arg0->work[1] = arg0->work[1] % D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board];
            } else {
                arg0->work[1]--;
                if (arg0->work[1] >= 0x80U) {
                    arg0->work[1] = D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board] - 1;
                }
            }
            mp3_func_800DECF0_F2910_shared_board();
        }
        
        for (i = 0; i < D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]; i++) {
            entry = &D_80102BD0_1167F0_shared_board[i];
            if (i == arg0->work[1]) {
                mp3_func_8005FBF8_607F8(entry->obj, 0, 0xC8, 0);
                mp3_func_8005BEE0_5CAE0(entry->obj, 0x100);
                mp3_func_8005BE30_5CA30(entry->obj, 0x2328);
            } else {
                mp3_func_8005FBF8_607F8(entry->obj, 0x40, 0x40, 0x80);
                mp3_func_8005BEE0_5CAE0(entry->obj, 0);
                mp3_func_8005BE30_5CA30(entry->obj, 0x2710);
            }
        }
        
        if ((arg0->work[1] == arg0->work[2]) || (arg0->scale.x < 1.0f)) {
            arg0->scale.x = (f32) ((f64) arg0->scale.x - 0.02);
        }
        
        if (arg0->scale.x <= 0.08f) {
            arg0->scale.x = 0.08f;
            if ((arg0->work[1] == arg0->work[2]) && (arg0->work[3] == 0) && ((arg0->scale.z + 0.08f) >= 1.0f)) {
                if ((rand8_Shared() & 0xF) || (arg0->scale.y == 1.0f) || (arg0->work[1] == 0)) {
                    if ((mp3_GwSystem.show_minigame_explanations == 0) || (mp3_GwSystem.current_board_index == 6)) {
                        mp3_HuAudFXPlay(0x105);
                    } else {
                        mp3_HuAudFXPlay(0x112);
                    }
                    
                    arg0->work[0] = 2;
                    arg0->work[3] = 0x3C;
                    mp3_func_8005D2D4_5DED4(entry->obj);
                    mp3_func_8005D294_5DE94(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj);
                    SetMp3MultigameMinigameString(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj,
                        (D_80102C08_116828_shared_board[arg0->work[1]]), -2, 4);
                    // mp3_func_8005B43C_5C03C(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj,
                    //     (char*)(D_80102C08_116828_shared_board[arg0->work[1]] + 0x46FF), -2, 4); 
                    mp3_func_8005C02C_5CC2C(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 1);
                    mp3_func_8005C154_5CD54(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 0xA0, 0xA0, 0xA0);
                    mp3_func_8005FBF8_607F8(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 0xFE, 0xFF, 0xD0);
                    mp3_func_8005BDFC_5C9FC(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 0);
                } else {
                    arg0->scale.y = 1.0f;
                    arg0->work[2]--;
                    if (arg0->work[2] >= 128) {
                        arg0->work[2] = D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board] - 1;
                    }
                }
            }
        }
        break;
    case 2:
        if (arg0->work[3] != 0) {
            arg0->work[3]--;
        } else {
            mp3_DrawPrevMinigameList = FALSE;
            D_800CC4A0_CD0A0.recentMinigames[D_80102C0D_11682D_shared_board][mp3_D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board]] = D_80102C08_116828_shared_board[arg0->work[2]];
            mp3_D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board]++;
            
            if (mp3__CheckFlag(0x20) != 0) {
                mp3_D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] = (mp3_D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] % (s32) D_80100E28_114A48_shared_board[D_80102C0D_11682D_shared_board]);
            } else {
                mp3_D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] = (mp3_D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] % (s32) D_80100E20_114A40_shared_board[D_80102C0D_11682D_shared_board]);
            }
            mp3_GWMgNoSet(D_80102C08_116828_shared_board[arg0->work[2]]);
            if (mp3_GwSystem.current_board_index != 6) {
                mp3_func_800E5B90_F97B0_shared_board();
                mp3_func_800DF8B4_F34D4_shared_board();
            }
        }
        arg0->rot.z += 1.0f;
        if (arg0->rot.z >= 13.0f) {
            arg0->rot.z -= 13.0f;
        }
        break;
    }
    if (D_80102C12_116832_shared_board != -1) {
        
        for (i = 0; !(arg0->rot.z < (f32) *D_80100E94_114AB4_shared_board[i]); i++) {}
        
        mp3_func_80054904_55504(D_80102C12_116832_shared_board, 0,
            (D_80100E94_114AB4_shared_board[i][1] + 50),
            (D_80100E8C_114AAC_shared_board[D_80102C0D_11682D_shared_board] + (arg0->work[1] * 20)));
    }
}

void newfunc_800DFBA8_F37C8_shared_board(s32 arg0) {
    ItemSlotEntry* entry;
    mp3_omObjData* obj;
    s32 category;
    s32 item;
    s32 forbidCount;
    s32 i;
    s32 j;
    s32 k;
    u8* minigameList;
    u8* avoidCounts;

    mp3_DrawPrevMinigameList = TRUE;

    switch (arg0) {
        case -1:
            category = mp3_func_800F52C4_108EE4_shared_board();
            if (category == -1) {
                category = 3;
            }
            break;
        case 1:
            category = 4;
            break;
        case 2:
            category = 5;
            break;
        case 0:
        default:
            category = 3;
            break;
    }

    D_80102C0D_11682D_shared_board = category;

    if (mp3__CheckFlag(0x20)) { //hard mode?
        minigameList = D_801020E0_115D00_shared_board[category];
        avoidCounts  = D_80100EF4_114B14_shared_board;
        forbidCount  = D_80100E28_114A48_shared_board[category];
    } else { //normal mode?
        minigameList = D_801020C8_115CE8_shared_board[category];
        avoidCounts  = newCategoryAmountsNormalMp3; //D_80100EEC_114B0C_shared_board;
        forbidCount  = D_80100E20_114A40_shared_board[category];
    }

    for (i = 0; i < D_80100E18_114A38_shared_board[category]; i++) {
        entry = &D_80102BD0_1167F0_shared_board[i];

        //new way to get xy and width/height. Original code crashes for some reason but this logic works out the same
        entry->x = D_801020B0_115CD0_shared_board.rects[category]->x;
        entry->y = D_801020B0_115CD0_shared_board.rects[category]->y + (i * 20);
        entry->w = D_801020B0_115CD0_shared_board.rects[category]->w;
        entry->h = D_801020B0_115CD0_shared_board.rects[category]->h;

        entry->obj = mp3_func_8005A968_5B568(
            (entry->x + (entry->w / 2)),
            (entry->y + (entry->h / 2)),
            entry->w,
            entry->h,
            0, 4);
        mp3_func_8005BE30_5CA30(entry->obj, 0x2328);
        mp3_func_80060144_60D44(entry->obj);
        mp3_func_8005BCA4_5C8A4(entry->obj, entry->w / 2, entry->h / 2);
        mp3_func_8005BEE0_5CAE0(entry->obj, 0);

        while (1) {
            D_80102C08_116828_shared_board[i] = minigameList[mp3_MBRand(avoidCounts[category])];

            /* reject duplicates */
            for (j = 0; j < i; j++) {
                if (D_80102C08_116828_shared_board[j] == D_80102C08_116828_shared_board[i]) {
                    break;
                }
            }

            if (j != i) {
                continue;
            }

            /* reject recently played */
            for (k = 0; k < forbidCount; k++) {
                if (D_80102C08_116828_shared_board[i] == D_800CC4A0_CD0A0.recentMinigames[category][k]) {
                    break;
                }
            }

            if (k != forbidCount) {
                continue;
            }

            /* reject certain games on early turns */
            if (mp3_BoardGetTurnTier(-1) == 0) {
                item = D_80102C08_116828_shared_board[i];
                if (item == 0x11) continue;
                if (item == ((item >= 0x12) ? 0x1C : 9)) continue;
            }

            break;
        }

        mp3_func_8005D2D4_5DED4(entry->obj);

        //@patch: show all minigame names for all 3 games, even locked ones
        SetMp3MultigameMinigameString(entry->obj, (D_80102C08_116828_shared_board[i]), -2, 4);

        // if (mp3_GWMgUnlockCheck(D_80102C08_116828_shared_board[i] - 1) != 0) {
        //     mp3_func_8005B43C_5C03C(entry->obj, (char*)(D_80102C08_116828_shared_board[i] + 0x46FF), -2, 4);
        // } else {
        //     mp3_func_8005B43C_5C03C(entry->obj, (char*)0x4748, -2, 4);
        // }

        mp3_func_8005C02C_5CC2C(entry->obj, minigameTextColor[D_80102C08_116828_shared_board[i]]);
        mp3_func_8005BDFC_5C9FC(entry->obj, 0);
    }

    obj = mp3_omAddObj(-0x8000, 0, 0, -1, newfunc_800DED3C_F295C_shared_board);
    D_80102C04_116824_shared_board = obj;
    obj->work[0] = 3;
    obj->work[1] = 5;
    obj->trans.y = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    obj->rot.z = 0.0f;
    mp3_func_800DF9EC_F360C_shared_board();

    mp3_func_80055420_56020(D_80102C0E_11682E_shared_board, 0,
        D_80100E30_114A50_shared_board[D_80102C0D_11682D_shared_board][0],
        D_80100E30_114A50_shared_board[D_80102C0D_11682D_shared_board][1],
        D_80100E30_114A50_shared_board[D_80102C0D_11682D_shared_board][2]);
}











typedef struct UnkOvl81 {
/* 0x00 */ void* unk0;
/* 0x04 */ void* unk4;
/* 0x08 */ void* unk8;
/* 0x0C */ char unk_0C[0x14];
/* 0x20 */ s16 unk_20;
/* 0x22 */ char unk_22[2];
} UnkOvl81;

extern s32 mp3_D_800A12CC;
extern s32 mp3_D_800A12D4;
extern f32 mp3_D_800C9938_CA538;
extern s16 mp3_D_800CC4A0_CD0A0;
extern s16 mp3_D_800CDD58_CE958;
extern s16 mp3_D_800CDD64_CE964;
extern s16 mp3_D_800D037C_D0F7C;
extern s32 mp3_D_800D1240_D1E40;
extern UnkOvl81 mp3_D_800D1360;
extern s16 mp3_D_800D1380_D1F80;
extern s16 mp3_D_800D1708_D2308;
extern s16 mp3_D_800D1F7A_D2B7A;
extern s16 mp3_D_800D1FEC_D2BEC;
extern s16 mp3_D_800D2130;
extern s16 mp3_D_800D4080_D4C80;
extern s32 mp3_D_800D41C0_D4DC0;
extern u16 mp3_D_800D530C_D5F0C;
extern u16 mp3_D_800D5558_D6158[4];
extern s16 mp3_D_800D6A44_D7644;
extern s32 mp3_D_80101944_115564_shared_board[];
extern s32 mp3_D_8010197C_11559C_shared_board[];
extern s32 mp3_D_801019D0_1155F0_shared_board[];
extern const char mp3_D_801025D0_1161F0_shared_board[];
extern s32 mp3_D_80105630_119250_shared_board[3];
extern s32 mp3_D_80105660_119280_shared_board;
extern s16 mp3_D_80105664_119284_shared_board;
extern s16 mp3_D_80105666_119286_shared_board;
void mp3_DataClose(void* data);
s32 mp3_GWBoardFlagCheck(s32);
void mp3_GWBoardFlagClear(s32 flag);
s16 mp3_GetCurrentPlayerIndex(void);
void mp3_HuPrcChildLink(mp3_Process*process, mp3_Process*child);
void mp3_HuPrcChildWait();
void mp3_HuSprAttrSet(s16 group, s16 member, s32 attr);
s16 mp3_HuSprGrpCreate(u16 arg0, u16 arg1);
void mp3_HuSprGrpKill(s16);
void mp3_HuSprKill(s16);
void mp3_HuSprPriSet(s16 group, s16 member, u16 prio);
void mp3_HuVecCopy3F(Vec * out, Vec * a);
void mp3_MBBattleKuriboStart(mp3_GW_PLAYER* arg0, s32 arg1);
void mp3_MBBlockMasuUpdate(void);
void mp3_MBCoinChangeCreate(s32 player, s32 coins);
void mp3_MBDlgResultWinExec(s32);
void mp3_MBDlgWinClose(void);
void mp3_MBDlgWinExec(s32, s32);
void mp3_MBDlgWinInsertCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void mp3_MBDlgWinKill(void);
mp3_GW_PLAYER* mp3_MBGetPlayerStruct(s32 playerIndex);
void mp3_MBItemKoopaNKinokoExec(void);
void mp3_MBItemKoopaRKinokoExec(void);
void mp3_MBKettouComResultSet(void);
s32 mp3_MBKettouExec(mp3_GW_PLAYER* arg0, s32 arg1);
s32 mp3_MBKettouPlayerBitGet(s32 arg0);
void mp3_MBKettouResultExec(void);
s32 mp3_MBLast5Check(void);
mp3_SpaceData* mp3_MBMasuGet(s16 arg0);
s16 mp3_MBMasuLinkMasuIdGet(u16 arg0, u16 arg1);
mp3_Process* mp3_MBMgCallBattleCreate(void);
mp3_Process* mp3_MBMgCallCreate(void);
mp3_Object* mp3_MBModelCreate(u8, u32*);
void mp3_MBModelKill(mp3_Object*);
void mp3_MBModelTempAllocFree(mp3_Object*);
void mp3_MBMotionSet(mp3_Object* arg0, s16 arg1, u16 arg2);
void mp3_MBNextPlayerTurn(void);
s32 mp3_PlayerHasEmptyItemSlot(s32 arg0);
s16 mp3_RNGPercentChance(s8 arg0);
void mp3_func_8001C92C_1D52C(s16, f32);
void mp3_func_8001FDE8_209E8(s16);
void mp3_func_8004ACE0_4B8E0(s32, s16);
void mp3_func_800500E0_50CE0(s32);
void mp3_func_8005035C_50F5C(s32);
void mp3_func_8005B6BC_5C2BC(s16 win_id, u32 arg1, s8 arg2);
void mp3_func_8005BA90_5C690(s16, s16, s16);
void mp3_func_8005BDFC_5C9FC(s16, s32);
void mp3_func_8005BEE0_5CAE0(s16, s32);
void mp3_func_8005C02C_5CC2C(s16, s32);
void mp3_func_8005D294_5DE94(s16);
s16 mp3_func_8005E0C0_5ECC0(s16);
void mp3_func_8005F364_5FF64(s16);
void mp3_func_8005FBF8_607F8(s16, s32, s32, s32);
void mp3_func_800600C0_60CC0(s16, s32);
void mp3_func_80060144_60D44(s16 obj);
void mp3_func_8006022C_60E2C(u32 mesg, s32);
void mp3_func_80060394_60F94(s32, s16*, s32);
s32 mp3_func_80061188_61D88(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5);
void mp3_func_80061388_61F88(s16);
void mp3_func_80061A5C_6265C(s16, s32);
void mp3_func_800DB884_EF4A4_shared_board(s32);
void mp3_func_800DBFBC_EFBDC_shared_board(s8);
s32 mp3_func_800DCD9C_F09BC_shared_board(s8);
mp3_Process* mp3_func_800DD6C4_F12E4_shared_board(s8);
mp3_Process* mp3_func_800DDDD4_F19F4_shared_board(s8);
void mp3_func_800DE414_F2034_shared_board(s8, u8);
mp3_Process* mp3_func_800DE7E4_F2404_shared_board(s8);
u8 mp3_func_800DE84C_F246C_shared_board(void);
void mp3_func_800DE858_F2478_shared_board(void);
void mp3_func_800DE868_F2488_shared_board(void);
s32 mp3_func_800DEB2C_F274C_shared_board(s32);
mp3_Process* mp3_func_800E0F84_F4BA4_shared_board(void);
void mp3_func_800E455C_F817C_shared_board(void);
void mp3_func_800E4954_F8574_shared_board(void);
mp3_Process* mp3_func_800E5CE0_F9900_shared_board(s8);
void mp3_func_800E648C_FA0AC_shared_board(void);
void mp3_func_800E8DD4_FC9F4_shared_board(f32);
mp3_Process* mp3_func_800E8EDC_FCAFC_shared_board(f32);
void mp3_func_800EB97C_FF59C_shared_board(s16);
s32 mp3_func_800EBAC8_FF6E8_shared_board(s16, s32);
void mp3_func_800EBCBC_FF8DC_shared_board(s16);
s16 mp3_func_800EBCC8_FF8E8_shared_board(void);
void mp3_func_800EBEC8_FFAE8_shared_board(void);
void mp3_func_800EC3C0_FFFE0_shared_board(s32);
void mp3_func_800ECC0C_10082C_shared_board(Vec*);
void mp3_func_800ECC28_100848_shared_board(short);
void mp3_func_800ECDD4_1009F4_shared_board(s32, u8);
void mp3_func_800ED128_100D48_shared_board(Vec*, Vec*, Vec*, s32);
void mp3_func_800ED1E4_100E04_shared_board(Vec*, Vec*, Vec*, s32);
void mp3_func_800ED410_101030_shared_board(s8, s32);
mp3_Process* mp3_func_800EDB98_1017B8_shared_board(mp3_Object*, f32, f32);
void mp3_func_800EDC58_101878_shared_board(s16, s32);
void mp3_func_800EE688_1022A8_shared_board(mp3_Object*, f32, f32);
s32 mp3_func_800F2198_105DB8_shared_board(s16);
void mp3_func_800F22C0_105EE0_shared_board(s32);
void mp3_func_800F2304_105F24_shared_board(s32 playerIndex, s16 arg1, u16 arg2);
void mp3_func_800F2388_105FA8_shared_board(s32, s32, s32, s32, s32);
mp3_Process* mp3_func_800F292C_10654C_shared_board(void);
mp3_Process* mp3_func_800F29EC_10660C_shared_board(void);
void mp3_func_800F3BD0_1077F0_shared_board(s32);
void mp3_func_800F3F0C_107B2C_shared_board(s32);
void mp3_func_800F4348_107F68_shared_board(void);
void mp3_func_800F462C_10824C_shared_board(s32);
void mp3_func_800F4798_1083B8_shared_board(u32, s32);
s32 mp3_func_800F482C_10844C_shared_board(s32);
void mp3_func_800F4994_1085B4_shared_board(s32);
void mp3_func_800F5644_109264_shared_board(void);
void mp3_func_800F5D44_109964_shared_board(s32, s32);
void mp3_func_800F5F98_109BB8_shared_board(s32, s32);
void mp3_func_800F64E4_10A104_shared_board(s32, s32);
void mp3_func_800F6748_10A368_shared_board(s16, s16, f32*, f32*);
void mp3_func_800F68E0_10A500_shared_board(s32 arg0, s32 arg1, s16 arg2);
void mp3_func_800F696C_10A58C_shared_board(s32, s32, f32, f32);
void mp3_func_800F6A88_10A6A8_shared_board(s16, u16);
void mp3_func_800F6E4C_10AA6C_shared_board(s32, s32, s32*, s32*);
void mp3_func_800F70F8_10AD18_shared_board(void);
void mp3_func_800F7108_10AD28_shared_board(void);
void mp3_func_800F76A4_10B2C4_shared_board(s32);
void mp3_func_800F85C0_10C1E0_shared_board(void);
void mp3_func_800F85E4_10C204_shared_board(void);
void mp3_func_800F88D0_10C4F0_shared_board(void);
void mp3_func_800F915C_10CD7C_shared_board(s16 arg0);
void mp3_func_800F95FC_10D21C_shared_board(s16 arg0);
void mp3_func_800F965C_10D27C_shared_board(s16);
void mp3_func_800F96E0_10D300_shared_board(s32 playerNo, s32 arg1);
s32 mp3_func_800F9A68_10D688_shared_board(s32 arg0);
s32 mp3_func_800FB624_10F244_shared_board(mp3_GW_PLAYER*);
void mp3_func_800FC3D0_10FFF0_shared_board(void);
void mp3_func_800FC4E0_110100_shared_board(void);
void mp3_func_800FC7C8_1103E8_shared_board(void);
void mp3_func_800FC8A4_1104C4_shared_board(void);
void mp3_func_800FF794_1133B4_shared_board(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void mp3_func_800FF840_113460_shared_board(Vec* arg0);
void mp3_func_800FF900_113520_shared_board(s16, s16);
void mp3_GWBoardFlagSet(s32 flag);
extern s16 mp3_kakusiMasuCoin;
extern s16 mp3_kakusiMasuCoinOld[10];
extern s16 mp3_kakusiMasuItem;
extern s16 mp3_kakusiMasuItemOld[10];
extern s16 mp3_kakusiMasuStar;
extern s16 mp3_kakusiMasuStarOld[10];

extern u8 mp3_D_80101E70_115A90_shared_board[][2];
extern void (*mp3_D_80101B6C_11578C_shared_board)(void);
extern u16 mp3_D_80101C24_115844_shared_board[];
extern u16 mp3_D_80101C2C_11584C_shared_board[][8];
extern u16 mp3_D_80101D2C_11594C_shared_board[][4][3];
extern u16 mp3_D_80101C8C_1158AC_shared_board[][5][8];
extern s32 mp3_D_80101C4C_11586C_shared_board[][8];

typedef struct CPU_GAMEGUY_STATS {
    u16 multiplier;
    u16 weight;
} CPU_GAMEGUY_STATS;

//not used by anything but MBMain so it's here for simplicity
CPU_GAMEGUY_STATS mp3_D_80101C08_115828_shared_board[] = {
    {0, 500},      // 0x multiplier - rolls 1-500 (50.0%)
    {2, 870},      // 2x multiplier - rolls 501-870 (37.0%)
    {4, 950},      // 4x multiplier - rolls 871-950 (8.0%)
    {8, 985},      // 8x multiplier - rolls 951-985 (3.5%)
    {16, 995},     // 16x multiplier - rolls 986-995 (1.0%)
    {32, 999},     // 32x multiplier - rolls 996-999 (0.4%)
    {64, 1000}     // 64x multiplier - roll 1000 (0.1%)
};

u8 mp3_D_80101C04_115824_shared_board[] = {
    5,  //5% game_guys_roulette
    30, //25% game_guys_lucky_7
    65, //35% game_guys_magic_boxes
    100 //35% game_guys_sweet_surprise
};

//game guy minigames
extern u8 mp3_D_80101C00_115820_shared_board[];

#define GAME_GUY_RANDOM_MAX 1000

void newMBMain(void) {
    mp3_Process* temp_s6;
    s32 var_s1;
    s16 temp_v0_2;
    s32 temp_v0_3;
    mp3_GW_PLAYER* temp_v0_4;
    s16 var_s5; //
    mp3_SpaceData* space;
    Vec sp20;
    mp3_Process* temp_s1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v0_10;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_16;
    s32 var_v1;
    s32 var_s0;
    s16 temp_v0_18;
    mp3_GW_PLAYER* temp_s0_2;
    s32 temp_v0_20;
    s32 temp_s2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_a0;
    s32 temp_s2_2;
    void* temp_v0_21;
    s32 temp_s3_3;
    mp3_Object* temp_v0_22;
    s32 temp_a0_4;
    u32 var_v1_3;
    s32 temp_v1_8;
    s32 temp_a0_3;
    s32 var_s1_12;
    s32 var_s0_2;
    mp3_GW_SYSTEM* system = &mp3_GwSystem;
    s16 sp30[2];
    s16 sp38[2];
    s16 sp40[2];
    char sp48[16]; //unknown buffer size
    s32 flag;
    s32 state;
    s32 eight;


    u8 TextSpeeds[] = {5, 25, 60};
    u8 speedIdx = mp3_GwSystem.message_speed;
    u8 textSpeed = TextSpeeds[speedIdx];
    mp3_D_800A12C0 = textSpeed;
    mp3_D_800A12C4 = textSpeed;

    temp_s6 = mp3_HuPrcCurrentGet();
    
    while (1) {  // Main game loop
        if ((mp3_D_800D1240_D1E40 == 0 || mp3_D_800D1240_D1E40 == 1) && system->current_player_index == 0) {
            // Initialize all player colors
            for (var_s1 = 0; var_s1 < 4; var_s1++) {
                mp3_MBGetPlayerStruct(var_s1)->color = 0;
                mp3_func_800F70F8_10AD18_shared_board();
            }
            
            // Check if we're in the last 5 turns
            if (system->total_turns >= 0) {
                short temp_v0 = (system->total_turns - system->current_turn) + 1;
                if (temp_v0 < 6) {
                    if (temp_v0 > 0) {
                        mp3_GWBoardFlagSet(2);  // Last 5 turns flag
                    }
                }
            }
            
            if (!mp3_GWBoardFlagCheck(1) && system->current_turn >= 2) {
                switch (system->save_mode) {
                    case 1:
                        system->save_mode = 2;
                    case 0:
                        mp3__SetFlag(0);
                        mp3_GWBoardFlagSet(0);
                        
                        mp3_func_80060394_60F94(1, sp30, 0x5900);
                        temp_v0_2 = mp3_func_8005A968_5B568(0, 0, sp30[0], sp30[1], 0, 2);
                        mp3_func_8005BEE0_5CAE0(temp_v0_2, 0);
                        mp3_func_8005B43C_5C03C(temp_v0_2, (char*)0x5900, -1, -1);
                        mp3_func_8005BDFC_5C9FC(temp_v0_2, 0);
                        
                        while (mp3_func_8005E0C0_5ECC0(temp_v0_2) != 0) {
                            mp3_HuPrcVSleep();
                        }
                        
                        if (system->playMode & 4) {
                            mp3__SetFlag(0x18);
                            mp3__SetFlag(0x28);
                            mp3_func_8005035C_50F5C(1);
                        } else {
                            mp3__SetFlag(0x16);
                            mp3_func_800500E0_50CE0(1);
                        }
                        
                        mp3_func_8005F364_5FF64(temp_v0_2);
                        mp3_func_80060394_60F94(1, sp30, 0x5901);
                        temp_v0_3 = mp3_func_8005A968_5B568(0, 0, sp30[0], sp30[1], 0, 2);
                        mp3_func_8005BEE0_5CAE0(temp_v0_3, 0);
                        mp3_func_8005B43C_5C03C(temp_v0_3, (char*)0x5901, -1, -1);
                        mp3_func_8005BDFC_5C9FC(temp_v0_3, 0);
                        mp3_HuPrcSleep(0xF);
                        mp3_func_8005F364_5FF64(temp_v0_3);
                        break;
                }
            }
            
            mp3_GWBoardFlagClear(1);
            mp3_D_800A12D4 = 0;
            mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(-2, 7);
        }
        

        mp3_D_800A12D4 = 1;
        
        var_s1 = 0;
        eight = 8; //definitely a hack
        for (; var_s1 < 4; var_s1++) {
            mp3_func_800F4798_1083B8_shared_board(var_s1, mp3_MBGetPlayerStruct(var_s1)->color);
            mp3_func_800F96E0_10D300_shared_board(var_s1, 1);
            
            state = mp3_D_800D1240_D1E40;
    
            if (state == eight) {
                // skip
            } else if (state < 8) {
                flag = 1;
                mp3_GwSystem.cur_player_used_item &= ~flag;
            } else if (state >= 16) {
                flag = 1;
                mp3_GwSystem.cur_player_used_item &= ~flag;
            } else if (state < 10) {
                flag = 1;
                mp3_GwSystem.cur_player_used_item &= ~flag;
            }
        }
        
        mp3_MBBlockMasuUpdate();
        temp_v0_4 = mp3_MBGetPlayerStruct(system->current_player_index);
        var_s5 = mp3_MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
        space = mp3_MBMasuGet(var_s5);
        mp3_func_800EBCBC_FF8DC_shared_board(var_s5);

        state = mp3_D_800D1240_D1E40;

        if (state == 0 || state == 1) {
            goto temp;
        }
        
        switch (state) {
            case 8:
            case 9:
            case 12:
                mp3_MBBattleKuriboStart(temp_v0_4, 1);
                break;
        
            case 18:
                var_s1 = 0;
                for (; var_s1 < 4; var_s1++) {
                    if (mp3_GwPlayer[var_s1].bonusCoin != 3)
                        break;
                }
                if (var_s1 >= 4) {
                    mp3_MBBattleKuriboStart(temp_v0_4, 1);
                }
                break;
        
            default:
                break;
        }

        while (mp3_WipeStatGet() != 0) {
            mp3_HuPrcVSleep();
        }
        
        mp3_D_800D037C_D0F7C = 1;
        
        switch (mp3_D_800D1240_D1E40) {
        case 12:
            mp3_MBKettouResultExec();
            mp3_func_800F88D0_10C4F0_shared_board();
            goto label654;

        case 13:  // Bank space
            mp3_func_800FC4E0_110100_shared_board();
            
                
        case 15:  // Some event
            mp3_func_800F88D0_10C4F0_shared_board();
            goto label654;
        case 14:
            mp3_MBItemKoopaNKinokoExec();
            mp3_MBItemKoopaRKinokoExec();
            mp3_func_800F88D0_10C4F0_shared_board();
            goto label654;
            
        case 11:
            mp3_D_800D1240_D1E40 = 0xA;
            mp3_func_800E4954_F8574_shared_board();
            mp3_func_800ECC0C_10082C_shared_board(&sp20);
            mp3_func_800ED128_100D48_shared_board(&temp_v0_4->player_obj->unk18, &sp20, 
                                              &temp_v0_4->player_obj->unk18, 8);
            mp3_HuPrcSleep(8);
            goto label654;

            temp:
            mp3_func_800EBAC8_FF6E8_shared_board(-4, 7);
            // Hide all player models
            mp3_func_8001FDE8_209E8(mp3_MBGetPlayerStruct(0)->player_obj->omObj1->model[0]);
            mp3_func_8001FDE8_209E8(mp3_MBGetPlayerStruct(1)->player_obj->omObj1->model[0]);
            mp3_func_8001FDE8_209E8(mp3_MBGetPlayerStruct(2)->player_obj->omObj1->model[0]);
            mp3_func_8001FDE8_209E8(mp3_MBGetPlayerStruct(3)->player_obj->omObj1->model[0]);
            
            mp3_func_800F2304_105F24_shared_board(-1, -1, 2);
            mp3_func_800F915C_10CD7C_shared_board(1);
            
            if (system->current_player_index == 4) {
                mp3_func_800E648C_FA0AC_shared_board();
            }
            
            // Camera setup
            if (mp3_D_800A12CC == 0) {
                mp3_D_800C9938_CA538 = 1.0f;
                mp3_func_800E8DD4_FC9F4_shared_board(1.0f);
                mp3_HuPrcChildLink(temp_s6, mp3_func_800F29EC_10660C_shared_board());
            } else if (system->current_player_index == 4 || system->current_player_index == 0) {
                mp3_D_800C9938_CA538 = 1.0f;
                mp3_func_800E8DD4_FC9F4_shared_board(1.0f);
                mp3_HuPrcChildLink(temp_s6, mp3_func_800F29EC_10660C_shared_board());
            } else {
                mp3_D_800C9938_CA538 = 1.0f;
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.0f));
            }
            
            mp3_HuPrcChildWait();
        default:
            mp3_HuPrcSleep(4);
            mp3_func_800FF900_113520_shared_board(-1, 3);
            mp3_HuPrcChildLink(temp_s6, mp3_func_800E5CE0_F9900_shared_board(system->current_player_index));
            mp3_HuPrcChildWait();
            mp3_func_800EBAC8_FF6E8_shared_board(-5, 7);
            goto label654;
        case 6:
        case 16:
            mp3_HuPrcSleep(0x1E);
            goto label2444;

        case 9:
            mp3_MBKettouResultExec();
            goto label2444;

        case 10:
            label654:
            // STATE 10: Dice roll and movement
            mp3_func_800FC7C8_1103E8_shared_board();
            mp3_D_800C9938_CA538 = 1.3f;
            mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.3f));
            temp_s1 = mp3_func_800DD6C4_F12E4_shared_board(system->current_player_index);
            mp3_HuPrcChildWait();
            mp3_HuPrcSleep(1);
            
            if (system->current_player_index != 4) {
                mp3_D_800CDD58_CE958 = 1;
                mp3_D_800D037C_D0F7C = 1;
                mp3_D_800CDD64_CE964 = 1;
                mp3_D_800CC4A0_CD0A0 = 1;
            }
        
            mp3_HuPrcChildLink(temp_s6, temp_s1);
            mp3_HuPrcChildWait();
            mp3_func_800FC8A4_1104C4_shared_board();
            
            mp3_D_800CDD58_CE958 = 0;
            mp3_D_800CDD64_CE964 = 0;
            mp3_D_800D41C0_D4DC0 = mp3_func_800DCD9C_F09BC_shared_board(system->current_player_index);
            
            if (mp3_D_80105660_119280_shared_board == 0 && (temp_v0_4->rev & 0x80)) {
                temp_v0_4->nlink = temp_v0_4->blink;
                temp_v0_4->nidx = temp_v0_4->bidx;
                temp_v0_4->rev ^= 1;
            }
        
            var_s5 = mp3_func_800EBCC8_FF8E8_shared_board();
            mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(var_s5, 9);
            mp3_func_800F2304_105F24_shared_board(-1, 0, 2);
        
            while (mp3_D_800D41C0_D4DC0 != 0) {
                short temp_s3;
                short temp_s0;
                mp3_func_800EBAC8_FF6E8_shared_board(var_s5, 8);
                
                // Save current position
                temp_s3 = temp_v0_4->clink;
                temp_s0 = temp_v0_4->cidx;
                
                // Update to next position
                temp_v0_4->clink = temp_v0_4->nlink;
                temp_v0_4->cidx = temp_v0_4->nidx;
                
                // Update walk speed animations
                for (var_s1 = 0; var_s1 < 4; var_s1++) {
                    mp3_func_800F96E0_10D300_shared_board(var_s1, (system->walk_speed * 5) + 5);
                }
                
                // Restore position temporarily
                temp_v0_4->clink = temp_s3;
                temp_v0_4->cidx = temp_s0;
                
                // Check if next space requires jumping
                space = mp3_MBMasuGet(mp3_MBMasuLinkMasuIdGet(temp_v0_4->nlink, temp_v0_4->nidx));
                
                if ((space->unk_02 & 0x8000) || mp3_func_800F9A68_10D688_shared_board(system->current_player_index)) {
                    // Jump animation
                    mp3_func_8004ACE0_4B8E0(0x3A, system->current_player_index);
                    mp3_func_800F2304_105F24_shared_board(-1, 2, 0);
                    
                    switch (system->walk_speed) {
                    case 0:
                        temp_v0_4->player_obj->velocity.y = 8.0f;
                        temp_v0_4->player_obj->velocity.z = -2.0f;
                        mp3_func_800ED410_101030_shared_board(system->current_player_index, 7);
                        break;
                    case 1:
                        temp_v0_4->player_obj->velocity.y = 4.0f;
                        temp_v0_4->player_obj->velocity.z = -0.5f;
                        mp3_func_800ED410_101030_shared_board(system->current_player_index, 0xF);
                        break;
                    case 2:
                        temp_v0_4->player_obj->velocity.y = 2.0f;
                        temp_v0_4->player_obj->velocity.z = -0.125f;
                        mp3_func_800ED410_101030_shared_board(system->current_player_index, 0x1E);
                        break;
                    }
                } else {
                    // Normal walk animation
                    if (temp_v0_4->player_obj->unk46 != 0) {
                        mp3_func_800F2304_105F24_shared_board(-1, 0, 2);
                    }
                    
                    switch (system->walk_speed) {
                    case 0:
                        mp3_func_8001C92C_1D52C(temp_v0_4->player_obj->omObj1->model[0], 2.0f);
                        mp3_func_800ED410_101030_shared_board(system->current_player_index, 5);
                        break;
                    case 1:
                        mp3_func_8001C92C_1D52C(temp_v0_4->player_obj->omObj1->model[0], 1.0f);
                        mp3_func_800ED410_101030_shared_board(system->current_player_index, 0xA);
                        break;
                    case 2:
                        mp3_func_8001C92C_1D52C(temp_v0_4->player_obj->omObj1->model[0], 0.75f);
                        mp3_func_800ED410_101030_shared_board(system->current_player_index, 0xF);
                        break;
                    }
                    mp3_func_8001C92C_1D52C(temp_v0_4->player_obj->omObj1->model[0], 1.0f);
                }
                
                // Update position
                temp_v0_4->blink = temp_v0_4->clink;
                temp_v0_4->bidx = temp_v0_4->cidx;
                temp_v0_4->clink = temp_v0_4->nlink;
                temp_v0_4->cidx = temp_v0_4->nidx;
                
                // Calculate next index based on direction
                if (temp_v0_4->rev & 1) {
                    temp_v0_4->nidx = temp_v0_4->nidx - 1;
                } else {
                    temp_v0_4->nidx = temp_v0_4->nidx + 1;
                }
                
                var_s5 = mp3_MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
                space = mp3_MBMasuGet(var_s5);
                mp3_func_800EBCBC_FF8DC_shared_board(var_s5);
                
                // Handle passing over certain space types
                switch (space->space_type) {
                case 1:   // Blue space
                case 2:   // Red space
                case 4:   // Happening space
                case 5:   // Event space
                case 6:   // Item space
                case 7:   // Bank space
                case 9:   // Battle space
                case 12:  // Bowser space
                case 15:  // Game guy space
                    mp3_func_800DBFBC_EFBDC_shared_board(system->current_player_index);
                    mp3_D_800D41C0_D4DC0--;
                    mp3_func_800EB97C_FF59C_shared_board(var_s5);
                    break;
                }
                
                // Play appropriate sound effect
                if (mp3_D_800D41C0_D4DC0 != 0) {
                    mp3_func_800F95FC_10D21C_shared_board(space->space_type);
                } else {
                    mp3_func_800F965C_10D27C_shared_board(space->space_type);
                }
                
                mp3_func_800E455C_F817C_shared_board();
                mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(var_s5, 1);
                
                if (mp3_D_80105664_119284_shared_board < 0) {
                    continue;
                }
                
                mp3_D_800D1240_D1E40 = 2;
                mp3_HuPrcSleep(-1);  // Suspend until resumed
        case 2:
                if (mp3_D_80105660_119280_shared_board & 1) {
                    var_s5 = mp3_func_800EBCC8_FF8E8_shared_board();
                    mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(var_s5, 2);
                    if (mp3_D_80105664_119284_shared_board >= 0) {
                        mp3_D_800D1240_D1E40 = 3;
                        mp3_HuPrcSleep(-1);
                        
                    }
                }
            /* fallthrough */
        case 3:
                if (mp3_D_80105660_119280_shared_board & 2) {
                    mp3_D_800D41C0_D4DC0 = 0;
                    continue;
                }
                mp3_func_800DB884_EF4A4_shared_board(system->current_player_index);
                mp3_HuPrcSleep(0xA);
            }

            if (system->current_board_index == 3) {
                mp3_GwSystem.boardData.halfWordBytes[4] = 0;
            }
            
            // Handle reverse direction cleanup
            if (temp_v0_4->rev & 0x80) {
                if (temp_v0_4->rev & 1) {
                    // Swap blink/nlink and bidx/nidx
                    temp_v1_2 = temp_v0_4->blink;
                    temp_v0_4->blink = temp_v0_4->nlink;
                    temp_v0_4->nlink = temp_v1_2;
                    
                    temp_v1_3 = temp_v0_4->bidx;
                    temp_v0_4->bidx = temp_v0_4->nidx;
                    temp_v0_4->nidx = temp_v1_3;
                }
                temp_v0_4->rev &= 0x7E;
            }
            
            mp3_func_800F2304_105F24_shared_board(-1, -1, 2);
            var_s5 = mp3_MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
            temp_v0_8 = mp3_MBMasuGet(var_s5)->space_type;
            
            // Update prize statistics
            switch (temp_v0_8) {
            case 4:  // Happening space
                mp3_func_800FF900_113520_shared_board(-1, 3);
                temp_v0_4->stats.prize.hatenaPrize++;
                break;
            case 2:  // Red space
                mp3_func_800FF900_113520_shared_board(-1, 1);
                temp_v0_4->stats.prize.redPrize++;
                break;
            case 1:  // Blue space
                temp_v0_4->stats.prize.bluePrize++;
                break;
            case 5:  // Event space
                mp3_func_800FF900_113520_shared_board(-1, 4);
                temp_v0_4->stats.prize.eventPrize++;
                break;
            case 15:  // Item space
                mp3_func_800FF900_113520_shared_board(-1, 4);
                temp_v0_4->stats.prize.gamblePrize++;
                break;
            case 12:  // Bank space
                mp3_func_800FF900_113520_shared_board(-1, 2);
                temp_v0_4->stats.prize.kupaPrize++;
                break;
            case 9:  // Battle space
                mp3_func_800FF900_113520_shared_board(0, 2);
                mp3_func_800FF900_113520_shared_board(1, 2);
                mp3_func_800FF900_113520_shared_board(2, 2);
                mp3_func_800FF900_113520_shared_board(3, 2);
                temp_v0_4->stats.prize.battlePrize++;
                break;
            case 6:  // Bowser space
                mp3_func_800FF900_113520_shared_board(-1, 2);
                temp_v0_4->stats.prize.itemPrize++;
                break;
            case 7:  // Gambling space
                mp3_func_800FF900_113520_shared_board(-1, 3);
                temp_v0_4->stats.prize.bankPrize++;
                break;
            }
            
            mp3_D_800D1240_D1E40 = 4;
            mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(var_s5, 3);
            
            if (mp3_D_80105664_119284_shared_board < 0) {
                goto labelE5C;
            }
            mp3_HuPrcSleep(-1);
            /* fallthrough */
        case 4:
        // STATE 4 & 5: Additional space handling
            if (mp3_D_80105660_119280_shared_board & 1) {
                mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(mp3_func_800EBCC8_FF8E8_shared_board(), 4);
                
                if (mp3_D_80105664_119284_shared_board >= 0) {
                    mp3_D_800D1240_D1E40 = 5;
                    mp3_HuPrcSleep(-1);
                }
            }
            /* fallthrough */
        case 5:
            mp3_HuPrcSleep(0x1E);
            labelE5C:
            
            // Return player to space position
            mp3_func_800ECC0C_10082C_shared_board(&sp20);
            mp3_func_800ED1E4_100E04_shared_board(&temp_v0_4->player_obj->unk18, &sp20, 
                                              &temp_v0_4->player_obj->unk18, 8);
            
            var_s5 = mp3_MBMasuLinkMasuIdGet(temp_v0_4->clink, temp_v0_4->cidx);
            space = mp3_MBMasuGet(var_s5);
            
            if (mp3_kakusiMasuStar == var_s5 || mp3_D_800D4080_D4C80 != 0) {
                mp3_func_800FF900_113520_shared_board(-1, 5);
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.6f));
                temp_s1 = mp3_func_800DDDD4_F19F4_shared_board(system->current_player_index);
                mp3_func_800DE858_F2478_shared_board();
                
                // Display message window
                mp3_func_80060394_60F94(1, sp30, 0x3F00);
                temp_v0_9 = mp3_func_80061188_61D88(-1, 0xA0 - (sp30[0] / 2), 0x96, sp30[0], sp30[1], 0);
                mp3_func_8005B43C_5C03C(temp_v0_9, (char*)0x3F00, -1, -1);
                mp3_func_80061388_61F88(temp_v0_9);
                mp3_func_800600C0_60CC0(temp_v0_9, 1);
                mp3_HuPrcChildWait();
                
                mp3_func_800600C0_60CC0(temp_v0_9, 0);
                mp3_func_800EDC58_101878_shared_board(temp_v0_9, temp_v0_4->turn);
                mp3_func_80061A5C_6265C(temp_v0_9, 0);
                mp3_func_8005F364_5FF64(temp_v0_9);
                mp3_func_800DE868_F2488_shared_board();
                
                // Wait for player input
                while (!(mp3_func_800DE84C_F246C_shared_board())) {
                    mp3_HuPrcVSleep();
                }
                
                // Display follow-up message
                mp3_func_80060394_60F94(1, sp30, 0x3F01);
                temp_v0_10 = mp3_func_80061188_61D88(-1, 0xA0 - (sp30[0] / 2), 0x96, sp30[0], sp30[1], 0);
                mp3_func_8005B43C_5C03C(temp_v0_10, (char*)0x3F01, -1, -1);
                mp3_func_80061388_61F88(temp_v0_10);
                mp3_func_800EDC58_101878_shared_board(temp_v0_10, temp_v0_4->turn);
                mp3_func_80061A5C_6265C(temp_v0_10, 0);
                mp3_func_8005F364_5FF64(temp_v0_10);
                mp3_func_800DE868_F2488_shared_board();
                
                mp3_HuPrcChildLink(temp_s6, temp_s1);
                mp3_HuPrcChildWait();
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.3f));
                mp3_HuPrcChildWait();
                mp3_HuPrcSleep(1);
                
                // Update star block history
                mp3_kakusiMasuStarOld[mp3_D_800D6A44_D7644++] = mp3_kakusiMasuStar;
                mp3_D_800D6A44_D7644 = mp3_D_800D6A44_D7644 % 10;
                mp3_kakusiMasuStar = -1;
                mp3_MBBlockMasuUpdate();
            }
            
            // COIN BLOCK HANDLING (similar structure to star block)
            if (mp3_kakusiMasuCoin == var_s5 || mp3_D_800D2130 != 0) {
                mp3_func_800FF900_113520_shared_board(-1, 5);
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.6f));
                temp_s1 = mp3_func_800DE7E4_F2404_shared_board(system->current_player_index);
                mp3_func_800DE858_F2478_shared_board();
                mp3_func_80060394_60F94(1, sp38, 0x3F00);
                temp_v0_13 = mp3_func_80061188_61D88(-1, 0xA0 - (sp38[0] / 2), 0x96, sp38[0], sp38[1], 0);
                mp3_func_8005B43C_5C03C(temp_v0_13, (char*)0x3F00, -1, -1);
                mp3_func_80061388_61F88(temp_v0_13);
                mp3_func_800600C0_60CC0(temp_v0_13, 1);
                mp3_HuPrcChildWait();
                mp3_func_800600C0_60CC0(temp_v0_13, 0);
                mp3_func_800EDC58_101878_shared_board(temp_v0_13, temp_v0_4->turn);
                mp3_func_80061A5C_6265C(temp_v0_13, 0);
                mp3_func_8005F364_5FF64(temp_v0_13);
                mp3_func_800DE868_F2488_shared_board();

                while (!mp3_func_800DE84C_F246C_shared_board()) {
                    mp3_HuPrcVSleep();
                }

                mp3_HuPrcChildLink(temp_s6, temp_s1);
                mp3_HuPrcChildWait();
                mp3_func_80060394_60F94(1, sp38, 0x3F02);
                temp_v0_13 = mp3_func_80061188_61D88(-1, 0xA0 - (sp38[0] / 2), 0x96, sp38[0], sp38[1], 0);
                mp3_func_8005B43C_5C03C(temp_v0_13, (char*)0x3F02, -1, -1);
                mp3_func_80061388_61F88(temp_v0_13);
                mp3_func_800EDC58_101878_shared_board(temp_v0_13, temp_v0_4->turn);
                mp3_func_80061A5C_6265C(temp_v0_13, 0);
                mp3_func_8005F364_5FF64(temp_v0_13);
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.3f));
                mp3_HuPrcChildWait();
                mp3_HuPrcSleep(1);
                mp3_kakusiMasuCoinOld[mp3_D_800D1FEC_D2BEC++] = mp3_kakusiMasuCoin;
                mp3_D_800D1FEC_D2BEC = mp3_D_800D1FEC_D2BEC % 10;
                mp3_kakusiMasuCoin = -1;
                mp3_MBBlockMasuUpdate();
            }
    
            // ITEM BLOCK HANDLING
            if (mp3_kakusiMasuItem == var_s5 || mp3_D_800D1708_D2308 != 0) {
                short var_s1;
                short temp_v1_6;
                mp3_func_800FF900_113520_shared_board(-1, 5);
                
                // Random item selection with weighted probabilities
                do {
                    var_s1 = 0;
                    temp_v1_6 = mp3_MBRand(100.0f) + 1;
                    
                    while (1) {
                        if (temp_v1_6 <= mp3_D_80101E70_115A90_shared_board[var_s1][1]) break;
                        var_s1++;
                    }
                    
                    // Reroll if Boo item and special flag is set
                } while (mp3_GwSystem.unk_52 != 0 && mp3_D_80101E70_115A90_shared_board[var_s1][0] == 0x12);
                
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.6f));
                mp3_func_800DE414_F2034_shared_board(system->current_player_index, 
                                                mp3_D_80101E70_115A90_shared_board[var_s1][0]);
                mp3_func_800DE858_F2478_shared_board();
                
                // Display item message window
                mp3_func_80060394_60F94(1, sp40, 0x3F00);
                temp_v0_13 = mp3_func_80061188_61D88(-1, 0xA0 - (sp40[0] / 2), 0x96, sp40[0], sp40[1], 0);
                mp3_func_8005B43C_5C03C(temp_v0_13, (char*)0x3F00, -1, -1);
                mp3_func_80061388_61F88(temp_v0_13);
                mp3_func_800600C0_60CC0(temp_v0_13, 1);
                mp3_HuPrcChildWait();
                
                mp3_func_800600C0_60CC0(temp_v0_13, 0);
                mp3_func_800EDC58_101878_shared_board(temp_v0_13, temp_v0_4->turn);
                mp3_func_80061A5C_6265C(temp_v0_13, 0);
                mp3_func_8005F364_5FF64(temp_v0_13);
                mp3_func_800DE868_F2488_shared_board();
                
                // Wait for input
                while (!(mp3_func_800DE84C_F246C_shared_board() & 0xFF)) {
                    mp3_HuPrcVSleep();
                }
                
                mp3_func_800DE868_F2488_shared_board();
                mp3_func_8006022C_60E2C(var_s1 + 0x3F04, 0);
                
                // Display item received message
                mp3_func_80060394_60F94(1, sp40, 0x3F03);
                temp_v0_14 = mp3_func_80061188_61D88(-1, 0xA0 - (sp40[0] / 2), 0x96, sp40[0], sp40[1], 0);
                mp3_func_8005B6BC_5C2BC(temp_v0_14, var_s1 + 0x3F04, 0);
                mp3_func_8005B43C_5C03C(temp_v0_14, (char*)0x3F03, -1, -1);
                mp3_func_80061388_61F88(temp_v0_14);
                mp3_func_800EDC58_101878_shared_board(temp_v0_14, temp_v0_4->turn);
                mp3_func_80061A5C_6265C(temp_v0_14, 0);
                mp3_func_8005F364_5FF64(temp_v0_14);
                
                // Check if player has empty item slot
                if (mp3_PlayerHasEmptyItemSlot(system->current_player_index) == -1) {
                    mp3_MBDlgResultWinExec(0x3F0A);  // Inventory full message
                }
                
                mp3_func_800DE858_F2478_shared_board();
                mp3_HuPrcSleep(5);
                
                // Wait for input
                while (!(mp3_func_800DE84C_F246C_shared_board() & 0xFF)) {
                    mp3_HuPrcVSleep();
                }
                
                mp3_HuPrcSleep(0xA);
                mp3_HuPrcChildLink(temp_s6, mp3_func_800E8EDC_FCAFC_shared_board(1.3f));
                mp3_HuPrcChildWait();
                mp3_HuPrcSleep(1);
                
                // Update item block history
                mp3_kakusiMasuItemOld[mp3_D_800D1F7A_D2B7A++] = mp3_kakusiMasuItem;
                mp3_D_800D1F7A_D2B7A = mp3_D_800D1F7A_D2B7A % 10;
                mp3_kakusiMasuItem = -1;
                mp3_MBBlockMasuUpdate();
            }
            
            // HAPPENING SPACE: Check for duel minigame
            if (space->space_type == 4) {
                goto label;
            } else {
                short temp_v0_15;
                temp_v0_15 = mp3_MBKettouPlayerBitGet(1);
                
                if (temp_v0_15 == 0) {
                    goto label;
                } else {
                    mp3_GwSystem.unk_58 = temp_v0_15;
                    mp3_GwSystem.playerIndexVisitingBowser = (1 << temp_v0_4->turn); //?
                    mp3_func_800FF900_113520_shared_board(temp_v0_4->turn, 3);
                    
                    temp_v0_16 = mp3_MBKettouExec(temp_v0_4, 0);
                    
                    if (temp_v0_16 == 0) {
                        goto label; //?
                        mp3_MBKettouResultExec();
                    } else if (temp_v0_16 == 1) {
                        mp3_HuPrcSleep(-1);
                    }
                    mp3_MBKettouComResultSet();
                }
            }
            /* fallthrough */
        case 8: 
            mp3_MBKettouResultExec();
            label:
            mp3_func_800ECDD4_1009F4_shared_board(-1, space->space_type);
            mp3_func_800F4798_1083B8_shared_board(system->current_player_index, temp_v0_4->color);
            
            switch (space->space_type) {
            case 1:  // BLUE SPACE
                var_v1 = (mp3_GWBoardFlagCheck(2) != 0) ? 2 : 1;  // Last 5 turns doubles coins
                var_s0 = var_v1*2;
                var_s0 += var_v1;

                label181C:
                mp3_MBCoinChangeCreate(system->current_player_index, var_s0);
                mp3_func_800F5D44_109964_shared_board(system->current_player_index, var_s0);
                mp3_HuPrcSleep(0x1E);
                goto label2444;
               
                
            case 2:  // RED SPACE
                var_v1 = (mp3_GWBoardFlagCheck(2) != 0) ? 2 : 1;
                var_s0 = var_v1*2;
                var_s0 += var_v1;
                var_s0 = -var_s0;
                goto label181C;
                
                // MBCoinChangeCreate(system->current_player_index, var_s0);
                // func_800F5D44_109964_shared_board(system->current_player_index, var_s0);
                break;
                
            case 4:  // HAPPENING SPACE
                if (mp3_D_80101B6C_11578C_shared_board == NULL) {
                    goto label2444;
                }
                
                // Execute board-specific happening event
                mp3_HuPrcChildLink(temp_s6, mp3_omAddPrcObj(mp3_D_80101B6C_11578C_shared_board, 0x4800, 0, 0));
                mp3_HuPrcChildWait();
                
                // Special handling for board 3
                if (system->current_board_index == 3 && mp3_GwSystem.boardData.halfWordBytes[3] != 0) {
                    mp3_GwSystem.boardData.halfWordBytes[3] = 0;
                    goto label654;  // Jump back to state 10 (dice roll)
                }
                
                // Check for another duel minigame
                temp_v0_18 = mp3_MBKettouPlayerBitGet(1);
                
                if (temp_v0_18 == 0) {
                    goto label2444;
                }
                mp3_GwSystem.unk_58 = temp_v0_18;
                mp3_GwSystem.playerIndexVisitingBowser = (1 << mp3_MBGetPlayerStruct(-1)->turn); //?
                mp3_func_800FF900_113520_shared_board(mp3_MBGetPlayerStruct(-1)->turn, 3);
                
                temp_v0_16 = mp3_MBKettouExec(temp_v0_4, 1);
                
                if (temp_v0_16 == 0) {
                    goto label2444;
                } else if (temp_v0_16 == 1) {
                    mp3_HuPrcSleep(-1);
                }
                mp3_MBKettouComResultSet();
                mp3_MBKettouResultExec();
                goto label2444;
                
            case 5:  // EVENT SPACE
                mp3_D_800D1240_D1E40 = 0x10;
                
                // Set up team groups
                for (var_s1 = 0; var_s1 < 4; var_s1++) {
                    temp_s0_2 = mp3_MBGetPlayerStruct(var_s1);
                    temp_s0_2->group = (var_s1 != mp3_GetCurrentPlayerIndex());
                }
                
                // Trigger event minigame
                mp3_func_800FF794_1133B4_shared_board(0x6A, 0, 5, 1);
                mp3_HuPrcSleep(-1);
                mp3_HuPrcSleep(0x1E);
                goto label2444;
                
            case 6:  // ITEM SPACE
                mp3_D_800D037C_D0F7C = 0;
                mp3_HuPrcSleep(8);
                
                // Check if last turn
                if (system->current_turn == system->total_turns) {
                    mp3_MBDlgResultWinExec(0x3C01);  // Last turn message
                    goto label2444;
                }
                
                // Check if inventory full
                if (mp3_PlayerHasEmptyItemSlot(system->current_player_index) == -1) {
                    mp3_MBDlgResultWinExec(0x3C00);  // Inventory full
                    goto label2444;
                }
                
                // Item shop - random outcome
                temp_v0_20 = mp3_MBRand(5.0f);

                switch (temp_v0_20) {
                case 0:
                    mp3_func_800F85C0_10C1E0_shared_board();  // Shop outcome 1
                    goto label2444;                    
                case 1:
                    mp3_func_800F85E4_10C204_shared_board();  // Shop outcome 2
                    goto label2444;                    
                default:
                    // Item minigame option
                    if (mp3_func_800F2198_105DB8_shared_board(-1) == 0 || system->show_com_minigames == 0) {
                        goto label1d70;
                    }
                                                // COM item minigame logic
                    mp3_WipeCreateOut(6, 0x10);
                    mp3_HuPrcSleep(0x11);
                    mp3_HuPrcSleep(5);
                    mp3_WipeCreateIn(6, 0x10);
                    mp3_HuPrcSleep(0x11);

                    temp_s2 = mp3_RNGPercentChance(66) ? 0 : 1;
                    
                    // AI decision logic
                    if (!(mp3_MBRand(100.0f) >= mp3_D_80101C24_115844_shared_board[mp3_GwPlayer[system->current_player_index].cpu_difficulty])) {
                        // AI accepts - determine item
                        var_s1 = 0;
                        temp_s0_3 = mp3_BoardPlayerRankCalc(system->current_player_index);
                        temp_s0_4 = mp3_D_80101D2C_11594C_shared_board[temp_s2][temp_s0_3][mp3_BoardGetTurnTier(-1)];
                        temp_a0 = mp3_MBRand(100.0f);

                        // Find item based on weighted table
                        for (var_s1 = 0; var_s1 < 8; var_s1++) {
                            if (mp3_D_80101C8C_1158AC_shared_board[temp_s2][temp_s0_4][var_s1] > temp_a0) {
                                break;
                            }               
                        }                            
                        

                        // Display message
                        mp3_MBDlgWinInsertCreate(-1, 0x3C22, mp3_D_80101C4C_11586C_shared_board[temp_s2][var_s1], 0, 0, 0, 0);
                        mp3_MBDlgWinClose();
                        mp3_MBDlgWinKill();
                        
                        // Store item
                        mp3_GwPlayer[system->current_player_index].bonusCoin = mp3_D_80101C2C_11584C_shared_board[temp_s2][var_s1];
                        
                        // Display item sprite with animation
                        temp_s2_2 = mp3_HuSprGrpCreate(1, 5);
                        temp_v0_21 = mp3_DataRead(mp3_D_8010197C_11559C_shared_board[mp3_D_80101C2C_11584C_shared_board[temp_s2][var_s1]]);
                        temp_s3_3 = mp3_func_80055810_56410(temp_v0_21);
                        mp3_DataClose(temp_v0_21);
                        
                        mp3_func_80055024_55C24(temp_s2_2, 0, temp_s3_3, 0);
                        mp3_HuSprPriSet(temp_s2_2, 0, 0xA);
                        mp3_func_800550F4_55CF4(temp_s2_2, 0, 0);
                        mp3_HuSprAttrSet(temp_s2_2, 0, 0x180C);
                        mp3_func_80054904_55504(temp_s2_2, 0, 0xA0, 0x5A);
                        mp3_func_80055458_56058(temp_s2_2, 0, 0);
                        mp3_HuAudFXPlay(0x10);
                        
                        // Animate sprite appearing
                        for (var_s1 = 0; var_s1 < 0xA; var_s1++) {
                            mp3_func_80055458_56058(temp_s2_2, 0, (var_s1 * 25));
                            mp3_HuPrcVSleep();
                        }
                        
                        mp3_func_80055458_56058(temp_s2_2, 0, 0x100);
                        mp3_HuPrcSleep(5);
                        mp3_func_800F2304_105F24_shared_board(-1, 5, 0);
                        mp3_HuPrcSleep(5);
                        mp3_func_8004ACE0_4B8E0(0x2BD, system->current_player_index);
                        mp3_HuPrcSleep(0x14);
                        mp3_func_800F2388_105FA8_shared_board(-1, -1, 0, 5, 2);
                        mp3_HuPrcSleep(0xA);
                        
                        // Clean up sprite
                        mp3_HuSprGrpKill(temp_s2_2);
                        mp3_HuSprKill(temp_s3_3);
                        goto tempCase17;
                    }
                    

                    mp3_MBDlgResultWinExec(0x3C32);
                    goto label2444;

                    label1d70:
                    mp3_func_800F7108_10AD28_shared_board();
    
                    for (var_s1 = 0; var_s1 < 4; var_s1++) {
                        mp3_GwPlayer[var_s1].group = 1;
                    }
                    
                    temp_v0_4->group = 0;
                    mp3_HuPrcChildLink(temp_s6, mp3_func_800E0F84_F4BA4_shared_board());
                    mp3_HuPrcChildWait();
                    
                    mp3_D_800D1240_D1E40 = 0x11;
                    mp3_D_80105664_119284_shared_board = 2;
                    mp3_D_80105666_119286_shared_board = 1;
                    mp3_D_800D1360.unk_20 = 6;
                    mp3_HuPrcSleep(-1);
                    goto label2444;
                }

                tempCase17:
                
                mp3_GwPlayer[system->current_player_index].itemNo[mp3_PlayerHasEmptyItemSlot(system->current_player_index)] = 
                    mp3_GwPlayer[system->current_player_index].bonusCoin;
                mp3_HuPrcSleep(0x1E);
                goto label2444;
            case 9:
                if (!(mp3_func_800FB624_10F244_shared_board(temp_v0_4))) {
                    goto label2444;
                } else {
                    mp3_D_800D037C_D0F7C = 0;
                    mp3_func_800F7108_10AD28_shared_board();
                    mp3_HuPrcChildLink(temp_s6, mp3_MBMgCallBattleCreate());
                    mp3_HuPrcChildWait();
                    mp3_D_800D1240_D1E40 = 0x12;
                    mp3_D_80105664_119284_shared_board = 2;
                    mp3_D_80105666_119286_shared_board = 1;
                    mp3_D_800D1380_D1F80 = 8;
                    mp3_HuPrcSleep(-1);
                }

                test:
                for (var_s1 = 0; var_s1 < 4; var_s1++) {
                    if (mp3_GwPlayer[var_s1].bonusCoin != 3) {
                        break;
                    }
                }
                
                if (var_s1 >= 4) {
                    // All players done with battle
                    mp3_func_800FC3D0_10FFF0_shared_board();
                }
                
                goto label2444;
            case 12:  // BOWSER SPACE
                mp3_D_800D1240_D1E40 = 6;
                mp3_GwSystem.playerIndexVisitingBowser = system->current_player_index;
                mp3_func_800FF794_1133B4_shared_board(0x50, 0, 3, 1);
                mp3_HuPrcSleep(-1);
                mp3_HuPrcSleep(0x1E);
                goto label2444;
                
            case 15:  // GAME GUY SPACE
                mp3_HuPrcSleep(8);
                
                // Create game guy object
                temp_v0_22 = mp3_MBModelCreate(0x3E, NULL);
                mp3_MBModelTempAllocFree(temp_v0_22);
                mp3_HuVecCopy3F(&temp_v0_22->coords, &temp_v0_4->player_obj->coords);
                temp_v0_22->velocity.x = 100.0f;
                
                // Animate game guy appearing on screen
                while (temp_v0_22->velocity.x >= 30.0f) {
                    temp_v0_22->velocity.x -= 2.0f;
                    mp3_HuPrcVSleep();
                }
                
                temp_s1 = mp3_func_800EDB98_1017B8_shared_board(temp_v0_22, 5.0f, 2.0f);
                mp3_HuAudFXPlay(0x2A1);
                
                if (mp3_GwPlayer[system->current_player_index].coin != 0) {
                    // Take all coins
                    mp3_MBDlgWinExec(0xA, 0x2F00);
                    mp3_GwPlayer[system->current_player_index].gameCoin = 
                        mp3_GwPlayer[system->current_player_index].coin;
                    
                    mp3_MBCoinChangeCreate(system->current_player_index, 
                                       -mp3_GwPlayer[system->current_player_index].coin);
                    mp3_func_800F5D44_109964_shared_board(system->current_player_index,
                                                     -mp3_GwPlayer[system->current_player_index].coin);
                    mp3_HuPrcSleep(0x1E);
                    mp3_MBDlgWinExec(0xA, 0x2F02);
                    mp3_omDelPrcObj(temp_s1);
                    
                    // Animate game guy leaving with player
                    while (temp_v0_22->velocity.x >= 10.0f) {
                        temp_v0_22->velocity.x -= 2.0f;
                        mp3_HuPrcVSleep();
                    }
                    
                    mp3_func_800EE688_1022A8_shared_board(temp_v0_22, 2.0f, 0.0001f);
                    mp3_func_800EE688_1022A8_shared_board(temp_v0_4->player_obj, 2.0f, 0.0001f);
                    mp3_HuPrcSleep(0x1E);
                } else {
                    mp3_MBDlgWinExec(0xA, 0x2F01);
                    mp3_omDelPrcObj(temp_s1);
                    // Animate game guy leaving with player
                    while (temp_v0_22->velocity.x <= 100.0f) {
                        temp_v0_22->velocity.x += 4.0f;
                        mp3_HuPrcVSleep();
                    }
                    mp3_MBModelKill(temp_v0_22);
                    goto label2488;
                }
                
                    
                if (mp3_func_800F2198_105DB8_shared_board(-1) != 0 && system->show_com_minigames != 0) {
                    // COM game guy - immediate result
                    mp3_WipeCreateOut(9, 0x10);
                    mp3_HuPrcSleep(0x11);
                    mp3_MBModelKill(temp_v0_22);
                    mp3_func_800EE688_1022A8_shared_board(temp_v0_4->player_obj, 0, 0);
                    temp_v0_4->player_obj->velocity.x = 0.0f;
                    mp3_HuPrcSleep(5);
                    mp3_WipeCreateIn(9, 0x10);
                    mp3_HuPrcSleep(0x11);
                    
                    // Weighted random multiplier
                    temp_v1_8 = mp3_MBRand(GAME_GUY_RANDOM_MAX) + 1;

                    for (var_s1 = 0; var_s1 < ARRAY_COUNT(mp3_D_80101C08_115828_shared_board); var_s1++) {
                        if (mp3_D_80101C08_115828_shared_board[var_s1].weight >= temp_v1_8) {
                            break;
                        }
                    }

                    
                    temp_a0_3 = mp3_D_80101C08_115828_shared_board[var_s1].multiplier;
                    
                    if (temp_a0_3 != 0) {
                        // Won multiplier
                        var_s1_12 = mp3_GwPlayer[system->current_player_index].gameCoin * temp_a0_3;
                        
                        if (var_s1_12 > 999) {
                            var_s1_12 = 999;
                        }
                        
                        mp3_sprintf(sp48, mp3_D_801025D0_1161F0_shared_board, var_s1_12);
                        mp3_MBDlgWinInsertCreate(-1, 0x2F03, (s32)sp48, 0, 0, 0, 0);
                        mp3_MBDlgWinClose();
                        mp3_MBDlgWinKill();
                        
                        mp3_MBCoinChangeCreate(system->current_player_index, var_s1_12);
                        mp3_func_800F5D44_109964_shared_board(system->current_player_index, var_s1_12);
                        mp3_HuPrcSleep(0x14);
                        mp3_func_800F2304_105F24_shared_board(-1, 5, 0);
                        mp3_func_8004ACE0_4B8E0(0x274, system->current_player_index);
                        mp3_func_800F22C0_105EE0_shared_board(-1);
                    } else {
                        // Lost everything
                        mp3_MBDlgWinExec(-1, 0x2F04);
                        mp3_func_800F2304_105F24_shared_board(-1, 3, 0);
                        mp3_func_8004ACE0_4B8E0(0x286, system->current_player_index);
                        mp3_func_800F22C0_105EE0_shared_board(-1);
                        mp3_HuPrcSleep(0x14);
                    }
                    
                    mp3_func_800F2388_105FA8_shared_board(-1, -1, 0, 5, 2);
                    mp3_HuPrcSleep(0xA);
                    goto label2488;
                } else {
                    // Setup for game guy minigame
                    mp3_D_800D1240_D1E40 = 0x13;
                    mp3_D_80105664_119284_shared_board = 2;
                    mp3_D_80105666_119286_shared_board = 1;
                    mp3_D_800D1360.unk_20 = 9;
                    
                    for (var_s1 = 0; var_s1 < 4; var_s1++) {
                        mp3_GwPlayer[var_s1].group = 1;
                    }
                    temp_v0_4->group = 0;
                    
                    // Select minigame based on weighted random
                    temp_a0_4 = mp3_MBRand(100.0f);
                    var_v1_3 = 0;

                    for (var_v1_3 = 0; var_v1_3 < ARRAY_COUNT(mp3_D_80101C04_115824_shared_board); var_v1_3++) {
                        if (mp3_D_80101C04_115824_shared_board[var_v1_3] > temp_a0_4) {
                            break;
                        }
                    }
                    
                    if (var_v1_3 == ARRAY_COUNT(mp3_D_80101C04_115824_shared_board)) {
                        var_v1_3 = ARRAY_COUNT(mp3_D_80101C04_115824_shared_board) - 1;
                    }
                    
                    system->minigame_index = mp3_D_80101C00_115820_shared_board[var_v1_3];
                    mp3_GwSystem.playerIndexVisitingBowser = system->current_player_index;
                }
                
                mp3_HuPrcSleep(-1);
                goto label2438;
                
            case 3:   // Star space
            case 7:   // Bank space (already handled)
            case 8:   // Boo space
            case 10:  // Mushroom space
            case 11:  // Warp space
            case 13:  // Chance time space
            case 14:  // Koopa bank space
            default:
                goto label2444;
            }
        case 17:
            goto tempCase17;
        case 18:
            goto test;
        case 19:
            label2438:
                mp3_func_800FC4E0_110100_shared_board();
                label2444:
                mp3_D_800D1240_D1E40 = 7;
                mp3_D_80105660_119280_shared_board = mp3_func_800EBAC8_FF6E8_shared_board(var_s5, 5);
                if (mp3_D_80105664_119284_shared_board < 0) {
                    goto label2488;
                }
                mp3_HuPrcSleep(-1);
        case 7:
            mp3_HuPrcSleep(0x1E);
            label2488:
            mp3_D_800D037C_D0F7C = 0;
            
            // END OF TURN: Check for end of round minigames
            if (system->current_player_index >= 3) {
                mp3_func_800EBAC8_FF6E8_shared_board(-3, 7);
                mp3_func_8001FDE8_209E8(mp3_MBGetPlayerStruct(3)->player_obj->omObj1->model[0]);
                mp3_D_800A12D4 = 0;
                mp3_func_800F7108_10AD28_shared_board();
                
                mp3_HuPrcChildLink(temp_s6, mp3_MBMgCallCreate());
                mp3_HuPrcChildWait();
                
                //@patch check 0xFF, not less than 0 (it's a u8 instead of s8 now)
                if (system->minigame_index != 0xFF) {
                    mp3_D_800D1240_D1E40 = 0;
                    
                    // Determine minigame type
                    if (system->total_turns >= 0 && system->current_turn >= system->total_turns) {
                        if (mp3_GwSystem.unk_52 == 2) {
                            mp3_D_80105664_119284_shared_board = 3;
                        } else {
                            mp3_D_80105664_119284_shared_board = 0x23;
                        }
                    } else {
                        mp3_D_80105664_119284_shared_board = 3;
                    }
                    mp3_D_80105666_119286_shared_board = 1;
                    mp3_D_800D1360.unk_20 = 0xA;
                    
                    for (var_s0_2 = 0; var_s0_2 < 4; var_s0_2++) {
                        mp3_func_800F482C_10844C_shared_board(var_s0_2);
                    }
                    
                    mp3_HuPrcSleep(-1);
                }
            }
            
            // Check for game end condition
            if (mp3_MBLast5Check() != 0) {
                mp3_D_800D1240_D1E40 = 0;
                mp3_D_80105664_119284_shared_board = 1;
                mp3_HuPrcSleep(-1);
            }
            
            mp3_HuPrcSleep(4);
            
            mp3_HuPrcChildLink(temp_s6, mp3_func_800F292C_10654C_shared_board());
            mp3_HuPrcChildWait();
            
            mp3_MBNextPlayerTurn();
            
            // Hide all players
            for (var_s1 = 0; var_s1 < 4; var_s1++) {
                mp3_func_800ECC28_100848_shared_board(var_s1);
                mp3_MBMotionSet(mp3_MBGetPlayerStruct(var_s1)->player_obj, -1, 2);
            }
            
            mp3_HuPrcVSleep();
        
            if (mp3_GwSystem.current_board_index == CHILLY_WATERS && mp3_GWBoardFlagCheck(0x12) != 0) {
                mp3_func_800EBEC8_FFAE8_shared_board();
                mp3_GWBoardFlagClear(0x12);
            }
            
            mp3_func_800FF840_113460_shared_board(NULL);
            mp3_D_800D1240_D1E40 = 1;
        }
    }
}