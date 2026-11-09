// #include "mp3.h"
// #include "mp3/boards/FA250.h"

// typedef struct UnkFAF78 {
//     /* 0x00 */ s32 unk_00;   /* count */
//     /* 0x04 */ s32 *unk_04;  /* id list */
//     /* 0x08 */ char pad08[4];
// } UnkFAF78; /* size = 0xC */

// extern u16 D_80102DC0_shared_board;
// extern OverlayBgEntry *D_801030A8_shared_board[6][6];
// extern OverlayBgEntry D_80102DD8_shared_board[36];
// extern OverlayBgEntry D_80103140_shared_board[];
// extern OSMesgQueue D_80103468_shared_board;
// extern u16 D_80105212_shared_board;
// extern u8 D_8010124C_shared_board;
// extern s32 D_801012C8_shared_board[];
// extern s32 D_80101318_shared_board[];
// extern s32* D_80101240_shared_board;
// extern u32 D_80102DB0_shared_board;
// extern s32 D_80102DB4_shared_board;
// extern u32* D_80101244_shared_board;
// extern u16 D_80102DC0_shared_board;
// extern f32 D_8010341C_shared_board;
// extern Vec2f D_801049F0_shared_board;
// extern f32 D_80101250_shared_board;
// extern f32 D_801049F8_shared_board[];
// extern OSMesgQueue D_80103468_shared_board;
// extern void* D_80103480_shared_board;
// extern OSThread D_80103510_shared_board;
// extern OSThread D_80103EC0_shared_board;
// extern s32 D_80104070_shared_board;
// extern void* D_80104898_shared_board;
// extern void* D_80104940_shared_board;
// extern void* D_801049E8_shared_board;
// extern OSThread D_80103EC0_shared_board;
// extern s32 D_80104070_shared_board;
// extern s16 D_80102DC2_shared_board;
// extern s16 D_80102DC4_shared_board;
// extern s16 D_80102DC6_shared_board;
// extern s16 D_80102DC8_shared_board;
// extern f32 D_80101250_shared_board;
// extern mp3_Process* D_80103414_shared_board;
// extern mp3_Process* D_80103410_shared_board;
// extern f32 D_80103418_shared_board;
// extern Vec D_80103420_shared_board;
// extern Vec D_8010342C_shared_board;
// extern Vec D_80103438_shared_board;
// extern Vec D_80103444_shared_board;
// extern Vec D_8010125C_shared_board;
// extern s32 D_80101268_shared_board;
// extern u8 D_8010126C_shared_board;
// extern Gfx D_80101270_shared_board[];
// extern s32 D_801012BC_shared_board;
// extern mp3_Process* D_801012B8_shared_board;
// extern f32 D_80102DBC_shared_board;
// extern void* D_801012C0_shared_board;
// extern s32 D_80105500_shared_board[];
// extern s16 D_80105540_shared_board[];
// extern s16 D_801054F8_shared_board;
// extern u8 D_80101468_shared_board[];
// extern s16 D_801054B6_shared_board;
// extern s16 D_801054B8_shared_board[];
// extern s16 D_801052B8_shared_board[];
// extern void* D_80105278_shared_board;
// extern void* D_8010527C_shared_board;
// extern void* D_80105280_shared_board;
// extern void* D_80105284_shared_board;
// extern s32 D_80105288_shared_board;
// extern s32 D_80105990_shared_board;
// extern s32* D_80101240_shared_board; //TODO: fix type
// extern Vec D_80103450_shared_board;
// extern f32 D_80101254_shared_board;
// extern f32 D_80101258_shared_board;
// extern s32 D_8010345C_shared_board;
// extern u16 D_8010345E_shared_board;
// extern s32 D_80103460_shared_board;
// extern UnkFAF78 *D_80103464_shared_board;
// extern u8* D_80102DCC_shared_board;
// extern HvqFileHeader* D_80103138_shared_board;
// extern OSMesgQueue D_80104880_shared_board;
// extern OSMesgQueue D_80104928_shared_board;
// extern OSMesgQueue D_801049D0_shared_board;
// extern HvqHeader* D_80102DD0_shared_board;
// extern UnkBoard7 D_80104A00_shared_board[64];
// extern s32 D_80105200_shared_board;
// extern s16 D_80105260_shared_board;
// extern u8* D_80105220_shared_board[]; //space form images
// extern s32 D_801052B0_shared_board;
// extern f32 D_80105290_shared_board[];
// extern s16 MTXBufNum;
// extern Mtx* MTXBuf;
// extern u16 gTotalSpaces;
// extern mp3_SpaceData* D_80105214_shared_board;
// extern LinkData* D_80105218_shared_board;
// extern u8 D_80105268_shared_board[];
// void *Mp2DataRead(s32 id);

