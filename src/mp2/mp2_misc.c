#include "mp2.h"

extern s8 D_800DF6C5_E02C5;
extern int mp2_sprintf(char *s, const char *fmt, ...);
void mp2_DrawDebugText(s32 xPos, s32 yPos, char* str);
void StringToUpper(char *str);

char* Mp2MinigameCategoryStrings[] = {
    "PLAYERS_4P",
    "PLAYERS_1V3",
    "PLAYERS_2V2",
    "PLAYERS_ITEM",
    "PLAYERS_BATTLE",
    "PLAYERS_DUEL"
};

void mp2_drawRecentMinigameListCategory(void) {
    s32 i, j;
    char buf[16];
    s32 y = 20;
    s8 category = D_800DF6C5_E02C5;
    char buffer[64];
    //mp3_fontcolor = FONT_PURPLE;
    mp2_sprintf(buf, "%s", Mp2MinigameCategoryStrings[category]);
    mp2_DrawDebugText(20, y, buf);
    y += 15;

    for (i = 0; i < 5; i++) {
        if (D_800DF690_E0290.recentMinigames[category][i] == -1 || D_800DF690_E0290.recentMinigames[category][i] == 0xFF) {
            mp2_DrawDebugText(20, y, "NONE");
            y += 10;
        } else {
            u8 minigame = D_800DF690_E0290.recentMinigames[category][i];
            MinigameIndexTable* minigameRef = NULL;
            for (j = 0; j < MINIGAME_END; j++) {
                if (minigame == minigameLUT[j].minigameIndex) {
                    minigameRef = &minigameLUT[j];
                    break;
                }
            }

            if (minigameRef != NULL) {
                //j+1 to skip \x0B byte. copy string to buffer
                for (j = 0; minigameRef->minigameStr[j+1] != '\0'; j++) {
                    buffer[j] = minigameRef->minigameStr[j+1];
                }
                buffer[j] = '\0';
                StringToUpper(buffer);
                mp2_DrawDebugText(20, y, buffer);
                y += 10;
            }
        }

    }
}

void mp2_drawDebug(void) {
    if (mp2_DrawPrevMinigameList == TRUE) {
        mp2_drawRecentMinigameListCategory();
    }
}