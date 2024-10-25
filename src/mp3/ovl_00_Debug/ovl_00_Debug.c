#include "marioparty.h"

#define MINIGAMES_PER_PAGE 16
#define MAX_PAGES 12

#define BACKGROUND_IMAGE_ID 0x001E0005
#define MENU_BACKGROUND_IMAGE_ID 0x000E0024

#define EEPROM_ABS_POS 0x2C0
#define EEPROM_BLOCK_POS EEPROM_ABS_POS / EEPROM_BLOCK_SIZE

s32 pageIndex = 0;
s32 cursorIndex = 0;

extern u8 D_800D09A8;
OSMesgQueue customMesgQueue = {0};
extern OSMesgQueue mp3_D_800CE1A0;
u8 customEepromData[0x140] = {0};

extern s16 mp3_D_800CDA7C[];
extern s16 mp3_D_800C9520;
extern s32 eepromLoadFailed;
extern char* MinigameList[];
extern u32 mp3_debug_font_color;

extern s32 mp3_osEepromLongRead(OSMesgQueue *, u8, u8 *, int);
void func_8000BBD4_C7D4(s32, s32, s32);
void mp3_ScaleESprite(s32 eSpriteID, f32 xScale, f32 yScale);

void to_uppercase(const char* input, char* output) {
    while (*input) {
        if (*input >= 'a' && *input <= 'z') {
            *output = *input - ('a' - 'A');  // Convert lowercase to uppercase
            output++;
        } else if ((*input >= 'A' && *input <= 'Z') || *input == ' ' || (*input >= '1' && *input <= '9')) {
            *output = *input;  // Copy uppercase letters, spaces, and digits 1-9
            output++;
        }
        // Skip other characters
        input++;
    }
    *output = '\0';  // Null-terminate the output string
}

void InvalidEepCheck(void) {
    // turn this back on for release
    if (eepromLoadFailed == 1) {
        mp3_DrawDebugText(10, 20, "INVALID SAVE TYPE FOUND");
        mp3_DrawDebugText(10, 30, "PLEASE SET THE SAVE TYPE TO");
        mp3_DrawDebugText(10, 40, "EEPROM 16KBIT");
    }
}

void SetMusicID(void) {
    char buffer[20];
    s32 songID = 1;

    //dpad up
    if (mp3_D_800C9520 & 0x800) { //dpad up
        songID++;
        mp3_HuAudSeqPlay(songID);
    } else if (mp3_D_800C9520 & 0x400) { //dpad down
        songID--;
        mp3_HuAudSeqPlay(songID);
    } else if (mp3_D_800C9520 & 0x200) { //dpad left
        songID -= 10;
        mp3_HuAudSeqPlay(songID);
    } else if (mp3_D_800C9520 & 0x100) { //dpad right
        songID += 10;
        mp3_HuAudSeqPlay(songID);
    }
    mp3_sprintf(buffer, "SONG ID: %d", songID);
    mp3_DrawDebugText(10, 10, buffer);
}

s32 DrawImageWrapper(s32 mainFileSystemID, s32 xPos, s32 yPos) {
    s32 curGraphicID;
    s32 curESpriteID;

    curGraphicID = func_8000B838_C438(mainFileSystemID);
    curESpriteID = InitEspriteSlot(curGraphicID, 0, 1);
    func_8000BBD4_C7D4(curESpriteID, xPos, yPos); //set sprite position
    return curESpriteID;
}

s32 GetMinigameFlag(s32 arg0) {
    return (customEepromData[arg0 / 8] >> (arg0 % 8)) & 1;
}

void SetMinigameFlag(s32 arg0, s32 value) {
    if (value) {
        // Set the bit (use OR to turn the bit on)
        customEepromData[arg0 / 8] |= (1 << (arg0 % 8));
    } else {
        // Clear the bit (use AND with the complement to turn the bit off)
        customEepromData[arg0 / 8] &= ~(1 << (arg0 % 8));
    }
}

void FlipMinigameFlag(s32 arg0) {
    s32 currentFlag = GetMinigameFlag(arg0);
    SetMinigameFlag(arg0, !currentFlag); // Flip the flag (1 -> 0, 0 -> 1)
}

void newDebugMenuMain(void) {
    char outputbuffer[40];
    s32 eSprite0;
    s32 eSprite1;
    s32 eSprite2;
    char buffer[100];
    s32 i;

    mp3_osEepromLongRead(&mp3_D_800CE1A0, EEPROM_BLOCK_POS, customEepromData, sizeof(customEepromData));
    mp3_HuPrcVSleep();

    HuWipeFadeIn(0xFF, 0x10);

    eSprite0 = DrawImageWrapper(BACKGROUND_IMAGE_ID, 160, 120);
    eSprite1 = DrawImageWrapper(MENU_BACKGROUND_IMAGE_ID, 200, 120);

    mp3_ScaleESprite(eSprite1, 1.70f, 1.0f);
    mp3_HuAudSeqPlay(4);

    while (1) {
        s32 xPos = 105;
        s32 yPos = 38;

        if (mp3_D_800C9520 & 0x200) { //dpad left
            mp3_debug_font_color--;
        } else if (mp3_D_800C9520 & 0x100) { //dpad right
            mp3_debug_font_color++;
        }

        //9 is blue
        //0 is black
        //12 is green

        if (mp3_D_800C9520 & 0x800) { //dpad up
            if (cursorIndex > 0) {
                cursorIndex--;
            } else {
                cursorIndex = MINIGAMES_PER_PAGE - 1; //wrap around
            }
        } else if (mp3_D_800C9520 & 0x400) { //dpad down
            if (cursorIndex < MINIGAMES_PER_PAGE - 1) {
                cursorIndex++;
            } else {
                cursorIndex = 0; //wrap around
            }
        } else if (mp3_D_800C9520 & 0x200) { //dpad left
            if (pageIndex > 0) {
                pageIndex--;
            } else {
                pageIndex = MAX_PAGES - 1; //wrap around
            }
        } else if (mp3_D_800C9520 & 0x100) { //dpad right
            if (pageIndex < MAX_PAGES - 1) {
                pageIndex++;
            } else {
                pageIndex = 0; //wrap around
            }
        }

        for (i = 0; i < MINIGAMES_PER_PAGE; i++) {
            u8 minigameFlag = GetMinigameFlag(pageIndex * MINIGAMES_PER_PAGE + i);

            mp3_bzero(outputbuffer, sizeof(outputbuffer));
            to_uppercase(&MinigameList[i + pageIndex * MINIGAMES_PER_PAGE][1], outputbuffer);

            if (minigameFlag == 1) {
                mp3_debug_font_color = 12;
            } else {
                mp3_debug_font_color = 0;
            }

            if (cursorIndex == i) {
                mp3_debug_font_color = 9;
            }

            mp3_DrawDebugText(xPos, yPos, outputbuffer);
            yPos += 10;
        }

        //if A pressed
        if (mp3_D_800C9520 & 0x8000) {
            // Flip the current minigame flag
            FlipMinigameFlag(pageIndex * MINIGAMES_PER_PAGE + cursorIndex);
        }

        //if start is pressed, save changes and then exit
        if (mp3_D_800C9520 & 0x1000) {
            //flush changes back to eeprom
            mp3_osEepromLongWrite(&mp3_D_800CE1A0, EEPROM_BLOCK_POS, customEepromData, sizeof(customEepromData));
            mp3_HuPrcVSleep();
            //reload mp3
            ComboSwitchGameToMp3();
        }
        mp3_HuPrcVSleep();
    }
}
