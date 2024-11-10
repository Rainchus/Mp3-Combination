#include "marioparty.h"
#include "mp3.h"

#define MINIGAMES_PER_PAGE 16
#define MAX_PAGES 12

#define BACKGROUND_IMAGE_ID 0x001E0005
#define MENU_BACKGROUND_IMAGE_ID 0x000E0024

#define MESSAGE_BOX_ID 0x00000090

#define EEPROM_ABS_POS 0x2C0
#define EEPROM_BLOCK_POS EEPROM_ABS_POS / EEPROM_BLOCK_SIZE

s32 pageIndex = 0;
s32 cursorIndex = 0;
s32 flipMinigameFlags = 0;

extern u8 mp3_D_800D09A8;
OSMesgQueue customMesgQueue = {0};
extern OSMesgQueue mp3_D_800CE1A0;
u8 customEepromData[0x140] = {0};
extern int		mp3_sprintf(char *s, const char *fmt, ...);
void mp3_HuAudSeqPlay(s32);
extern s16 mp3_D_800CDA7C[];
extern s16 mp3_D_800C9520;
extern s16 mp3_D_800D1350[];
void mp3_DrawDebugText(s32, s32, char*);
extern s32 mp3_osEepromLongRead(OSMesgQueue *, u8, u8 *, int);
void mp3_func_8000BBD4_C7D4(s32, s32, s32);
void mp3_ScaleESprite(s32 eSpriteID, f32 xScale, f32 yScale);
void mp3_HuPrcVSleep(void);
void mp3_HuWipeFadeIn(s32, s32);
void mp3_bzero(void*, s32);
void ComboSwitchGameToMp3(void);
s32 directionHeldFrames = 0;
s32 buttonHeld = 0;
extern mp3MinigameIndexTable minigameLUT[];
extern u32 mp3_debug_font_color;

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

s32 CheckHeldButtons(void) {
    if (directionHeldFrames == 0) {
        if (mp3_D_800D1350[0] != 0) {
            buttonHeld = mp3_D_800D1350[0];
            directionHeldFrames++;
        }
        return 0;
    }

    //button has been held for at least one frame
    if (mp3_D_800D1350[0] == buttonHeld) {
        directionHeldFrames++;
    } else {
        directionHeldFrames = 0;
    }
    //if button has been held for 10 frames, scroll every 2 frames
    if ((directionHeldFrames > 10) && (directionHeldFrames % 2) == 0) {
        return buttonHeld;
    }
    return 0;
}

s32 DrawImageWrapper(s32 mainFileSystemID, s32 xPos, s32 yPos) {
    s32 curGraphicID;
    s32 curESpriteID;

    curGraphicID = func_8000B838_C438(mainFileSystemID);
    curESpriteID = InitEspriteSlot(curGraphicID, 0, 1);
    mp3_func_8000BBD4_C7D4(curESpriteID, xPos, yPos); //set sprite position
    return curESpriteID;
}

void InvalidEepCheck(s32 xPos, s32 yPos) {
    if (eepromLoadFailed == 1) {
        mp3_DrawDebugText(xPos, yPos, "INVALID SAVE TYPE FOUND");
        mp3_DrawDebugText(xPos, yPos + 10, "PLEASE SET THE SAVE TYPE TO");
        mp3_DrawDebugText(xPos, yPos + 20, "EEPROM 16KBIT");
    }
}

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

