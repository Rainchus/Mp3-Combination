#include "marioparty.h"
#include "mp3.h"

//for drawing 2d images to the screen on top of everything else

Gfx* gfx_draw_textured_rectangle(Gfx* gfx, int x, int y, int width, int height, u8* texture) {
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

Gfx* gfx_draw_textured_rectangle_rgba16(Gfx* gfx, int x, int y, int width, int height, u8* texture) {
    gDPPipeSync(gfx++);

    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height,
                        0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + width) << 2, (y + height) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(gfx++);
    return gfx;
}

Gfx* gfx_draw_rectangle(Gfx* gfx, int x, int y, int width, int height, u32 color) {
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++,0,0,(color >> 24) & 0xFF,(color >> 16) & 0xFF,(color >> 8) & 0xFF,color & 0xFF);
    gDPPipeSync(gfx++);
    gDPFillRectangle(gfx++,x,y,x + width, y + height);
    return gfx;
}

Gfx* drawCi4Image(Gfx* gfx, int x, int y, int width, int height, u8* texture, u16* palette) {
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, 0, G_ON);
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA , G_CC_DECALRGBA );
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPTileSync(gfx++);
    gDPSetTile(gfx++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_NOMIRROR, 5, 0, G_TX_NOMIRROR, 5, 0);
    gDPSetTileSize(gfx++, 0, 0, 0, (width - 1) << 2, (height - 1) << 2);
    gSPClearGeometryMode(gfx++, G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_SHADING_SMOOTH);
    gDPLoadTLUT_pal16(gfx++, 0, palette);
    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_CI,width,height,0,G_TX_NOMIRROR,G_TX_NOMIRROR,5,5,0,0);
    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + width) << 2, (y + height) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(gfx++);
    return gfx;
};

Gfx* drawFonts3(void) {
    return WipeExecAlways(&mp3_gMainGfxPos); //restore from hook
}