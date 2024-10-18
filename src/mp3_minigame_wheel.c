#include "marioparty.h"

s32 mp2_MinigameIndexToLoad = -1;
s32 mp3_LoadBackFromMp2 = FALSE;

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
//mp2 minigames start
char BowserSlotsStr[] = {"\x0B""Bowser Slots"}; //mp2 1
char RollOutTheBarrelsStr[] = {"\x0B""Roll Out The Barrels"}; //mp2 2
char CoffinCongestionStr[] = {"\x0B""Coffin Congestion"}; //mp2 3
char HammerSlammerStr[] = {"\x0B""Hammer Slammer"}; //mp2 4
char GiveMeABrakeStr[] = {"\x0B" "Give Me A Brake\xC2"}; //mp2 5
char MalletGoRoundStr[] = {"\x0B""Mallet""\x3D""Go""\x3D""Round"}; //mp2 6
char GrabBagStr[] = {"\x0B""Grab Bag"}; //mp2 7
char BumperBalloonCarsStr[] = {"\x0B""Bumper Balloon Cars"}; //mp2 8
char RakinEmInStr[] = {"\x0B""Rakin""\x5C"" ""\x5C""em In"}; //mp2 9
//mp2 10 blank
char DayAtTheRacesStr[] = {"\x0B""Day At The Races"}; //mp2 11
char FaceLiftStrStr[] = {"\x0B""Face Lift"}; //mp2 12
char CrazyCuttersStr[] = {"\x0B""Crazy Cutters"}; //mp2 13
char HotBobombStr[] = {"\x0B""Hot Bob""\x3D""omb"}; //mp2 14
char BowlOverStr[] = {"\x0B""Bowl Over"}; //mp2 15
char RainbowRunStr[] = {"\x0B""Rainbow Run"}; //mp2 16
char CraneGameStr[] = {"\x0B""Crane Game"}; //mp2 17
char MoveToTheMusicStr[] = {"\x0B""Move To The Music"}; //mp2 18
char BobOmbBarrageStr[] = {"\x0B""Bob""\x3D""omb Barrage"}; //mp2 19
char LookAwayStr[] = {"\x0B""Look Away"}; //mp2 20
char ShockDropOrRollStr[] = {"\x0B""Shock""\x82"" Drop or Roll"}; //mp2 21
char LightsOutStr[] = {"\x0B""Lights Out"}; //mp2 22
char FiletRelayStr[] = {"\x0B""Filet Relay"}; //mp2 23
char ArcherivalStr[] = {"\x0B""Archer""\x3D""ival"}; //mp2 24
//mp2 25 blank
char ToadBandstandStr[] = {"\x0B""Toad Bandstand"}; //mp2 26
char BobsledRunMp2Str[] = {"\x0B""Bobsled Run"}; //mp2 27
char HandcarHavocMp2Str[] = {"\x0B""Handcar Havoc"}; //mp2 28
//mp2 29 blank
char BalloonBurstStr[] = {"\x0B""Balloon Burst"}; //mp2 30
char SkyPilotsStr[] = {"\x0B""Sky Pilots"}; //mp2 31
char SpeedHockeyStr[] = {"\x0B""Speed Hockey"}; //mp2 32
char CakeFactoryStr[] = {"\x0B""Cake Factory"}; //mp2 33
//mp2 34
char DungeonDashStr[] = {"\x0B""Dungeon Dash"}; //mp2 35
char MagnetCartaStar[] = {"\x0B""Magnet Carta"}; //mp2 36
char LavaTileIsleStr[] = {"\x0B""Lava Tile Isle"}; //mp2 37
char HotRopeJumpStr[] = {"\x0B""Hot Rope Jump"}; //mp2 38
char ShellShockedStr[] = {"\x0B""Shell Shocked"}; //mp2 39
char ToadInTheBoxStr[] = {"\x0B""TOAD In The Box"}; //mp2 40
char MechaMarathonStr[] = {"\x0B""Mecha""\x3D""Marathon"}; //mp2 41
char RollCallStr[] = {"\x0B""Roll Call"}; //mp2 42
char AbandonShipStr[] = {"\x0B""Abandon Ship"}; //mp2 43
char PlatformPerilStr[] = {"\x0B""Platform Peril"}; //mp2 44
char TotemPolePoundStr[] = {"\x0B""Totem Pole Pound"}; //mp2 45
char BumperBallsStr[] = {"\x0B""Bumper Balls"}; //mp2 46
//mp2 47
char BombsAwayStr[] = {"\x0B""Bombs Away"}; //mp2 48
char TipsyTourneyStr[] = {"\x0B""Tipsy Tourney"}; //mp2 49
char HoneycombHavocStr[] = {"\x0B""Honeycomb Havoc"}; //mp2 50
char HexagonHeatStr[] = {"\x0B""Hexagon Heat"}; //mp2 51
char SkateboardScamperStr[] = {"Skateboard Scamper"}; //mp2 52
char SlotCarDerbyStr[] = {"\x0B""Slot Car Derby"}; //mp2 53
char ShyGuySaysStr[] = {"\x0B""Shy Guy Says"}; //mp2 54
char SneakNSnoreStr[] = {"\x0B""Sneak ""\x5C""n""\x5C"" Snore"}; //mp2 55
//mp2 56
char DriversEdStr[] = {"\x0B""Driver""\x5C""s Ed"}; //mp2 57
char ChanceTimeMp2Str[] = {"\x0B""Chance Time"}; //mp2 58
char WesternLandDuelStr[] = {"\x0B""Western Land Duel"}; //mp2 59
char PirateLandDuelStr[] = {"\x0B""Pirate Land Duel"}; //mp2 60
char HorrorLandDuelStr[] = {"\x0B""Horror Land Duel"}; //mp2 61
char SpaceLandDuelStr[] = {"\x0B""Space Land Duel"}; //mp2 62
char MysteryLandDuelStr[] = {"\x0B""Mystery Land Duel"}; //mp2 63
char KoopaLandDuelStr[] = {"\x0B""Koopa Land Duel"}; //mp2 64
char BowsersBigBlastStr[] = {"\x0B""Bowser""\x5C""s Big Blast"}; //mp2 65
char LooneyLumberjacksStr[] = {"\x0B""Looney Lumberjacks"}; //mp2 66
char TorpedoTargetsStr[] = {"\x0B""Torpedo Targets"}; //mp2 67
char DestructionDuetStr[] = {"\x0B""Destruction Duet"}; //mp2 68
char DizzyDancingStr[] = {"\x0B""Dizzy Dancing"}; //mp2 69
char TileDriverStr[] = {"\x0B""Tile Driver"}; //mp2 70
char QuicksandCacheStr[] = {"\x0B""Quicksand Cache"}; //mp2 71
char DeepSeaSalvageStr[] = {"\x0B""Deep Sea Salvage"}; //mp2 72
char NullStr[] = {"\x0B""This Shouldn""\x5C""t Appear"};

