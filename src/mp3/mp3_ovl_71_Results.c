#include "mp3.h"

void mp3_AdjustPlayerCoins(s32 arg0, s32 arg1);
void mp3_HuAudSeqFadeOut(s16 speed);
s16 mp3_HuAudSeqPlay(s16 musId);
void mp3_WipeCreateIn(s32, s32);
s32 mp3_WipeCreateOut(s32, s32);
s32 mp3_WipeStatGet(void);
void func_80037258_37E58(void);                            /* extern */
void func_800E66E0_FA300_shared_board(void);               /* extern */
void func_800E69D8_FA5F8_shared_board(void);               /* extern */
s32 func_80106A80_4E7EA0_mgresultboard(s8);    /* extern */
s32 func_80106C80_4E80A0_mgresultboard(s8);    /* extern */
void func_80106D50_4E8170_mgresultboard(s32, s32);       /* extern */
s32 func_80106D88_4E81A8_mgresultboard(s32, s16);   /* extern */
s32 func_80106DB8_4E81D8_mgresultboard(s32, s16); /* extern */
void func_80107234_4E8654_mgresultboard(void); /* extern */
void func_80107650_4E8A70_mgresultboard(s8); /* extern */
void func_80107800_4E8C20_mgresultboard(s32);          /* extern */
void func_801079B0_4E8DD0_mgresultboard(s32);          /* extern */
void func_80107A58_4E8E78_mgresultboard();             /* extern */
void mp3_omVibrate(s16, s32, s32, s32);
u8 rand8_Shared(void);
extern s16 D_800CDA7C_CE67C[];
extern u32 D_8010AAF0_4EBF10_mgresultboard;
extern f32 D_8010AAF4_4EBF14_mgresultboard;
extern s32 D_8010AAF8_4EBF18_mgresultboard;
extern s32 D_8010AD90_4EC1B0_mgresultboard;
extern s8 D_8010AD94_4EC1B4_mgresultboard;

typedef struct PlayerResult {
/* 0x00 */ s8 idx;
/* 0x01 */ s8 unk_01;
/* 0x02 */ s8 unk_02;
/* 0x03 */ s8 unk_03;
/* 0x04 */ s16 score;
/* 0x06 */ s16 coin;
/* 0x08 */ s16 gameCoin;
/* 0x0A */ s16 bonusCoin;
} PlayerResult; //sizeof 0x0C
extern PlayerResult D_8010B018_4EC438_mgresultboard[4];
extern PlayerResult D_8010B048_4EC468_mgresultboard[4];

