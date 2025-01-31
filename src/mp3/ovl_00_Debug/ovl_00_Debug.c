#include "marioparty.h"
#include "mp3.h"

#define MINIGAMES_PER_PAGE 16
#ifdef MP1
    #define MAX_PAGES 12
#else
    #define MAX_PAGES 9
#endif

#define BACKGROUND_IMAGE_ID 0x001E0005
#define MENU_BACKGROUND_IMAGE_ID 0x000E0024

#define MESSAGE_BOX_ID 0x00000090

#define EEPROM_ABS_POS 0x2C0
#define EEPROM_BLOCK_POS EEPROM_ABS_POS / EEPROM_BLOCK_SIZE

s32 pageIndex = 0;
s32 cursorIndex = 0;
s32 flipMinigameFlags = 0;
extern s32 eepType;
extern u8 mp3_D_800D09A8;
extern OSMesgQueue mp3_D_800CE1A0;
//unsure if this needs to be aligned, but it cant hurt
EepData customEepromData = {0};
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
extern MinigameIndexTable minigameLUT[];
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
    return (customEepromData.minigameFlags[arg0 / 8] >> (arg0 % 8)) & 1;
}

void SetMinigameFlag(s32 arg0, s32 value) {
    if (value) {
        // Set the bit (use OR to turn the bit on)
        customEepromData.minigameFlags[arg0 / 8] |= (1 << (arg0 % 8));
    } else {
        // Clear the bit (use AND with the complement to turn the bit off)
        customEepromData.minigameFlags[arg0 / 8] &= ~(1 << (arg0 % 8));
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

void InvalidEepDetected(s32 xPos, s32 yPos) {
    mp3_omOvlCallEx(0, 0, 0);
}

void PrintInvalidEepWarning(s32 xPos, s32 yPos) {
    while (1) {
        mp3_DrawDebugText(xPos, yPos, "INVALID SAVE TYPE FOUND");
        mp3_DrawDebugText(xPos, yPos + 10, "PLEASE SET THE SAVE TYPE TO");
        mp3_DrawDebugText(xPos, yPos + 20, "EEPROM 16KBIT");
        mp3_HuPrcVSleep();
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

typedef struct UnkEepStruct {
    char unk_00[0x10];
} UnkEepStruct;

s32 InitializeCustomEepromData(void) {
    return mp3_osEepromLongWrite(&mp3_D_800CE1A0, EEPROM_BLOCK_POS, (void*)&customEepromData, sizeof(customEepromData));
}

s32 WriteEepromCustom(void) {
    return mp3_osEepromLongWrite(&mp3_D_800CE1A0, EEPROM_BLOCK_POS, customEepromData.minigameFlags, sizeof(customEepromData.minigameFlags));
}

void newDebugMenuMain(void) {
    MinigameIndexTable* curMinigameData;
    char outputbuffer[40];
    // s32 eSprite0;
    s32 eSprite1;
    u8 minigameflag;
    s32 i;
    s32 eSpriteMainMenu;
    s32 eSpriteMp3TitleMenu;
    
    mp3_HuPrcVSleep();
    mp3_HuWipeFadeIn(0xFF, 0x10);
    // eSprite0 = DrawImageWrapper(BACKGROUND_IMAGE_ID, 160, 120);
    DrawImageWrapper(BACKGROUND_IMAGE_ID, 160, 120);
    
    mp3_HuAudSeqPlay(8);

    if (eepType != EEPROM_TYPE_16K) {
        s32 invalidEepBoxSpriteId = DrawImageWrapper(MESSAGE_BOX_ID, 0, 0);
        mp3_ScaleESprite(invalidEepBoxSpriteId, 1.25f, 1.0f);
        //mp3_Hu3dModelCreateWrapper(0x000200A2, 0x6A9); //create tumble model
        s32 xPos = 24;
        s32 yPos = 35;
        while (1) {
            mp3_func_8000BBD4_C7D4(invalidEepBoxSpriteId, xPos, yPos); //set sprite position
            mp3_debug_font_color = 9;
            PrintInvalidEepWarning(xPos + 27, yPos - 15);
            mp3_HuPrcVSleep();
        }
    }

    eSprite1 = DrawImageWrapper(MENU_BACKGROUND_IMAGE_ID, 200, 105);
    mp3_ScaleESprite(eSprite1, 1.70f, 1.0f);

    // eSpriteMainMenu = DrawImageWrapper(0x00110016, 154, 125);
    // mp3_ScaleESprite(eSpriteMainMenu, 1.0f, 1.0f);

    // eSpriteMp3TitleMenu = DrawImageWrapper(0x00100002, 160, 19);
    // mp3_ScaleESprite(eSpriteMp3TitleMenu, 0.5f, 0.5f);

    // while (1) {
    //     mp3_HuPrcVSleep();
    // }

    while (1) {
        s32 xPos = 105;
        s32 yPos = 23;
        s32 currentlyHeldButtons;
        #ifdef MP1
            s32 cursorIndexLastPageMax = 13;
        #else
            s32 cursorIndexLastPageMax = 9;
        #endif

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
                if (cursorIndex >= cursorIndexLastPageMax && pageIndex == MAX_PAGES - 1) {
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
                    cursorIndex = cursorIndexLastPageMax; //wrap around
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
                    cursorIndex = cursorIndexLastPageMax; //wrap around
                } else {
                    if (cursorIndex > 0) {
                        cursorIndex--;
                    } else {
                        cursorIndex = MINIGAMES_PER_PAGE - 1; //wrap around
                    }
                }
            } else if (mp3_D_800C9520 & 0x400) { //dpad down
                //hardcoded check for last page
                if (cursorIndex >= cursorIndexLastPageMax && pageIndex == MAX_PAGES - 1) {
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
        if (cursorIndex > cursorIndexLastPageMax && pageIndex == MAX_PAGES - 1) {
            cursorIndex = cursorIndexLastPageMax; //wrap around
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
        //mp3_sprintf(outputbuffer, "CURSOR: %d", cursorIndex);
        // mp3_DrawDebugText(5, 193, outputbuffer); //193
        mp3_DrawDebugText(5, 193, "START: SAVE"); //193
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
            //no idea what any of these args do
            char sp10[16] = {0};
            s16 temp = 0x20; 

            //why is it required you do this this way?
            //and why only when writing? reading works fine?
            mp3_RequestSIFunction(&sp10, &WriteEepromCustom, &temp, 1);
            ComboSwitchGameToMp3();
        }
        mp3_HuPrcVSleep();
    }
}
