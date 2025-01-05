.headersize 0x8010AE2C - 0x32099C
.org 0x8010AE1C
    J chillyWatersBankCheck
    NOP

.org 0x8010AF48
    J chillyWatersBankCheck2
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

.org 0x80112430
    JAL 0x800E49DC
    ADDU s0, s3, r0

    //passes something on v0
    JAL chillyWatersSkeletonKeyThing4
    ADDU a0, s2, r0

.org 0x8011C8B0
    JAL GetTeamCurrentIndex
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
    LW v0, 0x00E8 (sp) //get team index stored from earlier
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