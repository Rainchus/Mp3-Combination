#include "marioparty.h"
#include "mp3.h"

#define N64_LOGO 0x00110000
#define NINTENO_LOGO 0x00110001
#define HUDSON_LOGO 0x00110002
#define CUSTOM_LOGO 0x00110013

void mp3_HuWipeFadeOut(s32, s32);

s32 initialBoot = 0;

//func_80105C80_3D7430
void mp3_newBootLogos(void) {
    s16 temp_v0;
    s16 temp_v0_copy;
    s16 temp_v0_3;
    s32 temp_s0;
    s32 temp_s0_copy;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0_2;
    s32 temp_v0_2_copy;
    s32 temp_v0_4;

    // temp_v0 = func_8000B838_C438(N64_LOGO);
    // temp_v0_2 = InitEspriteSlot(temp_v0, 0, 1);
    // temp_s0 = temp_v0_2 & 0xFFFF;
    // mp3_func_8000BBD4_C7D4(temp_s0, 0xA0, 0x78);
    // func_8000BB54_C754(temp_s0);
    // func_8000BCC8_C8C8(temp_s0, 0xFFFF);

    mp3_osEepromLongWrite(&mp3_D_800CE1A0, EEPROM_BLOCK_POS, customEepromData, sizeof(customEepromData));

    if (initialBoot == 0) {
        initialBoot = 1;
        temp_v0 = func_8000B838_C438(CUSTOM_LOGO);
        temp_v0_2 = InitEspriteSlot(temp_v0, 0, 1);
        temp_s0 = temp_v0_2 & 0xFFFF;
        mp3_func_8000BBD4_C7D4(temp_s0, 210, 0x78);
        mp3_func_8000BB54_C754(temp_s0);
        mp3_func_8000BCC8_C8C8(temp_s0, 0xFFFF);

        mp3_HuWipeFadeIn(0xB, 0x1E);
        while (mp3_HuWipeStatGet() != 0) {
            mp3_HuPrcVSleep();
        }

        //check for button inputs
        while (1) {
            if (mp3_D_800CDA7C[0] == -1) {
                mp3_HuPrcVSleep();
                continue;
            }
            if (mp3_D_800CDA7C[0] & 0x10) { //if R is pressed, load mario party 2
                mp3_HuWipeFadeOut(0xB, 9);

                while (mp3_HuWipeStatGet() != 0) {
                    mp3_HuPrcVSleep();
                }
                ComboSwitchGameToMp2();
            }
            #ifdef MP1
            else if (mp3_D_800CDA7C[0] & 0x20) { //if L is pressed, load mario party 1
                mp3_HuWipeFadeOut(0xB, 9);

                while (mp3_HuWipeStatGet() != 0) {
                    mp3_HuPrcVSleep();
                }
                ComboSwitchGameToMp1();
            }
            #endif
            else if (mp3_D_800CDA7C[0] & 0x2000) { //if Z is pressed, load minigame selection
                ForeignMinigameIndexToLoad = -1;
                mp3_HuWipeFadeOut(0xB, 9);

                while (mp3_HuWipeStatGet() != 0) {
                    mp3_HuPrcVSleep();
                }
                mp3_omOvlCallEx(0, 0, 0);
                mp3_HuPrcExit();
            } else if (mp3_D_800CDA7C[0] & 0x8000) { //if A is pressed, load mario party 3
                break;
            }
            mp3_HuPrcVSleep();
        }
        mp3_HuWipeFadeOut(0xB, 9);

        while (mp3_HuWipeStatGet() != 0) {
            mp3_HuPrcVSleep();
        }
    }


    temp_v0_copy = func_8000B838_C438(N64_LOGO);
    temp_v0_2_copy = InitEspriteSlot(temp_v0_copy, 0, 1);
    temp_s0_copy = temp_v0_2_copy & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0_copy, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_copy);
    mp3_func_8000BCC8_C8C8(temp_s0_copy, 0xFFFF);

    mp3_HuWipeFadeIn(0xB, 0x1E);
    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    mp3_HuWipeFadeOut(0xB, 9);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    temp_v0_3 = func_8000B838_C438(NINTENO_LOGO);
    temp_v0_4 = InitEspriteSlot(temp_v0_3, 0, 1);
    temp_s0_2 = temp_v0_4 & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0_2, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_2);
    mp3_func_8000BCC8_C8C8(temp_s0_2, 0xFFFF);
    mp3_HuWipeFadeIn(0xB, 9);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    mp3_HuWipeFadeOut(0xB, 9);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_func_8000C184_CD84(temp_v0_4 & 0xFFFF);
    mp3_func_80055670_56270(temp_v0_3);
    mp3_HuPrcSleep(9);
    temp_s0_3 = InitEspriteSlot(func_8000B838_C438(HUDSON_LOGO), 0, 1) & 0xFFFF;
    mp3_func_8000BBD4_C7D4(temp_s0_3, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_3);
    mp3_func_8000BCC8_C8C8(temp_s0_3, 0xFFFF);
    mp3_HuWipeFadeIn(0xB, 9);

    while (mp3_HuWipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }

    mp3_HuPrcSleep(5);
    mp3_D_800D530C = 1;

    while (1) {
        mp3_HuPrcVSleep();
    }
}