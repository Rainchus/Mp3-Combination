#include "marioparty.h"
#include "mp3.h"

#define COLD_BOOT 0
#define WARM_BOOT 1
#define osAppNmiBufferSize 64
#define EXTRA_FRAMES_BLACK_ON_BOOT 10

extern u8 mp3_osAppNmiBuffer[osAppNmiBufferSize];
extern u32 rnd_seed_shared;

s32 AddToDisplayQueue(void* imageData, s32 imageType, s32 xPos, s32 yPos, s32 width, s32 height, f32 scaleX, f32 scaleY);

void checkosAppNmiBufferReset(s32 resetType) {
    s32 i;

    if (resetType == COLD_BOOT) {
        for (i = 0; i < osAppNmiBufferSize; i++) {
            mp3_osAppNmiBuffer[i] = 0;
        }        
    }
}

//used for all 3 games sharing the same seed address
u8 rand8_Shared(void) {
    rnd_seed_shared = rnd_seed_shared * 0x41C64E6D + 0x3039;
    return ((rnd_seed_shared + 1) >> 16);
}

// Structure for RGBA pixel
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBAPixel;

void mp3_func_8006A370_6AF70(s32);
void mp3_func_80069E68_6AA68(void*);
void mp3_func_800698E8_6A4E8(void*, u16*, s32, void*);

// Function to convert HVQS texture to RGBA32
void* ConvertHVQSToRGBA(void* hvqmCompressed, void* hvqmData, void* alphaData) {
    u16* srcTexture;
    RGBAPixel* destTexture;
    void* tempBuffer;
    int pixelIndex;
    int x, y;
    u16 pixel16;
    u8* alphaPtr = (u8*)alphaData;
    u32 alphaOffset;
    
    // Allocate source texture buffer (16-bit, 128x96 = 24576 bytes)
    srcTexture = (u16*)mp3_HuMemMemoryAllocPerm(0x6000);
    
    // Setup HVQS decoding
    mp3_func_8006A370_6AF70(0xFF);
    mp3_func_80069E68_6AA68(hvqmCompressed);
    
    // Allocate temporary buffer for HVQS decoding
    tempBuffer = mp3_HuMemMemoryAllocPerm(0xC00);
    
    // Decode HVQS texture data into 16-bit format
    mp3_func_800698E8_6A4E8(hvqmData, srcTexture, 0x80, tempBuffer);
    
    // Free temporary buffer
    mp3_HuMemMemoryFreePerm(tempBuffer);
    
    // Allocate destination texture buffer (32-bit RGBA, 128x96x4 = 49152 bytes)
    destTexture = (RGBAPixel*)mp3_HuMemMemoryAllocPerm(0xC000);
    
    // Calculate alpha data offset
    // Original: arg3 + ((arg3->unkA << 0x10) + arg3->unkB)
    // This looks like it's reading a 32-bit offset from the alpha data header
    alphaOffset = *(u16*)((u8*)alphaData + 0xA);
    alphaPtr = (u8*)alphaData + alphaOffset;
    
    // Convert 16-bit RGB to 32-bit RGBA
    pixelIndex = 0;
    for (y = 0; y < 96; y++) {
        for (x = 0; x < 128; x++) {
            // Read 16-bit pixel
            pixel16 = srcTexture[pixelIndex];
            
            // Extract and expand RGB components (RGB555 format)
            destTexture[pixelIndex].r = (pixel16 >> 8) & 0xF8;
            destTexture[pixelIndex].g = (pixel16 >> 3) & 0xF8;
            destTexture[pixelIndex].b = (pixel16 << 2) & 0xF8;
            
            // Get alpha from separate alpha data
            destTexture[pixelIndex].a = alphaPtr[pixelIndex];
            
            pixelIndex++;
        }
    }
    
    // Free source texture
    mp3_HuMemMemoryFreePerm(srcTexture);
    
    return destTexture;
}

extern u16 mp3_player1pressedbuttons;

s32 frameCountWait = 0x0013;
s32 drawImages = 0;

void SetDrawImages(void) {
    drawImages = 1;
}

#define IMG_BASE_X 28
#define IMG_BASE_Y 128

s16 characterCursorPos[] = {
    IMG_BASE_X,
    IMG_BASE_X + 64,
    IMG_BASE_X + 128,
    IMG_BASE_X + 192
};

