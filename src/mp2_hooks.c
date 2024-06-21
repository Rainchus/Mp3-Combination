#include "ultra64.h"
#include "PR/os_eeprom.h"
#include "macros.h"
#include "marioparty.h"

extern s32 loadingBackFromMinigame;

#define NEW_EEP_OFFSET 0x600

#define EEP_BLOCK_OFFSET NEW_EEP_OFFSET / EEPROM_BLOCK_SIZE

extern u8 mp2_HUDSON_Header[];
extern u8 eepromBuffer[(EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)];
//u8 eepromBuffer[(EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)];
extern OSMesgQueue mp2_D_800FA5E0;

typedef struct unkfunc_8001AFD8 {
    s16 unk0;
    struct unkfunc_8001AFD8* unk4; //is this correct?
    s16 unk8;
} unkfunc_8001AFD8;

typedef struct unkfunc_8007EE0C {
    void* GetEepTypeFunc; //func pointer
    unkfunc_8001AFD8* unk4; //is this correct?
    s32 unk8;
    OSMesgQueue* mesgQueue;
} unkfunc_8007EE0C;

typedef struct UnkEep {
    u16 unk0;
    char unk2[2];
    u8* unk4;
    u16 unk8;
} UnkEep;

void mp2_bcopy(u8*, u8*, u16);