// void func_800E86CC_shared_board(Gfx** arg0, s32 arg1, u8 arg2);
// s32 func_800E7330_shared_board(u16 arg0);
// void func_800E90BC_shared_board(void);
// void func_800E9328_shared_board(void);
// void func_800E9358_shared_board(void);
// extern u16 D_80105262_shared_board;
// void MBMasuDraw(Gfx **arg0, Mtx *arg1, s32 arg2);
// f32 MBBackMdlScaleGet(void);

// /* MP2 and MP3 number their space types differently. Fill this in by comparing
//    the space type enums in both decomps. Anything >= SPACE_TYPES_TOTAL will
//    index past the per-type draw lists, so never pass an unmapped value through. */
// u16 Mp2SpaceTypeToMp3(u16 mp2Type) {
//     switch (mp2Type) {
//         /* case MP2_SPACE_BLUE: return MP3_SPACE_BLUE; ... */
//         default: return mp2Type;
//     }
// }

// s32 MBMasuCreateMp2(s32 dataId) {
//     LinkData *chain;
//     mp3_SpaceData *space;
//     u16 *src;
//     u16 *chainTbl;
//     s16 *dst;
//     s32 i, j;

//     D_801012C0_shared_board = Mp2DataRead(dataId);
//     if (D_801012C0_shared_board != NULL) {
//         D_80105278_shared_board = 0;
//         D_8010527C_shared_board = 0;
//         D_80105280_shared_board = 0;
//         D_80105284_shared_board = 0;

//         src = D_801012C0_shared_board;
//         gTotalSpaces = src[0];
//         D_80105212_shared_board = src[1];

//         D_80105214_shared_board = mp3_HuMemMemoryAllocTemp(gTotalSpaces * sizeof(mp3_SpaceData));
//         src = func_800EAE00_shared_board(D_801012C0_shared_board, 4);
//         space = D_80105214_shared_board;
//         for (i = 0; i < gTotalSpaces; i++, space++) {
//             space->unk_00     = 1;
//             space->unk_02     = *src++;
//             space->space_type = Mp2SpaceTypeToMp3(*src++);
//             space->coords.x   = ((f32 *)src)[0] * 5.0f * MBBackMdlScaleGet();
//             space->coords.y   = ((f32 *)src)[1] * 5.0f * MBBackMdlScaleGet();
//             space->coords.z   = ((f32 *)src)[2] * 5.0f * MBBackMdlScaleGet();
//             src += 6;
//             space->rot.x = space->rot.y = space->rot.z = MBBackMdlScaleGet();
//             space->event_list = NULL;
//         }

//         D_80105218_shared_board = mp3_HuMemMemoryAllocTemp(D_80105212_shared_board * 8);
//         chainTbl = func_800EAE00_shared_board(D_801012C0_shared_board, 6);
//         chain = D_80105218_shared_board;
//         for (i = 0; i < D_80105212_shared_board; i++, chain++) {
//             src = func_800EAE00_shared_board(chainTbl, i * 2);
//             chain->chainIndicies = *src++;
//             chain->spaces = mp3_HuMemMemoryAllocTemp(chain->chainIndicies * 2);
//             dst = chain->spaces;
//             for (j = 0; j < chain->chainIndicies; j++) {
//                 *dst++ = *src++;
//             }
//         }

