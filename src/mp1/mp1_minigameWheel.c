#include "mp1.h"

// Struct definitions needed (MP1 equivalents)
typedef struct mp1_ItemRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} mp1_ItemRect; // 0x8 bytes

typedef struct mp1_ItemRectTable {
    mp1_ItemRect *rects[4];  // 0x00–0x0F
} mp1_ItemRectTable;

typedef struct mp1_RecentMinigameTable {
    s8 recentMinigames[4][5]; // 4 categories, 5 recent entries (vs MP3's 6x10)
} mp1_RecentMinigameTable;

typedef struct mp1_ItemSlotEntry {
/* 0x00 */ s16 obj;
/* 0x02 */ s16 x;
/* 0x04 */ s16 y;
/* 0x06 */ s16 w;
/* 0x08 */ s16 h;
} mp1_ItemSlotEntry; // sizeof 0xA

extern mp1_ItemRectTable mp1_D_800CAD28; // sp18..sp24: rectTable (normal mode rects)
//extern ItemRectTable newMp1MinigameLists; // sp28..sp34: rectTable (hard mode rects)
extern mp1_ItemSlotEntry  mp1_D_800D6400[]; // item slot entries array
extern u8 mp1_D_800D6454[]; // selected minigame indices per slot
//extern mp1_RecentMinigameTable mp1_D_800D6438; // recent minigames table (4 categories * 5 entries)
extern s8 mp1_D_800D6459; // current category
extern mp1_omObjData* mp1_D_800D6450; // manager object
extern u8 mp1_D_800C4D3C[]; // slot count per category
//extern u8 mp1_minigameCategoryCounts[]; // minigame pool size per category (hard mode)
extern u8 mp1_D_800C4DCF[]; // minigame rotation/player count table
extern u32 mp1_D_800ECE10; // current player index
extern u8 mp1_D_800F32B8[]; // player minigame completion data

extern s16 mp1_func_8006D010(s16, s16, s16, s16, s32, s32);
extern void mp1_func_8006E0A4(s16, s32);
extern void mp1_func_800717C0(s32);
void mp1_func_8006DEC8(s16, s32, s32);
void mp1_func_8006E154(s16, s16);
void mp1_func_8006EB80(void);
void mp1_func_8006E288(s16, u8);
void mp1_func_8006E070(s16, s32);
void mp1_func_8004367C(void);
s32 mp1_func_80054FE4(void);            // equivalent to func_800F52C4 in MP3: get minigame category
u8 rand8_Shared(void);            // equivalent to MBRand
void mp1_LoadStringIntoWindow(s16 win_id, void* string_id, s16 a, s16 b);

void mp1_func_80042BAC(mp1_omObjData*); // manager object callback

// .word new4PMinigameListNormalMp1
// .word new1v3MinigameListNormalMp1
// .word new2v2MinigameListNormalMp1
// .word new1PMinigameListNormalMp1

extern u8* newMp1MinigameLists[4];
extern u8 newCategoryAmountsNormalMp1[];
extern u8 minigameTextColor[];

void SetMp1MultigameMinigameString(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = arg1;

    s32 i;
    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            mp1_LoadStringIntoWindow(arg0, minigameLUT[i].minigameStr, arg2, arg3);
            return;
        }
    }
    mp1_LoadStringIntoWindow(arg0, (void*)(mp1_D_800D6454[i] + 0x324), arg2, arg3);
}

