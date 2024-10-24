//data
.definelabel Player1Buttons,		0x800CCF7C
.definelabel Player1Pressedbuttons,	0x800C9520
.definelabel Player2Pressedbuttons,	0x800C9522
.definelabel Player3Pressedbuttons,	0x800C9524
.definelabel Player4Pressedbuttons,	0x800C9526
.definelabel inBoardPtr, 0x800CC3DC
.definelabel objects, 0x80114B18
.definelabel cur_rng_seed, 0x80097650
.definelabel debugPrintBool, 0x800A1760
.definelabel num_board_spaces, 0x80105210
.definelabel hydrated_space_data, 0x80105214
.definelabel mp3_gPlayers, 0x800D1108

//functions
.definelabel GetCurrentPlayerIndex, 0x800F2130
.definelabel GetPlayerStruct, 0x800F213C
.definelabel unknownDMAFunc, 0x8004DB14
.definelabel PlaySound, 0x8004AA88
.definelabel mp3_DrawDebugText, 0x8004DD7C
.definelabel mp3_SleepVProcess, 0x8004F074
.definelabel _sprintf, 0x8007BDC0
.definelabel HuGetRandomByte, 0x8000B16C
.definelabel DrawBox, 0x8004DE24
.definelabel RedrawSpaces, 0x800EBDAC
.definelabel osGetTime, 0x8007CC90
.definelabel osPiRawStartDma, 0x80080A60
.definelabel osEPiRawStartDma, 0x80072950

.definelabel osMemSize, 0x80000318
.definelabel __osCurrentTime, 0x800CE2B8
.definelabel memcpy, 0x8007BD94
.definelabel _Printf, 0x80081A40
.definelabel osWritebackDCacheAll, 0x80078D50
.definelabel osViBlack, 0x8007DC60
.definelabel osViSwapBuffer, 0x8007D900
.definelabel __osActiveQueue, 0x800A2DBC
.definelabel osSetEventMesg, 0x8007C2D0
.definelabel osRecvMesg, 0x8007C070
.definelabel osStopThread, 0x80086B70
.definelabel osCreateMesgQueue, 0x8007BF00
.definelabel mp3_osCreateThread, 0x8007C810
.definelabel mp3_osStartThread, 0x8007CAE0
.definelabel mp3_omovlhis, 0x800D2010
.definelabel mp3_omovlhisidx, 0x800A1768
.definelabel mp3_D_800CD2A2, 0x800CD2A2
.definelabel mp3_SetSpriteCenter, 0x8000BBD4
.definelabel mp3_HuObjCreate, 0x80047620

.definelabel D_800D20F0, 0x800D20F0
.definelabel D_800D6B60, 0x800D6B60
.definelabel D_800CD0AA, 0x800CD0AA
.definelabel mp3_D_80110998, 0x80110998
.definelabel mp3_D_800B1A30, 0x800B1A30
.definelabel mp3_rand8, 0x8000B16C
.definelabel func_80019C00_1A800, 0x80019C00
.definelabel func_8005B43C_5C03C, 0x8005B43C
.definelabel func_8005D294_5DE94, 0x8005D294
.definelabel func_80106B38_4F9028, 0x80106B38
.definelabel mp3_HuPrcSleep, 0x8004F010
.definelabel mp3_osViBlack, 0x8007DC60
.definelabel mp3___osInitialize_common, 0x8007ED78
.definelabel mp3___osInitialize_autodetect, 0x8007F048
.definelabel mp3_func_80050F50_51B50, 0x80050F50
.definelabel mp3_func_800357AC_363AC, 0x800357AC
.definelabel osAppNmiBuffer, 0x8000031C //global location for both games
.definelabel D_800B23B0, 0x800B23B0;
.definelabel mp3_omOvlCallEx, 0x80048128
.definelabel mp3_boardstate, 0x800CD058
.definelabel func_800F8610_10C230, 0x800F8610
.definelabel func_80108910_119290, 0x80108910

.definelabel HuWipeFadeIn, 0x80061FE8
.definelabel HuWipeFadeOut, 0x80062050
.definelabel HuWipeStatGet, 0x800620BC
.definelabel InitEspriteSlot, 0x8000BFEC
.definelabel func_8000B838_C438, 0x8000B838
.definelabel func_8000BB54_C754, 0x8000BB54
.definelabel mp3_HuPrcVSleep, 0x8004F074
.definelabel func_8000BBD4_C7D4, 0x8000BBD4
.definelabel func_8000BCC8_C8C8, 0x8000BCC8
.definelabel func_8000C184_CD84, 0x8000C184
.definelabel func_80055670_56270, 0x80055670
.definelabel D_800D530C, 0x800D530C


//hardcoded symbols
.definelabel mp3_omovlhisidx_copy, 0x807FFD90
.definelabel mp3_omovlhis_copy, 0x807FFDA0
.definelabel mp3_PlayersCopy, 0x807FFE00