//         Mp2DataClose(D_801012C0_shared_board);
//         func_8001F95C_main(1, &MBMasuDraw);
//         D_80105262_shared_board = 1;
//     }
//     D_801054B6_shared_board = 0;
//     D_801054F8_shared_board = 0;
//     return 0;
// }

// extern s16 D_80105664_shared_board;
// extern u32 mp2_hvq_data_ROM_START;
// extern u32 mp3_hvq_data_ROM_START;
// extern s16 D_80105666_shared_board;
// extern void (*D_80101B64_shared_board)(void);
// extern void (*D_80101B68_shared_board)(void);
// extern void (*D_80101B6C_shared_board)(void);
// void func_800F8908_shared_board(void);

// typedef struct UnkOvl81_1 {
//     s32 unk_00;
//     char unk_04[0xC];
// } UnkOvl81_1;

// s32 gMbMp2Setup = FALSE;

// void MBObjectSetupHook(s32 arg0, s16 arg1, s32 arg2, s32 unused) {
//     mp3_Process *temp_v0_2;
//     UnkOvl81_1 *temp_v0_3;
//     u8 playerIndex;
//     mp3_Object *temp_v0;
//     s32 i;
//     mp3_GW_SYSTEM *system;
//     s32 isMp2 = gMbMp2Setup;
//     gMbMp2Setup = FALSE;

//     func_800E9EF4_shared_board();
//     // func_800E6630_shared_board(&mp3_hvq_data_ROM_START);
//     if (isMp2) {
//         func_800E6630_shared_board((u32)&mp2_hvq_data_ROM_START);
//     } else {
//         func_800E6630_shared_board((u32)&mp3_hvq_data_ROM_START);
//     }

//     if (arg0 >= 0) {
//         MBBackLoad(arg0);
//     }

//     func_800EA60C_shared_board();
//     // if (arg1 >= 0) {
//     //     MBMasuCreate(0x13, (s32)arg1);
//     // }
//     if (arg1 >= 0) {
//         if (isMp2) {
//             MBMasuCreateMp2(MP2_DATA_ID(0xA, arg1));
//         } else {
//             MBMasuCreate(0x13, (s32)arg1);
//         }
//     }

//     func_800D76D0_shared_board(arg2);
//     MBModelInit();
//     func_800F26E8_shared_board();
//     MBKSuitInit();
//     func_800F25D8_shared_board(0);
//     func_800F25D8_shared_board(1);
//     func_800F25D8_shared_board(2);
//     func_800F25D8_shared_board(3);

//     for (i = 0; i < MB_MAX_PLAYERS; i++) {
//         MBModelTempAllocFree(mp3_MBGetPlayerStruct(i)->player_obj);
//         temp_v0 = mp3_MBGetPlayerStruct(i)->player_obj;
//         temp_v0->unkA |= 2;
//         MBModelDispOn(mp3_MBGetPlayerStruct(i)->player_obj);
//     }

//     system = &mp3_GwSystem;
//     playerIndex = system->current_player_index;
//     if ((playerIndex < 4) && (mp3_GwPlayer[system->current_player_index].itemTurn != 0)) {
//         MBKSuitCreate();
//         MBModelDispOff(mp3_GwPlayer[system->current_player_index].player_obj);
//     }