//is this font colors for the strings?
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

//this array is constructed from the indexes below that have NullStr and then add 1 to the index
u8 minigameBlacklistIDs[] = {
    0x52, 0x61, 0x65, 0x6A, 0x77, 0x80
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
/* 0x48 */ BowserSlotsStr, //mp2 1
/* 0x49 */ RollOutTheBarrelsStr, //mp2 2
/* 0x4A */ CoffinCongestionStr, //mp2 3
/* 0x4B */ HammerSlammerStr, //mp2 4
/* 0x4C */ GiveMeABrakeStr, //mp2 5
/* 0x4D */ MalletGoRoundStr, //mp2 6
/* 0x4E */ GrabBagStr, //mp2 7
/* 0x4F */ BumperBalloonCarsStr, //mp2 8
/* 0x50 */ RakinEmInStr, //mp2 9
/* 0x51 */ NullStr, //mp2 10
/* 0x52 */ DayAtTheRacesStr, //mp2 11
/* 0x53 */ FaceLiftStrStr, //mp2 12
/* 0x54 */ CrazyCuttersStr, //mp2 13
/* 0x55 */ HotBobombStr, //mp2 14
/* 0x56 */ BowlOverStr, //mp2 15
/* 0x57 */ RainbowRunStr, //mp2 16
/* 0x58 */ CraneGameStr, //mp2 17
/* 0x59 */ MoveToTheMusicStr, //mp2 18
/* 0x5A */ BobOmbBarrageStr, //mp2 19
/* 0x5B */ LookAwayStr, //mp2 20
/* 0x5C */ ShockDropOrRollStr, //mp2 21
/* 0x5D */ LightsOutStr, //mp2 22
/* 0x5E */ FiletRelayStr, //mp2 23
/* 0x5F */ ArcherivalStr, //mp2 24
/* 0x60 */ NullStr, //mp2 25
/* 0x61 */ ToadBandstandStr, //mp2 26
/* 0x62 */ BobsledRunMp2Str, //mp2 27
/* 0x63 */ HandcarHavocMp2Str, //mp2 28
/* 0x64 */ NullStr, //mp2 29
/* 0x65 */ BalloonBurstStr, //mp2 30
/* 0x66 */ SkyPilotsStr, //mp2 31
/* 0x67 */ SpeedHockeyStr, //mp2 32
/* 0x68 */ CakeFactoryStr, //mp2 33
/* 0x69 */ NullStr, //mp2 34
/* 0x6A */ DungeonDashStr, //mp2 35
/* 0x6B */ MagnetCartaStar, //mp2 36
/* 0x6C */ LavaTileIsleStr, //mp2 37
/* 0x6D */ HotRopeJumpStr, //mp2 38
/* 0x6E */ ShellShockedStr, //mp2 39
/* 0x6F */ ToadInTheBoxStr, //mp2 40
/* 0x70 */ MechaMarathonStr, //mp2 41
/* 0x71 */ RollCallStr, //mp2 42
/* 0x72 */ AbandonShipStr, //mp2 43
/* 0x73 */ PlatformPerilStr, //mp2 44
/* 0x74 */ TotemPolePoundStr, //mp2 45
/* 0x75 */ BumperBallsStr, //mp2 46
/* 0x76 */ NullStr, //mp2 47
/* 0x77 */ BombsAwayStr, //mp2 48
/* 0x78 */ TipsyTourneyStr, //mp2 49
/* 0x79 */ HoneycombHavocStr, //mp2 50
/* 0x7A */ HexagonHeatStr, //mp2 51
/* 0x7B */ SkateboardScamperStr, //mp2 52
/* 0x7C */ SlotCarDerbyStr, //mp2 53
/* 0x7D */ ShyGuySaysStr, //mp2 54
/* 0x7E */ SneakNSnoreStr, //mp2 55
/* 0x7F */ NullStr, //mp2 56
/* 0x80 */ DriversEdStr, //mp2 57
/* 0x81 */ ChanceTimeStr, //mp2 58
/* 0x82 */ WesternLandDuelStr, //mp2 59
/* 0x83 */ PirateLandDuelStr, //mp2 60
/* 0x84 */ HorrorLandDuelStr, //mp2 61
/* 0x85 */ SpaceLandDuelStr, //mp2 62
/* 0x86 */ MysteryLandDuelStr, //mp2 63
/* 0x87 */ KoopaLandDuelStr, //mp2 64
/* 0x88 */ BowsersBigBlastStr, //mp2 65
/* 0x89 */ LooneyLumberjacksStr, //mp2 66
/* 0x8A */ TorpedoTargetsStr, //mp2 67
/* 0x8B */ DestructionDuetStr, //mp2 68
/* 0x8C */ DizzyDancingStr, //mp2 69
/* 0x8D */ TileDriverStr, //mp2 70
/* 0x8E */ QuicksandCacheStr, //mp2 71
/* 0x8F */ DeepSeaSalvageStr, //mp2 72
};

