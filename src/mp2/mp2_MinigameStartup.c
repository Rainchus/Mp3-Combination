#include "mp2.h"

typedef struct ItemSlotEntry {
/* 0x00 */ s16 obj;
/* 0x02 */ s16 x;
/* 0x04 */ s16 y;
/* 0x06 */ s16 w;
/* 0x08 */ s16 h;
} ItemSlotEntry; //sizeof 0xA

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
    ItemRect *rects[6];
} ItemRectTable; //sizeof 0x18

typedef struct DefinitelyNotItemRectTable {
    DefinitelyNotItemRect *notRects[6];
} DefinitelyNotItemRectTable; //sizeof 0x18

typedef struct mp2_Sp18Struct {
    ItemRectTable rectTable;
    DefinitelyNotItemRectTable notRectTable1;
} mp2_Sp18Struct;

typedef struct {
    u8 unk0[8];
    s8 recentMinigames[6][5]; /* recent minigames per player, up to 2 */
} UnkData_E0290;

extern ItemRectTable D_800D26E8_D32E8;
extern DefinitelyNotItemRectTable D_800D2700_D3300;
extern s8 D_800DF6C5_E02C5;
extern u8 D_800CBD10_CC910[];
extern ItemSlotEntry D_800DF660_E0260[];
extern u8 D_800DF6C0_E02C0[];
extern u8 D_800CBD18_CC918[];
extern UnkData_E0290 D_800DF690_E0290;
extern u8 D_800CBDC8_CC9C8[];
extern u8 D_800CBD77_CC977[];
extern mp2_omObjData* D_800DF6BC_E02BC;
s32 func_80060A1C_6161C(void);
s32 func_800888A8_894A8(s16, s16, s16, s16, s16, s16);
void func_80089A7C_8A67C(s16, s16);
void func_8008D88C_8E48C(s32);
s16 func_80068040_68C40(s16);
void func_800898F0_8A4F0(s16, s16, s16);
void func_80089B2C_8A72C(s16, s32);
void func_8008AD84_8B984(void);
s32 mp2_MBRand(f32);
void func_800890CC_89CCC(s16, char*, s32, s32);
void func_80089C78_8A878(s16, s32);
void func_80089A48_8A648(s16, s32);
void func_8004AB24_4B724(void);


typedef struct Unk800CC3DC {
    s8 unk_00[4];
} Unk800CC3DC;

extern Unk800CC3DC D_800DF6B6_E02B6;
extern u16 D_800DF664_E0264;
extern s16 D_800DF6C6_E02C6;
extern u8 D_800CBD60_CC960[];
extern u8 D_800CBD10_CC910[];
extern s8 D_800DF6C5_E02C5;
void func_8008D530_8E130(s16, s32, s32, s32);
void func_800896DC_8A2DC(s16, s16, s16);
void mp2_SprPosSet(s16 group, s16 member, s16 arg2, s16 arg3);
void func_8007959C_7A19C(s16);
void func_80089DA0_8A9A0(s16, s32, s32, s32);
void func_80089A48_8A648(s16, s32);
void func_80067E6C_68A6C(s8 arg0);
void func_8004FDE0_509E0(void);
void func_8004A9EC_4B5EC(void);
void func_80049FB0_4ABB0(void);
void func_8008AD44_8B944(s16);
s32 func_8005A358_5AF58(s16);
void func_8004AC60_4B860(void);
u8 rand8_Shared(void);

extern s16 D_800DF6CA_E02CA;
extern s16 D_80102C0E_11682E_shared_board;
extern s8 D_800CBD70_CC970[][2];
extern u8 D_800CBD68_CC968[];
extern u8 newCategoryAmountsNormalMp2[];
extern u8* mp2_minigameLists[];

s32 mp2_func_8003F6F0_402F0(s16 overlayID) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    s32 explanationOverlayID;

    if (localOverlayID < 30) {
        explanationOverlayID = 0x5F;
    } else {
        explanationOverlayID = 0x60;
    }
    return explanationOverlayID;
}

