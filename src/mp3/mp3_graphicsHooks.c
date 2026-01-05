#include "marioparty.h"
#include "mp3.h"

Gfx* mp3_WipeExecAlways(Gfx**);

Gfx* drawCi8Image(Gfx* gfx, int x, int y, int width, int height, u8* texture, u16* palette) {
    gDPPipeSync(gfx++);
    
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    
    // Load the 256-color palette
    gDPLoadTLUT_pal256(gfx++, palette);
    
    // Use LoadTextureTile instead of LoadTextureBlock for odd-sized textures
    gDPLoadTextureTile(gfx++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, 
                       width, height,
                       0, 0, width - 1, height - 1,
                       0,
                       G_TX_NOMIRROR, G_TX_NOMIRROR, 
                       G_TX_NOMASK, G_TX_NOMASK, 
                       G_TX_NOLOD, G_TX_NOLOD);
    
    // Draw the textured rectangle
    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + width) << 2, (y + height) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(gfx++);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    
    return gfx;
}

//has fix by claude, fixes black outline on images?
Gfx* drawCi4Image(Gfx* gfx, int x, int y, int width, int height, u8* texture, u16* palette) {
    gDPPipeSync(gfx++);
    
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPSetTextureFilter(gfx++, G_TF_POINT);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetBlendColor(gfx++, 0, 0, 0, 1);
    
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    
    gDPLoadTLUT_pal16(gfx++, 0, palette);
    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_CI, width, height, 0,
                           G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    
    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + width) << 2, (y + height) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(gfx++);
    return gfx;
}

Gfx* drawCi4ImageScaled(Gfx* gfx, int x, int y, int width, int height, 
                        u8* texture, u16* palette, float scaleX, float scaleY) {
    gDPPipeSync(gfx++);
    
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPSetTextureFilter(gfx++, G_TF_POINT);  // or G_TF_BILERP for smoother scaling
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetBlendColor(gfx++, 0, 0, 0, 1);
    
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    
    gDPLoadTLUT_pal16(gfx++, 0, palette);
    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_CI, width, height, 0,
                           G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    
    int dsdx = (int)((1 << 10) / scaleX);
    int dtdy = (int)((1 << 10) / scaleY);
    int scaledWidth = (int)(width * scaleX);
    int scaledHeight = (int)(height * scaleY);
    
    gSPTextureRectangle(gfx++, x << 2, y << 2, 
                        (x + scaledWidth) << 2, (y + scaledHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    gDPPipeSync(gfx++);
    return gfx;
}

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
    void* paletteData;
    s32 imageType; //RGBA32 = 0, RGBA16 = 1, etc.
    s32 xPos;
    s32 yPos;
    s32 width;
    s32 height;
    f32 xScale;
    f32 yScale;
    s32 active;
} DisplayQueueItem;

#define MAX_DISPLAY_QUEUE 8
DisplayQueueItem displayQueue[MAX_DISPLAY_QUEUE] = {0};
static s32 queueInitialized = FALSE;

// Update position of a specific queue item
void UpdateDisplayQueuePosition(s32 index, s32 xPos, s32 yPos) {
    if (index >= 0 && index < MAX_DISPLAY_QUEUE && displayQueue[index].active) {
        displayQueue[index].xPos = xPos;
        displayQueue[index].yPos = yPos;
    }
}

// Update scale of a specific queue item
void UpdateDisplayQueueScale(s32 index, f32 scaleX, f32 scaleY) {
    if (index >= 0 && index < MAX_DISPLAY_QUEUE && displayQueue[index].active) {
        displayQueue[index].xScale = scaleX;
        displayQueue[index].yScale = scaleY;
    }
}

// Get a reference to a queue item for direct manipulation
DisplayQueueItem* GetDisplayQueueItem(s32 index) {
    if (index >= 0 && index < MAX_DISPLAY_QUEUE && displayQueue[index].active) {
        return &displayQueue[index];
    }
    return NULL;
}

// Find index of an item by its imageData pointer (useful if you saved the pointer)
s32 FindDisplayQueueIndex(void* imageData) {
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        if (displayQueue[i].active && displayQueue[i].imageData == imageData) {
            return i;
        }
    }
    return -1;
}

// Initialize the queue (call this once at startup)
void InitDisplayQueue(void) {
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        displayQueue[i].imageData = NULL;
        displayQueue[i].paletteData = NULL;
        displayQueue[i].imageType = -1;
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
s32 AddToDisplayQueue(void* imageData, s32 imageType, s32 xPos, s32 yPos, s32 width, s32 height, f32 scaleX, f32 scaleY) {
    if (!queueInitialized) {
        InitDisplayQueue();
    }
    
    // Find first available slot
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        if (!displayQueue[i].active) {
            if (imageType == RGBA32 || imageType == RGBA16) {
                displayQueue[i].imageData = imageData;
                displayQueue[i].imageType = imageType;
            } else if (imageType == CI8 || imageType == CI4) {
                u32 paletteOffset = *(u32*)((u8*)imageData + 0xC); //gets offset 0xC (palette offset) from file
                u32 imgOffset = *(u32*)((u8*)imageData + 0x8); //gets offset 0x8 (image start) from file

                displayQueue[i].imageData = (u32)imageData + (u32)imgOffset;
                displayQueue[i].imageType = imageType;
                displayQueue[i].paletteData = (u32)imageData + (u32)paletteOffset;
            }

            displayQueue[i].active = TRUE;
            displayQueue[i].xPos = xPos;
            displayQueue[i].yPos = yPos;
            displayQueue[i].width = width;
            displayQueue[i].height = height;
            displayQueue[i].xScale = scaleX;
            displayQueue[i].yScale = scaleY;
            return i;
        }
    }
    
    return -1; // Queue full
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

Gfx* drawCi4ImageScaled(Gfx* gfx, int x, int y, int width, int height, 
                        u8* texture, u16* palette, float scaleX, float scaleY);

// Updated draw function
Gfx* drawFonts3(void) {
    if (!queueInitialized) {
        InitDisplayQueue();
    }
    
    // Draw all active items in the queue
    for (s32 i = 0; i < MAX_DISPLAY_QUEUE; i++) {
        if (displayQueue[i].active && displayQueue[i].imageData != NULL) {
            if (displayQueue[i].imageType == RGBA32) {
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
            } else if (displayQueue[i].imageType == CI8) {
                mp3_gMainGfxPos = drawCi8Image(
                    mp3_gMainGfxPos, 
                    displayQueue[i].xPos, 
                    displayQueue[i].yPos, 
                    displayQueue[i].width, 
                    displayQueue[i].height, 
                    displayQueue[i].imageData,
                    displayQueue[i].paletteData 
                    //displayQueue[i].xScale, 
                    //displayQueue[i].yScale
                );
            } else if (displayQueue[i].imageType == CI4) {
                mp3_gMainGfxPos = drawCi4ImageScaled(
                    mp3_gMainGfxPos, 
                    displayQueue[i].xPos, 
                    displayQueue[i].yPos, 
                    displayQueue[i].width, 
                    displayQueue[i].height, 
                    displayQueue[i].imageData,
                    displayQueue[i].paletteData, 
                    displayQueue[i].xScale, 
                    displayQueue[i].yScale
                );
            }
        }
    }
    
    return mp3_WipeExecAlways(&mp3_gMainGfxPos);
}