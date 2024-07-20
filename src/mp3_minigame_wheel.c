#include "marioparty.h"

s32 mp2_MinigameIndexToLoad = -1;

char HookLineAndSinkerStr[] = {"\x0B""Hand""\x82"" Line and Sinker"};
char CoconutConkStr[] = {"\x0B""Coconut Conk"};
char SpotlightSwimStr[] = {"\x0B""Spotlight Swim"};
char BoulderBallStr[] = {"\x0B""Boulder Ball"};
char CrazyCogsStr[] = {"\x0B""Crazy Cogs"};
char HideAndSneakStr[] = {"\x0B""Hide and Sneak"};
char RidiculousRelayStr[] = {"\x0B""Ridiculous Relay"};
char ThwompPullStr[] = {"\x0B""Thwomp Pull"};
char RiverRaidersStr[] = {"\x0B""River Raiders"};
char TidalTossStr[] = {"\x0B""Tidal Toss"};
char EatsaPizzaStr[] = {"\x0B""Eatsa Pizza"};
char BabyBowserBroadsideStr[] = {"\x0B""Baby Bowser Broadside"};
char PumpPumpAndAwayStr[] = {"\x0B""Pump""\x82"" Pump and Away"};
char HyperHydrantsStr[] = {"\x0B""Hyper Hydrants"};
char PickingPanicStr[] = {"\x0B""Picking Panic"};
char CosmicCoasterStr[] = {"\x0B""Cosmic Coaster"};
char PuddlePaddleStr[] = {"\x0B""Puddle Paddle"};
char EtchNCatchStr[] = {"\x0B""Etch ""\x5C""n""\x5C"" Catch"};
char LogJamStr[] = {"\x0B""Log Jam"};
char SlotSyncStr[] = {"\x0B""Slot Sync"};
char TreadmillGrillStr[] = {"\x0B""Treadmill Grill"};
char ToadstoolTitanStr[] = {"\x0B""Toadstool Titan"};
char AcesHighStr[] = {"\x0B""Aces High"};
char BounceNTrounceStr[] = {"\x0B""Bounce ""\x5C""n""\x5C"" Trounce"};
char IceRinkRiskStr[] = {"\x0B""Ice Rink Risk"};
char LockedOutStr[] = {"\x0B""Locked Out"};
char ChipShotChallengeStr[] = {"\x0B""Chip Shot Challenge"};
char ParasolPlummetStr[] = {"\x0B""Parasol Plummet"};
char MessoryMemoryStr[] = {"\x0B""Messy Memory"};
char PictureImperfectStr[] = {"\x0B""Picture Imperfect"};
char MariosPuzzlePartyStr[] = {"\x0B""Mario""\x5C""s Puzzle Party"};
char TheBeatGoesOnStr[] = {"\x0B""The Beat Goes On"};
char MPIQStr[] = {"\x0B""M""\x85""P""\x85""I""\x85""Q""\x85"""};
char CurtainCallStr[] = {"\x0B""Curtain Call"};
char WaterWhirledStr[] = {"\x0B""Water Whirled"};
char FrigidBridgesStr[] = {"\x0B""Frigid Bridges"};
char AwfulTowerStr[] = {"\x0B""Awful Tower"};
char CheepCheepChaseStr[] = {"\x0B""Cheep Cheep Chase"};
char PipeCleanersStr[] = {"\x0B""Pipe Cleaners"};
char SnowballSummitStr[] = {"\x0B""Snowball Summit"};
char AllFiredUpStr[] = {"\x0B""All Fired Up"};
char StackedDeckStr[] = {"\x0B""Stacked Deck"};
char ThreeDoorMontyStr[] = {"\x0B""Three Door Monty"};
char RockinRacewayStr[] = {"\x0B""Rockin""\x5C"" Raceway"};
char MerryGoChompStr[] = {"\x0B""Merry Go Chomp"};
char SlapDownStr[] = {"\x0B""Slap Down"};
char StormChasersStr[] = {"\x0B""Storm Chasers"};
char EyeSoreStr[] = {"\x0B""Eye Sore"};
char VineWithMeStr[] = {"\x0B""Vine With Me"};
char PopgunPickOffStr[] = {"\x0B""Popgun Pick""\x3D""Off"};
char EndOfTheLinerStr[] = {"\x0B""End Of The Line"};
char BowserTossStr[] = {"\x0B""Bowser Toss"};
char BabyBowserBonkersStr[] = {"\x0B""Baby Bowser Bonkers"};
char MotorRooterStr[] = {"\x0B""Motor Rooter"};
char SillyScrewsStr[] = {"\x0B""Silly Screws"};
char CrowdCoverStr[] = {"\x0B""Crowd Cover"};
char TickTockHopStr[] = {"\x0B""Tick Tock Hop"};
char FowlPlayStr[] = {"\x0B""Fowl Play"};
char WinnersWheelStr[] = {"\x0B""Winner""\x5C""s Wheel"};
char HeyBatterBatterStr[] = {"\x0B""Hey""\x82"" Batter""\x82"" Batter""\xC2"""};
char BobbingBowloonsStr[] = {"\x0B""Bobbing Bow""\x3D""loons"};
char DorrieDipStr[] = {"\x0B""Dorrie Dip"};
char SwingingWithSharksStr[] = {"\x0B""Swinging with Sharks"};
char SwingNSwipeStr[] = {"\x0B""Swing ""\x5C""n""\x5C"" Swipe"};
char ChanceTimeStr[] = {"\x0B""Chance Time"};
char StardustBattleStr[] = {"\x0B""Stardust Battle"};
char GameGuysRouletteStr[] = {"\x0B""Game Guy""\x5C""s Roulette"};
char GameGuysLucky7Str[] = {"\x0B""Game Guy""\x5C""s Lucky 7"};
char GameGuysMagicBoxesStr[] = {"\x0B""Game Guy""\x5C""s Magic Boxes"};
char GameGuysSweetSurpriseStr[] = {"\x0B""Game Guy""\x5C""s Sweet Surprise"};
char DizzyDinghiesStr[] = {"\x0B""Dizzy Dinghies"};
char MariosPuzzlePartyPro2Str[] = {"\x0B""Mario""\x5C""s Puzzle Party Pro"};
char BowserSlotsStr[] = {"\x0B""Bowser Slots"};
char RollOutTheBarrelsStr[] = {"\x0B""Roll Out The Barrels"};
char CoffinCongestionStr[] = {"\x0B""Coffin Congestion"};
char HammerSlammerStr[] = {"\x0B""Hammer Slammer"};
char GiveMeABrakeStr[] = {"\x0B" "Give Me A Brake\xC2"};
char MalletGoRoundStr[] = {"\x0B""Mallet""\x3D""Go""\x3D""Round"};
char GrabBagStr[] = {"\x0B""Grab Bag"};
char LavaTileIsleStr[] = {"\x0B""Lava Tile Isle"};
char BumperBalloonCarsStr[] = {"\x0B""Bumper Balloon Cars"};
char RakinEmInStr[] = {"\x0B""Rakin""\x5C"" ""\x5C""em In"};
char DayAtTheRacesStr[] = {"\x0B""Day At The Races"};
char HotRopeJumpStr[] = {"\x0B""Hot Rope Jump"};
char HotBobOmbStr[] = {"\x0B""Hot Bob""\x3D""omb"};
char BowlOverStr[] = {"\x0B""Bowl Over"};
char RainbowRunStr[] = {"\x0B""Rainbow Run"};
char CraneGameStr[] = {"\x0B""Crane Game"};
char MoveToTheMusicStr[] = {"\x0B""Move To The Music"};
char BobOmbBarrageStr[] = {"\x0B""Bob""\x3D""omb Barrage"};
char LookAwayStr[] = {"\x0B""Look Away"};
char ShockDropOrRollStr[] = {"\x0B""Shock""\x82"" Drop or Roll"};
char LightsOutStr[] = {"\x0B""Lights Out"};
char FiletRelayStr[] = {"\x0B""Filet Relay"};
char ArcherivalStr[] = {"\x0B""Archer""\x3D""ival"};
char ToadBandstandStr[] = {"\x0B""Toad Bandstand"};
char BobsledRunMp2Str[] = {"\x0B""Bobsled Run"};
char HandcarHavocMp2Str[] = {"\x0B""Handcar Havoc"};
//char MechaMarathonStr[] = {"\x0B""Mecha""\x3D""Marathon"};

