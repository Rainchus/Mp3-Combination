#include "marioparty.h"
#include "mp3.h"
#include "mp3/game/object.h"

typedef s16 Array2D[2][18];

s16 HuAudFXPlay(s32);
void HuFreeFileTemp(void*);
void* HuReadFileTemp(s32);
void func_8000BBD4_C7D4(u16, s32, s32);
void func_8000BBFC_C7FC(u16, s16);
void func_8000BC48_C848(u16, s32);
void func_8000BCC8_C8C8(u16, s32);
void func_8000BE5C_CA5C(u16, f32, f32);
void func_8000C184_CD84(u16);
void func_8001ACDC_1B8DC(s16);
void func_8001C150_1CD50(s16, f32, f32, f32);
void func_8001C1A0_1CDA0(s16, f32, f32, f32);
void func_8001C258_1CE58(s16, s32, s32);
void func_80055670_56270(s16);
void func_8010B82C_507A8C_name_78(s32);
void func_8010B858_507AB8_name_78(void);
void func_8010B998_507BF8_name_78(void);
s32 func_8010D684_5098E4_name_78(s16, s16*);
void func_8010DDD8_50A038_name_78(void*);
mp3_omObjData* func_8010DE38_50A098_name_78(s32, s32, s32);
void func_8010E4BC_50A71C_name_78(Array2D*, s32, s32);
void func_8010E4D8_50A738_name_78(Array2D*, s32);
void func_8010E8C8_50AB28_name_78(Array2D*, s32, s32, f32, f32, f32, f32, s32);
void func_8010F320_50B580_name_78(s32, s32, s16, s16);
extern s32 D_80119420_515680_name_78;
extern s32 PartyModeBoardImages[];
// extern s32 DuelModeBoardImages[];
// extern s32 PartyModeBoardDescriptions[];



char TestString[] = "\x0BSpooky spells \x7E floating pages\x85";

enum PartyModeBoards {
    CHILLY_WATERS,
    DEEP_BLOOBER_SEA,
    SPINY_DESERT,
    WOODY_WOODS,
    CREEPY_CAVERN,
    WALUIGIS_ISLAND
};

//board description IDs
s32 PartyModeBoardDescriptions[] = {
    [CHILLY_WATERS]     0x0000151E,
    [DEEP_BLOOBER_SEA]  0x0000151F,
    [SPINY_DESERT]      0x00001520,
    [WOODY_WOODS]       0x00001521,
    [CREEPY_CAVERN]     0x00001522,
    [WALUIGIS_ISLAND]   0x00001523,
};

s32 DuelModeBoardImages[] = {
    [CHILLY_WATERS]     0x00140051,
    [DEEP_BLOOBER_SEA]  0x00140052,
    [SPINY_DESERT]      0x00140053,
    [WOODY_WOODS]       0x00140054,
    [CREEPY_CAVERN]     0x00140055,
    [WALUIGIS_ISLAND]   0x00140056
};

//board background main fs ids
s32 PartyModeBoardImages[] = {
    [CHILLY_WATERS]     0x00140048,
    [DEEP_BLOOBER_SEA]  0x00140049,
    [SPINY_DESERT]      0x0014004A,
    [WOODY_WOODS]       0x0014004B,
    [CREEPY_CAVERN]     0x0014004C,
    [WALUIGIS_ISLAND]   0x0014004D,
    //0x0014006C //extra board id
};

s32 DuelModeBoardDescriptions[] = {
    [CHILLY_WATERS]     0x00002415,
    [DEEP_BLOOBER_SEA]  0x00002416,
    [SPINY_DESERT]      0x00002417,
    [WOODY_WOODS]       0x00002418,
    [CREEPY_CAVERN]     0x00002419,
    [WALUIGIS_ISLAND]   0x0000241A,
    //0x00002414
};

s32 GetPartyModeBoardFlag(s32 bitIndex) {
    return (customEepromData.mp3UnlockedPartyBoards >> bitIndex) & 1;
}

s32 GetDuelModeBoardFlag(s32 bitIndex) {
    return (customEepromData.mp3UnlockedDuelBoards >> bitIndex) & 1;
}

s32 PartyModeBoardImagesGenerated[] = {-1, -1, -1, -1, -1, -1};
s32 DuelModeBoardImagesGenerated[] = {-1, -1, -1, -1, -1, -1};
s32 PartyModeBoardDescriptionsGenerated[] = {-1, -1, -1, -1, -1, -1};
s32 DuelModeBoardDescriptionsGenerated[] = {-1, -1, -1, -1, -1, -1};

//Upon reloading the area, they would still hold old data so we reset them
void ResetGeneratedUnlockedBoardArrays(void) {
    for (int i = 0; i < 6; i++) {
        PartyModeBoardImagesGenerated[i] = PartyModeBoardImages[i];
        DuelModeBoardImagesGenerated[i] = DuelModeBoardImages[i];
        PartyModeBoardDescriptionsGenerated[i] = PartyModeBoardDescriptions[i];
        DuelModeBoardDescriptionsGenerated[i] = DuelModeBoardDescriptions[i];
    }
}

