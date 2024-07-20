//mp2 overlay 0 (Debug) hooks
.headersize 0x7E02D010
//.org 0x8010282C
//J hookOvlDebugStart
//NOP

.org 0x801052EC //remove fade out in debug screen
NOP
NOP

.org 0x80103A20 //insta press start
NOP
NOP

.org 0x80102D10 //increase fade in time on overlay 0
NOP
NOP

.org 0x80105194 //auto start minigame
NOP

//.org 0x80102C14 //remove drawing of background images
//NOP

//.org 0x80102C2C //dont draw coin cursor
//NOP

.org 0x80105AC8 //prevent overwriting of our page info
NOP

.org 0x80105030 //
LUI v1, hi(mp2_MinigameIndexToLoad)
LW v1, lo(mp2_MinigameIndexToLoad) (v1)

.org 0x8010387C
J ifSkipDebugTextDraw
NOP

//.org 0x80102D4C
//J LoadMinigameData
//ADDIU sp, sp, 0x40

.org 0x80103670
NOP //dont set initial page to -1

.org 0x80105AE8
NOP //dont set initial cursor index to -1

.org 0x8010500C //skip copying of gDebugPlayers to gPlayers
NOP

.org 0x80103798 //skip copy of gDebugPlayers
J 0x8010380C
NOP

//.org 0x80103938
//LUI a0, 0x8010
//ADDIU a0, a0, 0x1080
//SB r0, 0x0000 (a0)
//NOP
//NOP
//NOP
//NOP

//.org 0x80102D4C
//J hookOvlDebugStart2
//ADDIU sp, sp, 0x40

//.org 0x80103830
//J hookOvlDebugSetStats
//NOP

//.org 0x801034FC
//ORI v0, r0, 0x1000 //always pressing start in debug overlay