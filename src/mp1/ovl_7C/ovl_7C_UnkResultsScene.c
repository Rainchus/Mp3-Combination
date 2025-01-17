#include "marioparty.h"
#include "mp1.h"

extern s16 D_800FA0D0_UnknownResultsScreen[];
extern s16 D_800FA0D8_UnknownResultsScreen[];
extern s16 D_800FA0F0_UnknownResultsScreen[];

s32 mp1_get_team_index(mp1_GW_PLAYER* player) {
    return (player->flags & 0x30) >> 5; //returns team index 0 or 1
}

void FixGivenCoinsForTeamMode4p(mp1_GW_PLAYER* curPlayer1stTeammate, mp1_GW_PLAYER* curPlayer2ndTeammate, mp1_GW_PLAYER* otherTeam1stTeammate, mp1_GW_PLAYER* otherTeam2ndTeammate) {
    s32 i;
    //find losing player, set team captain to -10 for losing team (or all their coins if they have less than 10)
    if (curPlayer1stTeammate->coins_mg < 5) {
        s32 teamIndex = mp1_get_team_index(curPlayer1stTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 10) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -10;
                }
            }
        }
    } else if (curPlayer2ndTeammate->coins_mg < 5) {
        s32 teamIndex = mp1_get_team_index(curPlayer2ndTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 10) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -10;
                }
            }
        }
    } else if (otherTeam1stTeammate->coins_mg < 5) {
        s32 teamIndex = mp1_get_team_index(otherTeam1stTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 10) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -10;
                }
            }
        }
    } else if (otherTeam2ndTeammate->coins_mg < 5) {
        s32 teamIndex = mp1_get_team_index(otherTeam2ndTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 10) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -10;
                }
            }
        }
    }

    curPlayer2ndTeammate->coins_mg = 0;
    otherTeam2ndTeammate->coins_mg = 0;
}

void FixGivenCoinsForTeamMode2v2(mp1_GW_PLAYER* curPlayer1stTeammate, mp1_GW_PLAYER* curPlayer2ndTeammate, mp1_GW_PLAYER* otherTeam1stTeammate, mp1_GW_PLAYER* otherTeam2ndTeammate) {
    s32 i;
    //find losing player, set team captain to -10 for losing team (or all their coins if they have less than 10)
    if (curPlayer1stTeammate->coins_mg < 10) {
        s32 teamIndex = mp1_get_team_index(curPlayer1stTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 20) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -20;
                }
            }
        }
    } else if (curPlayer2ndTeammate->coins_mg < 10) {
        s32 teamIndex = mp1_get_team_index(curPlayer2ndTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 20) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -20;
                }
            }
        }
    } else if (otherTeam1stTeammate->coins_mg < 10) {
        s32 teamIndex = mp1_get_team_index(otherTeam1stTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 20) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -20;
                }
            }
        }
    } else if (otherTeam2ndTeammate->coins_mg < 10) {
        s32 teamIndex = mp1_get_team_index(otherTeam2ndTeammate);
        for (i = 0; i < MAX_PLAYERS; i++) {
            s32 curPlayerTeam = mp1_get_team_index(&mp1_gPlayers[i]);
            if (teamIndex == curPlayerTeam) {
                if (mp1_gPlayers[i].coins < 20) {
                    mp1_gPlayers[i].coins_mg = -mp1_gPlayers[i].coins;
                } else {
                    mp1_gPlayers[i].coins_mg = -20;
                }
            }
        }
    }

    curPlayer2ndTeammate->coins_mg = 0;
    otherTeam2ndTeammate->coins_mg = 0;
}

