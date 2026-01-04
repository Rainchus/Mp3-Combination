.headersize 0x8010ACC0 - 0x4EC0E0
.org 0x80105B28
    LH v0, 0x1110 (v0) //was LHU (loads GwPlayer[i].bonusCoins)

.org 0x801072E8
    LH v0, 0x1110 (v0) //was LHU (loads GwPlayer[i].bonusCoins)

.org 0x801072E8
    LH v0, 0x1110 (v0) //was LHU (loads GwPlayer[i].bonusCoins)

.org 0x80107304
    LH v0, 0x1110 (v0) //was LHU (loads GwPlayer[i].bonusCoins)

//.org 0x80105E5C
    //BEQZ a1, 0x80105E7C //was BGTZ

// .org 0x80105F1C
//     BEQZL a1, 0x80105F94 //was BLEZL

//.org 0x80106030
    //BEQZ a1, 0x80106058 //was BLEZ

//.org 0x801061C0
    //BEQZL a1, 0x80106238 //was BLEZL

//.org 0x801062E0
    //BEQZ a1, 0x8010630C //was BLEZ

.org 0x80105B38
    LH v0, 0x1130 (v0) //was LHU (loads GwPlayer[i].gamePrize //minigame star)

//.org 0x80105CE8
    //J func_80105CE8_4E7108_mgresultboard
    //NOP