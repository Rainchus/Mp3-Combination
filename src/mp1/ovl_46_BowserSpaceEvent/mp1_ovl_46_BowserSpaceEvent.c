

#include "marioparty.h"
#include "mp1.h"

extern s32 mp1_D_800F8ED0_BowserSpaceEvent;
s32 mp1_func_80072718(void);
void mp1_func_800F8EA8_BowserSpaceEvent(void);
void mp1_func_800F8DC0_BowserSpaceEvent(void);
void mp1_func_80054654(void);
void mp1_func_80070ED4(void);
s32 mp1_omOvlReturnEx(s16 level);
void mp1_SetBoardFeatureFlag(s32 flag);
void mp1_omOvlGotoEx(s32, s16, u16);
void mp1_func_80059348(s16);
void mp1_omOvlHisChg(s16 arg0, s32 overlay, s16 event, s16 stat);
s32 mp1_omOvlCallEx(s32 arg0, s16 arg1, u16 arg2);

void new_func_800F8B1C_BowserSpaceEvent(void) {
    #ifdef MP1
    s32 combinedIndex;

    if (mp1_func_80072718() == 0) {
        mp1_func_800F8EA8_BowserSpaceEvent();
        mp1_func_800F8DC0_BowserSpaceEvent();
        mp1_func_80054654();
        mp1_func_80070ED4();

        //convert mp1 minigame to global minigame index (this gets converted back in the explanation overlay)
        switch (mp1_D_800F8ED0_BowserSpaceEvent) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            combinedIndex = BASH_N_CASH;
            break;
        case 3:
            combinedIndex = MP1_FACE_LIFT;
            break;
        case 4:
            combinedIndex = TUG_O_WAR;
            break;
        case 5:
            combinedIndex = MP1_BALLOON_BURST;
            break;
        }
        switch (mp1_D_800F8ED0_BowserSpaceEvent) {
            case 0:
                mp1_omOvlReturnEx(1);
                break;
            case 1:
                mp1_SetBoardFeatureFlag(69);
                mp1_omOvlGotoEx(1, 0, 146);
                break;
            case 2:
                mp1_SetBoardFeatureFlag(69);
                //mp1_func_80059348(16);
                mp1_func_80059348(combinedIndex);
                mp1_omOvlCallEx(111, 0, 148);
                mp1_omOvlHisChg(1, 70, 1, 146);
                break;
            case 3:
                mp1_SetBoardFeatureFlag(69);
                //mp1_func_80059348(14);
                mp1_func_80059348(combinedIndex);
                mp1_omOvlCallEx(111, 0, 148);
                mp1_omOvlHisChg(1, 70, 1, 146);
                break;
            case 4:
                mp1_SetBoardFeatureFlag(69);
                //mp1_func_80059348(51);
                mp1_func_80059348(combinedIndex);
                mp1_omOvlCallEx(111, 0, 148);
                mp1_omOvlHisChg(1, 70, 1, 146);
                break;
            case 5:
                mp1_SetBoardFeatureFlag(69);
                //mp1_func_80059348(19);
                mp1_func_80059348(combinedIndex);
                mp1_omOvlCallEx(111, 0, 148);
                mp1_omOvlHisChg(1, 70, 1, 146);
                break;
        }
    }
    #endif
}
