// #include "mp2.h"

// //this is the debug overlay. We load this to handle swap logic
// //this overlay should only ever be reached if mp2 is only being played for a minigame (and therefore isn't the CurBaseGame)

// void SaveMp2PlayerToMp3PlayerCopy(void);
// void SaveMp2PlayerToMp1PlayerCopy(void);

// void mp2_DebugMenuSetup(void) {
//     mp2_func_80020070_20C70(1);
//     mp2_omInitObjMan(16, 4);
//     mp2_D_80102708_103308 = 1;

//     //this handles how each game is loaded back into
//     switch (CurBaseGame) {
//     case MP1_BASE:
//         ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
//         SaveMp2PlayerToMp1PlayerCopy(); //copy mp2 player structs to mp1's gPlayer Copy
//         ComboSwitchGameToMp1();
//         break;
//     case MP2_BASE: //this should never happen
//         break;
//     case MP3_BASE:
//         ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
//         SaveMp2PlayerToMp3PlayerCopy(); //copy mp2 player structs to mp3's gPlayer Copy
//         ComboSwitchGameToMp3();
//         break;
//     }
// }

// //this is only ran when we need to return to a different game
// void mp2_ovl00EntryFunc(void) {
//     mp2_DebugMenuSetup(); 
// }