//     func_8001FDE8_main(mp3_MBGetPlayerStruct(0)->player_obj->omObj1->model[0]);
//     func_8001FDE8_main(mp3_MBGetPlayerStruct(1)->player_obj->omObj1->model[0]);
//     func_8001FDE8_main(mp3_MBGetPlayerStruct(2)->player_obj->omObj1->model[0]);
//     func_8001FDE8_main(mp3_MBGetPlayerStruct(3)->player_obj->omObj1->model[0]);
//     func_800F2A20_shared_board();
//     func_800DF854_shared_board();
//     MBCoinChangeInit();
//     MBTelopInit();
//     func_800F453C_shared_board();
//     func_800DB5DC_shared_board();
//     func_8005A6B0_main();
//     func_800ECAB4_shared_board();
//     D_80105664_shared_board = -1;
//     mp3_D_800D1360.unk_20 = 0;
//     D_80105666_shared_board = 0;
//     func_800F27D0_shared_board();
//     D_80101B64_shared_board = NULL;
//     D_80101B68_shared_board = NULL;
//     D_80101B6C_shared_board = NULL;
//     func_8004CF30_main();

//     for (i = 0; i < MB_MAX_PLAYERS; i++) {
//         temp_v0_2 = mp3_omAddPrcObj(func_800F8908_shared_board, 0, 0, 0x40);
//         temp_v0_3 = mp3_HuMemMemoryAlloc(temp_v0_2->heap, sizeof(UnkOvl81_1));
//         temp_v0_2->user_data = temp_v0_3;
//         temp_v0_3->unk_00 = i;
//         mp3_omPrcSetStatBit(temp_v0_2, 0xA0);
//     }
// }









// void MB1Ev_StarShuffle(void);
// void MB1Ev_StarNextPos(void);
// void MB1Ev_StarMasuInit(void);
// void MB1Ev_StarMapView(void);
// void MB1_StarGuideCreateAll(void);
// void MB1_TeresaGuideCreateAll(void);
// void MB1_BankCoinCreateAll(void);
// void func_801088B4_ChillyWaters(void);
// void func_80108B24_ChillyWaters(void);
// void func_80108BA4_ChillyWaters(void);
// void MB1Ev_BranchMerge(s32 masuAbsIndex, s16 arg1, s16 arg2);
// void func_80116AA0_ChillyWaters(void);
// void MB1Ev_TuruturuMain(void);
// void MB1Ev_SnowmanObjMain(void);
// s32 MB1Ev_SnowmanPathGet(s32);
// void MB1Ev_Teresa(void);
// void MB1Ev_ItemMajinLamp(void);
// void MB1Ev_ItemMajinLampStar(void);
// void MB1Ev_ItemWarpBlock(void);
// void MB1Ev_ItemKinoko(void);
// void MB1Ev_ItemShake(void);
// void MB1Ev_ItemPhoneMove(void);
// void MB1Ev_KSuitStart(void);
// void MB1Ev_KSuitEnd(void);
// void MB1Ev_ItemShopPhone(void);
// void MB1Ev_ItemKoopaPhone(void);
// void MB1Ev_ItemStarYoke(void);
// void MB1Ev_ItemKeyManUse(void);
// void MB1Ev_ItemNullUse(void);
// void MB1Ev_ItemExchangeBox(void);
// void MB1Ev_ItemGambleCoin(void);
// void MB1Ev_ItemAfter5(void);
// void MB1Ev_ItemKoopaNKinoko(void);
// void MB1Ev_ItemNKinoko(void);
// void MB1Ev_ItemKoopaRKinoko(void);
// void MB1Ev_ItemRKinoko(void);
// void MB1Ev_ItemRobBox(void);
// s32 MB1_ComItemDecide(void);
// void MB1_ObjectSetup(void);
// void MB1Ev_SnowmanStart(void);
// void MB1_BankCoinHide(void);
// void MB1_BankCoinCreate(s16);

// typedef struct BranchLink {
//     /* 0x00 */ s16 link;
//     /* 0x02 */ s16 idx;
//     /* 0x04 */ s16 rev;
// } BranchLink; /* size 6 */

// s16 MBComTreeExec(DecisionTreeNonLeafNode *arg0);
// void MB1_BranchHelpEnd(void);
// void MB1Ev_BranchMain(s16 (*masu)[3], BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);