void UpdateDisplayQueuePosition(s32 index, s32 xPos, s32 yPos);

s8 characterCursorIdx[4] = {0, 1, 2, 3};

void newVoteSystem(void) {
    // void* image0;
    // void* image1;
    // void* image2;
    // void* minigameImages[4];
    // void* playerImages[4];
    // //s32 playerIdxInQueue[4];
    // s32 i;
    // s32 mainFS_ID = 0x00170048;
    
    // u16* playerPressedInputs = &mp3_player1pressedbuttons;
    
    // drawImages = 0;

    // image2 = mp3_DataRead(0x170007);
    // for (i = 0; i < 4; i++, mainFS_ID+= 2) {
    //     image0 = mp3_DataRead(mainFS_ID);
    //     image1 = mp3_DataRead(mainFS_ID+1);
    //     minigameImages[i] = ConvertHVQSToRGBA(image1, image0, image2);
    // }

    // while (drawImages == 0) {
    //     mp3_HuPrcVSleep();
    // }

    // for (i = 0; i < frameCountWait; i++) {
    //     mp3_HuPrcVSleep();
    // }

    // for (i = 0; i < 4; i++) {
    //     // Calculate position based on slot index
    //     s32 column = i % 4;  // 0-3, wraps every 4
    //     s32 row = i / 4;     // 0 for first 4, 1 for next 4, etc.

    //     s32 xPos = IMG_BASE_X + (128/2 * column);
    //     s32 yPos = IMG_BASE_Y + (48 * row);
    //     s32 width = 128;
    //     s32 height = 96;
    //     f32 scale = 0.5f;


    //     AddToDisplayQueue(minigameImages[i], RGBA32, xPos, yPos, width, height, scale, scale);
    // }

    // //now add player icons
    // mainFS_ID = 0x0012002D; //mario icon, 20x22

    // //basic thing for creating and moving character icons (maybe just swap to hand graphic that's used for items)
    // //also, this isn't perfect and has issues (such as not checking the player's port)
    // for (i = 0; i < 4; i++) {
    //     // Calculate position based on slot index
    //     s32 column = i % 4;  // 0-3, wraps every 4
    //     s32 row = i / 4;     // 0 for first 4, 1 for next 4, etc.

    //     s32 xPos = IMG_BASE_X + (128/2 * column);
    //     s32 yPos = IMG_BASE_Y + (48 * row);
    //     s32 width = 20;
    //     s32 height = 22;
    //     f32 scale = 1.0f;

    //     playerImages[i] = mp3_DataRead(mainFS_ID + mp3_GwPlayer[i].chr);
    //     //playerIdxInQueue[i] = AddToDisplayQueue(playerImages[i], CI8, xPos, yPos, width, height, scale, scale);
    // }

    // while (1) {
    //     // playerPressedInputs = &mp3_player1pressedbuttons;
    //     // for (i = 0; i < 4; i++, playerPressedInputs++) {
    //     //     if (*playerPressedInputs & 0x0100) { //right
    //     //         characterCursorIdx[i]++;
    //     //         if (characterCursorIdx[i] >= ARRAY_COUNT(characterCursorIdx)) {
    //     //             characterCursorIdx[i] = 0;
    //     //         }

    //     //     } else if (*playerPressedInputs & 0x0200) { //left
    //     //         characterCursorIdx[i]--;
    //     //         if (characterCursorIdx[i] < 0) {
    //     //             characterCursorIdx[i] = ARRAY_COUNT(characterCursorIdx) - 1;
    //     //         }
    //     //     }

    //     //     s32 column = i % 4;  // 0-3, wraps every 4
    //     //     s32 row = i / 4;     // 0 for first 4, 1 for next 4, etc.
    //     //     s32 xPos = characterCursorPos[characterCursorIdx[i]];
    //     //     s32 yPos = IMG_BASE_Y + (48 * row);

    //     //     UpdateDisplayQueuePosition(playerIdxInQueue[i], xPos, yPos);
    //     // }
        
    //     mp3_HuPrcVSleep();
    // }
}

