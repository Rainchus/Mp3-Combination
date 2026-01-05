#include "marioparty.h"
#include "mp3.h"

Gfx* mp3_WipeExecAlways(Gfx**);

Gfx* gfx_draw_textured_rectangle_rgba32(Gfx* gfx, int x, int y, int width, int height, u8* texture) {
    gDPPipeSync(gfx++);

    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height,
                        0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + width) << 2, (y + height) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(gfx++);
    return gfx;
}

Gfx* gfx_draw_textured_rectangle_rgba32_tiled(Gfx* gfx, int x, int y, int width, int height, u8* texture) {
    gDPPipeSync(gfx++);

    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);

    // TMEM is 4KB. For RGBA32 (4 bytes per pixel), max pixels = 4096 / 4 = 1024
    // We'll use 32-pixel wide tiles, allowing up to 32 rows per tile (32 * 32 = 1024 pixels)
    #define TILE_WIDTH 32
    #define MAX_TILE_HEIGHT 32

    for (int tile_y = 0; tile_y < height; tile_y += MAX_TILE_HEIGHT) {
        int current_tile_height = MAX_TILE_HEIGHT;
        if (tile_y + current_tile_height > height) {
            current_tile_height = height - tile_y;
        }

        for (int tile_x = 0; tile_x < width; tile_x += TILE_WIDTH) {
            int current_tile_width = TILE_WIDTH;
            if (tile_x + current_tile_width > width) {
                current_tile_width = width - tile_x;
            }

            // Calculate the offset into the texture for this tile
            u8* tile_texture = texture + ((tile_y * width) + tile_x) * 4;

            gDPLoadTextureTile(gfx++, tile_texture, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                               width, current_tile_height,  // stride is full width, height is tile height
                               0, 0,  // Start from 0,0 in the tile_texture pointer
                               current_tile_width - 1, current_tile_height - 1,
                               0,
                               G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            int screen_x = x + tile_x;
            int screen_y = y + tile_y;

            gSPTextureRectangle(gfx++,
                                screen_x << 2, screen_y << 2,
                                (screen_x + current_tile_width) << 2, (screen_y + current_tile_height) << 2,
                                G_TX_RENDERTILE,
                                0 << 5, 0 << 5,  // Texture coordinates start at 0,0 since we're loading from tile_texture
                                1 << 10, 1 << 10);
        }
    }

    gDPPipeSync(gfx++);
    return gfx;

    #undef TILE_WIDTH
    #undef MAX_TILE_HEIGHT
}

Gfx* gfx_draw_textured_rectangle_rgba32_tiled_scaled(Gfx* gfx, int x, int y, int width, int height, u8* texture, float scale_x, float scale_y) {
    gDPPipeSync(gfx++);

    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);

    // TMEM is 4KB. For RGBA32 (4 bytes per pixel), max pixels = 4096 / 4 = 1024
    // We'll use 32-pixel wide tiles, allowing up to 32 rows per tile (32 * 32 = 1024 pixels)
    #define TILE_WIDTH 32
    #define MAX_TILE_HEIGHT 32

    // Calculate texture step values (10.2 fixed point format)
    // These determine how much to step through the texture per screen pixel
    int dsdx = (int)((1.0f / scale_x) * (1 << 10));
    int dtdy = (int)((1.0f / scale_y) * (1 << 10));

    for (int tile_y = 0; tile_y < height; tile_y += MAX_TILE_HEIGHT) {
        int current_tile_height = MAX_TILE_HEIGHT;
        if (tile_y + current_tile_height > height) {
            current_tile_height = height - tile_y;
        }

        for (int tile_x = 0; tile_x < width; tile_x += TILE_WIDTH) {
            int current_tile_width = TILE_WIDTH;
            if (tile_x + current_tile_width > width) {
                current_tile_width = width - tile_x;
            }

            // Calculate the offset into the texture for this tile
            u8* tile_texture = texture + ((tile_y * width) + tile_x) * 4;

            gDPLoadTextureTile(gfx++, tile_texture, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                               width, current_tile_height,
                               0, 0,
                               current_tile_width - 1, current_tile_height - 1,
                               0,
                               G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            // Calculate scaled screen position for this tile
            int screen_x = x + (int)(tile_x * scale_x);
            int screen_y = y + (int)(tile_y * scale_y);
            int screen_x_end = x + (int)((tile_x + current_tile_width) * scale_x);
            int screen_y_end = y + (int)((tile_y + current_tile_height) * scale_y);

            gSPTextureRectangle(gfx++,
                                screen_x << 2, screen_y << 2,
                                screen_x_end << 2, screen_y_end << 2,
                                G_TX_RENDERTILE,
                                0 << 5, 0 << 5,
                                dsdx, dtdy);
        }
    }

    gDPPipeSync(gfx++);
    return gfx;

    #undef TILE_WIDTH
    #undef MAX_TILE_HEIGHT
}