u8 unkFontTable[] = {
    0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};

char* MinigameList[] = { //add 1 to this value and stick into table
/* 0x00 */ HookLineAndSinkerStr,
/* 0x01 */ CoconutConkStr,
/* 0x02 */ SpotlightSwimStr,
/* 0x03 */ BoulderBallStr,
/* 0x04 */ CrazyCogsStr,
/* 0x05 */ HideAndSneakStr,
/* 0x06 */ RidiculousRelayStr,
/* 0x07 */ ThwompPullStr,
/* 0x08 */ RiverRaidersStr,
/* 0x09 */ TidalTossStr,
/* 0x0A */ EatsaPizzaStr,
/* 0x0B */ BabyBowserBroadsideStr,
/* 0x0C */ PumpPumpAndAwayStr,
/* 0x0D */ HyperHydrantsStr,
/* 0x0E */ PickingPanicStr,
/* 0x0F */ CosmicCoasterStr,
/* 0x10 */ PuddlePaddleStr,
/* 0x11 */ EtchNCatchStr,
/* 0x12 */ LogJamStr,
/* 0x13 */ SlotSyncStr,
/* 0x14 */ TreadmillGrillStr,
/* 0x15 */ ToadstoolTitanStr,
/* 0x16 */ AcesHighStr,
/* 0x17 */ BounceNTrounceStr,
/* 0x18 */ IceRinkRiskStr,
/* 0x19 */ LockedOutStr,
/* 0x1A */ ChipShotChallengeStr,
/* 0x1B */ ParasolPlummetStr,
/* 0x1C */ MessoryMemoryStr,
/* 0x1D */ PictureImperfectStr,
/* 0x1E */ MariosPuzzlePartyStr,
/* 0x1F */ TheBeatGoesOnStr,
/* 0x20 */ MPIQStr,
/* 0x21 */ CurtainCallStr,
/* 0x22 */ WaterWhirledStr,
/* 0x23 */ FrigidBridgesStr,
/* 0x24 */ AwfulTowerStr,
/* 0x25 */ CheepCheepChaseStr,
/* 0x26 */ PipeCleanersStr,
/* 0x27 */ SnowballSummitStr,
/* 0x28 */ AllFiredUpStr,
/* 0x29 */ StackedDeckStr,
/* 0x2A */ ThreeDoorMontyStr,
/* 0x2B */ RockinRacewayStr,
/* 0x2C */ MerryGoChompStr,
/* 0x2D */ SlapDownStr,
/* 0x2E */ StormChasersStr,
/* 0x2F */ EyeSoreStr,
/* 0x30 */ VineWithMeStr,
/* 0x31 */ PopgunPickOffStr,
/* 0x32 */ EndOfTheLinerStr,
/* 0x33 */ BowserTossStr,
/* 0x34 */ BabyBowserBonkersStr,
/* 0x35 */ MotorRooterStr,
/* 0x36 */ SillyScrewsStr,
/* 0x37 */ CrowdCoverStr,
/* 0x38 */ TickTockHopStr,
/* 0x39 */ FowlPlayStr,
/* 0x3A */ WinnersWheelStr,
/* 0x3B */ HeyBatterBatterStr,
/* 0x3C */ BobbingBowloonsStr,
/* 0x3D */ DorrieDipStr,
/* 0x3E */ SwingingWithSharksStr,
/* 0x3F */ SwingNSwipeStr,
/* 0x40 */ ChanceTimeStr,
/* 0x41 */ StardustBattleStr,
/* 0x42 */ GameGuysRouletteStr,
/* 0x43 */ GameGuysLucky7Str,
/* 0x44 */ GameGuysMagicBoxesStr,
/* 0x45 */ GameGuysSweetSurpriseStr,
/* 0x46 */ DizzyDinghiesStr,
/* 0x47 */ MariosPuzzlePartyPro2Str,
/* 0x48 */ BowserSlotsStr,
/* 0x49 */ RollOutTheBarrelsStr,
/* 0x4A */ CoffinCongestionStr,
/* 0x4B */ HammerSlammerStr,
/* 0x4C */ GiveMeABrakeStr,
/* 0x4D */ MalletGoRoundStr,
/* 0x4E */ GrabBagStr,
/* 0x4F */ BumperBalloonCarsStr,
/* 0x50 */ LavaTileIsleStr,
/* 0x51 */ RakinEmInStr,
/* 0x52 */ DayAtTheRacesStr,
/* 0x53 */ HotRopeJumpStr,
/* 0x54 */ HotBobOmbStr,
/* 0x55 */ BowlOverStr,
/* 0x56 */ RainbowRunStr,
/* 0x57 */ CraneGameStr,
/* 0x58 */ MoveToTheMusicStr,
/* 0x59 */ BobOmbBarrageStr,
/* 0x5A */ LookAwayStr,
/* 0x5B */ ShockDropOrRollStr,
/* 0x5C */ LightsOutStr,
/* 0x5D */ FiletRelayStr,
/* 0x5E */ ArcherivalStr,
/* 0x5F */ ToadBandstandStr,
/* 0x60 */ BobsledRunMp2Str,
/* 0x61 */ HandcarHavocMp2Str
};