//how mp4 let's player 1 choose a battle minigame
// BoardPickerCreate(currPlayer, 2, battleCursorPosTbl, var_r25);
// BoardPickerBackFlagSet(0);
// while (!BoardPickerDoneCheck()) {
//     HuPrcVSleep();
// }
// mgChoice = BoardPickerChoiceGet();

s32 mp3_func_80106B38_4F9028(s32);
void mp3_func_8005D294_5DE94(s16);

void func_80107730_4F9C20_Copy(s32 arg0, s32 messageID) {
    //i wanted to make this a choice textbox, but that's tricky
    //for now, it will say loading mario party 2 and then sleep for 1 second and load

    char newMessage[] = {"\x0B""Loading Mario Party 2""\xFF"};
    // char newMessage[] = {"\x0B""Huh""\xC3"" Do you want to swap to Mario Party 2""\xC3""\xFF"};
    // char newMessage[] = {"\x0B""Huh" "\xC3" " Do you want to swap to\nMario Party 2" "\xC3" "\x0C Yes\x0D   \x0C No\x0D"};
    u32 temp_v0; //pointer to message

    //Huh? My suggestion? textbox
    if (messageID == 0x3125) {
        mp3_func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, newMessage, -1, -1);
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INDEX_BOOT_VAL;
        CurBaseGame = MP2_BASE;
        mp3_HuPrcSleep(30);
        ComboSwitchGameToMp2();
        return;
    }

    mp3_func_8005D294_5DE94(mp3_D_80110998[arg0].unk_00);

    if (mp3_D_80110998[arg0].unk_04 != 0) {
        mp3_func_80019C00_1A800(mp3_D_80110998[arg0].unk_04);
        mp3_D_80110998[arg0].unk_04 = 0;
    }

    temp_v0 = mp3_func_80106B38_4F9028(messageID);

    //pointer check
    if (temp_v0 > 0x80000000U) {
        mp3_D_80110998[arg0].unk_04 = temp_v0;
    }

    mp3_func_8005B43C_5C03C(mp3_D_80110998[arg0].unk_00, (char*)temp_v0, -1, -1);
}


typedef struct {
    s32 unk00;
    u16 unk04;
    s32 unk08;
    OSMesgQueue *unk0C;
    s32 unk10; // OSMesg to send to unk0C
} graphicsMessage; // OSMesg

typedef struct combinedStruct {
    OSTask task;
    OSMesgQueue mesgQueue;
} swapChainTaskQueue;

void func_8000F024_FC24(void**, u16, u16); // Init graphics frame buffer pool                        
void func_8000F04C_FC4C(u64**); // Set gThreadStacks
void func_8000F088_FC88(s32*); // Set graphics state
void func_8000F094_FC94(u32); // Set unk swap chain state
void func_8000EBEC_F7EC(void*); // Swap Chain Loop

/* TODO: Where is the libultra header for this? */
extern void		*osViGetCurrentFramebuffer(void);
extern void		*osViGetNextFramebuffer(void);
extern void		osViSwapBuffer(void *);
extern void		osViBlack(u8);
extern void		osViSetYScale(f32);

// TODO: Move to respective header files
typedef struct {
    s32 unk00;
    OSMesgQueue *unk04;
    s32 unk08;
} unkSchedStruct;

typedef struct {
    u8 unk00[0x20];
} unkGraphicsMessage2; // OSMesg


void mp3_AddSchedulerClient(unkSchedStruct*, OSMesgQueue*, s32);
void func_8004D85C_4E45C();
void func_8004D878_4E478();


extern swapChainTaskQueue swapChainTask;
extern OSThread swapChainThread;
extern u8 swapChainStack[];

extern graphicsMessage gMesgRingBuffer[0x40];
extern s16 ringBufferIndex;

extern void **frameBufferPool;
extern u16 frameBufferCount;
extern u16 frameBufferSegmentID;

extern u64 *gThreadOutStackSize;
extern u64 *gThreadYieldStack;
extern u64 *gThreadOutStack;
extern u64 *gThread3Stack;

extern Gfx gTaskDataPointers[];

extern s32 D_800CC0A4_CCCA4;
extern void *nextFrameBuffer;
extern void *currFrameBuffer;

extern s32 *gUCodeAddresses;
extern u32 D_800B19A0_B25A0; // message count?


extern OSMesgQueue gSwapChainMesgQueue;
extern void* gSwapChainInitMesg;
extern s16 gSwapChainMesgTotal;