void func_800F8194_UnknownResultsScreen(void) {
    s32 i;
    mp1_GW_PLAYER* curPlayer1stTeammate = NULL;
    mp1_GW_PLAYER* otherTeam1stTeammate = NULL;

    mp1_GW_PLAYER* curPlayer2ndTeammate = NULL;
    mp1_GW_PLAYER* otherTeam2ndTeammate = NULL;

    //if playing mario party 3 team mode, give all coins to captain
    if ((CurBaseGame == MP3_BASE) && (mp1_gPlayers[0].flags & 0x30)) {


        //add dummy character coins to team captain
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (mp1_get_team_index(&mp1_gPlayers[i]) == 0) {
                if (curPlayer1stTeammate == NULL) {
                    curPlayer1stTeammate = &mp1_gPlayers[i];
                } else {
                    curPlayer2ndTeammate = &mp1_gPlayers[i];
                    curPlayer1stTeammate->coins_mg += curPlayer2ndTeammate->coins_mg;
                }
            } else {
                if (otherTeam1stTeammate == NULL) {
                    otherTeam1stTeammate = &mp1_gPlayers[i];
                } else {
                    otherTeam2ndTeammate = &mp1_gPlayers[i];
                    otherTeam1stTeammate->coins_mg += otherTeam2ndTeammate->coins_mg;
                }
            }
        }

        s32 prevMinigameType = ForeignMinigameGetType(ForeignMinigameIndexToLoad);

        //massive hack for minigames in team mode where you can lose coins
        if ((ForeignMinigameIndexToLoad == MP1_HOT_BOB_OMB) || (ForeignMinigameIndexToLoad == MP1_HOT_ROPE_JUMP)) { //mp1
            FixGivenCoinsForTeamMode4p(curPlayer1stTeammate, curPlayer2ndTeammate, otherTeam1stTeammate, otherTeam2ndTeammate);
        } else if ( (ForeignMinigameIndexToLoad == KEY_PA_WAY) || (ForeignMinigameIndexToLoad == RUNNING_OF_THE_BULB)) {
            if (mp1_gPlayers[0].coins_mg == 10 && mp1_gPlayers[1].coins_mg == 10 && mp1_gPlayers[2].coins_mg == 10 && mp1_gPlayers[3].coins_mg == 10) {
                //do nothing
            } else { //players lost, set team captain coins_mg to -10
                if (curPlayer1stTeammate->coins < 10) {
                    curPlayer1stTeammate->coins_mg = -curPlayer1stTeammate->coins;
                } else {
                    curPlayer1stTeammate->coins_mg = -10;
                }

                if (otherTeam1stTeammate->coins < 10) {
                    otherTeam1stTeammate->coins_mg = -otherTeam1stTeammate->coins;
                } else {
                    otherTeam1stTeammate->coins_mg = -10;
                }
            }
        } else if (prevMinigameType == PLAYERS_2V2) {
            FixGivenCoinsForTeamMode2v2(curPlayer1stTeammate, curPlayer2ndTeammate, otherTeam1stTeammate, otherTeam2ndTeammate);
        } else {
            curPlayer2ndTeammate->coins_mg = 0;
            otherTeam2ndTeammate->coins_mg = 0;
        }
    }

    if (customEepromData.preventMinigameCoinLoss == TRUE) {
        //set all negative coin gains to 0
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (mp1_gPlayers[i].coins_mg < 0) {
                mp1_gPlayers[i].coins_mg = 0;
            }
        }
    }

    //sanity check to try and make sure dummy teammates dont get coins
    if ((CurBaseGame == MP3_BASE) && (mp1_gPlayers[0].flags & 0x30)) {
        curPlayer2ndTeammate->coins_mg = 0;
        otherTeam2ndTeammate->coins_mg = 0;        
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        D_800FA0F0_UnknownResultsScreen[i] = mp1_gPlayers[i].coins;
        D_800FA0D0_UnknownResultsScreen[i] = mp1_gPlayers[i].coins_mg;
        if ((mp1_gPlayers[i].coins + D_800FA0D0_UnknownResultsScreen[i]) > 999) {
            D_800FA0D0_UnknownResultsScreen[i] = 999 - mp1_gPlayers[i].coins;
        }
        if ((mp1_gPlayers[i].coins + D_800FA0D0_UnknownResultsScreen[i] < 0)) {
            D_800FA0D0_UnknownResultsScreen[i] = -mp1_gPlayers[i].coins;
        }
        mp1_gPlayers[i].coins_total = mp1_gPlayers[i].coins_total + mp1_gPlayers[i].coins_mg;
        D_800FA0D8_UnknownResultsScreen[i] = mp1_gPlayers[i].coins_mg;
        mp1_gPlayers[i].coins_mg = 0;
    }
}