u8 new4PMinigameListNormalMp3[] = {
    TREADMILL_GRILL,        TOADSTOOL_TITAN,    ACES_HIGH,      BOUNCE_N_TROUNCE,       ICE_RINK_RISK,
    CHIP_SHOT_CHALLENGE,    PARASOL_PLUMMET,    MESSY_MEMORY,   PICTURE_IMPERFECT,      MARIOS_PUZZLE_PARTY,
    THE_BEAT_GOES_ON,       MPIQ,               CURTAIN_CALL,   WATER_WHIRLED,          FRIGID_BRIDGES,
    AWFUL_TOWER,            CHEEP_CHEEP_CHASE,  PIPE_CLEANERS,  SNOWBALL_SUMMIT,        ROCKIN_RACEWAY,
    //mp2 minigame
    LAVA_TILE_ISLE, HOT_ROPE_JUMP_MP2, SHELL_SHOCKED, TOAD_IN_THE_BOX, MECHA_MARATHON,
    ROLL_CALL, ABANDON_SHIP, PLATFORM_PERIL_MP2, TOTEM_POLE_POUND, BUMPER_BALLS_MP2, 
    BOMBS_AWAY, TIPSY_TOURNEY, HONEYCOMB_HAVOC, HEXAGON_HEAT, SKATEBOARD_SCAMPER,
    SLOT_CAR_DERBY, SHY_GUY_SAYS_MP2, SNEAK_N_SNORE, DIZZY_DANCING, TILE_DRIVER,
    DEEP_SEA_SALVAGE
};
u8 new1v3MinigameListNormalMp3[] = {
    HAND_LINE_AND_SINKER,   COCONUT_CONK,       SPOTLIGHT_SWIM, BOULDER_BALL,   CRAZY_COGS,
    HIDE_AND_SNEAK,         RIDICULOUS_RELAY,   THWOMP_PULL,    RIVER_RAIDERS,  TIDAL_TOSS,
    //mp2 minigames
    BOWL_OVER_MP2, CRANE_GAME_MP2, MOVE_TO_THE_MUSIC, BOB_OMB_BARRAGE, LOOK_AWAY,
    SHOCK_DROP_OR_ROLL, LIGHTS_OUT, FILET_RELAY, ARCHERIVAL, QUICKSAND_CACHE,
    RAINBOW_RUN
};
u8 new2v2MinigameListNormalMp3[] = {
    EATSA_PIZZA,    BABY_BOWSER_BROADSIDE,  PUMP_PUMP_AND_AWAY,     HYPER_HYDRANTS, PICKING_PANIC,
    COSMIC_COASTER, PUDDLE_PADDLE,          ETCH_N_CATCH, LOG_JAM,  SLOT_SYNC,

    TOAD_BANDSTAND, BOBSLED_RUN, HANDCAR_HAVOC_MP2, BALLOON_BURST_MP2, SKY_PILOTS,
    SPEED_HOCKEY, CAKE_FACTORY, MAGNET_CARTA, LOONEY_LUMBERJACKS, TORPEDO_TARGETS,
    DESTRUCTION_DUET, DUNGEON_DASH
};
u8 newBattleMinigameListNormalMp3[] = {
    LOCKED_OUT, ALL_FIRED_UP, STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP,
    SLAP_DOWN, STORM_CHASERS, EYE_SORE,
    GRAB_BAG_MP2, BUMPER_BALLOON_CARS, RAKIN_EM_IN, DAY_AT_THE_RACES, FACE_LIFT_MP2,
    CRAZY_CUTTERS, HOT_BOB_OMB_MP2, BOWSERS_BIG_BLAST
};
u8 newItemMinigameListNormalMp3[] = {
    //no mp2 minigames currently for these
    WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS, SWING_N_SWIPE
};
u8 newDuelMinigameListNormalMp3[] = {
    VINE_WITH_ME, POPGUN_PICK_OFF, END_OF_THE_LINE, BABY_BOWSER_BONKERS, SILLY_SCREWS,
    CROWD_COVER, TICK_TOCK_HOP, BOWSER_TOSS, MOTOR_ROOTER, FOWL_PLAY,
    //mp2 minigames
};