extern void* tempDisplayTest;
extern void* tempDisplayTest1;
extern void* tempDisplayTest2;
extern void* tempDisplayTest3;

#define IMG_BASE_X 28
#define IMG_BASE_Y 128

// Gfx* drawFonts3(void) {
//     f32 xScale = 0.5f;
//     f32 yScale = 0.5f;

//     if (tempDisplayTest != NULL) {
//         mp3_gMainGfxPos = gfx_draw_textured_rectangle_rgba32_tiled_scaled(mp3_gMainGfxPos, BASE_X + (128/2 * 0), 20, 128, 96, tempDisplayTest, xScale, yScale);
//     }
    
//     return mp3_WipeExecAlways(&mp3_gMainGfxPos); //restore from hook
// }

// Define the structure to hold display information
typedef struct {
    void* imageData;
    s32 xPos;
    s32 yPos;
    s32 width;
    s32 height;
    f32 xScale;
    f32 yScale;
    s32 active;
} DisplayQueueItem;

#define MAX_DISPLAY_QUEUE 4
static DisplayQueueItem displayQueue[MAX_DISPLAY_QUEUE];
static s32 queueInitialized = FALSE;

// Initialize the queue (call this once at startup)
void InitDisplayQueue(void) {
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        displayQueue[i].imageData = NULL;
        displayQueue[i].active = FALSE;
        displayQueue[i].xPos = 0;
        displayQueue[i].yPos = 0;
        displayQueue[i].width = 128;
        displayQueue[i].height = 96;
        displayQueue[i].xScale = 0.5f;
        displayQueue[i].yScale = 0.5f;
    }
    queueInitialized = TRUE;
}

// Add an item to the display queue
s32 AddToDisplayQueue(void* imageData) {
    if (!queueInitialized) {
        InitDisplayQueue();
    }
    
    // Find first available slot
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        if (!displayQueue[i].active) {
            displayQueue[i].imageData = imageData;
            displayQueue[i].active = TRUE;
            
            // Calculate position based on slot index
            s32 column = i % 4;  // 0-3, wraps every 4
            s32 row = i / 4;     // 0 for first 4, 1 for next 4, etc.
            
            displayQueue[i].xPos = IMG_BASE_X + (128/2 * column);
            displayQueue[i].yPos = IMG_BASE_Y + (48 * row);
            
            displayQueue[i].width = 128;
            displayQueue[i].height = 96;
            displayQueue[i].xScale = 0.5f;
            displayQueue[i].yScale = 0.5f;
            return TRUE;
        }
    }
    
    return FALSE; // Queue full
}

// Remove an item from the display queue
void RemoveFromDisplayQueue(s32 index) {
    if (index >= 0 && index < MAX_DISPLAY_QUEUE) {
        if (displayQueue[index].imageData != NULL) {
            mp3_HuMemMemoryFreePerm(displayQueue[index].imageData);
            displayQueue[index].imageData = NULL;
        }
        displayQueue[index].active = FALSE;
    }
}

// Clear all items from queue
void ClearDisplayQueue(void) {
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        if (displayQueue[i].active && displayQueue[i].imageData != NULL) {
            mp3_HuMemMemoryFreePerm(displayQueue[i].imageData);
        }
        displayQueue[i].imageData = NULL;
        displayQueue[i].active = FALSE;
    }
}

// Updated draw function
Gfx* drawFonts3(void) {
    if (!queueInitialized) {
        InitDisplayQueue();
    }
    
    // Draw all active items in the queue
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        if (displayQueue[i].active && displayQueue[i].imageData != NULL) {
            mp3_gMainGfxPos = gfx_draw_textured_rectangle_rgba32_tiled_scaled(
                mp3_gMainGfxPos, 
                displayQueue[i].xPos, 
                displayQueue[i].yPos, 
                displayQueue[i].width, 
                displayQueue[i].height, 
                displayQueue[i].imageData, 
                displayQueue[i].xScale, 
                displayQueue[i].yScale
            );
        }
    }
    
    return mp3_WipeExecAlways(&mp3_gMainGfxPos);
}