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
.definelabel DrawDebugText, 0x8004DD7C
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
.definelabel osCreateThread, 0x8007C810
.definelabel osStartThread, 0x8007CAE0

//hardcoded symbols
.definelabel mp3_PlayersCopy, 0x807FFE00