// extern s32 DuelModeBoardDescriptions[];
extern s16 D_8011A938_516B98_name_78;
extern s16 D_8011A948_516BA8_name_78;
extern u8 D_8011AA45_516CA5_name_78;
typedef struct UnkStarLift {
    char unk_00[0x04];
    s16 unk4;
} UnkStarLift;

s32 mp3_CheckFlag(s32);
s16 func_80055810_56410(void*);

//these build an array of unlocked board indexes
s32 GetPartyModeBoardCount(u8* unlockedBoards) {
    s32 partyBoardTotal = 0;

    for (int i = 0; i < 6; i++) {
#ifdef DEBUG
        if (1) {
#else
        if (GetPartyModeBoardFlag(i) == 1) {
#endif
            unlockedBoards[partyBoardTotal] = i;
            PartyModeBoardImagesGenerated[partyBoardTotal] = PartyModeBoardImages[partyBoardTotal];
            PartyModeBoardImagesGenerated[partyBoardTotal] = PartyModeBoardImages[partyBoardTotal];
            partyBoardTotal++;
        }
    }

    //if this happens, this is bad! force a crash
    if (partyBoardTotal == 0) {
        *(s32*)0 = 0;
    }

    return partyBoardTotal;
}

s32 GetDuelModeBoardCount(u8* unlockedBoards) {
    s32 duelBoardTotal = 0;

    for (int i = 0; i < 6; i++) {
        #ifdef DEBUG
        if (1) {
#else
        if (GetDuelModeBoardFlag(i) == 1) {
#endif
            unlockedBoards[duelBoardTotal] = i;
            DuelModeBoardImagesGenerated[duelBoardTotal] = DuelModeBoardImages[duelBoardTotal];
            DuelModeBoardImagesGenerated[duelBoardTotal] = DuelModeBoardImages[duelBoardTotal];
            duelBoardTotal++;
        }
    }
    //if this happens, this is bad! force a crash
    if (duelBoardTotal == 0) {
        *(s32*)0 = 0;
    }

    return duelBoardTotal;
}

s32 newfunc_80113ED4_510134_name_78(UnkStarLift* arg0) {
    #define MODE_PARTY 0
    #define MODE_DUEL 1
    #define FLAG_WALUIGIS_ISLAND 0x31
    #define FLAG_BACKTRACK 0x30
    u8 unlockedBoards[8];
    Array2D sp20;
    s16 unk_68;
    s32* mainFSArray;
    s32 boardCountMaxCopy;
    f32 var_f20;
    void* temp_v0_4;
    mp3_omObjData* temp_s5;
    s16 prevBoardIndex;
    s16 backgroundEspriteSlot;
    s16 var_s6;
    s32 pad;
    s32 var_fp;
    s32 boardCountMax;
    s32* curModeBoardDescriptions;
    s16 curBoardIndex;
    s16 temp;
    s32 i;
    f32 tempFloat;

    ResetGeneratedUnlockedBoardArrays();

    curModeBoardDescriptions = NULL;
    mainFSArray = NULL;
    curBoardIndex = D_8011AA45_516CA5_name_78;
    arg0->unk4 = 0;
    backgroundEspriteSlot = -1;
    var_s6 = -1;
    boardCountMax = ARRAY_COUNT(PartyModeBoardImages);
    var_fp = 70;
    tempFloat = 1.0f;

    switch (D_8011A938_516B98_name_78) { //current mode
    case MODE_PARTY:
        curModeBoardDescriptions = (s32*)PartyModeBoardDescriptionsGenerated;
        mainFSArray = PartyModeBoardImagesGenerated; //party mode board backgrounds
        tempFloat = 1.0f;
        var_fp = 74;
        boardCountMax = GetPartyModeBoardCount(unlockedBoards);

        //remove this to always have waluigi's island unlocked
        // if (_CheckFlag(FLAG_WALUIGIS_ISLAND) != 0) {
        //     boardCountMax = 6;
        // }
        break;
    case MODE_DUEL:
        curModeBoardDescriptions = (s32*)DuelModeBoardDescriptionsGenerated;
        mainFSArray = DuelModeBoardImagesGenerated; //duel mode board backgrounds
        var_fp = 74;
        boardCountMax = GetDuelModeBoardCount(unlockedBoards);
        break;
    }

    func_8010B998_507BF8_name_78();
    func_8010E4BC_50A71C_name_78(&sp20, 2, 0);
    func_8010E4D8_50A738_name_78(&sp20, 2);
    temp = sp20[0][12];
    temp_s5 = func_8010DE38_50A098_name_78(0x40, 0x100, 0x48);
    if (D_8011A938_516B98_name_78 == MODE_PARTY) {
        func_8010B82C_507A8C_name_78(0x0000151D); //pick board you want to play text box
    } else {
        func_8010B82C_507A8C_name_78(0x00002414); //duel board you want to play text box
    }
    func_8010B858_507AB8_name_78();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_50AB28_name_78(&sp20, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_1CE58(sp20[1][12], 4, 4);
    
    for (var_f20 = 0.0f; var_f20 < 180.0f; var_f20 += (180.0f / 7.0f)) {
        func_8001C150_1CD50(temp, 0, var_f20, 0);
        mp3_HuPrcVSleep();
    }
    
    func_8001C150_1CD50(temp, 0, 180.0f, 0);
    temp_s5->work[0] = 1;
    temp_s5->work[1] = 36;
    
    for (var_f20 = 1.0f; var_f20 < 2.5f; var_f20 += (3.0f / 14.0f)) {
        func_8001C1A0_1CDA0(temp, var_f20, var_f20, var_f20);
        mp3_HuPrcVSleep();
    }
    
    func_8001C1A0_1CDA0(temp, 2.5f, 2.5f, 2.5f);
    prevBoardIndex = -1;
    pad = func_8010D684_5098E4_name_78(D_8011A948_516BA8_name_78, &unk_68);
    boardCountMaxCopy = boardCountMax;
    while (1) {
        pad = func_8010D684_5098E4_name_78(D_8011A948_516BA8_name_78, &unk_68);
        if (pad & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (pad & B_BUTTON) {
            HuAudFXPlay(4);
            curBoardIndex = -1;
            break;
        }
        if (pad & (U_JPAD | R_JPAD)) {
            curBoardIndex++;
            curBoardIndex = (boardCountMaxCopy <= curBoardIndex) ? 0 : curBoardIndex;
            HuAudFXPlay(1);
            temp_s5->work[0] = 4;
        } else {
            if (pad & (D_JPAD | L_JPAD)) {
                if (--curBoardIndex < 0) {
                    curBoardIndex = boardCountMax - 1;
                }
                HuAudFXPlay(1);
                temp_s5->work[0] = 3;
            }
        }
        //check if background image should update
        if (prevBoardIndex != curBoardIndex) {
            if (backgroundEspriteSlot >= 0) {
                for (i = 255; i > 0; i -= (255 / 5)) {
                    func_8000BBFC_C7FC(backgroundEspriteSlot, i);
                    mp3_HuPrcVSleep();
                }
                func_8000C184_CD84(backgroundEspriteSlot);
                func_80055670_56270(var_s6);
            }
            temp_v0_4 = HuReadFileTemp(mainFSArray[curBoardIndex]);
            var_s6 = func_80055810_56410(temp_v0_4);
            HuFreeFileTemp(temp_v0_4);
            backgroundEspriteSlot = InitEspriteSlot(var_s6, 0, 1);
            func_8000BC48_C848(backgroundEspriteSlot, 0x1000);
            func_8000BCC8_C8C8(backgroundEspriteSlot, 1);
            func_8000BBD4_C7D4(backgroundEspriteSlot, 0xA0, var_fp);
            func_8000BE5C_CA5C(backgroundEspriteSlot, tempFloat, tempFloat);
            for (i = 0; i < 255; i += (255 / 5)) {
                func_8000BBFC_C7FC(backgroundEspriteSlot, i);
                mp3_HuPrcVSleep();
            }
            func_8000BBFC_C7FC(backgroundEspriteSlot, 0xFF);
            prevBoardIndex = curBoardIndex;
            func_8010B82C_507A8C_name_78(curModeBoardDescriptions[curBoardIndex]);
        }
        mp3_HuPrcVSleep();
    }
    
    arg0->unk4 = curBoardIndex;
    if (curBoardIndex >= 0) {
        D_8011AA45_516CA5_name_78 = curBoardIndex;
    }

    temp_s5->work[0] = 2;
    temp_s5->work[1] = 17;
    
    for (i = 255; i > 0; i -= (255 / 5)) {
        func_8000BBFC_C7FC(backgroundEspriteSlot, i);
        mp3_HuPrcVSleep();
    }

    func_8000BBFC_C7FC(backgroundEspriteSlot, 0);

    for (var_f20 = 2.5f; var_f20 > 1.0f; var_f20 += -(3.0f / 14.0f)) {
        func_8001C1A0_1CDA0(temp, var_f20, var_f20, var_f20);
        mp3_HuPrcVSleep();
    }

    func_8001C1A0_1CDA0(temp, 1.0f, 1.0f, 1.0f);

    for (var_f20 = 180.0f; var_f20 < 360.0f; var_f20 += (180.0f / 7.0f)) {
        func_8001C150_1CD50(temp, 0, var_f20, 0);
        mp3_HuPrcVSleep();
    }

    func_8001C150_1CD50(temp, 0, 0.0f, 0);
    func_8001C258_1CE58(sp20[1][12], 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_50AB28_name_78(&sp20, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);

    if (curBoardIndex >= 0) {
        func_8010F320_50B580_name_78(D_80119420_515680_name_78, 0, sp20[0][12], -1);
        func_8010F320_50B580_name_78(D_80119420_515680_name_78, 2, backgroundEspriteSlot, var_s6);
        func_8001ACDC_1B8DC(sp20[1][12]);
    } else {
        for (i = 0; i < 2; i++) {
            func_8001ACDC_1B8DC(sp20[i][12]);
        }
        func_8000C184_CD84(backgroundEspriteSlot);
        func_80055670_56270(var_s6);
    }
    func_8010DDD8_50A038_name_78(temp_s5);
    return 0;
}