// void MB1Ev_After5LineShow(mp3_omObjData*);
// void MB1Ev_After5NumFade(mp3_omObjData*);
// void MB1Ev_After5Effect(void);
// void MB1Ev_After5ItemMove(s32, s32, f32*);
// s32 func_8011CE94_ChillyWaters(void);
// s32 func_8011D1F8_ChillyWaters(void);
// s32 MB1Ev_YesNoChoiceGet(DecisionTreeNonLeafNode *arg0, s32 arg1);

// extern s32 mbWalkNum;
// extern RGB D_8011E4B8_ChillyWaters[2];
// extern s32 mb1_After5GrpId[4];
// extern void* D_8011FB90_ChillyWaters;
// extern s16 D_8011FB8E_ChillyWaters;
// extern mp3_Object *D_8011D314_ChillyWaters;
// extern mp3_Object *D_8011D318_ChillyWaters;

// extern mp3_Object* mb1_BankCoinBaseMdl;
// extern mp3_Object* mb1_BankCoinMdl[10];
// extern mp3_omObjData *D_800CE194_main;
// extern event_table_entry mb1_CommonEventTbl[]; //unknown type
// extern event_table_entry mb1_TeresaEventTbl[]; //unknown type
// extern event_table_entry mb1_TurnStatusEventTbl[]; //unknown type
// extern event_table_entry mb1_SpecialEventTbl[]; //unknown type
// extern RectF D_8011E8B8_ChillyWaters;
// extern s16 mb1ev_StarGuideMasu[8];
// extern s16 D_8011D31C_ChillyWaters; //unknown type
// extern s16 D_8011D320_ChillyWaters[]; //unknown type

// extern s16 mb1ev_StarFlag[STAR_POSITIONS_TOTAL];
// extern s16 mb1ev_StarMasu[STAR_POSITIONS_TOTAL];
// extern s16 D_8011D280_ChillyWaters[STAR_POSITIONS_TOTAL];
// extern s16 D_8011D290_ChillyWaters[STAR_POSITIONS_TOTAL];
// extern Unk3* mb1_BranchStickHelp;
// extern Unk3* mb1_BranchBtnHelp;
// extern Unk3* mb1_BranchMapScrollHelp;
// extern Unk3* mb1_BranchMapOverheadHelp;
// extern Unk3* mb1_BranchItemHelp;
// extern Object *D_8011FAEC_ChillyWaters;



// extern DecisionTreeNonLeafNode *mb1ev_Branch3RevComTree[];  // ai
// extern s16 mb1ev_Branch3RevMasu[][3];                       // spaces
// extern BranchLink mb1ev_Branch3RevLink[][2];                // chain
// extern DecisionTreeNonLeafNode *mb1ev_Branch2ComTree[];     // ai
// extern s16 mb1ev_Branch2Masu[][3];                          // spaces
// extern BranchLink mb1ev_Branch2Link[][2];                   // chain

// extern s16 D_8011DACC_ChillyWaters[][3];             // spaces
// extern BranchLink D_8011DAE0_ChillyWaters[][2];      // chain
// extern DecisionTreeNonLeafNode *D_8011D5F0_ChillyWaters[];  // ai

// extern s16 D_8011E010_ChillyWaters[][3];             // spaces
// extern BranchLink D_8011E024_ChillyWaters[][2];      // chain
// extern DecisionTreeNonLeafNode *D_8011DA58_ChillyWaters[];  // ai

// extern DecisionTreeNonLeafNode *D_8011D668_ChillyWaters[];  // ai
// extern s16 D_8011DB14_ChillyWaters[][3];                    // spaces
// extern BranchLink D_8011DB28_ChillyWaters[][2];             // links
// extern DecisionTreeNonLeafNode *D_8011D974_ChillyWaters[];
// extern s16 D_8011DDF8_ChillyWaters[][3];
// extern BranchLink D_8011DE0C_ChillyWaters[][2];

// void MB1_ObjectSetup(void) {
//     Vec sp10;
//     mp3_SpaceData *space;
//     s32 i;