s32 GetEepType(s8** arg0) {
    s16 eepromProbeResult;
    s32 var_s1;
    s16 i;

    var_s1 = 0;
    eepromProbeResult = mp2_osEepromProbe(&mp2_D_800FA5E0);
    if ((eepromProbeResult) == 0) {
        for (i = 0; i < 4; i++) {
            eepromProbeResult = mp2_osEepromProbe(&mp2_D_800FA5E0);
            if (eepromProbeResult != 0) {
                break;
            }
        }

        if (i == 4) {
            return EEPROM_TYPE_4K;
        }
    }

    //ASSERT(eepromProbeResult == EEPROM_TYPE_4K);

    if (mp2_osEepromLongRead(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, eepromBuffer, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        //return EEPROM_TYPE_16K;
    }

    i = 1;
    if (mp2_HUDSON_Header[i] != 0) {
        while (1) {
            if (eepromBuffer[i] != mp2_HUDSON_Header[i]) {
                var_s1 = 1;
                //Write "HUDSON\0\0" header
                for (i = 0; i < 8; i++) {
                    eepromBuffer[i] = mp2_HUDSON_Header[i];
                }

                for (i = 8; i < EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE; i++) {
                    eepromBuffer[i] = 0;
                }

                //write actual save data (write all eeprom blocks except first)
                if (mp2_osEepromLongWrite(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET + 1, &eepromBuffer[8], (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - EEPROM_BLOCK_SIZE) != 0) {
                    //return EEPROM_TYPE_16K;
                }
                //write "HUDSON\0\0" header (only write 1 eeprom block)
                if (mp2_osEepromLongWrite(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, &eepromBuffer[0], EEPROM_BLOCK_SIZE) == 0) {
                    **arg0 = var_s1;
                    return 0;
                }
                //return EEPROM_TYPE_16K;
            }      
            i++;
            if (mp2_HUDSON_Header[i] == 0) {
                break;
            }
        }
    }
    **arg0 = var_s1;
    return 0;
}

s32 func_8001AEDC_1BADC(unkfunc_8001AFD8* arg0) {
    unkfunc_8007EE0C sp10;
    unkfunc_8001AFD8* sp20 = arg0; //?

    return mp2_func_8007ee0c_7fa0c(&sp10, &GetEepType, &sp20, 1);
}

s32 func_8001AF0C_1BB0C(UnkEep* arg0) {
    u8 eepromBlockOffset;
    u8 eepromBufferOffset;
    s16 i;
    s32 alignmentOffset;
    s32 size;

    if (arg0->unk0 >= 8) {
            for (i = 0; i < arg0->unk8; i++) {
                if (arg0->unk0 + i >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
                    break;
                }
                eepromBuffer[arg0->unk0 + i] = arg0->unk4[i];
            }
        
        
        eepromBlockOffset = (arg0->unk0 / EEPROM_BLOCK_SIZE);
        eepromBufferOffset = eepromBlockOffset;
        eepromBlockOffset = eepromBlockOffset + EEP_BLOCK_OFFSET;
        alignmentOffset = arg0->unk0 & 7;
        size = (arg0->unk8 + alignmentOffset + 7) & 0xFFF8;
        return (mp2_osEepromLongWrite(&mp2_D_800FA5E0, eepromBlockOffset, &eepromBuffer[eepromBufferOffset * EEPROM_BLOCK_SIZE], size) != 0) * 2;
    }
    return 2;
}

void func_8001AFD8_1BBD8(s32 arg0, unkfunc_8001AFD8* arg1, s16 arg2) {
    unkfunc_8007EE0C sp10;
    unkfunc_8001AFD8 sp20;

    sp20.unk0 = arg0 + 8;
    sp20.unk4 = arg1;
    sp20.unk8 = arg2;

    mp2_func_8007ee0c_7fa0c(&sp10, func_8001AF0C_1BB0C, &sp20, 1);
}

s32 func_8001B014_1BC14(UnkEep* arg0) {
    if (mp2_osEepromLongRead(&mp2_D_800FA5E0, EEP_BLOCK_OFFSET, eepromBuffer, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) != 0) {
        return 2;
    }
    mp2_bcopy(&eepromBuffer[arg0->unk0], arg0->unk4, arg0->unk8);
    return 0;
}

void func_8001B078_1BC78(s32 arg0, unkfunc_8001AFD8* arg1, s16 arg2) {
    unkfunc_8007EE0C sp10;
    unkfunc_8001AFD8 sp20;

    sp20.unk0 = arg0 + 8;
    sp20.unk4 = arg1;
    sp20.unk8 = arg2;

    mp2_func_8007ee0c_7fa0c(&sp10, func_8001B014_1BC14, &sp20, 1);
}

s32 func_8001B0B4_1BCB4(void) {
    return (mp2_osEepromWrite(&mp2_D_800FA5E0, 0, &mp2_HUDSON_Header[1]) != 0) * 2;
}

s32 func_8001B0E8_1BCE8(unkfunc_8001AFD8* arg0) {
    unkfunc_8007EE0C sp10;

    return mp2_func_8007ee0c_7fa0c(&sp10, &func_8001B0B4_1BCB4, 0, 1);
}

s32 GetSaveFileChecksum(u16 checksumAddrOffset, u16 size) {
    u16 offset;
    u16 checksumTotal;

    checksumTotal = 0;
    checksumAddrOffset += 8;

    while (size--) {
        offset = checksumAddrOffset;
        checksumAddrOffset++;
        checksumTotal += eepromBuffer[offset];
        if ((checksumAddrOffset) >= (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE)) {
            break;
        }
    }
    return checksumTotal;
}


u16 func_8007DC50_7E850(void) {
    return GetSaveFileChecksum(NEW_EEP_OFFSET, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - 0x10);
}

u16 func_80068720_69320(void) {
    return GetSaveFileChecksum(NEW_EEP_OFFSET, (EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE) - 0x10);
}


u8 fourPlayerMinigamesSet0[] = {0x15, 0x16, 0x17, 0x18, 0x19, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2C};
u8 fourPlayerMinigamesSet1[] = {0x15, 0x19, 0x1C, 0x1D, 0x1E, 0x21, 0x22, 0x26, 0x28};


//80100DC0
u8 oneVersusThreeMinigamesSet0[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
u8 oneVersusThreeMinigamesSet1[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

//800DFC1C

//800DFFD4 minigame message IDs set here

typedef struct ovlTableCustom {
    u16 overlayID;
    u16 unk2;
    u32 unk4;
    u16 unk8;
    u32 entryPointer;
} ovlTableCustom;

extern u16 D_800F93C6;
extern u16 D_800F93C8;

extern mp2_PlayerData debug_gPlayers[4];
extern s32 mp2_OverlayToLoad;

enum overlayBaseID {
   DEBUG = 0x00,
   BOWSERSLOTS = 0x01,
   ROLLOUTTHEBARRELS = 0x02,
   COFFINCONGESTION = 0x03,
   HAMMERSLAMMER = 0x04,
   GIVEMEABRAKE = 0x05,
   MALLETGOROUND = 0x06,
   GRABBAG = 0x07,
   LAVATILEISLE = 0x08,
   BUMPERBALLOONCARS = 0x09,
   RAKINEMIN = 0x0A,
   DAYATTHERACES = 0x0B,
   HOTROPEJUMP = 0x0C,
   HOTBOBOMB = 0x0D,
   BOWLOVER = 0x0E,
   RAINBOWRUN = 0x0F,
   CRANEGAME = 0x10,
   MOVETOTHEMUSIC = 0x11,
   BOBOMBBARRAGE = 0x12,
   LOOKAWAY = 0x13,
   SHOCKDROPORROLL = 0x14,
   LIGHTSOUT = 0x15,
   FILETRELAY = 0x16,
   ARCHERIVAL = 0x17,
   TOADBANDSTAND = 0x18,
   BOBSLEDRUN = 0x19,
   HANDCARHAVOC = 0x1A,
   BALLONBURST = 0x1B,
   SKYPILOTS = 0x1C,
   SPEEDHOCKEY = 0x1D,
   CAKEFACTORY = 0x1E,
   DUNGEONDASH = 0x1F,
   MAGNETCARTA = 0x20,
   FACELIFT = 0x21,
   SHELLSHOCKED = 0x22,
   CRAZYCUTTERS = 0x23,
   TOADINTHEBOX = 0x24,
   MECHAMARATHON = 0x25,
   ROLLCALL = 0x26,
   ABANDONSHIP = 0x27,
   PLATFORMPERIL = 0x28,
   TOTEMPOLEPOUND = 0x29,
   BUMPERBALLS = 0x2A,
   BOMBSAWAY = 0x2B,
   TIPSYTOURNEY = 0x2C,
   HONEYCOMBHAVOC = 0x2D,
   HEXAGONHEAT = 0x2E,
   SKATEBOARDSCAMPER = 0x2F,
   SLOTCARDERBY = 0x30,
   SHYGUYSAYS = 0x31,
   SNEAKNSNORE = 0x32,
   DRIVERSED = 0x33,
   CHANCETIME = 0x34,
   LOONEYLUMBERJACKS = 0x35,
   DIZZYDANCING = 0x36,
   TILEDRIVER = 0x37,
   QUICKSANDCACHE = 0x38,
   BOWSERSBIGBLAST = 0x39,
   TORPEDOTARGETS = 0x3A,
   DESTRUCTIONDUET = 0x3B,
   DEEPSEASALVAGE = 0x3C,
   NAME_3D = 0x3D,
   NAME_3E = 0x3E,
   DESERTDUEL = 0x3F,
   LAST5TURNS = 0x40,
   NAME_41 = 0x41,
   PIRATEDUEL = 0x42,
   NAME_43 = 0x43,
   NAME_44 = 0x44,
   NAME_45 = 0x45,
   NAME_46 = 0x46,
   NAME_47 = 0x47,
   NAME_48 = 0x48,
   NAME_49 = 0x49,
   NAME_4A = 0x4A,
   NAME_4B = 0x4B,
   NAME_4C = 0x4C,
   RULESLAND = 0x4D,
   NAME_4E = 0x4E,
   NAME_4F = 0x4F,
   NAME_50 = 0x50,
   NAME_51 = 0x51,
   NAME_52 = 0x52,
   NAME_53 = 0x53,
   NAME_54 = 0x54,
   NAME_55 = 0x55,
   NAME_56 = 0x56,
   NAME_57 = 0x57,
   NAME_58 = 0x58,
   NAME_59 = 0x59,
   NAME_5A = 0x5A,
   NAME_5B = 0x5B,
   NAME_5C = 0x5C,
   NAME_5D = 0x5D,
   NAME_5E = 0x5E,
   NAME_5F = 0x5F,
   NAME_60 = 0x60,
   NAME_61 = 0x61,
   NAME_62 = 0x62,
   NAME_63 = 0x63,
   NAME_64 = 0x64,
   NAME_65 = 0x65,
   NAME_66 = 0x66,
   NAME_67 = 0x67,
   NAME_68 = 0x68,
   NAME_69 = 0x69,
   NAME_6A = 0x6A,
   NAME_6B = 0x6B,
   NAME_6C = 0x6C,
   NAME_6D = 0x6D,
   NAME_6E = 0x6E,
   NAME_6F = 0x6F,
   NAME_70 = 0x70,
   NAME_71 = 0x71,
   NAME_72 = 0x72,
};

ovlTableCustom ovl_table_custom[] = {
	{0x0001, 0x0B00, 0x00000001, 0x0064, 0x80107138},
	{0x0002, 0x0B00, 0x00000002, 0x0064, 0x80107120},
	{0x0003, 0x0B00, 0x00000003, 0x0064, 0x8010710C},
	{0x0004, 0x0B00, 0x00000004, 0x0064, 0x801070F8},
	{0x0005, 0x0B00, 0x00000005, 0x0064, 0x801070E4},
	{0x0006, 0x0B00, 0x00000006, 0x0064, 0x801070D0},
	{0x0007, 0x0B00, 0x00000007, 0x0064, 0x801070B4},
	{0x0025, 0x0B00, 0x00000008, 0x0064, 0x801070A0},
	{0x0008, 0x0B00, 0x00000009, 0x0064, 0x80107084},
	{0x0009, 0x0B00, 0x0000000A, 0x0064, 0x80107068},
	{0x000B, 0x0B00, 0x0000000B, 0x0064, 0x80107054},
	{0x0026, 0x0B00, 0x0000000C, 0x0064, 0x8010703C},
	{0x000E, 0x0B00, 0x0000000D, 0x0064, 0x80107020},
	{0x000F, 0x0B00, 0x0000000E, 0x0064, 0x8010700C},
	{0x0010, 0x0B00, 0x0000000F, 0x0064, 0x80106FF4},
	{0x0011, 0x0B00, 0x00000010, 0x0064, 0x80106FD8},
	{0x0012, 0x0B00, 0x00000011, 0x0064, 0x80106FC4},
	{0x0013, 0x0B00, 0x00000012, 0x0064, 0x80106FB0},
	{0x0014, 0x0B00, 0x00000013, 0x0064, 0x80106F98},
	{0x0015, 0x0B00, 0x00000014, 0x0064, 0x80106F80},
	{0x0016, 0x0B00, 0x00000015, 0x0064, 0x80106F6C},
	{0x0017, 0x0B00, 0x00000016, 0x0064, 0x80106F4C},
	{0x0018, 0x0B00, 0x00000017, 0x0064, 0x80106F38},
	{0x001A, 0x0B00, 0x00000018, 0x0064, 0x80106F20},
	{0x001B, 0x0B00, 0x00000019, 0x0064, 0x80106F08},
	{0x001C, 0x0B00, 0x0000001A, 0x0064, 0x80106EF8},
	{0x001E, 0x0B00, 0x0000001B, 0x0064, 0x80106EE0},
	{0x001F, 0x0B00, 0x0000001C, 0x0064, 0x80106ED0},
	{0x0020, 0x0B00, 0x0000001D, 0x0064, 0x80106EBC},
	{0x0021, 0x0B00, 0x0000001E, 0x0064, 0x80106EA8},
	{0x0023, 0x0B00, 0x0000001F, 0x0064, 0x80106E94},
	{0x0024, 0x0B00, 0x00000020, 0x0064, 0x80106E78},
	{0x000C, 0x0B00, 0x00000021, 0x0064, 0x80106E64},
	{0x0027, 0x0B00, 0x00000022, 0x0064, 0x80106E50},
	{0x000D, 0x0B00, 0x00000023, 0x0064, 0x80106E38},
	{0x0028, 0x0B00, 0x00000024, 0x0064, 0x80106E24},
	{0x0029, 0x0B00, 0x00000025, 0x0064, 0x80106E0C},
	{0x002A, 0x0B00, 0x00000026, 0x0064, 0x80106DFC},
	{0x002B, 0x0B00, 0x00000027, 0x0064, 0x80106DE8},
	{0x002C, 0x0B00, 0x00000028, 0x0064, 0x80106DD0},
	{0x002D, 0x0B00, 0x00000029, 0x0064, 0x80106DC0},
	{0x002E, 0x0B00, 0x0000002A, 0x0064, 0x80106DAC},
	{0x0030, 0x0B00, 0x0000002B, 0x0064, 0x80106D98},
	{0x0031, 0x0B00, 0x0000002C, 0x0064, 0x80106D80},
	{0x0032, 0x0B00, 0x0000002D, 0x0064, 0x80106D74},
	{0x0033, 0x0B00, 0x0000002E, 0x0064, 0x80106D64},
	{0x0034, 0x0B00, 0x0000002F, 0x0064, 0x80106D50},
	{0x0035, 0x0B00, 0x00000030, 0x0064, 0x80106D3C},
	{0x0036, 0x0B00, 0x00000031, 0x0064, 0x80106D28},
	{0x0037, 0x0B00, 0x00000032, 0x0064, 0x80106D14},
	{0x0039, 0x0B00, 0x00000033, 0x0064, 0x80106D00},
	{0x003A, 0x0B00, 0x00000034, 0x0064, 0x80106CF0},
	{0x003B, 0x0B00, 0x0000003F, 0x0064, 0x80106CD8},
	{0x003C, 0x0B00, 0x00000042, 0x0064, 0x80106CC0},
	{0x003D, 0x0B00, 0x00000044, 0x0064, 0x80106CA8},
	{0x003E, 0x0B00, 0x00000046, 0x0064, 0x80106C94},
	{0x003F, 0x0B00, 0x00000048, 0x0064, 0x80106C7C},
	{0x0040, 0x0B00, 0x0000004A, 0x0064, 0x80106C68},
	{0x0042, 0x0B00, 0x00000035, 0x0064, 0x80106C50},
	{0x0045, 0x0B00, 0x00000036, 0x0064, 0x80106C3C},
	{0x0046, 0x0B00, 0x00000037, 0x0064, 0x80106C28},
	{0x0047, 0x0B00, 0x00000038, 0x0064, 0x80106C10},
	{0x0041, 0x0B00, 0x00000039, 0x0064, 0x80106BF8},
	{0x0043, 0x0B00, 0x0000003A, 0x0064, 0x80106BE0},
	{0x0044, 0x0B00, 0x0000003B, 0x0064, 0x80106BCC},
	{0x0048, 0x0B00, 0x0000003C, 0x0064, 0x80106BB4}
};

s32 check = 0;

// void LoadMinigameFromBoot(s32 arg0, s32 arg1, s32 arg2) {
//     if (mp2_OverlayToLoad == -1) {
//         //original code
//         //can load either corrupt save data screen or boot logos
//         // mp2_omOvlCallEx(arg0, arg1, arg2);
//     } else if (check == 1) {
//         ComboSwitchGameToMp3(); //doesn't return
//     } else if (check == 0) { 
//         D_800F93C8 = ovl_table_custom[mp2_OverlayToLoad].overlayID;
//         D_800F93C6 = 0;
//         CopyMp3_gPlayerCopy_To_Mp2();
//         func_800683BC_68FBC(0xC); //?
//         mp2_omOvlCallEx(ovl_table_custom[mp2_OverlayToLoad].overlayID, 0, 0x92);
//         mp2_omOvlHisChg(1, ovl_table_custom[mp2_OverlayToLoad].overlayID, 0, 0x192);        
//         check = 1;
//         return;
//     }
// }


extern u16 mp2_pageID;
extern u16 mp2_debugCursorIndex;



void LoadMinigameData(void) {
    if (mp2_OverlayToLoad != -1) {
        //mp2_debugMode = 1;
        CopyMp3_gPlayerCopy_To_Mp2();
        mp2_pageID = 0;
        if (mp2_OverlayToLoad == 0) {
            mp2_debugCursorIndex = 0;
        } else {
            mp2_debugCursorIndex = mp2_OverlayToLoad; //
        }
        loadingBackFromMinigame = 1;
    }
}

// void LoadMinigameFromBoot(s32 arg0, s32 arg1, s32 arg2) {
//     if (mp2_OverlayToLoad == -1) {
//         //original code
//         //can load either corrupt save data screen or boot logos
//         mp2_omOvlCallEx(arg0, arg1, arg2);
//     } else if (check == 1) {
//         ComboSwitchGameToMp3(); //doesn't return
//     } else if (check == 0) { 
//         D_800F93C8 = ovl_table_custom[mp2_OverlayToLoad].overlayID;
//         D_800F93C6 = 0;

//         CopyMp3_gPlayerCopy_To_Mp2();

//         func_800683BC_68FBC(0xC);
        
//         //mp2_omOvlCallEx(func_8003F6F0_402F0(ovl_table_custom[mp2_OverlayToLoad].overlayID), 0, 0x92);
//         //mp2_omOvlCallEx(func_8003F6F0_402F0(ovl_table_custom[mp2_OverlayToLoad].overlayID), 0, 0x92);
//         omOvlCallEx(ovl_table_custom[mp2_OverlayToLoad].overlayID, 0, 0x92);
//         omOvlHisChg(1, ovl_table_custom[mp2_OverlayToLoad].overlayID, 0, 0x192);        
//         check = 1;
//         return;
//     }
// }