u8 new4PMinigameListNormalMp3[] = {
    // TREADMILL_GRILL,        TOADSTOOL_TITAN,    ACES_HIGH,      BOUNCE_N_TROUNCE,       ICE_RINK_RISK,
    // CHIP_SHOT_CHALLENGE,    PARASOL_PLUMMET,    MESSY_MEMORY,   PICTURE_IMPERFECT,      MARIOS_PUZZLE_PARTY,
    // THE_BEAT_GOES_ON,       MPIQ,               CURTAIN_CALL,   WATER_WHIRLED,          FRIGID_BRIDGES,
    // AWFUL_TOWER,            CHEEP_CHEEP_CHASE,  PIPE_CLEANERS,  SNOWBALL_SUMMIT,        ROCKIN_RACEWAY,
    //mp2 minigame
    TOADSTOOL_TITAN, GRAB_BAG_MP2, LAVA_TILE_ISLE, HOT_ROPE_JUMP_MP2, TREADMILL_GRILL
};
u8 new1v3MinigameListNormalMp3[] = {
    // HAND_LINE_AND_SINKER,   COCONUT_CONK,       SPOTLIGHT_SWIM, BOULDER_BALL,   CRAZY_COGS,
    // HIDE_AND_SNEAK,         RIDICULOUS_RELAY,   THWOMP_PULL,    RIVER_RAIDERS,  TIDAL_TOSS
    //mp2 minigames
    MOVE_TO_THE_MUSIC, CRANE_GAME, LOOK_AWAY, SHOCK_DROP_OR_ROLL, TOAD_BANDSTAND,
    ARCHER_IVAL, FILET_RELAY, LIGHTS_OUT
};
u8 new2v2MinigameListNormalMp3[] = {
    // EATSA_PIZZA,    BABY_BOWSER_BROADSIDE,  PUMP_PUMP_AND_AWAY,     HYPER_HYDRANTS, PICKING_PANIC,
    // COSMIC_COASTER, PUDDLE_PADDLE,          ETCH_N_CATCH, LOG_JAM,  SLOT_SYNC

    HANDCAR_HAVOC, BOBSLED_RUN, EATSA_PIZZA, PUMP_PUMP_AND_AWAY
};
u8 newBattleMinigameListNormalMp3[] = {
    LOCKED_OUT, ALL_FIRED_UP, STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP,
    SLAP_DOWN, STORM_CHASERS, EYE_SORE
};
u8 newItemMinigameListNormalMp3[] = {
    WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS, SWING_N_SWIPE
};

