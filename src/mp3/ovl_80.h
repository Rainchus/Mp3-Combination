#include "marioparty.h"
#include "mp3/game/object.h"
#include "mp3/malloc.h"

typedef struct BoardStatus {
    /* 0x00 */ s8 uiUpdatePaused;
    /* 0x01 */ s8 unk1;
    /* 0x02 */ u8 unk2[2];
    /* 0x04 */ u8 spaceType;
    /* 0x04 */ u8 uiVisible;
    /* 0x06 */ s8 prevStars;
    /* 0x07 */ s8 prevRank;
    /* 0x08 */ s16 prevCoins;
    /* 0x0A */ s16 playerIndex;
    /* 0x0C */ char unk_0C[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ f32 xPos;
    /* 0x14 */ f32 yPos;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ char pad34[2];
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ char unk_38[2];
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ char unk_3C[4];
    /* 0x40 */ s16 unk_40[3];
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ char pad48[0x1E];
    /* 0x66 */ s16 counts[3]; //star count, coin count?
} BoardStatus; //sizeof 0x6C

typedef struct UnkBoard {
/* 0x00 */ s16 unk_00;
/* 0x02 */ s16 unk_02;
/* 0x04 */ s32 unk_04;
/* 0x08 */ mp3_omObjData* unk_08;
} UnkBoard; //sizeof 0x0C

typedef struct UnkBoard2 {
/* 0x00 */ s16 unk_00;
/* 0x04 */ Object* obj;
} UnkBoard2;

typedef struct UnkCoinThing {
/* 0x00 */ u8 digits[3];
/* 0x03 */ char unk_03[5];
/* 0x08 */ s16 unk_08[2];
} UnkCoinThing;

void func_800DA790_EE3B0_shared_board(s32, u16, char*, s32, s32);
Object* func_800D90C8_ECCE8_shared_board(u8, s32);
void func_800D9714_ED334_shared_board(Object*);
void func_800F3400_107020_shared_board(mp3_omObjData*);
void func_800F4190_107DB0_shared_board(void);
void func_800F43FC_10801C_shared_board(s32);
void func_800F4798_1083B8_shared_board(u32, s32);
void func_800F4874_108494_shared_board(s32, s16, s16);
s32 func_800EECB0_1028D0_shared_board(s32);
s32 func_800D9E0C_EDA2C_shared_board(s32);
void func_800D9D84_ED9A4_shared_board(s32, s16, s32, s32, u16);
void func_800EE7AC_1023CC_shared_board(mp3_omObjData* func);
s32 BoardPlayerRankCalc(s32 player);
void newUpdatePlayerBoardStatus(s32, s32);
void func_800F6A88_10A6A8_shared_board(s16, u16);
void func_800F6AD0_10A6F0_shared_board(s32, f32, f32);
void func_800F6E4C_10AA6C_shared_board(s32, s32, s32*, s32*);
void func_800F6748_10A368_shared_board(s16, s16, f32*, f32*);
void func_800F64E4_10A104_shared_board(s32, s32);
void func_800F3A80_1076A0_shared_board(s32);
void func_800F3BD0_1077F0_shared_board(s32);
void func_800F3E34_107A54_shared_board(s32);
void func_800F3FF4_107C14_shared_board(s32);
void func_800F5F98_109BB8_shared_board(s32, s32);
void func_800F6AA4_10A6C4_shared_board(s16 arg0, s16 arg1);
void func_800F4994_1085B4_shared_board(s32);
void func_800F4348_107F68_shared_board(void);
void func_800F462C_10824C_shared_board(s32);
void func_800F5644_109264_shared_board(void);
void func_800F5BF4_109814_shared_board(s32, s32, s32);
void func_800F3D70_107990_shared_board(s32);
void func_800F3F0C_107B2C_shared_board(s32);
void SprAttrSet(s16, s16, u16);
void SprAttrReset(s16, s16, u16);
void func_80055140_55D40(s32, s16, u16, s32);
void func_800550F4_55CF4(s16, s16, s32);
void func_800550B4_55CB4(s32, s16, f32);
void func_80055024_55C24(s16, s16, s16, s32);
void SprPriSet(s16, s16, u16);
void func_80054904_55504(s16, s16, s16, s16);
void UpdatePlayerBoardStatus(s32);
void SprScale(s16, s16, f32, f32);
void func_800552DC_55EDC(s16, s16, f32);
void func_80055458_56058(s16, s16, u16);
void func_80055420_56020(s16, s32, u8, u8, s32);
void func_800E1934_F5554_shared_board(s32, s32);
void func_800F59B4_1095D4_shared_board(mp3_omObjData* arg0);

extern s8 D_80102C48_116868_shared_board;
extern s16 D_80101908_115528_shared_board[];
extern s16 D_8010559A_1191BA_shared_board;
extern s16 D_80105592_1191B2_shared_board[];
extern s32 D_80101788_1153A8_shared_board;
extern s32 D_8010178C_1153AC_shared_board;
extern char D_800D5218_D5E18[];
extern s16 gCoinBlockSpaceIndex;
extern s16 gStarBlockSpaceIndex;
extern s16 mp3_D_80105588_1191A8_shared_board[];
extern RGB D_8010188C_1154AC_shared_board[];
extern s8 D_800D20B1_D2CB1;
extern s32 D_80101780_1153A0_shared_board;
extern s16 D_8010559C_1191BC_shared_board[];
extern s16 D_801018E4_115504_shared_board[12][2]; //is this actually [12][2]?
extern s32 D_80101790_1153B0_shared_board;
extern f32 D_801055C8_1191E8_shared_board;
extern s16 D_801055E4_119204_shared_board;
extern Vec2f D_801055CC_1191EC_shared_board;
extern Vec2f D_801055DC_1191FC_shared_board;
extern Vec2f D_801055D4_1191F4_shared_board;
extern s16 PlayerBoardStatusRootPosition[8][2];
extern Process* D_80105580_1191A0_shared_board;
extern s16 D_801055C2_1191E2_shared_board;
extern s16 D_801055C4_1191E4_shared_board;
extern s32 D_80101784_1153A4_shared_board;
extern BoardStatus D_801057E0_119400_shared_board[];
extern UnkBoard D_80105718_119338_shared_board[16];
extern mp3_omObjData* D_801055E8_119208_shared_board[];
extern s32 D_80101F30_115B50_shared_board[3];
extern s32 mp3_D_80101944_115564_shared_board[]; //mainFS ids for character images
extern s32 mp3_D_801019D0_1155F0_shared_board[];