extern OSMesgQueue gMesgQueue;
extern void* gMesgQueueInitMesg;

extern u32 D_800D2094_D2C94; // Unk
extern OSMesgQueue D_800CC3C0_CCFC0; // Another system's message queue

extern void		mp3_osViSetYScale(f32);
extern void		mp3_osCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);
extern s32		mp3_osRecvMesg(OSMesgQueue *, OSMesg *, s32);
void* func_8000EB60_F760(void);
extern s32		mp3_osSendMesg(OSMesgQueue *, OSMesg, s32);
extern OSIntMask	mp3_osGetIntMask(void);
extern OSIntMask	mp3_osSetIntMask(OSIntMask);
void mp3_osViSwapBuffer(void*);
extern void		mp3_osViBlack(u8);

/* Swap Chain Loop */
void func_8000EBEC_F7EC(void* arg0) {
    unkSchedStruct sp10;
    OSMesgQueue mesgQueue;
    unkGraphicsMessage2 sp38;
    unkSchedStruct sp58;
    OSMesgQueue mesgQueue2;
    unkGraphicsMessage2 sp68;
    graphicsMessage* recvdMesg;
    void* pAvailableFrameBuffer;
    s32 var_s4;
    u32 i;

    swapChainTaskQueue *pSwapChain;
    OSTask *pTask;

    recvdMesg = NULL;
    pSwapChain = &swapChainTask;
    pTask = &swapChainTask.task;
    var_s4 = 0;

    mp3_osCreateMesgQueue(&mesgQueue, (OSMesg*) &sp38, 8);
    mp3_AddSchedulerClient(&sp10, &mesgQueue, 1);
    mp3_osCreateMesgQueue(&mesgQueue2, (OSMesg*) &sp68, 8);
    mp3_AddSchedulerClient(&sp58, &mesgQueue2, 2);
    
    while (TRUE) {
        do {
            recvmesg:
            mp3_osRecvMesg(&mesgQueue, NULL, 1);
            if (mp3_osRecvMesg(&mesgQueue2, NULL, 0) == 0) { while (TRUE); } // Infinite loop?
            if ((D_800D2094_D2C94 - var_s4) < D_800B19A0_B25A0) {
                goto recvmesg;
            }
    
            var_s4 = D_800D2094_D2C94;
            func_8004D85C_4E45C();
            pAvailableFrameBuffer = (void *) func_8000EB60_F760();
        } while (pAvailableFrameBuffer == NULL);

        currFrameBuffer = nextFrameBuffer;
        nextFrameBuffer = pAvailableFrameBuffer;

        /* Need redundant do for regalloc? */
        do { do {

            mp3_osRecvMesg(&gSwapChainMesgQueue, (OSMesg) &recvdMesg, 1);
            if (mp3_osRecvMesg(&mesgQueue2, NULL, 0) == 0) {
                while (TRUE);
            } else {
                u32 intMask;
                Gfx *dl = gTaskDataPointers;
                gSPSegment(dl++, frameBufferSegmentID, pAvailableFrameBuffer);
                gSPBranchList(dl++, recvdMesg->unk00);
                pSwapChain->mesgQueue.fullqueue = (void *) recvdMesg->unk08;
                pTask->t.dram_stack = gThread3Stack;
                pTask->t.output_buff = gThreadOutStack;
                pTask->t.output_buff_size = gThreadOutStackSize;
                pTask->t.yield_data_ptr = gThreadYieldStack;
                pTask->t.ucode =      (u64 *) *(   (recvdMesg->unk04* 2)      + gUCodeAddresses); // offset     (data pairs?)
                pTask->t.ucode_data = (u64 *) *( ( (recvdMesg->unk04* 2) | 1) + gUCodeAddresses); // offset + 1
    
                mp3_osSendMesg(&D_800CC3C0_CCFC0, (OSMesg) pSwapChain, 1);
                mp3_osRecvMesg(&gMesgQueue, NULL, 1);
    
                intMask = mp3_osSetIntMask(1);
                gSwapChainMesgTotal -= 1;
                mp3_osSetIntMask(intMask);
    
                if (recvdMesg->unk0C != NULL) {
                    mp3_osSendMesg(recvdMesg->unk0C, (OSMesg) recvdMesg->unk10, 1);
                }            
            }

        } while (!((s32) recvdMesg->unk08 & 1)); } while (FALSE);
    
        for (i = 1; i < D_800B19A0_B25A0; i++) {
            mp3_osRecvMesg(&mesgQueue, NULL, 1);
        }
    
        mp3_osViSwapBuffer(pAvailableFrameBuffer);
        //@patch: black the screen for a few extra frames on boot when specific overlays (prevents visual glitches)
        if (mp3_omovlhis[mp3_omovlhisidx].overlayID == OVL_GAME_END_SCENE ||
            mp3_omovlhis[mp3_omovlhisidx].overlayID == OVL_RESULTS_SCENE ||
            //mp3_omovlhis[mp3_omovlhisidx].overlayID == mgresultboard ||
            mp3_omovlhis[mp3_omovlhisidx].overlayID == OVL_LAST_5_TURNS) {
            if (D_800CC0A4_CCCA4 < EXTRA_FRAMES_BLACK_ON_BOOT) {
                if (D_800CC0A4_CCCA4 == 0) {
                    if (mp3_osRecvMesg(&mesgQueue2, NULL, 0) == 0) { while (TRUE); }
                    mp3_osViSetYScale(1.0f);
                } else {
                    mp3_osViBlack(1);
                }
            } else if ( D_800CC0A4_CCCA4 == EXTRA_FRAMES_BLACK_ON_BOOT) {
                if (mp3_osRecvMesg(&mesgQueue2, NULL, 0) == 0) { while (TRUE); }
                mp3_osViSetYScale(1.0f);
                mp3_osViBlack(0);
            }
        } else if (D_800CC0A4_CCCA4 == 0) {
            if (mp3_osRecvMesg(&mesgQueue2, NULL, 0) == 0) { while (TRUE); }
            mp3_osViSetYScale(1.0f);
            mp3_osViBlack(0);
        }
        
        D_800CC0A4_CCCA4++;
        func_8004D878_4E478(); // empty function
    }
}