//     mp3_omInitObjMan(0xA0, 0x28);
//     mp3_HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
//     mp3_HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
//     MBObjectSetup(3, 0x23A, 5, 0);
//     MBMasuBlockTblExtSet(&D_8011D31C_ChillyWaters);
//     MBMasuBlockTblSet(D_8011D320_ChillyWaters);
//     space = MBMasuGet(0x77);
//     MBVecDirGet(&space->coords, &MBMasuGet(0x73)->coords, &sp10);
//     MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
//     space = MBMasuGet(0x7C);
//     MBVecDirGet(&space->coords, &MBMasuGet(0x6E)->coords, &sp10);
//     MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
//     space = MBMasuGet(0x8F);
//     MBVecDirGet(&space->coords, &MBMasuGet(0x80)->coords, &sp10);
//     MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
//     MBItemHookSet(0, &MB1Ev_Teresa); // boo event
//     MBItemHookSet(1, &MB1Ev_ItemMajinLamp); // magic lamp
//     MBItemHookSet(9, &MB1Ev_ItemMajinLampStar);
//     MBItemHookSet(2, &MB1Ev_ItemWarpBlock); // warp block
//     MBItemHookSet(3, &MB1Ev_ItemRobBox); // plunder chest
//     MBItemHookSet(4, &MB1Ev_KSuitStart); // activate bowser suit
//     MBItemHookSet(5, &MB1Ev_KSuitEnd); // when landing on a space as bowser suit
//     MBItemHookSet(6, &MB1Ev_ItemKinoko); // mushroom/golden mushroom/bowser suit
//     MBItemHookSet(7, &MB1Ev_ItemShake); // dueling glove/boo bell (?)
//     MBItemHookSet(8, &MB1Ev_ItemPhoneMove);
//     MBItemHookSet(0xA, &MB1Ev_ItemNKinoko); // poison mushroom
//     MBItemHookSet(0xB, &MB1Ev_ItemRKinoko); // reverse mushroom
//     MBItemHookSet(0xE, &MB1Ev_ItemShopPhone);
//     MBItemHookSet(0xF, &MB1Ev_ItemKoopaPhone);  // bowser phone
//     MBItemHookSet(0x10, &MB1Ev_ItemStarYoke); // lucky lamp
//     MBItemHookSet(0x11, &MB1Ev_ItemKeyManUse); // skeleton key throw away event
//     MBItemHookSet(0x12, &MB1Ev_ItemNullUse); // boo repellant/koopa kard thrown away
//     MBItemHookSet(0x13, &MB1Ev_ItemExchangeBox); // barter box
//     MBItemHookSet(0x14, &MB1Ev_ItemGambleCoin); // game guy coin
//     MBItemHookSet(0x15, &MB1Ev_ItemAfter5);                 // wacky watch
//     MBItemHookSet(0xC, &MB1Ev_ItemKoopaNKinoko);
//     MBItemHookSet(0xD, &MB1Ev_ItemKoopaRKinoko);
//     MBComItemDecideHookSet(&MB1_ComItemDecide);

//     for (i = 0; i < ARRAY_COUNT(mb1ev_StarGuideMasu); i++) {
//         MBMasuStarSet(i, mb1ev_StarGuideMasu[i]);
//     }

//     if (GWBoardFlagCheck(0xE) != 0) {
//         GWBoardFlagClear(0xE);
//         MB1Ev_StarNextPos();
//     }

//     MB1Ev_StarMasuInit();
//     MB1_StarGuideCreateAll();
//     MB1_TeresaGuideCreateAll();
//     MB1_BankCoinCreateAll();
//     func_801088B4_ChillyWaters();
//     func_80108B24_ChillyWaters();
//     func_80108BA4_ChillyWaters();
//     func_80116AA0_ChillyWaters();
//     func_800EBDAC_shared_board();
//     omAddPrcObj(MB1Ev_SnowmanObjMain, 0x4800, 0, 0);
// }