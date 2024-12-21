#ifndef _GAMEWORK_DATA_H
#define _GAMEWORK_DATA_H

#include "ultra64.h"

// typedef struct mp3_PlayerData {
// /* 0x00 */ u8 group; //for which group you belong to in a minigame
// /* 0x01 */ u8 cpu_difficulty;
// /* 0x02 */ u8 controller_port;
// /* 0x03 */ u8 characterID;
// /* 0x04 */ u8 flags1; //value & 1 == Player is CPU
// /* 0x05 */ char unk_05;
// /* 0x06 */ s16 minigameCoinsWon; //extra coins collected in minigames
// /* 0x08 */ s16 minigameCoins; //coins for winning current minigame
// /* 0x0A */ s16 coins; //referenced as u16 and s16 (usually if u16 it's casted to s16)
// /* 0x0C */ char unk_0C[2];
// /* 0x0E */ s8 stars;
// /* 0x0F */ u8 chainIndexCur;
// /* 0x10 */ u8 spaceIndexCur;
// /* 0x11 */ u8 chainIndexNext;
// /* 0x12 */ u8 spaceIndexNext;
// /* 0x13 */ u8 unk_13; //(Chain Index?)
// /* 0x14 */ u8 unk_14; //(Space Index?)
// /* 0x15 */ u8 chainIndexPrevious;
// /* 0x16 */ u8 spaceIndexPrevious;
// /* 0x17 */ u8 flags2;
// /* 0x18 */ u8 items[3];
// /* 0x1B */ u8 bowser_suit_flags;
// /* 0x1C */ u8 turn_status; //space type landed on (blue, red, etc.)
// /* 0x1D */ s8 playerIndex;
// /* 0x1E */ char unk_1E[2]; //likely padding
// /* 0x20 */ void* unk_20;
// /* 0x24	*/ void* player_obj; //ptr to struct 0x48 in size (things like model position, rotation, etc.)
// /* 0x28 */ s16 minigameCoinsTotal; //for minigame star
// /* 0x2A */ s16 coinsPeak; //most coins held at once for coin star
// /* 0x2C */ s8 happeningSpacesLandedOn;
// /* 0x2D */ s8 redSpacesLandedOn;
// /* 0x2E */ s8 blueSpacesLandedOn;
// /* 0x2F */ s8 chanceSpacesLandedOn;
// /* 0x30 */ s8 bowserSpacesLandedOn;
// /* 0x31 */ s8 battleSpacesLandedOn;
// /* 0x32 */ s8 itemSpacesLandedOn;
// /* 0x33 */ s8 bankSpacesLandedOn;
// /* 0x34 */ s8 gameGuySpacesLandedOn;
// /* 0x35 */ char unk_35[3]; //likely padding
// } GW_PLAYER; //sizeof 0x38

// extern GW_PLAYER GwPlayer[4];

#endif