void func_8004B1AC(void);
extern s32 mp3_DrawPrevMinigameList;
extern s8 D_80102C0D_11682D_shared_board;

char* Mp3MinigameCategoryStrings[] = {
    "PLAYERS_4P",
    "PLAYERS_1V3",
    "PLAYERS_2V2",
    "PLAYERS_ITEM",
    "PLAYERS_BATTLE",
    "PLAYERS_DUEL"
};

void StringToUpper(char *str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str -= 32;
        }
        str++;
    }
}

enum FONT_COLORS {
    FONT_BLACK = 0,
    FONT_DARK_BLUE,
    FONT_DARK_RED,
    FONT_DARK_PURPLE,
    FONT_DARK_GREEN,
    FONT_DARK_CYAN,
    FONT_DARK_YELLOW,
    FONT_DARK_GRAY,
    FONT_LIGHT_GRAY,
    FONT_BLUE,
    FONT_RED,
    FONT_PURPLE,
    FONT_LIGHT_GREEN,
    FONT_CYAN,
    FONT_YELLOW,
    FONT_WHITE
};

extern s32 mp3_fontcolor;

void drawRecentMinigameListCategory(void) {
    s32 i, j;
    char buf[16];
    s32 y = 20;
    s8 category = D_80102C0D_11682D_shared_board;
    char buffer[64];
    mp3_fontcolor = FONT_PURPLE;
    mp3_sprintf(buf, "%s", Mp3MinigameCategoryStrings[category]);
    mp3_DrawDebugText(20, y, buf);
    y += 15;

    for (i = 0; i < 10; i++) {
        if (D_800CC4A0_CD0A0.recentMinigames[category][i] == -1 || D_800CC4A0_CD0A0.recentMinigames[category][i] == 0xFF) {
            mp3_DrawDebugText(20, y, "NONE");
            y += 10;
        } else {
            u8 minigame = D_800CC4A0_CD0A0.recentMinigames[category][i];
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
                mp3_DrawDebugText(20, y, buffer);
                y += 10;
            }
        }

    }
}

void drawDebug(void) {
    func_8004B1AC(); //restore from hook
    if (mp3_DrawPrevMinigameList == TRUE) {
        drawRecentMinigameListCategory();
    }
}