//at 80100EEC originally (normal minigame list, amount of minigames in each category)
u8 newCategoryAmountsNormal[] = {
    ARRAY_COUNT(new4PMinigameListNormalMp3),
    ARRAY_COUNT(new1v3MinigameListNormalMp3),
    ARRAY_COUNT(new2v2MinigameListNormalMp3),
    ARRAY_COUNT(newItemMinigameListNormalMp3),
    ARRAY_COUNT(newBattleMinigameListNormalMp3),
};

u8 new4PMinigameListEasyMp3[] = {0x15, 0x19, 0x1C, 0x1D, 0x1E, 0x21, 0x22, 0x26, 0x28};
u8 new1v3MinigameListEasyMp3[] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x09, 0x0A};
u8 new2v2MinigameListEasyMp3[] = {0x0B, 0x0C, 0x10, 0x11, 0x13};
u8 newBattleMinigameListEasyMp3[] = {0x2A, 0x2B, 0x2D, 0x2E};
u8 newItemMinigameListEasyMp3[] = {0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40};

//at 80100EF4 originally (east minigame list, amount of minigames in each category)
u8 newCategoryAmountsEasy[] = {
    ARRAY_COUNT(new4PMinigameListEasyMp3),
    ARRAY_COUNT(new1v3MinigameListEasyMp3),
    ARRAY_COUNT(new2v2MinigameListEasyMp3),
    ARRAY_COUNT(newBattleMinigameListEasyMp3),
    ARRAY_COUNT(newItemMinigameListEasyMp3),
};

char* GetNewMinigameString(s32 minigameIndex) {
    return MinigameList[minigameIndex];
}