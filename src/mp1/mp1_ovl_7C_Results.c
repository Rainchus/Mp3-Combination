#include "mp1.h"

void func_800F7754_UnknownResultsScreen(void);
void func_800F7A3C_UnknownResultsScreen(void);
void func_800F7A9C_UnknownResultsScreen(void);
void func_800F7F38_UnknownResultsScreen(void);
void func_800F82C4_UnknownResultsScreen(void);
extern void func_800F6688_UnknownResultsScreen(void);
extern void func_800F79C8_UnknownResultsScreen(void);
void func_800F8194_UnknownResultsScreen(void);
void mp1_func_80060128(s32);

void newfunc_800F65E0_UnknownResultsScreen(void) {
    mp1_omInitObjMan(0x14, 0x14);
    func_800F7F38_UnknownResultsScreen();
    func_800F7A9C_UnknownResultsScreen();
    func_800F7A3C_UnknownResultsScreen();
    func_800F8194_UnknownResultsScreen();
    func_800F82C4_UnknownResultsScreen();
    mp1_omAddPrcObj(func_800F7754_UnknownResultsScreen, 0x300, 0x2500, 0);
    mp1_func_80060128(0x16);
    mp1_omAddObj(5, 0, 0, -1, &func_800F79C8_UnknownResultsScreen);
    mp1_omAddObj(5, 0, 0, -1, &func_800F6688_UnknownResultsScreen);
}