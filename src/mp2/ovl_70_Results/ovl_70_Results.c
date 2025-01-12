#include "marioparty.h"
#include "mp2.h"

extern s16 D_80107830_413C90_Results[];
extern s16 D_80107838_413C98_Results[];
extern s16 D_80107840_413CA0_Results[];
extern s16 D_80107848_413CA8_Results[];
extern s16 D_80107860_413CC0_Results[];

s32 mp2_get_team_index(mp2_GW_PLAYER* player) {
    return (player->flags & 0x30) >> 5; //returns team index 0 or 1
}

void func_80104B90_410FF0_Results(void) {
    s32 i;

    if ((CurBaseGame == MP3_BASE) && (mp2_gPlayers[0].flags & 0x30)) {
        mp2_GW_PLAYER* curPlayer1stTeammate = NULL;
        mp2_GW_PLAYER* otherTeam1stTeammate = NULL;

        mp2_GW_PLAYER* curPlayer2ndTeammate = NULL;
        mp2_GW_PLAYER* otherTeam2ndTeammate = NULL;

        //add dummy character coins to team captain
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (mp2_get_team_index(&mp2_gPlayers[i]) == 0) {
                if (curPlayer1stTeammate == NULL) {
                    curPlayer1stTeammate = &mp2_gPlayers[i];
                } else {
                    curPlayer2ndTeammate = &mp2_gPlayers[i];
                    curPlayer1stTeammate->coins_mg += curPlayer2ndTeammate->coins_mg;
                    curPlayer1stTeammate->coins_mg_bonus += curPlayer2ndTeammate->coins_mg_bonus;
                }
            } else {
                if (otherTeam1stTeammate == NULL) {
                    otherTeam1stTeammate = &mp2_gPlayers[i];
                } else {
                    otherTeam2ndTeammate = &mp2_gPlayers[i];
                    otherTeam1stTeammate->coins_mg += otherTeam2ndTeammate->coins_mg;
                    otherTeam1stTeammate->coins_mg_bonus += otherTeam2ndTeammate->coins_mg_bonus;
                }
            }
        }

        curPlayer2ndTeammate->coins_mg = 0;
        otherTeam2ndTeammate->coins_mg = 0;

        curPlayer2ndTeammate->coins_mg_bonus = 0;
        otherTeam2ndTeammate->coins_mg_bonus = 0;
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        D_80107860_413CC0_Results[i] = mp2_gPlayers[i].coins;
        D_80107830_413C90_Results[i] =  mp2_gPlayers[i].coins_mg_bonus;
        D_80107838_413C98_Results[i] = mp2_gPlayers[i].coins_mg;
        if ((mp2_gPlayers[i].coins + D_80107830_413C90_Results[i] + D_80107838_413C98_Results[i]) > 999) {
            D_80107830_413C90_Results[i] = 999 - mp2_gPlayers[i].coins;
            D_80107838_413C98_Results[i] = 0;
        }
        if ((mp2_gPlayers[i].coins + D_80107830_413C90_Results[i] + D_80107838_413C98_Results[i] < 0)) {
            D_80107830_413C90_Results[i] = -mp2_gPlayers[i].coins;
            D_80107838_413C98_Results[i] = 0;
        }
        mp2_gPlayers[i].coins_total += mp2_gPlayers[i].coins_mg;
        mp2_gPlayers[i].coins_total += mp2_gPlayers[i].coins_mg_bonus;
        D_80107840_413CA0_Results[i] = mp2_gPlayers[i].coins_mg_bonus;
        D_80107848_413CA8_Results[i] = mp2_gPlayers[i].coins_mg;
    }
}