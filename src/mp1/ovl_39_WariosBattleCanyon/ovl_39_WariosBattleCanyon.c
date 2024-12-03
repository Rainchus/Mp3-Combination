#include "marioparty.h"
#include "mp1.h"

mp1_GW_PLAYER* mp1_GetPlayerStruct(s32);
s32 mp1_CreateTextWindow(s32, s32, s32, s32);
void mp1_LoadStringIntoWindow(s16 win_id, void* string_id, s16 a, s16 b);
void mp1_func_8006E070(s16, s32);
mp1_Object* mp1_CreateObject(u8, void*);
void mp1_func_8003E174(mp1_Object* ptr);
s16 mp1_GetRandomSpaceOfTypeInChain(u16 type, u16 chainIndex);
s16 mp1_GetAbsSpaceIndexFromChainSpaceIndex(u16 chainIndex, u16 spaceIndex);
s16 mp1_GetChainSpaceIndexFromAbsSpaceIndex(s16 absIndex, s32 chainIndex);
s16 mp1_RNGPercentChance(s8);
mp1_SpaceData* mp1_GetSpaceData(s16 index);
void mp1_func_800A0D50(Vec3f* ptr, Vec3f* ptr2);
s32 mp1_PlaySound(s32);
u32 mp1_PlayerIsCPU(s16 index);
extern u16 mp1_D_800F5460[];
f32 mp1_func_800AEFD0(f32);
void mp1_func_800A0D00(void*, f32, f32, f32);
void mp1_DestroyObject(void*);
void mp1_func_80070D90(s16);

extern s16 mp1_D_800F544C[];
extern s16 mp1_D_800F98A8_WariosBattleCanyon[];
extern s16 mp1_D_800F98B4_WariosBattleCanyon[];

//wip for controlling the cannon as a player (cpus still do the random shot)
s16 new_func_800F7DCC_WariosBattleCanyon(s32 arg0) {
    mp1_GW_PLAYER* curPlayer;
    mp1_Object* cursorObject;
    f32 temp_f0;
    f32 var_f20;
    s16 textWindowInstance;
    s16 chosenSpace;
    s16 prevChosenSpace;
    s16 temp_a0;
    s32 frameCounter;
    s32 cpuFrameTimer;
    s32 i;
    u32 isCpu = mp1_PlayerIsCPU(-1);
    s32 frameCooldown = 0;

    curPlayer = mp1_GetPlayerStruct(-1);
    chosenSpace = 0;
    prevChosenSpace = -1;
    textWindowInstance = mp1_CreateTextWindow(0x73, 0xC8, 7, 1);
    mp1_LoadStringIntoWindow(textWindowInstance, (void* )0x1CD, -1, -1);
    mp1_func_8006E070(textWindowInstance, 0);
    cursorObject = mp1_CreateObject(0x4B, NULL);
    mp1_func_8003E174(cursorObject);
    cpuFrameTimer = 30; //how many frames it takes the cpu to make a choice
    frameCounter = 0;
    if (isCpu != 0) {
        for (frameCounter = 0;; mp1_HuPrcVSleep()) {
            //if the frame counter is zero, select a new space
            if (frameCounter == 0) {
                do {
                    chosenSpace = mp1_GetRandomSpaceOfTypeInChain(0xE, mp1_D_800F98A8_WariosBattleCanyon[arg0]);
                } while (prevChosenSpace == chosenSpace);
                temp_a0 = mp1_GetAbsSpaceIndexFromChainSpaceIndex(mp1_D_800F98A8_WariosBattleCanyon[arg0], chosenSpace);
                if (arg0 != 4) {
                    if ((mp1_GetChainSpaceIndexFromAbsSpaceIndex(temp_a0, mp1_D_800F98B4_WariosBattleCanyon[arg0])) >= 0 && mp1_RNGPercentChance(100)) {
                        do {
                            chosenSpace = mp1_GetRandomSpaceOfTypeInChain(0xE, mp1_D_800F98A8_WariosBattleCanyon[arg0]);
                        } while (prevChosenSpace == chosenSpace);
                    }
                }
                prevChosenSpace = chosenSpace;
                mp1_func_800A0D50(&cursorObject->coords, &mp1_GetSpaceData(mp1_GetAbsSpaceIndexFromChainSpaceIndex(mp1_D_800F98A8_WariosBattleCanyon[arg0], chosenSpace & 0xFFFF))->coords);
                frameCounter = 3;
                mp1_PlaySound(0xC1);
            } else {
                frameCounter--;
            }

            if (isCpu != 0) {
                cpuFrameTimer -= 1;
                if (cpuFrameTimer == 0) {
                    break;
                }
            } else if ((mp1_D_800F5460[curPlayer->port] & A_BUTTON)) {
                break;
            }
        }
    } else {
        while (1) {
            mp1_GW_PLAYER* curPlayer = mp1_GetPlayerStruct(-1);

            if (frameCooldown > 0) {
                frameCooldown--;
            }
            if (frameCooldown == 0) {
                switch (mp1_D_800F544C[curPlayer->port]) {
                case 0x100: //right
                    chosenSpace++;
                    mp1_PlaySound(0xC1);
                    frameCooldown = 4;
                    break;
                case 0x200: //left
                    chosenSpace--;
                    if (chosenSpace < 0) {
                        chosenSpace = 0;
                    }
                    mp1_PlaySound(0xC1);
                    frameCooldown = 4;
                    break;
                }
            }

            mp1_func_800A0D50(&cursorObject->coords, &mp1_GetSpaceData(mp1_GetAbsSpaceIndexFromChainSpaceIndex(mp1_D_800F98A8_WariosBattleCanyon[arg0], chosenSpace & 0xFFFF))->coords);
            
            if (mp1_D_800F5460[curPlayer->port] & A_BUTTON) {
                break;
            }
            mp1_HuPrcVSleep();
        }

    }

    mp1_PlaySound(0xC8);
    var_f20 = 0.0f;
    for (cpuFrameTimer = 0; cpuFrameTimer < 40; cpuFrameTimer++) {
        var_f20 += 50.0f;
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }
        temp_f0 = (mp1_func_800AEFD0(var_f20) * 0.3f) + 1.2f;
        mp1_func_800A0D00(&cursorObject->xScale, temp_f0, 1.0f, temp_f0);
        mp1_HuPrcVSleep();
    }
    mp1_DestroyObject(cursorObject);
    mp1_func_80070D90(textWindowInstance);
    return chosenSpace;
}