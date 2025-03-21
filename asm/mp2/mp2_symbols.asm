.definelabel mp2_osEPiRawStartDma, 0x8009D950; //rom:0x9E550
.definelabel mp2_osEepromProbe, 0x8009CAD0; // rom:0x9D6D0
.definelabel mp2_osSiGetAccess, 0x800A5F94; // rom:0xA6B94
.definelabel mp2_osEepStatus, 0x8009C930; // rom:0x9D530
.definelabel mp2_osEepromLongRead, 0x8009CC40; // rom:0x9D840
.definelabel mp2_osEepromLongWrite, 0x8009CB50; // rom:0x9D750
.definelabel mp2_osEepromWrite, 0x8009C720; //rom:0x9D320
.definelabel mp2_osCreateMesgQueue, 0x800A5720; // rom:0xA6320
.definelabel mp2_osSendMesg, 0x800A59C0; // rom:0xA65C0
.definelabel mp2_osRecvMesg, 0x800A5890; // rom:0xA6490
.definelabel mp2_SleepVProcess, 0x8007DA44; // rom:0x7E644
.definelabel mp2_GetEepType, 0x8001ACD0; //rom:0x1B8D0
.definelabel mp2_GetSaveFileChecksum, 0x8001B114; //rom:0x1BD14

.definelabel eepromBuffer, 0x800D89F0;
.definelabel mp2_HUDSON_Header, 0x800C9B60;
.definelabel mp2_D_800FA5E0, 0x800FA5E0;
.definelabel mp2_bcopy, 0x800a5210; //rom:0xa5e10
.definelabel mp2_func_8007ee0c_7fa0c, 0x8007ee0c; //rom:0xa5e10
.definelabel func_80062BE0_637E0, 0x80062BE0; //rom:0x637E0
.definelabel func_8000e9e8, 0x8000e9e8;
.definelabel debug_gPlayers, 0x801072B8;
.definelabel mp2_gPlayers, 0x800FD2C0;
.definelabel func_800683BC_68FBC, 0x800683bc; //rom:0x68fbc
.definelabel func_8003f6f0_402f0, 0x8003f6f0; //rom:0x402f0
.definelabel mp2_omOvlCallEx, 0x800770EC; //rom:0x77CEC
.definelabel mp2_omOvlHisChg, 0x80077538; // rom:0x78138
.definelabel mp2__ClearFlag, 0x800683BC;
.definelabel D_800F93C6, 0x800F93C6;
.definelabel D_800F93C8, 0x800F93C8;

.definelabel D_80107830_413C90_Results, 0x80107830;
.definelabel D_80107838_413C98_Results, 0x80107838;
.definelabel D_80107840_413CA0_Results, 0x80107840;
.definelabel D_80107848_413CA8_Results, 0x80107848;
.definelabel D_80107860_413CC0_Results, 0x80107860;

.definelabel mp2_hidden_block_coins_space_index, 0x800FA608
.definelabel mp2_hidden_block_star_space_index, 0x800FD418
.definelabel mp2_BoardState, 0x800F93A8

.definelabel mp2_omovlhis, 0x800FDBE8;
.definelabel mp2_omovlhisidx, 0x800CD418;

.definelabel mp2_pageID, 0x801072A0;
.definelabel mp2_debugCursorIndex, 0x801072A2;
.definelabel mp2_debugMode, 0x800CD40E;

.definelabel mp2_func_80067E6C_68A6C, 0x80067E6C;
.definelabel mp2_func_8006836C_68F6C, 0x8006836C;
.definelabel mp2_D_800CD2C4_CDEC4, 0x800cd2c4;
.definelabel mp2_D_800F93C8_F9FC8, 0x800F93C8;
.definelabel mp2_BankCoins, 0x800F8D1E

.definelabel mp2_func_800794A8, 0x800794A8
.definelabel mp2_func_800683BC_68FBC, 0x800683BC
.definelabel mp2_omInitObjMan, 0x800760C0
.definelabel mp2_omAddObj, 0x80076598
.definelabel mp2_func_80079E60_7AA60, 0x80079E60
.definelabel mp2_InitFadeIn, 0x8008F544
.definelabel mp2_InitFadeOut, 0x8008F5AC
.definelabel mp2_HuPrcSleep, 0x8007D9E0
.definelabel mp2_HuPrcVSleep, 0x8007DA44
.definelabel mp2_func_8007959C_7A19C, 0x8007959C
.definelabel mp2_D_80107400_DA3F0_Debug, 0x80107400
.definelabel mp2__SetFlag, 0x8006836C
.definelabel mp2_D_800F93CD_F9FCD, 0x800F93CD
.definelabel mp2_D_800CD408_CE008, 0x800CD408
.definelabel mp2_func_80102D54_D5D44_Debug, 0x80102D54
.definelabel mp2_func_80026D28_27928, 0x80026D28
.definelabel mp2_func_80026DAC_279AC, 0x80026DAC
.definelabel mp2_func_80026E00_27A00, 0x80026E00
.definelabel mp2_D_800F93A8, 0x800F93A8

.definelabel mp2_func_8001A2F8_1AEF8, 0x8001A2F8
.definelabel mp2_func_8001AAAC_1B6AC, 0x8001AAAC
.definelabel mp2_espPosSet, 0x8001A694
.definelabel mp2_espDispOn, 0x8001A614
.definelabel mp2_func_8001A788_1B388, 0x8001A788
.definelabel mp2_func_8008F618_90218, 0x8008F618
.definelabel mp2_func_8001AC44_1B844, 0x8001AC44
.definelabel mp2_SprAnimKill, 0x80082660
.definelabel mp2_SprAnimKillAll, 0x80082790
.definelabel mp2_D_801011FC_101DFC, 0x801011FC
.definelabel mp2_rnd_seed, 0x800C99B4
.definelabel mp2_osGetCount, 0x800ADD50
.definelabel mp2_BattleMinigameCoins, 0x800F9208
.definelabel mp2_prevMinigamesPlayed, 0x800DF698
.definelabel mp2_func_800890CC, 0x800890CC
.definelabel mp2_HuPrcKill, 0x8007D8A8
.definelabel mp2_HuPrcEnd, 0x8007D9A4
.definelabel mp2_UnkCamThing, 0x80052E68
.definelabel mp2_OtherBoardState, 0x800F8CD8
.definelabel mp2_D_800E1F50_E2B50, 0x800E1F50
.definelabel mp2_D_800E1F52_E2B52, 0x800E1F52
.definelabel mp2_rand8, 0x80018AFC
.definelabel mp2_midTurnMinigameThing, 0x800E1F8C
.definelabel mp2_func_8004CA14_4D614, 0x8004CA14
.definelabel mp2_func_8006135C_61F5C, 0x8006135C

//hardcoded symbols
.definelabel mp2_omovlhisidx_copy, 0x807FFB00
.definelabel mp2_PlayersCopy, 0x807FFC00