void SetMp2MultigameMinigameString(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = (s32)arg1;

    s32 i;
    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            func_800890CC_89CCC(arg0, minigameLUT[i].minigameStr, arg2, arg3);
            return;
        }
    }
    func_800890CC_89CCC(arg0, (char*)((D_800DF6C0_E02C0[i] + 0x3D8)), arg2, arg3);
}

void newfunc_80049FFC_4ABFC(mp2_omObjData* arg0) {
    ItemSlotEntry* entry = NULL;
    s32 i;
    s16 new_var;
    
    switch (arg0->work[0]) {
    case 3:
        break;
    case 0:
        arg0->trans.y += 16.0f;
        for (i = 0; i < D_800CBD10_CC910[D_800DF6C5_E02C5]; i++) {
            entry = &D_800DF660_E0260[i];
            func_800896DC_8A2DC(entry->obj, (entry->x + (entry->w / 2)), ((s32) -arg0->trans.y + entry->y + (entry->h / 2)));
        }
        
        new_var = (s32) -arg0->trans.y + D_800DF664_E0264;
        mp2_SprPosSet(D_800DF6C6_E02C6, 0, 0xA0, (D_800CBD60_CC960[D_800DF6C5_E02C5] + new_var));
        if (arg0->trans.y > 218.0f) {
            func_80049FB0_4ABB0();
            arg0->work[0] = 1;
            arg0->scale.x = 1.0f;
            arg0->scale.z = -1.0f;
            arg0->scale.y = 0.0f;
            arg0->work[1] = 0;
            arg0->work[2] = mp2_MBRand(D_800CBD10_CC910[D_800DF6C5_E02C5]);
            arg0->work[3] = 0;
            func_8004AC60_4B860();
        }
        break;
    case 1:
        arg0->scale.z = arg0->scale.z + arg0->scale.x;
        
        if (arg0->scale.z >= 1.0f) {
            if ((arg0->work[3] != 0) && (arg0->scale.x <= 0.08f)) {
                arg0->work[3] = arg0->work[3] - 1;
            }
            arg0->scale.z -= 1.0f;
            if (arg0->scale.y == 0.0f) {
                arg0->work[1] = arg0->work[1] + 1;
                arg0->work[1] = arg0->work[1] % (u8) D_800CBD10_CC910[D_800DF6C5_E02C5];
            } else {
                arg0->work[1] = arg0->work[1] - 1;
                if (arg0->work[1] >= 0x80U) {
                    arg0->work[1] = D_800CBD10_CC910[D_800DF6C5_E02C5] - 1;
                }
            }
            func_80049FB0_4ABB0();
        }
        
        for (i = 0; i < D_800CBD10_CC910[D_800DF6C5_E02C5]; i++) {
            entry = &D_800DF660_E0260[i];
            if (i == arg0->work[1]) {
                func_8008D530_8E130(entry->obj, 0, 0xC8, 0);
                func_80089B2C_8A72C(entry->obj, 0x100);
                func_80089A7C_8A67C(entry->obj, 0x2328);
            } else {
                func_8008D530_8E130(entry->obj, 0x40, 0x40, 0x80);
                func_80089B2C_8A72C(entry->obj, 0);
                func_80089A7C_8A67C(entry->obj, 0x2710);
            }
        }
        
        if ((arg0->work[1] == arg0->work[2]) || (arg0->scale.x < 1.0f)) {
            arg0->scale.x = (f32) ((f64) arg0->scale.x - 0.02);
        }
        
        if (arg0->scale.x <= 0.08f) {
            arg0->scale.x = 0.08f;
            if ((arg0->work[1] == arg0->work[2]) && (arg0->work[3] == 0) && ((arg0->scale.z + 0.08f) >= 1.0f)) {
                if ((rand8_Shared() & 0xF) || (arg0->scale.y == 1.0f) || (arg0->work[1] == 0)) {
                    if ((mp2_GwSystem.minigameExplanations == 0) || (mp2_GwSystem.current_board_index == 8)) {
                        func_8007959C_7A19C(0x325);
                    } else {
                        func_8007959C_7A19C(0x374);
                    }
                    
                    arg0->work[0] = 2;
                    arg0->work[3] = 0x3C;
                    func_8008AD84_8B984();
                    func_8008AD44_8B944(D_800DF660_E0260[arg0->work[1]].obj);
                    SetMp2MultigameMinigameString(D_800DF660_E0260[arg0->work[1]].obj, D_800DF6C0_E02C0[arg0->work[1]], -2, 4);
                    //func_800890CC_89CCC(D_800DF660_E0260[arg0->work[1]].obj, (char*)((D_800DF6C0_E02C0[arg0->work[1]] + 0x3D8)), -2, 4);
                    switch (D_800DF6C0_E02C0[arg0->work[1]]) {
                    case 0x19:                         /* switch 2 */
                    case 0x24:                        /* switch 2 */
                    case 0x38:                        /* switch 2 */
                    case 0x47:                        /* switch 2 */
                    case 0x48:                        /* switch 2 */
                        func_80089C78_8A878(D_800DF660_E0260[arg0->work[1]].obj, 4);
                        break;
                    default:                        /* switch 2 */
                        func_80089C78_8A878(D_800DF660_E0260[arg0->work[1]].obj, 1);
                        break;
                    }
                    func_80089DA0_8A9A0(D_800DF660_E0260[arg0->work[1]].obj, 0xA0, 0xA0, 0xA0);
                    func_8008D530_8E130(D_800DF660_E0260[arg0->work[1]].obj, 0xFE, 0xFF, 0xD0);
                    func_80089A48_8A648(D_800DF660_E0260[arg0->work[1]].obj, 0);
                } else {
                    arg0->scale.y = 1.0f;
                    arg0->work[2]--;
                    if (arg0->work[2] >= 0x80U) {
                        arg0->work[2] = D_800CBD10_CC910[D_800DF6C5_E02C5] - 1;
                    }
                }
            }
        }
        break;
    case 2:
        if (arg0->work[3] != 0) {
            arg0->work[3]--;
        } else {
            D_800DF690_E0290.recentMinigames[D_800DF6C5_E02C5][D_800DF6B6_E02B6.unk_00[D_800DF6C5_E02C5]] = D_800DF6C0_E02C0[arg0->work[2]];
            D_800DF6B6_E02B6.unk_00[D_800DF6C5_E02C5]++;
            
            D_800DF6B6_E02B6.unk_00[D_800DF6C5_E02C5] = (D_800DF6B6_E02B6.unk_00[D_800DF6C5_E02C5] % (s32) D_800CBD18_CC918[D_800DF6C5_E02C5]);
            func_80067E6C_68A6C(D_800DF6C0_E02C0[arg0->work[2]]);
            if (mp2_GwSystem.current_board_index != 8) {
                func_8004FDE0_509E0();
                func_8004A9EC_4B5EC();
            }
        }
        arg0->rot.z += 1.0f;
        if (arg0->rot.z >= 13.0f) {
            arg0->rot.z -= 13.0f;
        }
        break;
    }
    if (D_800DF6CA_E02CA != -1) {
        for (i = 0; !(arg0->rot.z < (f32) *D_800CBD70_CC970[i]); i++) {}
        
        mp2_SprPosSet(D_800DF6CA_E02CA, 0,
            (D_800CBD70_CC970[i][1] + 50),
            (D_800CBD68_CC968[D_800DF6C5_E02C5] + (arg0->work[1] * 0x14)));
    }
}