void func_8004388C(s32 arg0) {
    mp1_ItemSlotEntry* entry;
    mp1_omObjData* obj;
    s32 category;
    s32 i;
    s32 j;
    s32 k;

    //sp18 = D_800CAD28; //text positions?
    //sp28 = D_800CAD38; //category ids

    category = 3;
    if (arg0 == -1) {
        category = mp1_func_80054FE4();
        if (category == arg0) {
            category = 3;
        }
    }

    mp1_D_800D6459 = category;

    for (i = 0; i < mp1_D_800C4D3C[category]; i++) {
        u8* minigameList = newMp1MinigameLists[category];

        entry = &mp1_D_800D6400[i];
        entry->x = mp1_D_800CAD28.rects[category][i].x;
        entry->y = mp1_D_800CAD28.rects[category][i].y;
        entry->w = mp1_D_800CAD28.rects[category][i].w;
        entry->h = mp1_D_800CAD28.rects[category][i].h;

        entry->obj = mp1_func_8006D010(
            entry->x + (entry->w / 2),
            entry->y + (entry->h / 2),
            entry->w,
            entry->h,
            0, 0);
        mp1_func_8006E0A4(entry->obj, 0x2328);
        mp1_func_800717C0(entry->obj);
        mp1_func_8006DEC8(entry->obj, entry->w / 2, entry->h / 2);
        mp1_func_8006E154(entry->obj, 0);

        while (1) {
            mp1_D_800D6454[i] = minigameList[rand8_Shared() % newCategoryAmountsNormalMp1[category]];

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (mp1_D_800D6454[j] == mp1_D_800D6454[i]) {
                    break;
                }
            }
            if (j != i) {
                continue;
            }

            for (k = 0; k < mp1_D_800C4D3C[category]; k++) {
                if (mp1_D_800D6454[i] == mp1_D_800D6438.recentMinigames[category][k]) { 
                    break;
                }
            }

            if (k != mp1_D_800C4D3C[category]) {
                continue;
            }

            // if ((category == 3) || (category == 0)) {
            //     for (k = 0; k < 5; k++) {
            //         if (mp1_D_800D6454[i] == mp1_D_800D6438.recentMinigames[category][k]) {
            //             break;
            //         }
            //     }
            //     if (k != 5) {
            //         continue;
            //     }
            // } else {
            //     if (mp1_D_800D6454[i] == mp1_D_800D6438.recentMinigames[category][0]) { //?
            //         continue;
            //     }
            // }

            switch (mp1_D_800D6454[i]) {
                case YOSHIS_TONGUE_MEETING:
                case MP1_BOBSLED_RUN:
                case MP1_HANDCAR_HAVOC:
                case MP1_HANDCAR_HAVOC + 2: //TODO: what? +2 over MP1_HANDCAR_HAVOC ? that doesn't exist in the list
                    for (k = 0; k < 4; k++) {
                        if (mp1_GwPlayer[k].coin < 15) {
                            break;
                        }
                    }
                    if (k != 4) {
                        continue;
                    }
                    break;
                case MP1_BOWL_OVER:
                case KNOCK_BLOCK_TOWER:
                case PADDLE_BATTLE:
                    if (mp1_GwPlayer[mp1_GwSystem.curPlayerIndex].coin < 15) {
                        continue;
                    }
                    break;
                case 52:
                    for (k = 0; k < 4; k++) {
                        if (k == mp1_GwSystem.curPlayerIndex) {
                            if (mp1_GwPlayer[k].coin < 15) {
                                break;
                            }
                        } else {
                            if (mp1_GwPlayer[k].coin < 5) {
                                break;
                            }
                        }
                    }
                    if (k != 4) {
                        continue;
                    }
                    break;
            }
            break;
        }

        mp1_func_8006EB80();
        SetMp1MultigameMinigameString(entry->obj, mp1_D_800D6454[i], -2, 4);
        //mp1_LoadStringIntoWindow(entry->obj, (void*)(mp1_D_800D6454[i] + 0x324), -2, 4);
        mp1_func_8006E288(entry->obj, minigameTextColor[mp1_D_800D6454[i]]);
        mp1_func_8006E070(entry->obj, 0);
    }

    obj = mp1_omAddObj(-0x8000, 0, 0, -1, &mp1_func_80042BAC);
    mp1_D_800D6450 = obj;
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    mp1_func_8004367C();
}