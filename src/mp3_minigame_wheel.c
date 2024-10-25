#include "marioparty.h"

s32 ForeignMinigameIndexToLoad = -1;
//there's probably a better way to track this
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
char mp2_GrabBagStr[] = {"\x0B""""\x5D""MP2""\x5E"" Grab Bag"}; //mp2 7
char BumperBalloonCarsStr[] = {"\x0B""Bumper Balloon Cars"}; //mp2 8
char RakinEmInStr[] = {"\x0B""Rakin""\x5C"" ""\x5C""em In"}; //mp2 9
//mp2 10 blank
char DayAtTheRacesStr[] = {"\x0B""Day At The Races"}; //mp2 11
char mp2_FaceLiftStr[] = {"""\x5D""MP2""\x5E"" Face Lift"}; //mp2 12
char mp2_CrazyCuttersStr[] = {"""\x5D""MP2""\x5E"" Crazy Cutters"}; //mp2 13
char mp2_HotBobombStr[] = {"\x0B""""\x5D""MP2""\x5E"" Hot Bob""\x3D""omb"}; //mp2 14
char mp2_BowlOverStr[] = {"\x0B""""\x5D""MP2""\x5E"" Bowl Over"}; //mp2 15
char RainbowRunStr[] = {"\x0B""Rainbow Run"}; //mp2 16
char mp2_CraneGameStr[] = {"\x0B""""\x5D""MP2""\x5E"" Crane Game"}; //mp2 17
char MoveToTheMusicStr[] = {"\x0B""Move To The Music"}; //mp2 18
char BobOmbBarrageStr[] = {"\x0B""Bob""\x3D""omb Barrage"}; //mp2 19
char LookAwayStr[] = {"\x0B""Look Away"}; //mp2 20
char ShockDropOrRollStr[] = {"\x0B""Shock""\x82"" Drop or Roll"}; //mp2 21
char LightsOutStr[] = {"\x0B""Lights Out"}; //mp2 22
char FiletRelayStr[] = {"\x0B""Filet Relay"}; //mp2 23
char ArcherivalStr[] = {"\x0B""Archer""\x3D""ival"}; //mp2 24
//mp2 25 blank
char ToadBandstandStr[] = {"\x0B""Toad Bandstand"}; //mp2 26
char mp2_BobsledRunStr[] = {"\x0B""""\x5D""MP2""\x5E"" Bobsled Run"}; //mp2 27
char mp2_HandcarHavocStr[] = {"\x0B""""\x5D""MP2""\x5E"" Handcar Havoc"}; //mp2 28
//mp2 29 blank
char mp2_BalloonBurstStr[] = {"\x0B""""\x5D""MP2""\x5E"" Balloon Burst"}; //mp2 30
char SkyPilotsStr[] = {"\x0B""Sky Pilots"}; //mp2 31
char SpeedHockeyStr[] = {"\x0B""Speed Hockey"}; //mp2 32
char CakeFactoryStr[] = {"\x0B""Cake Factory"}; //mp2 33
//mp2 34
char DungeonDashStr[] = {"\x0B""Dungeon Dash"}; //mp2 35
char MagnetCartaStar[] = {"\x0B""Magnet Carta"}; //mp2 36
char LavaTileIsleStr[] = {"\x0B""Lava Tile Isle"}; //mp2 37
char mp2_HotRopeJumpStr[] = {"\x0B""""\x5D""MP2""\x5E"" Hot Rope Jump"}; //mp2 38
char ShellShockedStr[] = {"\x0B""Shell Shocked"}; //mp2 39
char ToadInTheBoxStr[] = {"\x0B""TOAD In The Box"}; //mp2 40
char MechaMarathonStr[] = {"\x0B""Mecha""\x3D""Marathon"}; //mp2 41
char RollCallStr[] = {"\x0B""Roll Call"}; //mp2 42
char AbandonShipStr[] = {"\x0B""Abandon Ship"}; //mp2 43
char mp2_PlatformPerilStr[] = {"\x0B""""\x5D""MP2""\x5E"" Platform Peril"};; //mp2 44
char TotemPolePoundStr[] = {"\x0B""Totem Pole Pound"}; //mp2 45
char mp2_BumperBallsStr[] = {"\x0B""""\x5D""MP2""\x5E"" Bumper Balls"}; //mp2 46
//mp2 47
char mp2_BombsAwayStr[] = {"\x0B""""\x5D""MP2""\x5E"" Bombs Away"}; //mp2 48
char mp2_TipsyTourneyStr[] = {"\x0B""""\x5D""MP2""\x5E"" Tipsy Tourney"};; //mp2 49
char HoneycombHavocStr[] = {"\x0B""Honeycomb Havoc"}; //mp2 50
char HexagonHeatStr[] = {"\x0B""Hexagon Heat"}; //mp2 51
char mp2_SkateboardScamperStr[] = {"\x0B""""\x5D""MP2""\x5E"" Skateboard Scamper"}; //mp2 52
char mp2_SlotCarDerbyStr[] = {"\x0B""""\x5D""MP2""\x5E"" Slot Car Derby"}; //mp2 53
char mp2_ShyGuySaysStr[] = {"\x0B""""\x5D""MP2""\x5E"" Shy Guy Says"}; //mp2 54
char SneakNSnoreStr[] = {"\x0B""Sneak ""\x5C""n""\x5C"" Snore"}; //mp2 55
//mp2 56
char DriversEdStr[] = {"\x0B""Driver""\x5C""s Ed"}; //mp2 57
char mp2_ChanceTimeStr[] = {"\x0B""""\x5D""MP2""\x5E"" Chance Time"};; //mp2 58
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
//mp1 minigames start
char MemoryMatchStr[] = {"\x0B""Memory Match"}; //mp1 00
char ChanceTimeMp1Str[] = {"\x0B""Chance Time"}; //mp1 01
char SlotMachineStr[] = {"\x0B""Slot Machine"}; //mp1 02
char BuriedTreasureStr[] = {"\x0B""Buried Treasure"}; //mp1 03
char TreasureDiversStr[] = {"\x0B""Treasure Divers"}; //mp1 04
char ShellGameStr[] = {"\x0B""Shell Game"}; //mp1 05
//mp1 06
//mp1 07
//mp1 08
char mp1_HotBobOmbStr[] = {"\x0B""""\x5D""MP1""\x5E"" Hot Bob""\x3D""omb"}; //mp1 09
//mp1 10
char PipeMazeStr[] = {"\x0B""Pipe Maze"}; //mp1 11
char GhostGuestStr[] = {"\x0B""Ghost Guess"}; //mp1 12
char MusicalMushroomStr[] = {"\x0B""Mushroom Musical"}; //mp1 13
char PedalPowerStr[] = {"\x0B""Pedal Power"}; //mp1 14
char mp1_CrazyCutterStr[] = {"\x0B""""\x5D""MP1""\x5E"" Crazy Cutter"}; //mp1 15
char mp1_FaceLiftStr[] = {"\x0B""""\x5D""MP1""\x5E"" Face Lift"}; //mp1 16
char WhackAPlantStr[] = {"\x0B""Whack""\x3D""a""\x3D""Plant"}; //mp1 17
//mp1 18
//mp1 19
char BashNCashStr[] = {"\x0B""Bash ""\x5C""n""\x5C"" Cash"}; //mp1 20
char mp1_BowlOverStr[] = {"\x0B""""\x5D""MP1""\x5E"" Bowl Over"}; //mp1 21
char GroundPoundStr[] = {"\x0B""Ground Pound"}; //mp1 22
char BalloonBurstStr[] = {"\x0B""Balloon Burst"}; //mp1 23
char CoinBlockBlitzStr[] = {"\x0B""Coin Block Blitz"}; //mp1 24
char CoinBlockBashStr[] = {"\x0B""Coin Block Bash"}; //mp1 25
char mp1_SkateboardScamperStr[] = {"\x0B""""\x5D""MP1""\x5E"" Skateboard Scamper"}; //mp1 26
//mp1 27
char BoxMountainMayhemStr[] = {"\x0B""Box Mountain Mayhem"}; //mp1 28
char mp1_PlatformPerilStr[] = {"\x0B""""\x5D""MP1""\x5E"" Platform Peril"}; //mp1 29
char TeeteringTowersStr[] = {"\x0B""Teetering Towers"}; //mp1 30
char MushroomMixupStr[] = {"\x0B""Mushroom Mix""\x3D""Up"}; //mp1 31
//mp1 32
//mp1 33
char HammerDropStr[] = {"\x0B""Hammer Drop"}; //mp1 34
char mp1_GrabBagStr[] = {"\x0B""""\x5D""MP1""\x5E"" Grab Bag"};; //mp1 35
char mp1_BobsledRunStr[] = {"\x0B""""\x5D""MP1""\x5E"" Bobsled Run"}; //mp1 36
char mp1_BumperBallsStr[] = {"\x0B""""\x5D""MP1""\x5E"" Bumper Balls"}; //mp1 37
char TightropeTreacheryStr[] = {"\x0B""Tightrope Treachery"}; //mp1 38
char KnockBlockTowerStr[] = {"\x0B""Knock Block Tower"}; //mp1 39
char mp1_TipsyTourneyStr[] = {"\x0B""""\x5D""MP1""\x5E"" Tipsey Tourney"}; //mp1 40
char mp1_BombsAwayStr[] = {"\x0B""""\x5D""MP1""\x5E"" Bombs Away"}; //mp1 41
char mp1_CraneGameStr[] = {"\x0B""""\x5D""MP1""\x5E"" Crane Game"}; //mp1 42
//mp1 43
//mp1 44
//mp1 45
char CoinShowerFlowerStr[] = {"\x0B""Coin Shower Flower"}; //mp1 46
//mp1 47
//mp1 48
char mp1_SlotCarDerbyStr[] = {"\x0B""""\x5D""MP1""\x5E"" Slot Car Derby"}; //mp1 49
char mp1_BandStandStr[] = {"\x0B""""\x5D""MP1""\x5E"" Mario Bandstand"}; //mp1 50
char DesertDashStr[] = {"\x0B""Desert Dash"}; //mp1 51
char mp1_ShyGuySaysStr[] = {"\x0B""""\x5D""MP1""\x5E"" Shy Guy Says"}; //mp1 52
//mp1 53
char LimboDanceStr[] = {"\x0B""Limbo Dance"}; //mp1 54
char BombsketballStr[] = {"\x0B""Bombsketball"}; //mp1 55
char CastAwaysStr[] = {"\x0B""Cast Aways"}; //mp1 56
char KeyPaWayStr[] = {"\x0B""Key""\x3D""pa""\x3D""Way"}; //mp1 57
char RunningOfTheBulbStr[] = {"\x0B""Running Of The Bulb"}; //mp1 58
char mp1_HotRopeJumpStr[] = {"\x0B""""\x5D""MP1""\x5E"" Hot Rope Jump"}; //mp1 59
//mp1 60
//mp1 61
//mp1 62
char mp1_HandcarHavocStr[] = {"\x0B""""\x5D""MP1""\x5E"" Handcar Havoc"}; //mp1 63
//mp1 64
char DeepSeaDiversStr[] = {"\x0B""Deep Sea Salvage"}; //mp1 65
char PiranhaPursuitStr[] = {"\x0B""Piranha Pursuit"}; //mp1 66
char TugOWarStr[] = {"\x0B""Tug o""\x5C"" War"}; //mp1 67
char PaddleBattleStr[] = {"\x0B""Paddle Battle"}; //mp1 68

char NullStr[] = {"\x0B""This Shouldn""\x5C""t Appear"};

u8 minigameTextColor[] = {
    0, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7,
    //start of mp2 minigames (offset 0x48), make them cyan
    7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7,
    //start of mp1 minigames, make them green
    7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7,
};

//this array is constructed from the indexes below that have NullStr and then add 1 to the index
u8 minigameBlacklistIDs[] = {
    0x48, 0x52, 0x61, 0x65, 0x6A, 0x77, 0x80
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
/* 0x48 */ NullStr, //mp2 0 //TODO: fix index comments
/* 0x49 */ BowserSlotsStr, //mp2 1
/* 0x4A */ RollOutTheBarrelsStr, //mp2 2
/* 0x4B */ CoffinCongestionStr, //mp2 3
/* 0x4C */ HammerSlammerStr, //mp2 4
/* 0x4D */ GiveMeABrakeStr, //mp2 5
/* 0x4E */ MalletGoRoundStr, //mp2 6
/* 0x4F */ mp2_GrabBagStr, //mp2 7
/* 0x50 */ BumperBalloonCarsStr, //mp2 8
/* 0x51 */ RakinEmInStr, //mp2 9
/* 0x52 */ NullStr, //mp2 10
/* 0x53 */ DayAtTheRacesStr, //mp2 11
/* 0x54 */ mp2_FaceLiftStr, //mp2 12
/* 0x55 */ mp2_CrazyCuttersStr, //mp2 13
/* 0x56 */ mp2_HotBobombStr, //mp2 14
/* 0x57 */ mp2_BowlOverStr, //mp2 15
/* 0x58 */ RainbowRunStr, //mp2 16
/* 0x59 */ mp2_CraneGameStr, //mp2 17
/* 0x5A */ MoveToTheMusicStr, //mp2 18
/* 0x5B */ BobOmbBarrageStr, //mp2 19
/* 0x5C */ LookAwayStr, //mp2 20
/* 0x5D */ ShockDropOrRollStr, //mp2 21
/* 0x5E */ LightsOutStr, //mp2 22
/* 0x5F */ FiletRelayStr, //mp2 23
/* 0x60 */ ArcherivalStr, //mp2 24
/* 0x61 */ NullStr, //mp2 25
/* 0x62 */ ToadBandstandStr, //mp2 26
/* 0x63 */ mp2_BobsledRunStr, //mp2 27
/* 0x64 */ mp2_HandcarHavocStr, //mp2 28
/* 0x65 */ NullStr, //mp2 29
/* 0x66 */ mp2_BalloonBurstStr, //mp2 30
/* 0x67 */ SkyPilotsStr, //mp2 31
/* 0x68 */ SpeedHockeyStr, //mp2 32
/* 0x69 */ CakeFactoryStr, //mp2 33
/* 0x6A */ NullStr, //mp2 34
/* 0x6B */ DungeonDashStr, //mp2 35
/* 0x6C */ MagnetCartaStar, //mp2 36
/* 0x6D */ LavaTileIsleStr, //mp2 37
/* 0x6E */ mp2_HotRopeJumpStr, //mp2 38
/* 0x6F */ ShellShockedStr, //mp2 39
/* 0x70 */ ToadInTheBoxStr, //mp2 40
/* 0x71 */ MechaMarathonStr, //mp2 41
/* 0x72 */ RollCallStr, //mp2 42
/* 0x73 */ AbandonShipStr, //mp2 43
/* 0x74 */ mp2_PlatformPerilStr, //mp2 44
/* 0x75 */ TotemPolePoundStr, //mp2 45
/* 0x76 */ mp2_BumperBallsStr, //mp2 46
/* 0x77 */ NullStr, //mp2 47
/* 0x78 */ mp2_BombsAwayStr, //mp2 48
/* 0x79 */ mp2_TipsyTourneyStr, //mp2 49
/* 0x7A */ HoneycombHavocStr, //mp2 50
/* 0x7B */ HexagonHeatStr, //mp2 51
/* 0x7C */ mp2_SkateboardScamperStr, //mp2 52
/* 0x7D */ mp2_SlotCarDerbyStr, //mp2 53
/* 0x7E */ mp2_ShyGuySaysStr, //mp2 54
/* 0x7F */ SneakNSnoreStr, //mp2 55
/* 0x80 */ NullStr, //mp2 56
/* 0x81 */ DriversEdStr, //mp2 57
/* 0x82 */ ChanceTimeStr, //mp2 58
/* 0x83 */ WesternLandDuelStr, //mp2 59
/* 0x84 */ PirateLandDuelStr, //mp2 60
/* 0x85 */ HorrorLandDuelStr, //mp2 61
/* 0x86 */ SpaceLandDuelStr, //mp2 62
/* 0x87 */ MysteryLandDuelStr, //mp2 63
/* 0x88 */ KoopaLandDuelStr, //mp2 64
/* 0x89 */ BowsersBigBlastStr, //mp2 65
/* 0x8A */ LooneyLumberjacksStr, //mp2 66
/* 0x8B */ TorpedoTargetsStr, //mp2 67
/* 0x8C */ DestructionDuetStr, //mp2 68
/* 0x8D */ DizzyDancingStr, //mp2 69
/* 0x8E */ TileDriverStr, //mp2 70
/* 0x8F */ QuicksandCacheStr, //mp2 71
/* 0x90 */ DeepSeaSalvageStr, //mp2 72
#ifdef MP1
/* 0x91 */ MemoryMatchStr, //mp1 00
/* 0x92 */ ChanceTimeMp1Str, //mp1 01
/* 0x93 */ SlotMachineStr, //mp1 02
/* 0x94 */ BuriedTreasureStr, //mp1 03
/* 0x95 */ TreasureDiversStr, //mp1 04
/* 0x96 */ ShellGameStr, //mp1 05
/* 0x97 */ NullStr, //mp1 06 (Same Game, unused)
/* 0x98 */ mp1_HotBobOmbStr, //mp1 07
/* 0x99 */ NullStr, //mp1 08 (yoshi's tongue meeting)
/* 0x9A */ PipeMazeStr, //mp1 09
/* 0x9B */ GhostGuestStr, //mp1 10
/* 0x9C */ MusicalMushroomStr, //mp1 11
/* 0x9D */ PedalPowerStr, //mp1 12
/* 0x9E */ mp1_CrazyCutterStr, //mp1 13
/* 0x9E */ mp1_FaceLiftStr, //mp1 14
/* 0x9F */ WhackAPlantStr, //mp1 15
/* 0xA0 */ BashNCashStr, //mp1 16
/* 0xA1 */ mp1_BowlOverStr, //mp1 17
/* 0xA2 */ GroundPoundStr, //mp1 18
/* 0xA3 */ BalloonBurstStr, //mp1 19
/* 0xA4 */ CoinBlockBlitzStr, //mp1 20
/* 0xA5 */ CoinBlockBashStr, //mp1 21
/* 0xA6 */ mp1_SkateboardScamperStr, //mp1 22
/* 0xA7 */ BoxMountainMayhemStr, //mp1 23
/* 0xA8 */ mp1_PlatformPerilStr, //mp1 24
/* 0xA9 */ TeeteringTowersStr, //mp1 25
/* 0xAA */ MushroomMixupStr, //mp1 26
/* 0xAB */ HammerDropStr, //mp1 27
/* 0xAC */ mp1_GrabBagStr, //mp1 28
/* 0xAD */ mp1_BobsledRunStr, //mp1 29
/* 0xAE */ mp1_BumperBallsStr, //mp1 30
/* 0xAF */ TightropeTreacheryStr, //mp1 31
/* 0xB0 */ KnockBlockTowerStr, //mp1 32
/* 0xB1 */ mp1_TipsyTourneyStr, //mp1 33
/* 0xB2 */ mp1_BombsAwayStr, //mp1 34
/* 0xB3 */ mp1_CraneGameStr, //mp1 35
/* 0xB4 */ CoinShowerFlowerStr, //mp1 36
/* 0xB5 */ mp1_SlotCarDerbyStr, //mp1 37
/* 0xB6 */ mp1_BandStandStr, //mp1 38
/* 0xB7 */ DesertDashStr, //mp1 39
/* 0xB8 */ mp1_ShyGuySaysStr, //mp1 40
/* 0xB9 */ LimboDanceStr, //mp1 41
/* 0xBA */ BombsketballStr, //mp1 42
/* 0xBB */ CastAwaysStr, //mp1 43
/* 0xBC */ KeyPaWayStr, //mp1 44
/* 0xBD */ RunningOfTheBulbStr, //mp1 45
/* 0xBE */ mp1_HotRopeJumpStr, //mp1 46
/* 0xBF */ mp1_HandcarHavocStr, //mp1 47
/* 0xC0 */ DeepSeaDiversStr, //mp1 48
/* 0xC1 */ PiranhaPursuitStr, //mp1 49
/* 0xC2 */ TugOWarStr, //mp1 50
/* 0xC3 */ PaddleBattleStr, //mp1 51
#endif
};

u8 new4PMinigameListNormalMp3[] = {
    TREADMILL_GRILL,        TOADSTOOL_TITAN,    ACES_HIGH,      BOUNCE_N_TROUNCE,       ICE_RINK_RISK,
    CHIP_SHOT_CHALLENGE,    PARASOL_PLUMMET,    MESSY_MEMORY,   PICTURE_IMPERFECT,      MARIOS_PUZZLE_PARTY,
    THE_BEAT_GOES_ON,       MPIQ,               CURTAIN_CALL,   WATER_WHIRLED,          FRIGID_BRIDGES,
    AWFUL_TOWER,            CHEEP_CHEEP_CHASE,  PIPE_CLEANERS,  SNOWBALL_SUMMIT,        ROCKIN_RACEWAY,
    //mp2 minigame
    LAVA_TILE_ISLE, MP2_HOT_ROPE_JUMP, SHELL_SHOCKED, TOAD_IN_THE_BOX, MECHA_MARATHON,
    ROLL_CALL, ABANDON_SHIP, MP2_PLATFORM_PERIL, TOTEM_POLE_POUND, MP2_BUMPER_BALLS, 
    MP2_BOMBS_AWAY, MP2_TIPSY_TOURNEY, HONEYCOMB_HAVOC, HEXAGON_HEAT, MP2_SKATEBOARD_SCAMPER,
    MP2_SLOT_CAR_DERBY, MP2_SHY_GUY_SAYS, SNEAK_N_SNORE, DIZZY_DANCING, TILE_DRIVER,
    DEEP_SEA_SALVAGE,
    //mp1 minigames
    #ifdef MP1
    BURIED_TREASURE, TREASURE_DIVERS, MP1_HOT_BOB_OMB, MUSICAL_MUSHROOM, MP1_CRAZY_CUTTER,
    MP1_FACE_LIFT, MP1_BALLOON_BURST, COIN_BLOCK_BLITZ, MP1_SKATEBOARD_SCAMPER, BOX_MOUNTAIN_MAYHEM,
    MP1_PLATFORM_PERIL, MUSHROOM_MIXUP, MP1_GRAB_BAG, MP1_BUMPER_BALLS, MP1_TIPSY_TOURNEY,
    MP1_BOMBS_AWAY, MARIO_BANDSTAND, MP1_SHY_GUY_SAYS, CAST_AWAYS, KEY_PA_WAY,
    RUNNING_OF_THE_BULB, MP1_HOT_ROPE_JUMP, HAMMER_DROP, MP1_SLOT_CAR_DERBY,
    #endif
    0xFF
};
u8 new1v3MinigameListNormalMp3[] = {
    HAND_LINE_AND_SINKER,   COCONUT_CONK,       SPOTLIGHT_SWIM, BOULDER_BALL,   CRAZY_COGS,
    HIDE_AND_SNEAK,         RIDICULOUS_RELAY,   THWOMP_PULL,    RIVER_RAIDERS,  TIDAL_TOSS,
    //mp2 minigames
    MP2_BOWL_OVER, MP2_CRANE_GAME, MOVE_TO_THE_MUSIC, BOB_OMB_BARRAGE, LOOK_AWAY,
    SHOCK_DROP_OR_ROLL, LIGHTS_OUT, FILET_RELAY, ARCHERIVAL, QUICKSAND_CACHE,
    RAINBOW_RUN,
    //mp1 minigames
    #ifdef MP1
    PIPE_MAZE, BASH_N_CASH, MP1_BOWL_OVER, COIN_BLOCK_BASH, TIGHTROPE_TREACHERY,
    MP1_CRANE_GAME, PIRANHA_PURSUIT, TUG_O_WAR, PADDLE_BATTLE, COIN_SHOWER_FLOWER,
    #endif
    0xFF
};
u8 new2v2MinigameListNormalMp3[] = {
    EATSA_PIZZA,    BABY_BOWSER_BROADSIDE,  PUMP_PUMP_AND_AWAY,     HYPER_HYDRANTS, PICKING_PANIC,
    COSMIC_COASTER, PUDDLE_PADDLE,          ETCH_N_CATCH, LOG_JAM,  SLOT_SYNC,

    //mp2 minigames
    TOAD_BANDSTAND, MP2_BOBSLED_RUN, MP2_HANDCAR_HAVOC, MP2_BALLOON_BURST, SKY_PILOTS,
    SPEED_HOCKEY, CAKE_FACTORY, MAGNET_CARTA, LOONEY_LUMBERJACKS, TORPEDO_TARGETS,
    DESTRUCTION_DUET, DUNGEON_DASH,
    //mp1 minigames
    #ifdef MP1
    MP1_BOBSLED_RUN, DESERT_DASH, BOMBSKETBALL, MP1_HANDCAR_HAVOC, DEEP_SEA_DIVERS,
    #endif
    0xFF
};
u8 newBattleMinigameListNormalMp3[] = {
    LOCKED_OUT, ALL_FIRED_UP, STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP,
    SLAP_DOWN, STORM_CHASERS, EYE_SORE,
    MP2_GRAB_BAG, BUMPER_BALLOON_CARS, RAKIN_EM_IN, DAY_AT_THE_RACES, MP2_FACE_LIFT,
    MP2_CRAZY_CUTTERS, MP2_HOT_BOB_OMB, BOWSERS_BIG_BLAST,
    0xFF
};
u8 newItemMinigameListNormalMp3[] = {
    //no mp2 minigames currently for these
    WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS, SWING_N_SWIPE,
    0xFF
};
u8 newDuelMinigameListNormalMp3[] = {
    VINE_WITH_ME, POPGUN_PICK_OFF, END_OF_THE_LINE, BABY_BOWSER_BONKERS, SILLY_SCREWS,
    CROWD_COVER, TICK_TOCK_HOP, BOWSER_TOSS, MOTOR_ROOTER, FOWL_PLAY,
    0xFF
};

//at 80100EEC originally (normal minigame list, amount of minigames in each category)
u8 newCategoryAmountsNormal[] = {
    ARRAY_COUNT(new4PMinigameListNormalMp3) -1,
    ARRAY_COUNT(new1v3MinigameListNormalMp3) -1,
    ARRAY_COUNT(new2v2MinigameListNormalMp3) -1,
    ARRAY_COUNT(newItemMinigameListNormalMp3) -1,
    ARRAY_COUNT(newBattleMinigameListNormalMp3) -1,
    ARRAY_COUNT(newDuelMinigameListNormalMp3) -1,
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