//matches mp3's func_800DFBA8_F37C8_shared_board
void newfunc_8004AD34_4B934(s32 arg0) {
    ItemSlotEntry* entry;
    mp2_omObjData* obj;
    s32 category;
    s32 i;
    s32 j;
    s32 k;

    // sp18.rectTable = D_800D26E8_D32E8;
    // sp18.notRectTable1 = D_800D2700_D3300;
    
    category = 3;
    switch (arg0) {
        case -1:
            category = func_80060A1C_6161C();
            if (category == -1) {
                category = 3;
            }
            break;
        case 0:
        default:
            category = 3;
            break;
        case 1:
            category = 4;
            break;
        case 2:
            category = 5;
            break;
    }

    D_800DF6C5_E02C5 = category;

    for (i = 0; i < D_800CBD10_CC910[category]; i++) {
        entry = &D_800DF660_E0260[i];

        entry->x = D_800D26E8_D32E8.rects[category]->x;
        entry->y = D_800D26E8_D32E8.rects[category]->y + (i * 20);
        entry->w = D_800D26E8_D32E8.rects[category]->w;
        entry->h = D_800D26E8_D32E8.rects[category]->h;

        entry->obj = func_800888A8_894A8(
            (entry->x + (entry->w / 2)),
            (entry->y + (entry->h / 2)),
            entry->w,
            entry->h,
            0, 4);
        func_80089A7C_8A67C(entry->obj, 0x2328);
        func_8008D88C_8E48C(entry->obj);
        func_800898F0_8A4F0(entry->obj, entry->w / 2, entry->h / 2);
        func_80089B2C_8A72C(entry->obj, 0);

        while (1) {
            //D_800DF6C0_E02C0[i] = D_800D26E8_D32E8.rects[mp2_MBRand(D_800CBDC8_CC9C8[category])];
            D_800DF6C0_E02C0[i] = mp2_minigameLists[category][mp2_MBRand(newCategoryAmountsNormalMp2[category])];
    
            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (D_800DF6C0_E02C0[j] == D_800DF6C0_E02C0[i]) {
                    break;
                }
            }
            
            if (j != i) {
                continue;
            }

            for (k = 0; k < D_800CBD18_CC918[category]; k++) {
                if (D_800DF6C0_E02C0[i] == D_800DF690_E0290.recentMinigames[category][k]) { 
                    break;
                }
            }
    
            if (k != D_800CBD18_CC918[category]) {
                continue;
            }

            switch (mp2_GwSystem.current_game_length) {
            case 0:
                if (mp2_GwSystem.current_turn >= 6) {
                    break;
                }
            case 1:
                if (mp2_GwSystem.current_turn > 20) {
                    break;
                }
            case 2:
                if (mp2_GwSystem.current_turn > 35) {
                    break;
                }

                switch (D_800DF6C0_E02C0[i]) {
                case 0x19:
                case 0x24:
                case 0x38:
                case 0x47:
                case 0x48:
                    continue;
                default:
                    break;
                }
                break;
            }
            if (D_800DF6C0_E02C0[i] == 0x10) {
                //?
            } else if (D_800DF6C0_E02C0[i] != 0x23) {
                break;
            }
            if (func_80068040_68C40(D_800DF6C0_E02C0[i] - 1)) {
                break;
            }
        }
        
        func_8008AD84_8B984();
        SetMp2MultigameMinigameString(entry->obj, D_800DF6C0_E02C0[i], -2, 4);
        //func_800890CC_89CCC(entry->obj, D_800DF6C0_E02C0[i] + 0x3D8, -2, 4);
        func_80089C78_8A878(entry->obj, D_800CBD77_CC977[D_800DF6C0_E02C0[i]]);
        func_80089A48_8A648(entry->obj, 0);
    }

    obj = mp2_omAddObj(-0x8000, 0U, 0U, -1, newfunc_80049FFC_4ABFC);
    D_800DF6BC_E02BC = obj;
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    func_8004AB24_4B724();
}