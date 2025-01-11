.headersize 0x801059A0 - 0x3C27C0

//TODO:
//Bowser's revolution //fix player icons (does function correctly though)
//Bowser's coin potluck //fix player icons (does function correctly though)

.org 0x80108F48
    J bowserCoinCheckAsm
    NOP

.org 0x80107E18
    JAL bowserPhoneGiveEvent
    NOP

.org 0x8010832C
    JAL bowserPhoneGiveEvent2
    NOP

.org 0x80107AD8
    JAL bowserSuitGiveEvent
    NOP

.org 0x80107DA8
    JAL bowserSuitGiveEvent2
    NOP

.org 0x801077C4
    JAL coinsForBowserEvent
    NOP

.org 0x80107730
    JAL coinsForBowserEvent2
    NOP