void newDebugMenuMain(void) {
    mp3MinigameIndexTable* curMinigameData;
    char outputbuffer[40];
    // s32 eSprite0;
    s32 eSprite1;
    u8 minigameflag;
    s32 i;
    
    mp3_HuPrcVSleep();
    mp3_HuWipeFadeIn(0xFF, 0x10);
    // eSprite0 = DrawImageWrapper(BACKGROUND_IMAGE_ID, 160, 120);
    DrawImageWrapper(BACKGROUND_IMAGE_ID, 160, 120);
    
    mp3_HuAudSeqPlay(8);

    if (eepromLoadFailed == 1) {
        s32 invalidEepBoxSpriteId = DrawImageWrapper(MESSAGE_BOX_ID, 0, 0);
        mp3_ScaleESprite(invalidEepBoxSpriteId, 1.25f, 1.0f);
        //mp3_Hu3dModelCreateWrapper(0x000200A2, 0x6A9); //create tumble model
        s32 xPos = 24;
        s32 yPos = 35;
        while (1) {
            mp3_func_8000BBD4_C7D4(invalidEepBoxSpriteId, xPos, yPos); //set sprite position
            mp3_debug_font_color = 9;
            InvalidEepCheck(xPos + 27, yPos - 15);
            mp3_HuPrcVSleep();
        }
    }

    eSprite1 = DrawImageWrapper(MENU_BACKGROUND_IMAGE_ID, 200, 105);
    mp3_ScaleESprite(eSprite1, 1.70f, 1.0f);

    while (1) {
        s32 xPos = 105;
        s32 yPos = 23;
        s32 currentlyHeldButtons;

        // if (mp3_D_800C9520 & 0x200) { //dpad left
        //     mp3_debug_font_color--;
        // } else if (mp3_D_800C9520 & 0x100) { //dpad right
        //     mp3_debug_font_color++;
        // }

        currentlyHeldButtons = CheckHeldButtons();
        if (currentlyHeldButtons != 0) {
            switch (currentlyHeldButtons) {
            case 0x400:
                //hardcoded check for last page
                if (cursorIndex >= 13 && pageIndex == MAX_PAGES - 1) {
                    cursorIndex = 0; //wrap around
                } else {
                    if (cursorIndex < MINIGAMES_PER_PAGE - 1) {
                        cursorIndex++;
                    } else {
                        cursorIndex = 0; //wrap around
                    }
                }
                break;                
            case 0x800:
                //hardcoded check for last page
                if (cursorIndex == 0 && pageIndex == MAX_PAGES - 1) {
                    cursorIndex = 13; //wrap around
                } else {
                    if (cursorIndex > 0) {
                        cursorIndex--;
                    } else {
                        cursorIndex = MINIGAMES_PER_PAGE - 1; //wrap around
                    }
                }
            }
        } else {
            if (mp3_D_800C9520 & 0x800) { //dpad up
                //hardcoded check for last page
                if (cursorIndex == 0 && pageIndex == MAX_PAGES - 1) {
                    cursorIndex = 13; //wrap around
                } else {
                    if (cursorIndex > 0) {
                        cursorIndex--;
                    } else {
                        cursorIndex = MINIGAMES_PER_PAGE - 1; //wrap around
                    }
                }
            } else if (mp3_D_800C9520 & 0x400) { //dpad down
                //hardcoded check for last page
                if (cursorIndex >= 13 && pageIndex == MAX_PAGES - 1) {
                    cursorIndex = 0; //wrap around
                } else {
                    if (cursorIndex < MINIGAMES_PER_PAGE - 1) {
                        cursorIndex++;
                    } else {
                        cursorIndex = 0; //wrap around
                    }
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
        }
        //if swapped to last page, make sure cursor is set accordingly
        if (cursorIndex > 13 && pageIndex == MAX_PAGES - 1) {
            cursorIndex = 13; //wrap around
        }
        for (i = 0; i < MINIGAMES_PER_PAGE; i++) {
            s32 minigameIndex = pageIndex * MINIGAMES_PER_PAGE + i;

            if (minigameIndex >= MINIGAME_END -1) {
                continue;
            }
            curMinigameData = &minigameLUT[minigameIndex];
            minigameflag = GetMinigameFlag(curMinigameData->minigameIndex);

            if (minigameflag == 1) {
                mp3_debug_font_color = 12;
            } else {
                mp3_debug_font_color = 0;
            }

            if (cursorIndex == i) {
                mp3_debug_font_color = 5;
            }

            mp3_bzero(outputbuffer, sizeof(outputbuffer));
            to_uppercase(&curMinigameData->minigameStr[1], outputbuffer);
            mp3_DrawDebugText(xPos, yPos, outputbuffer);
            
            mp3_bzero(outputbuffer, sizeof(outputbuffer));
            mp3_sprintf(outputbuffer, "%d", curMinigameData->minigameIndex);
            mp3_DrawDebugText(10, yPos, outputbuffer);

            mp3_bzero(outputbuffer, sizeof(outputbuffer));
            mp3_sprintf(outputbuffer, "%d", minigameflag);
            mp3_DrawDebugText(45, yPos, outputbuffer);
            yPos += 10;
        }

        s32 minigameLutIndex = pageIndex * MINIGAMES_PER_PAGE + cursorIndex;
        if (minigameLutIndex < MINIGAME_END - 1) {
            if (mp3_D_800C9520 & 0x8000) {
                curMinigameData = &minigameLUT[minigameLutIndex];
                // Flip the current minigame flag
                FlipMinigameFlag(curMinigameData->minigameIndex);
            }
        }

        mp3_debug_font_color = 0;
        mp3_bzero(outputbuffer, sizeof(outputbuffer));
        mp3_sprintf(outputbuffer, "CURSOR: %d", cursorIndex);
        mp3_DrawDebugText(5, 193, outputbuffer); //193
        mp3_DrawDebugText(5, 203, "DPAD - SCROLL");  //203
        mp3_DrawDebugText(5, 213, "B - TOGGLE ALL"); //213
        mp3_DrawDebugText(5, 223, "A - TOGGLE MINIGAME"); //223
        

        //if B is pressed, turn all flags off
        if (mp3_D_800C9520 & 0x4000) {
            for (i = 0; i < MINIGAME_END; i++) {
                SetMinigameFlag(i, flipMinigameFlags);
            }
            flipMinigameFlags = !flipMinigameFlags;
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