//at 80100EEC originally (normal minigame list, amount of minigames in each category)
u8 newCategoryAmountsNormal[] = {
    ARRAY_COUNT(new4PMinigameListNormalMp3),
    ARRAY_COUNT(new1v3MinigameListNormalMp3),
    ARRAY_COUNT(new2v2MinigameListNormalMp3),
    ARRAY_COUNT(newItemMinigameListNormalMp3),
    ARRAY_COUNT(newBattleMinigameListNormalMp3),
    ARRAY_COUNT(newDuelMinigameListNormalMp3),
};

u8 new4PMinigameListEasyMp3[] = {0x15, 0x19, 0x1C, 0x1D, 0x1E, 0x21, 0x22, 0x26, 0x28};
u8 new1v3MinigameListEasyMp3[] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x09, 0x0A};
u8 new2v2MinigameListEasyMp3[] = {0x0B, 0x0C, 0x10, 0x11, 0x13};
u8 newBattleMinigameListEasyMp3[] = {0x2A, 0x2B, 0x2D, 0x2E};
u8 newItemMinigameListEasyMp3[] = {0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40};
u8 newDuelMinigameListEasyMp3[] = {0x31, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39};

//at 80100EF4 originally (east minigame list, amount of minigames in each category)
u8 newCategoryAmountsEasy[] = {
    ARRAY_COUNT(new4PMinigameListEasyMp3),
    ARRAY_COUNT(new1v3MinigameListEasyMp3),
    ARRAY_COUNT(new2v2MinigameListEasyMp3),
    ARRAY_COUNT(newBattleMinigameListEasyMp3),
    ARRAY_COUNT(newItemMinigameListEasyMp3),
    ARRAY_COUNT(newDuelMinigameListEasyMp3),
};

char* GetNewMinigameString(s32 minigameIndex) {
    return MinigameList[minigameIndex];
}