void func_80105CE8_4E7108_mgresultboard(void) {
    s32 temp_a1;
    s32 temp_a2;
    s16 var_a1;
    s8 var_a0;
    u16 var_a0_3;
    u16 var_a1_3;
    s32 var_s3;
    s32 var_s5;
    u32 var_s4;
    s32 var_v1_3;
    s8 i;
    s8 new_var;
    
    var_s5 = 0;
    var_s4 = D_8010AAF0_4EBF10_mgresultboard;
    var_s3 = 0;
    switch (var_s4) {
    case 0:
        mp3_HuAudSeqPlay(0x14);
        D_8010AD90_4EC1B0_mgresultboard = 0;
        var_s4 += 1;
        break;
    case 1:
        if (D_8010AAF8_4EBF18_mgresultboard == 1) {
            mp3_WipeCreateIn(0xFF, 0x10);
            var_s4 += 1;
        }
        break;
    case 2:
        D_8010AD90_4EC1B0_mgresultboard++;
        if (D_8010AD90_4EC1B0_mgresultboard >= 0x14) {
            D_8010AD94_4EC1B4_mgresultboard = 0;
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 3:
        D_8010AD90_4EC1B0_mgresultboard++;
        if (D_8010AD90_4EC1B0_mgresultboard >= ((s32) (40.0f / D_8010AAF4_4EBF14_mgresultboard) + (s32) (15.0f / D_8010AAF4_4EBF14_mgresultboard))) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            D_8010AD94_4EC1B4_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 4:
        D_8010AD94_4EC1B4_mgresultboard = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            //temp_v0_2 = D_8010B048_4EC468_mgresultboard[var_v1 >> 0x18].idx * 0x38;
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin;
            temp_a1 += mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].gameCoin;
            if (temp_a1 <= 0) {
                D_8010AD94_4EC1B4_mgresultboard++;
            }
        }

        if (D_8010AD94_4EC1B4_mgresultboard >= 4) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 = 0x10;
        } else {
            D_8010AD94_4EC1B4_mgresultboard = 0;
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 5:
        var_s3 = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].gameCoin;
            temp_a1 += mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin;
            if (temp_a1 > 0) {
                var_s5++;
                var_s3 = func_80106D88_4E81A8_mgresultboard(i, ((((rand8_Shared()) << 8) | (rand8_Shared())) % 1000));
                func_80107800_4E8C20_mgresultboard(i);               
            } else {
                func_80107650_4E8A70_mgresultboard(i);
            }
        }

        if (var_s3 == 1) {
            if (++D_8010AD90_4EC1B0_mgresultboard >= 2) {
                D_8010AD90_4EC1B0_mgresultboard = 0;
                var_s4 += 1;
            }
        }
        break;
    case 6:
        var_s3 = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].gameCoin;
            temp_a1 += mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin;
            if (temp_a1 > 0) {
                var_s3 = func_80106D88_4E81A8_mgresultboard(i, temp_a1);
                func_80107800_4E8C20_mgresultboard(i);
                var_s5++;
            } else {
                func_80107650_4E8A70_mgresultboard(i);
            }
        }

        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin;
            if (temp_a1 >= 10) {
                func_80106D50_4E8170_mgresultboard(i, 4);
                var_s5++;
            }
        }
        if (var_s3 == 1) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }

        break;
    case 7:
        D_8010AD90_4EC1B0_mgresultboard++;
        if (!(D_8010AD90_4EC1B0_mgresultboard < ((s32) (40.0f / D_8010AAF4_4EBF14_mgresultboard) + (s32) (15.0f / D_8010AAF4_4EBF14_mgresultboard)))) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 8:
        var_s3 = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].gameCoin;
            temp_a1 += mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin;
            if (temp_a1 > 0) {
                var_s5++;
                var_s3 = func_80106DB8_4E81D8_mgresultboard(i, ((((rand8_Shared()) << 8) | (rand8_Shared())) % 1000));
                func_80107800_4E8C20_mgresultboard(i);
                
            } else {
                func_80107650_4E8A70_mgresultboard(i);
            }
        }

        if (var_s3 == 1) {
        D_8010AD90_4EC1B0_mgresultboard++;
        if (D_8010AD90_4EC1B0_mgresultboard >= 2) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break; //TODO: fallthrough?
        }
        break;
    case 9:
        var_s3 = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_a2 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].coin;
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].gameCoin;
            if ((temp_a1 += mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin) > 0) {  //TODO: this check is wrong i think
                var_s3 = func_80106DB8_4E81D8_mgresultboard(i, temp_a2 + temp_a1);
                func_80107800_4E8C20_mgresultboard(i);
                var_s5++;
            } else {
                func_80107650_4E8A70_mgresultboard(i);
            }
        }
 
        if (var_s3 == 1) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 10:
        D_8010AD90_4EC1B0_mgresultboard++;
        if (D_8010AD90_4EC1B0_mgresultboard < ((s32) (40.0f / D_8010AAF4_4EBF14_mgresultboard) + (s32) (15.0f / D_8010AAF4_4EBF14_mgresultboard))) {

        } else {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 11:
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            D_8010B018_4EC438_mgresultboard[i] = D_8010B048_4EC468_mgresultboard[i];
            new_var = D_8010B048_4EC468_mgresultboard[i].idx;
            var_v1_3 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].coin;
            temp_a1 = mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].gameCoin;
            temp_a1 += var_v1_3 + mp3_GwPlayer[D_8010B048_4EC468_mgresultboard[i].idx].bonusCoin;
            temp_a2 = temp_a1;
            
            if (temp_a1 < 0x3E8){
                mp3_GwPlayer[new_var].coin = temp_a2;
            } else {
                mp3_GwPlayer[new_var].coin = 0x3E7;
            }
            mp3_GwPlayer[new_var].gameCoin = 0;
            mp3_GwPlayer[new_var].bonusCoin = 0;
        }
        
        var_s4 += 1;
        func_80107234_4E8654_mgresultboard();
        break;
    case 12:
        D_8010AD94_4EC1B4_mgresultboard = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            var_a0 = 0;
            if (D_8010B048_4EC468_mgresultboard[i].unk_01 != D_8010B018_4EC438_mgresultboard[i].unk_01) {
                D_8010AD94_4EC1B4_mgresultboard++;
                var_a0 = 1;
            }

            if (D_8010B048_4EC468_mgresultboard[i].idx != D_8010B018_4EC438_mgresultboard[i].idx) {
                D_8010AD94_4EC1B4_mgresultboard++;
                var_a0++;
            }

            if (D_8010B018_4EC438_mgresultboard[i].bonusCoin >= 10) {
                D_8010AD94_4EC1B4_mgresultboard++;
                var_a0++;
            }

            if (var_a0 > 0) {
                new_var = D_8010B048_4EC468_mgresultboard[i].idx; //??? why does this help so much
                if (mp3_GwPlayer[new_var].stat & 1) {
                    continue;
                } else {
                    mp3_omVibrate(new_var, 5, 0, 5);
                }
            }
        }

        if (D_8010AD94_4EC1B4_mgresultboard == 0) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 = 0xF;
        } else {
            D_8010AD94_4EC1B4_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 13:
        var_s3 = 0;
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            var_a1 = D_8010B048_4EC468_mgresultboard[i].unk_01 != D_8010B018_4EC438_mgresultboard[i].unk_01;
            if (D_8010B048_4EC468_mgresultboard[i].idx != D_8010B018_4EC438_mgresultboard[i].idx) {
                var_a1 = 1;
            }
            if (D_8010B018_4EC438_mgresultboard[i].bonusCoin >= 10) {
                var_a1 = 1;
            }
            if (var_a1 == 1) {
                var_s3 = func_80106A80_4E7EA0_mgresultboard(i);
                func_80107800_4E8C20_mgresultboard(i);
                var_s5 += 1;
            } else {
                func_80107650_4E8A70_mgresultboard(i);
            }        
        }
 
        if (var_s3 == 1) {
            D_8010AD94_4EC1B4_mgresultboard += 1;
        }
        if (D_8010AD94_4EC1B4_mgresultboard >= 2) {
            D_8010AD94_4EC1B4_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 14:
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            var_a1 = D_8010B048_4EC468_mgresultboard[i].unk_01 != D_8010B018_4EC438_mgresultboard[i].unk_01;
            if (D_8010B048_4EC468_mgresultboard[i].idx != D_8010B018_4EC438_mgresultboard[i].idx) {
                var_a1 = 1;
            }
            if (D_8010B018_4EC438_mgresultboard[i].bonusCoin >= 10) {
                var_a1 = 1;
            }
            if (var_a1 == 1) {
                var_s3 = func_80106C80_4E80A0_mgresultboard(i);
                func_80107800_4E8C20_mgresultboard(i);
                var_s5++;
            }
        }

        if (var_s3 == 1) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 15:
        D_8010AD90_4EC1B0_mgresultboard++;
        if (D_8010AD90_4EC1B0_mgresultboard >= 0x1E) {
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                func_80107800_4E8C20_mgresultboard(i);
            }
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break;
    case 16:
        D_8010AD90_4EC1B0_mgresultboard++;
        if (D_8010AD90_4EC1B0_mgresultboard >= 0x28) {
            D_8010AD90_4EC1B0_mgresultboard = 0;
            var_s4 += 1;
        }
        break; //TODO: fallthrough?
    case 17:
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            mp3_AdjustPlayerCoins(i, 0);
        }
        mp3_WipeCreateOut(0, 0x14);
        mp3_HuAudSeqFadeOut(0x1E);
        var_s4 += 1;
        break;
    case 18:
        if (mp3_WipeStatGet() == 0) {
            func_80037258_37E58();
            func_800E69D8_FA5F8_shared_board();
            func_800E66E0_FA300_shared_board();
            mp3_omOvlReturnEx(1);
        }
        break;
    }
    
    if (var_s5 > 0) {
        func_801079B0_4E8DD0_mgresultboard(var_s5);
    } else {
        func_80107A58_4E8E78_mgresultboard();
    }
    
    D_8010AAF0_4EBF10_mgresultboard = var_s4;
    var_a0_3 = 0;
    var_a1_3 = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(mp3_GwPlayer[i].stat & 1)) {
            var_a0_3 |= D_800CDA7C_CE67C[mp3_GwPlayer[i].pad];
        } else {
            var_a1_3++;
        }
    }
    
    D_8010AAF4_4EBF14_mgresultboard = ((var_a0_3 & 0x8000) || (var_a1_3 >= 4)) ? 4.0f : 1.0f;
}