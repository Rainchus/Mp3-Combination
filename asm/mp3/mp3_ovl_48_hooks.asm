.headersize 0x8010AE2C - 0x32099C
.org 0x8010AE1C
    J chillyWatersBankCheck
    NOP

.org 0x8010AF38
    J chillyWatersBankCheck2
    NOP

.org 0x8010AE6C
    J chillyWatersBankCheck3
    NOP

.org 0x8010AEC4
    J chillyWatersBankCheck4
    NOP

.org 0x8010AF14
    J chillyWatersBankCheck5
    NOP

.org 0x8010AEF0
    JAL BankShowPlayerCoinChangeHook
    LB a0, 0x000F (s4)
    //NOPs for clarity (it's implemented in the above function call)
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

.org 0x801122BC
    JAL 0x800E4A7C
    ADDU s0, s3, r0

    JAL chillyWatersItemMenuClosing
    ADDU a0, s2, r0

.org 0x8011217C //0x801121AC
    J chillyWatersSkeletonKeyThing
    NOP

.org 0x8010F970
    JAL chillyWatersSkeletonKeyThing2
    ADDIU a3, sp, 0x0014

.org 0x8010FA58
    JAL chillyWatersSkeletonKeyThing3
    SRA a3, a3, 16

.org 0x8010FEC8
    J dragItemCheck
    NOP

.org 0x8010FF90
    JAL itemDragFadeCheck
    SRA a2, a2, 16

.org 0x8010FFD0
    JAL itemDragFadecheck2
    ADDU a2, r0, r0

.org 0x8010FEF8 //we do these instructions a bit early in the dragItemCheck hook
    NOP
    NOP

.org 0x80112430
    JAL 0x800E49DC
    ADDU s0, s3, r0

    //passes something on v0
    JAL chillyWatersSkeletonKeyThing4
    ADDU a0, s2, r0

.org 0x8011C8B0
    JAL GetTeamCaptainCurrentIndex
    SW s0, 0x0020 (sp)

//TODO: verify this is an item check
.org 0x8011CC0C
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011CDCC
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x801111F4
    J unkItemsAsm0
    LB a0, 0x000F (s3)

.org 0x8010BBD4
    J shopCoinsCheck
    NOP

//bought shop item from cellular shopper
.org 0x8010BF88
    J boughtItemShopper
    NOP

.org 0x8011C964
    SLT v0, a0, gp

.org 0x801121AC
    NOP //remove `LB v0, 0x000F (s1)` related to the skeleton key removal from your inventory

.org 0x801170B0
    J itemUsedRemoveFromLargeItemList
    NOP

//used for making the item fade when used in teams mode
.org 0x8010FDA4
    J teamCheck6Asm
    SRA a2, a2, 16

.org 0x8010FDC0
    J teamCheck11Asm
    ADDU a2, r0, r0

//if teams is on, return either 1st place for winning team and 4th for losing team
.org 0x8010BC8C
    JAL GetPlayerPlacementForTeamShop
    ADDU s1, v0, r0

//change player index when coins are read for teams
//.org 0x8010BDA8
.org 0x8010B6A0
    J storeTeamIndex_Asm
    NOP
    NOP

//extend stack of function for some temporary space
.org 0x8010B65C
    ADDIU sp, sp, -0xF0
.org 0x8010C910
    ADDIU sp, sp, 0xF0

.org 0x8010BDA8 //load team player index for coin checks in shop
    LW v1, 0x00E8 (sp) //get team index stored from earlier
    NOP

//make item bag give items to team leader
.org 0x8010C538
    J teamCheck10Asm
    NOP

//award star to 1st player on current player's team
//this hook sets t0 for the 0x80106DF8 hook below it
.org 0x80106DC4
    J teamCheck8Asm 
    NOP
    NOP
.org 0x80106DF8
    ADDU v1, t0, r0

//hook boo coin check to check team coins
.org 0x8010E36C
    J newBooCheck
    LB v0, 0x000F (s7) //restore from hook (load current player index)

.org 0x8010E4B4
    J newBooCanStealStarCheck
    LB v0, 0x000F (s7) //restore from hook (load current player index)

//if plunder chest found player had max items, set to either 3 or 5 depending on if teams are active
.org 0x80117FE0
    ADDU s0, r0, gp

//plunder chest who you can steal from list generation
.org 0x80117E2C
    J newPlunderChestCheck
    NOP

//for storing newly aquired item
.org 0x80117FFC
    J newPlunderChestItemStoreCheck
    NOP

.org 0x80118090
    J newPlunderChest2
    NOP

.org 0x801180F0
    JAL newPlunderChest3
    ADDIU a2, r0, 0x0100

.org 0x80118118
    JAL newPlunderChest4
    ADDIU a2, r0, 0x4786

.org 0x8011812C
    J newPlunderChest5
    NOP

.org 0x801103E0
    J newDuelGlove
    NOP

.org 0x80110440
    JAL newDuelGlove2
    SRA a2, a2, 16

.org 0x80110464
    J newDuelGlove3
    NOP

.org 0x801104A0
    JAL newDuelGlove4
    NOP

//for removing lucky lamp when it's used
.org 0x80111764
    J luckyLampRemovalCheck
    NOP

//for making the reverse mushroom vanish when you select a player
.org 0x801178F4
    JAL ReverseMushroomVanishHook
    ADDU a1, v0, r0

//game guy takes coins hook
.org 0x80114FA0 //lucky coin item only?
    JAL gameGuyCoinCheck
    ADDU a0, s2, r0 //pass player index into a0
    NOP

//wacky watch removal check
.org 0x80115E44
    J wackyWatchRemovalCheck
    NOP

.org 0x80115DC8
    JAL wackyWatchMovementCheck1
    ADDU a2, r0, r0

.org 0x80115DE4
    JAL wackyWatchMovementCheck2
    ADDIU a3, sp, 0x0034