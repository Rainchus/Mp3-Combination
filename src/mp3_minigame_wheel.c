#include "marioparty.h"
#include "mp3.h"

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
char MessyMemoryStr[] = {"\x0B""Messy Memory"};
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
char mp3_ChanceTimeStr[] = {"\x0B""Chance Time"};
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
char mp2_PlatformPerilStr[] = {"\x0B""""\x5D""MP2""\x5E"" Platform Peril"}; //mp2 44
char TotemPolePoundStr[] = {"\x0B""Totem Pole Pound"}; //mp2 45
char mp2_BumperBallsStr[] = {"\x0B""""\x5D""MP2""\x5E"" Bumper Balls"}; //mp2 46
//mp2 47
char mp2_BombsAwayStr[] = {"\x0B""""\x5D""MP2""\x5E"" Bombs Away"}; //mp2 48
char mp2_TipsyTourneyStr[] = {"\x0B""""\x5D""MP2""\x5E"" Tipsy Tourney"}; //mp2 49
char HoneycombHavocStr[] = {"\x0B""Honeycomb Havoc"}; //mp2 50
char HexagonHeatStr[] = {"\x0B""Hexagon Heat"}; //mp2 51
char mp2_SkateboardScamperStr[] = {"\x0B""""\x5D""MP2""\x5E"" Skateboard Scamper"}; //mp2 52
char mp2_SlotCarDerbyStr[] = {"\x0B""""\x5D""MP2""\x5E"" Slot Car Derby"}; //mp2 53
char mp2_ShyGuySaysStr[] = {"\x0B""""\x5D""MP2""\x5E"" Shy Guy Says"}; //mp2 54
char SneakNSnoreStr[] = {"\x0B""Sneak ""\x5C""n""\x5C"" Snore"}; //mp2 55
//mp2 56
char DriversEdStr[] = {"\x0B""Driver""\x5C""s Ed"}; //mp2 57
char mp2_ChanceTimeStr[] = {"\x0B""""\x5D""MP2""\x5E"" Chance Time"}; //mp2 58
char WesternLandDuelStr[] = {"\x0B""Western Land Duel"}; //mp2 59
char PirateLandDuelStr[] = {"\x0B""Pirate Land Duel"}; //mp2 60
char HorrorLandDuelStr[] = {"\x0B""Horror Land Duel"}; //mp2 61
char SpaceLandDuelStr[] = {"\x0B""Space Land Duel"}; //mp2 62
char MysteryLandDuelStr[] = {"\x0B""Mystery Land Duel"}; //mp2 63
char KoopaLandDuelStr[] = {"\x0B""Bowser Land Duel"}; //mp2 64
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
char mp1_ChanceTimeStr[] = {"\x0B""Chance Time"}; //mp1 01
char SlotMachineStr[] = {"\x0B""Slot Machine"}; //mp1 02
char BuriedTreasureStr[] = {"\x0B""Buried Treasure"}; //mp1 03
char TreasureDiversStr[] = {"\x0B""Treasure Divers"}; //mp1 04
char ShellGameStr[] = {"\x0B""Shell Game"}; //mp1 05
char SameGameStr[] = {"\x0B""Same Game"}; //mp1 06
//mp1 07
char YoshisToungueStr[] = {"\x0B""Yoshi""\x5C""s Tongue Meeting"}; //mp1 08
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
char mp1_GrabBagStr[] = {"\x0B""""\x5D""MP1""\x5E"" Grab Bag"}; //mp1 35
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
// u8 minigameBlacklistIDs[] = {
//     0x48, 0x52, 0x61, 0x65, 0x6A, 0x77, 0x80
// };

mp3MinigameIndexTable minigameLUT[] = {
    {ACES_HIGH, AcesHighStr, 23, PLAYERS_4P},
    {AWFUL_TOWER, AwfulTowerStr, 37, PLAYERS_4P},
    {BOUNCE_N_TROUNCE, BounceNTrounceStr, 24, PLAYERS_4P},
    {CHEEP_CHEEP_CHASE, CheepCheepChaseStr, 38, PLAYERS_4P},
    {CHIP_SHOT_CHALLENGE, ChipShotChallengeStr, 27, PLAYERS_4P},
    {CURTAIN_CALL, CurtainCallStr, 34, PLAYERS_4P},
    {FRIGID_BRIDGES, FrigidBridgesStr, 36, PLAYERS_4P},
    {ICE_RINK_RISK, IceRinkRiskStr, 25, PLAYERS_4P},
    {MPIQ, MPIQStr, 33, PLAYERS_4P},
    {MARIOS_PUZZLE_PARTY, MariosPuzzlePartyStr, 31, PLAYERS_4P},
    {MESSY_MEMORY, MessyMemoryStr, 29, PLAYERS_4P},
    {PARASOL_PLUMMET, ParasolPlummetStr, 28, PLAYERS_4P},
    {PICTURE_IMPERFECT, PictureImperfectStr, 30, PLAYERS_4P},
    {PIPE_CLEANERS, PipeCleanersStr, 39, PLAYERS_4P},
    {ROCKIN_RACEWAY, RockinRacewayStr, 44, PLAYERS_4P},
    {SNOWBALL_SUMMIT, SnowballSummitStr, 40, PLAYERS_4P},
    {THE_BEAT_GOES_ON, TheBeatGoesOnStr, 32, PLAYERS_4P},
    {TOADSTOOL_TITAN, ToadstoolTitanStr, 22, PLAYERS_4P},
    {TREADMILL_GRILL, TreadmillGrillStr, 21, PLAYERS_4P},
    {WATER_WHIRLED, WaterWhirledStr, 35, PLAYERS_4P},

    //mp2 4p minigames
    {ABANDON_SHIP, AbandonShipStr, 43, PLAYERS_4P}, //mp2 43
    {MP2_BOMBS_AWAY, mp2_BombsAwayStr, 48, PLAYERS_4P}, //mp2 48
    {MP2_BUMPER_BALLS, mp2_BumperBallsStr, 46, PLAYERS_4P}, //mp2 46
    {DEEP_SEA_SALVAGE, DeepSeaSalvageStr, 72, PLAYERS_4P}, //mp2 72
    {DIZZY_DANCING, DizzyDancingStr, 69, PLAYERS_4P}, //mp2 69
    {HEXAGON_HEAT, HexagonHeatStr, 51, PLAYERS_4P}, //mp2 51
    {HONEYCOMB_HAVOC, HoneycombHavocStr, 50, PLAYERS_4P}, //mp2 50
    {MP2_HOT_ROPE_JUMP, mp2_HotRopeJumpStr, 38, PLAYERS_4P}, //mp2 38
    {LAVA_TILE_ISLE, LavaTileIsleStr, 37, PLAYERS_4P}, //mp2 37
    {MECHA_MARATHON, MechaMarathonStr, 41, PLAYERS_4P}, //mp2 41
    {MP2_PLATFORM_PERIL, mp2_PlatformPerilStr, 44, PLAYERS_4P}, //mp2 44
    {ROLL_CALL, RollCallStr, 42, PLAYERS_4P}, //mp2 42
    {SHELL_SHOCKED, ShellShockedStr, 39, PLAYERS_4P}, //mp2 39
    {MP2_SHY_GUY_SAYS, mp2_ShyGuySaysStr, 54, PLAYERS_4P}, //mp2 54
    {MP2_SKATEBOARD_SCAMPER, mp2_SkateboardScamperStr, 52, PLAYERS_4P}, //mp2 52
    {MP2_SLOT_CAR_DERBY, mp2_SlotCarDerbyStr, 53, PLAYERS_4P}, //mp2 53
    {SNEAK_N_SNORE, SneakNSnoreStr, 55, PLAYERS_4P}, //mp2 55
    {TILE_DRIVER, TileDriverStr, 70, PLAYERS_4P}, //mp2 70
    {MP2_TIPSY_TOURNEY, mp2_TipsyTourneyStr, 49, PLAYERS_4P}, //mp2 49
    {TOAD_IN_THE_BOX, ToadInTheBoxStr, 40, PLAYERS_4P}, //mp2 40
    {TOTEM_POLE_POUND, TotemPolePoundStr, 45, PLAYERS_4P}, //mp2 45

    #ifdef MP1
    //mp1 4p minigames
    {MP1_BALLOON_BURST, BalloonBurstStr, 19, PLAYERS_4P}, //mp1 19
    {MP1_BOMBS_AWAY, mp1_BombsAwayStr, 34, PLAYERS_4P}, //mp1 34  
    {BOX_MOUNTAIN_MAYHEM, BoxMountainMayhemStr, 23, PLAYERS_4P}, //mp1 23
    {MP1_BUMPER_BALLS, mp1_BumperBallsStr, 30, PLAYERS_4P}, //mp1 30
    {BURIED_TREASURE, BuriedTreasureStr, 3, PLAYERS_4P}, //mp1 3
    {CAST_AWAYS, CastAwaysStr, 43, PLAYERS_4P}, //mp1 43
    {COIN_BLOCK_BLITZ, CoinBlockBlitzStr, 20, PLAYERS_4P}, //mp1 20
    {MP1_CRAZY_CUTTER, mp1_CrazyCutterStr, 13, PLAYERS_4P}, //mp1 13
    {MP1_FACE_LIFT, mp1_FaceLiftStr, 14, PLAYERS_4P}, //mp1 14
    {MP1_GRAB_BAG, mp1_GrabBagStr, 28, PLAYERS_4P}, //mp1 28
    {HAMMER_DROP, HammerDropStr, 55, PLAYERS_4P}, //mp1 55
    {MP1_HOT_BOB_OMB, mp1_HotBobOmbStr, 7, PLAYERS_4P}, //mp1 7
    {MP1_HOT_ROPE_JUMP, mp1_HotRopeJumpStr, 46, PLAYERS_4P}, //mp1 46
    {KEY_PA_WAY, KeyPaWayStr, 44, PLAYERS_4P}, //mp1 44
    {MARIO_BANDSTAND, mp1_BandStandStr, 38, PLAYERS_4P}, //mp1 38
    {MUSHROOM_MIXUP, MushroomMixupStr, 26, PLAYERS_4P}, //mp1 26
    {MUSICAL_MUSHROOM, MusicalMushroomStr, 11, PLAYERS_4P}, //mp1 11
    {MP1_PLATFORM_PERIL, mp1_PlatformPerilStr, 24, PLAYERS_4P}, //mp1 24
    {RUNNING_OF_THE_BULB, RunningOfTheBulbStr, 45, PLAYERS_4P}, //mp1 45
    {MP1_SHY_GUY_SAYS, mp1_ShyGuySaysStr, 40, PLAYERS_4P}, //mp1 40
    {MP1_SKATEBOARD_SCAMPER, mp1_SkateboardScamperStr, 22, PLAYERS_4P}, //mp1 22  
    {MP1_SLOT_CAR_DERBY, mp1_SlotCarDerbyStr, 37, PLAYERS_4P}, //mp1 37
    {MP1_TIPSY_TOURNEY, mp1_TipsyTourneyStr, 33, PLAYERS_4P}, //mp1 33
    {TREASURE_DIVERS, TreasureDiversStr, 4, PLAYERS_4P}, //mp1 4
    {YOSHIS_TONGUE_MEETING, YoshisToungueStr, 8, PLAYERS_4P}, //mp1 8
    #endif

    //1v3 minigames
    {BOULDER_BALL, BoulderBallStr, 4, PLAYERS_1V3},
    {COCONUT_CONK, CoconutConkStr, 2, PLAYERS_1V3},
    {CRAZY_COGS, CrazyCogsStr, 5, PLAYERS_1V3},
    {HAND_LINE_AND_SINKER, HookLineAndSinkerStr, 1, PLAYERS_1V3},
    {HIDE_AND_SNEAK, HideAndSneakStr, 6, PLAYERS_1V3},
    {RIDICULOUS_RELAY, RidiculousRelayStr, 7, PLAYERS_1V3},
    {RIVER_RAIDERS, RiverRaidersStr, 9, PLAYERS_1V3},
    {SPOTLIGHT_SWIM, SpotlightSwimStr, 3, PLAYERS_1V3},
    {THWOMP_PULL, ThwompPullStr, 8, PLAYERS_1V3},
    {TIDAL_TOSS, TidalTossStr, 10, PLAYERS_1V3},

    //mp2 1v3 minigames
    {ARCHERIVAL, ArcherivalStr, 24, PLAYERS_1V3}, //mp2 24
    {BOB_OMB_BARRAGE, BobOmbBarrageStr, 19, PLAYERS_1V3}, //mp2 19
    {MP2_BOWL_OVER, mp2_BowlOverStr, 15, PLAYERS_1V3}, //mp2 15
    {MP2_CRANE_GAME, mp2_CraneGameStr, 17, PLAYERS_1V3}, //mp2 17
    {FILET_RELAY, FiletRelayStr, 23, PLAYERS_1V3}, //mp2 23
    {LIGHTS_OUT, LightsOutStr, 22, PLAYERS_1V3}, //mp2 22
    {LOOK_AWAY, LookAwayStr, 20, PLAYERS_1V3}, //mp2 20
    {MOVE_TO_THE_MUSIC, MoveToTheMusicStr, 18, PLAYERS_1V3}, //mp2 18
    {QUICKSAND_CACHE, QuicksandCacheStr, 71, PLAYERS_1V3}, //mp2 71
    {RAINBOW_RUN, RainbowRunStr, 16, PLAYERS_1V3}, //mp2 16
    {SHOCK_DROP_OR_ROLL, ShockDropOrRollStr, 21, PLAYERS_1V3}, //mp2 21

    #ifdef MP1
    //mp1 1v3 minigames
    {BASH_N_CASH, BashNCashStr, 16, PLAYERS_1V3}, //mp1 16
    {MP1_BOWL_OVER, mp1_BowlOverStr, 17, PLAYERS_1V3}, //mp1 17
    {COIN_BLOCK_BASH, CoinBlockBashStr, 21, PLAYERS_1V3}, //mp1 21
    {COIN_SHOWER_FLOWER, CoinShowerFlowerStr, 36, PLAYERS_1V3}, //mp1 36
    {MP1_CRANE_GAME, mp1_CraneGameStr, 35, PLAYERS_1V3}, //mp1 35
    {PADDLE_BATTLE, PaddleBattleStr, 51, PLAYERS_1V3}, //mp1 51
    {PIPE_MAZE, PipeMazeStr, 9, PLAYERS_1V3}, //mp1 9
    {PIRANHA_PURSUIT, PiranhaPursuitStr, 49, PLAYERS_1V3}, //mp1 49
    {TIGHTROPE_TREACHERY, TightropeTreacheryStr, 31, PLAYERS_1V3}, //mp1 31
    {TUG_O_WAR, TugOWarStr, 50, PLAYERS_1V3}, //mp1 50
    #endif

    //2v2 minigames
    {BABY_BOWSER_BROADSIDE, BabyBowserBroadsideStr, 12, PLAYERS_2V2},
    {COSMIC_COASTER, CosmicCoasterStr, 16, PLAYERS_2V2},
    {EATSA_PIZZA, EatsaPizzaStr, 11, PLAYERS_2V2},
    {ETCH_N_CATCH, EtchNCatchStr, 18, PLAYERS_2V2},
    {HYPER_HYDRANTS, HyperHydrantsStr, 14, PLAYERS_2V2},
    {LOG_JAM, LogJamStr, 19, PLAYERS_2V2},
    {PICKING_PANIC, PickingPanicStr, 15, PLAYERS_2V2},
    {PUDDLE_PADDLE, PuddlePaddleStr, 17, PLAYERS_2V2},
    {PUMP_PUMP_AND_AWAY, PumpPumpAndAwayStr, 13, PLAYERS_2V2},
    {SLOT_SYNC, SlotSyncStr, 20, PLAYERS_2V2},
    {TORPEDO_TARGETS, TorpedoTargetsStr, 67, PLAYERS_2V2}, //mp2 67

    //mp2 2v2 minigames
    {MP2_BALLOON_BURST, mp2_BalloonBurstStr, 30, PLAYERS_2V2}, //mp2 30
    {MP2_BOBSLED_RUN, mp2_BobsledRunStr, 27, PLAYERS_2V2}, //mp2 27
    {CAKE_FACTORY, CakeFactoryStr, 33, PLAYERS_2V2}, //mp2 33
    {DESTRUCTION_DUET, DestructionDuetStr, 68, PLAYERS_2V2}, //mp2 68
    {DUNGEON_DASH, DungeonDashStr, 35, PLAYERS_2V2}, //mp2 35
    {MP2_HANDCAR_HAVOC, mp2_HandcarHavocStr, 28, PLAYERS_2V2}, //mp2 28
    {LOONEY_LUMBERJACKS, LooneyLumberjacksStr, 66, PLAYERS_2V2}, //mp2 66
    {MAGNET_CARTA, MagnetCartaStar, 36, PLAYERS_2V2}, //mp2 36
    {SKY_PILOTS, SkyPilotsStr, 31, PLAYERS_2V2}, //mp2 31
    {SPEED_HOCKEY, SpeedHockeyStr, 32, PLAYERS_2V2}, //mp2 32
    {TOAD_BANDSTAND, ToadBandstandStr, 26, PLAYERS_2V2}, //mp2 26

    #ifdef MP1
    //mp1 2v2 minigames
    {MP1_BOBSLED_RUN, mp1_BobsledRunStr, 29, PLAYERS_2V2}, //mp1 29
    {BOMBSKETBALL, BombsketballStr, 42, PLAYERS_2V2}, //mp1 42
    {DEEP_SEA_DIVERS, DeepSeaDiversStr, 48, PLAYERS_2V2}, //mp1 48
    {DESERT_DASH, DesertDashStr, 39, PLAYERS_2V2}, //mp1 39
    {MP1_HANDCAR_HAVOC, mp1_HandcarHavocStr, 47, PLAYERS_2V2}, //mp1 47
    #endif

    //battle minigames
    {ALL_FIRED_UP, AllFiredUpStr, 41, PLAYERS_BATTLE},
    {EYE_SORE, EyeSoreStr, 48, PLAYERS_BATTLE},
    {LOCKED_OUT, LockedOutStr, 26, PLAYERS_BATTLE},
    {MERRY_GO_CHOMP, MerryGoChompStr, 45, PLAYERS_BATTLE},
    {SLAP_DOWN, SlapDownStr, 46, PLAYERS_BATTLE},
    {STACKED_DECK, StackedDeckStr, 42, PLAYERS_BATTLE},
    {STORM_CHASERS, StormChasersStr, 47, PLAYERS_BATTLE},
    {THREE_DOOR_MONTY, ThreeDoorMontyStr, 43, PLAYERS_BATTLE},

    //mp2 battle minigames
    {BOWSERS_BIG_BLAST, BowsersBigBlastStr, 65, PLAYERS_DUEL}, //mp2 65
    {BUMPER_BALLOON_CARS, BumperBalloonCarsStr, 8, PLAYERS_BATTLE}, //mp2 8
    {MP2_CRAZY_CUTTERS, mp2_CrazyCuttersStr, 13, PLAYERS_BATTLE}, //mp2 13
    {DAY_AT_THE_RACES, DayAtTheRacesStr, 11, PLAYERS_BATTLE}, //mp2 11
    {MP2_FACE_LIFT, mp2_FaceLiftStr, 12, PLAYERS_BATTLE}, //mp2 12
    {MP2_GRAB_BAG, mp2_GrabBagStr, 7, PLAYERS_BATTLE}, //mp2 7
    {MP2_HOT_BOB_OMB, mp2_HotBobombStr, 14, PLAYERS_BATTLE}, //mp2 14
    {RAKIN_EM_IN, RakinEmInStr, 9, PLAYERS_BATTLE}, //mp2 9

    //item minigames
    {BOBBING_BOW_LOONS, BobbingBowloonsStr, 61, PLAYERS_ITEM},
    {DORRIE_DIP, DorrieDipStr, 62, PLAYERS_ITEM},
    {HEY_BATTER_BATTER, HeyBatterBatterStr, 60, PLAYERS_ITEM},
    {SWING_N_SWIPE, SwingNSwipeStr, 64, PLAYERS_ITEM},
    {SWINGING_WITH_SHARKS, SwingingWithSharksStr, 63, PLAYERS_ITEM},
    {WINNERS_WHEEL, WinnersWheelStr, 59, PLAYERS_ITEM},
    
    //mp2 item minigames
    
    {BOWSER_SLOTS, BowserSlotsStr, 1, PLAYERS_ITEM}, //mp2 1
    {COFFIN_CONGESTION, CoffinCongestionStr, 3, PLAYERS_ITEM}, //mp2 3
    {GIVE_ME_A_BRAKE, GiveMeABrakeStr, 5, PLAYERS_ITEM}, //mp2 5
    {HAMMER_SLAMMER, HammerSlammerStr, 4, PLAYERS_ITEM}, //mp2 4
    {MALLET_GO_ROUND, MalletGoRoundStr, 6, PLAYERS_ITEM}, //mp2 6
    {ROLL_OUT_THE_BARRELS, RollOutTheBarrelsStr, 2, PLAYERS_ITEM}, //mp2 2
    
    //duel minigames
    {BABY_BOWSER_BONKERS, BabyBowserBonkersStr, 53, PLAYERS_DUEL},
    {BOWSER_TOSS, BowserTossStr, 52, PLAYERS_DUEL},
    {CROWD_COVER, CrowdCoverStr, 56, PLAYERS_DUEL},
    {END_OF_THE_LINE, EndOfTheLinerStr, 51, PLAYERS_DUEL},
    {FOWL_PLAY, FowlPlayStr, 58, PLAYERS_DUEL},
    {MOTOR_ROOTER, MotorRooterStr, 54, PLAYERS_DUEL},
    {POPGUN_PICK_OFF, PopgunPickOffStr, 50, PLAYERS_DUEL},
    {SILLY_SCREWS, SillyScrewsStr, 55, PLAYERS_DUEL},
    {TICK_TOCK_HOP, TickTockHopStr, 57, PLAYERS_DUEL},
    {VINE_WITH_ME, VineWithMeStr, 49, PLAYERS_DUEL},
    
    //mp2 duel minigames
    {KOOPA_LAND_DUEL, KoopaLandDuelStr, 64, PLAYERS_DUEL}, //mp2 64
    {HORROR_LAND_DUEL, HorrorLandDuelStr, 61, PLAYERS_DUEL}, //mp2 61
    {MYSTERY_LAND_DUEL, MysteryLandDuelStr, 63, PLAYERS_DUEL}, //mp2 63
    {PIRATE_LAND_DUEL, PirateLandDuelStr, 60, PLAYERS_DUEL}, //mp2 60
    {SPACE_LAND_DUEL, SpaceLandDuelStr, 62, PLAYERS_DUEL}, //mp2 62
    {WESTERN_LAND_DUEL, WesternLandDuelStr, 59, PLAYERS_DUEL}, //mp2 59

    //mp3 game guy minigames
    {GAME_GUYS_LUCKY_7, GameGuysLucky7Str, 68, PLAYERS_GAME_GUY},
    {GAME_GUYS_MAGIC_BOXES, GameGuysMagicBoxesStr, 69, PLAYERS_GAME_GUY},
    {GAME_GUYS_ROULETTE, GameGuysRouletteStr, 67, PLAYERS_GAME_GUY},
    {GAME_GUYS_SWEET_SURPRISE, GameGuysSweetSurpriseStr, 70, PLAYERS_GAME_GUY},
    
    //special overlays
    {MP3_CHANCE_TIME, mp3_ChanceTimeStr, 65, PLAYERS_SPECIAL},
    {DIZZY_DINGHIES, DizzyDinghiesStr, 71, PLAYERS_SPECIAL},
    {MARIO_PUZZLE_PARTY_PRO, MariosPuzzlePartyPro2Str, 72, PLAYERS_SPECIAL},
    {STARDUST_BATTLE, StardustBattleStr, 66, PLAYERS_SPECIAL},
    {MP2_CHANCE_TIME, mp2_ChanceTimeStr, 58, PLAYERS_SPECIAL}, //mp2 58
    {DRIVERS_ED, DriversEdStr, 57, PLAYERS_SPECIAL}, //mp2 57
    #ifdef MP1
    {MP1_CHANCE_TIME, mp1_ChanceTimeStr, 1, PLAYERS_SPECIAL}, //mp1 1

    
    //mp1 1p minigames
    {GHOST_GUESS, GhostGuestStr, 10, PLAYERS_1P}, //mp1 10
    {GROUND_POUND, GroundPoundStr, 18, PLAYERS_1P}, //mp1 18
    {KNOCK_BLOCK_TOWER, KnockBlockTowerStr, 32, PLAYERS_1P}, //mp1 32
    {LIMBO_DANCE, LimboDanceStr, 41, PLAYERS_1P}, //mp1 41
    {MEMORY_MATCH, MemoryMatchStr, 0, PLAYERS_1P}, //mp1 0
    {PEDAL_POWER, PedalPowerStr, 12, PLAYERS_1P}, //mp1 12
    {SLOT_MACHINE, SlotMachineStr, 2, PLAYERS_1P}, //mp1 2
    {SHELL_GAME, ShellGameStr, 5, PLAYERS_1P}, //mp1 5
    {SAME_GAME, SameGameStr, 6, PLAYERS_1P}, //mp1 6
    {TEETERING_TOWER, TeeteringTowersStr, 25, PLAYERS_1P}, //mp1 25
    {WHACKA_A_PLANT, WhackAPlantStr, 15, PLAYERS_1P}, //mp1 15
    #endif
};

s32 ForeignMinigameIDToGame(s32 minigameCombinedIndex) {
    s32 i;
    //find the minigame and get the overlay id for the specific game
    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            return minigameLUT[i].gameOverlayID;
        }
    }
    return -1; //minigame not found
}

// char* MinigameList[] = { //add 1 to this value and stick into table
// /* 0x00 */ HookLineAndSinkerStr,
// /* 0x01 */ CoconutConkStr,
// /* 0x02 */ SpotlightSwimStr,
// /* 0x03 */ BoulderBallStr,
// /* 0x04 */ CrazyCogsStr,
// /* 0x05 */ HideAndSneakStr,
// /* 0x06 */ RidiculousRelayStr,
// /* 0x07 */ ThwompPullStr,
// /* 0x08 */ RiverRaidersStr,
// /* 0x09 */ TidalTossStr,
// /* 0x0A */ EatsaPizzaStr,
// /* 0x0B */ BabyBowserBroadsideStr,
// /* 0x0C */ PumpPumpAndAwayStr,
// /* 0x0D */ HyperHydrantsStr,
// /* 0x0E */ PickingPanicStr,
// /* 0x0F */ CosmicCoasterStr,
// /* 0x10 */ PuddlePaddleStr,
// /* 0x11 */ EtchNCatchStr,
// /* 0x12 */ LogJamStr,
// /* 0x13 */ SlotSyncStr,
// /* 0x14 */ TreadmillGrillStr,
// /* 0x15 */ ToadstoolTitanStr,
// /* 0x16 */ AcesHighStr,
// /* 0x17 */ BounceNTrounceStr,
// /* 0x18 */ IceRinkRiskStr,
// /* 0x19 */ LockedOutStr,
// /* 0x1A */ ChipShotChallengeStr,
// /* 0x1B */ ParasolPlummetStr,
// /* 0x1C */ MessyMemoryStr,
// /* 0x1D */ PictureImperfectStr,
// /* 0x1E */ MariosPuzzlePartyStr,
// /* 0x1F */ TheBeatGoesOnStr,
// /* 0x20 */ MPIQStr,
// /* 0x21 */ CurtainCallStr,
// /* 0x22 */ WaterWhirledStr,
// /* 0x23 */ FrigidBridgesStr,
// /* 0x24 */ AwfulTowerStr,
// /* 0x25 */ CheepCheepChaseStr,
// /* 0x26 */ PipeCleanersStr,
// /* 0x27 */ SnowballSummitStr,
// /* 0x28 */ AllFiredUpStr,
// /* 0x29 */ StackedDeckStr,
// /* 0x2A */ ThreeDoorMontyStr,
// /* 0x2B */ RockinRacewayStr,
// /* 0x2C */ MerryGoChompStr,
// /* 0x2D */ SlapDownStr,
// /* 0x2E */ StormChasersStr,
// /* 0x2F */ EyeSoreStr,
// /* 0x30 */ VineWithMeStr,
// /* 0x31 */ PopgunPickOffStr,
// /* 0x32 */ EndOfTheLinerStr,
// /* 0x33 */ BowserTossStr,
// /* 0x34 */ BabyBowserBonkersStr,
// /* 0x35 */ MotorRooterStr,
// /* 0x36 */ SillyScrewsStr,
// /* 0x37 */ CrowdCoverStr,
// /* 0x38 */ TickTockHopStr,
// /* 0x39 */ FowlPlayStr,
// /* 0x3A */ WinnersWheelStr,
// /* 0x3B */ HeyBatterBatterStr,
// /* 0x3C */ BobbingBowloonsStr,
// /* 0x3D */ DorrieDipStr,
// /* 0x3E */ SwingingWithSharksStr,
// /* 0x3F */ SwingNSwipeStr,
// /* 0x40 */ ChanceTimeStr,
// /* 0x41 */ StardustBattleStr,
// /* 0x42 */ GameGuysRouletteStr,
// /* 0x43 */ GameGuysLucky7Str,
// /* 0x44 */ GameGuysMagicBoxesStr,
// /* 0x45 */ GameGuysSweetSurpriseStr,
// /* 0x46 */ DizzyDinghiesStr,
// /* 0x47 */ MariosPuzzlePartyPro2Str,
// /* 0x48 */ BowserSlotsStr, //mp2 1
// /* 0x49 */ RollOutTheBarrelsStr, //mp2 2
// /* 0x4A */ CoffinCongestionStr, //mp2 3
// /* 0x4B */ HammerSlammerStr, //mp2 4
// /* 0x4C */ GiveMeABrakeStr, //mp2 5
// /* 0x4D */ MalletGoRoundStr, //mp2 6
// /* 0x4E */ mp2_GrabBagStr, //mp2 7
// /* 0x4F */ BumperBalloonCarsStr, //mp2 8
// /* 0x50 */ RakinEmInStr, //mp2 9
// /* 0x51 */ DayAtTheRacesStr, //mp2 11
// /* 0x52 */ mp2_FaceLiftStr, //mp2 12
// /* 0x53 */ mp2_CrazyCuttersStr, //mp2 13
// /* 0x54 */ mp2_HotBobombStr, //mp2 14
// /* 0x55 */ mp2_BowlOverStr, //mp2 15
// /* 0x56 */ RainbowRunStr, //mp2 16
// /* 0x57 */ mp2_CraneGameStr, //mp2 17
// /* 0x58 */ MoveToTheMusicStr, //mp2 18
// /* 0x59 */ BobOmbBarrageStr, //mp2 19
// /* 0x5A */ LookAwayStr, //mp2 20
// /* 0x5B */ ShockDropOrRollStr, //mp2 21
// /* 0x5C */ LightsOutStr, //mp2 22
// /* 0x5D */ FiletRelayStr, //mp2 23
// /* 0x5E */ ArcherivalStr, //mp2 24
// /* 0x5F */ ToadBandstandStr, //mp2 26
// /* 0x60 */ mp2_BobsledRunStr, //mp2 27
// /* 0x61 */ mp2_HandcarHavocStr, //mp2 28
// /* 0x62 */ mp2_BalloonBurstStr, //mp2 30
// /* 0x63 */ SkyPilotsStr, //mp2 31
// /* 0x64 */ SpeedHockeyStr, //mp2 32
// /* 0x65 */ CakeFactoryStr, //mp2 33
// /* 0x66 */ DungeonDashStr, //mp2 35
// /* 0x67 */ MagnetCartaStar, //mp2 36
// /* 0x68 */ LavaTileIsleStr, //mp2 37
// /* 0x69 */ mp2_HotRopeJumpStr, //mp2 38
// /* 0x6A */ ShellShockedStr, //mp2 39
// /* 0x6B */ ToadInTheBoxStr, //mp2 40
// /* 0x6C */ MechaMarathonStr, //mp2 41
// /* 0x6D */ RollCallStr, //mp2 42
// /* 0x6E */ AbandonShipStr, //mp2 43
// /* 0x6F */ mp2_PlatformPerilStr, //mp2 44
// /* 0x70 */ TotemPolePoundStr, //mp2 45
// /* 0x71 */ mp2_BumperBallsStr, //mp2 46
// /* 0x72 */ mp2_BombsAwayStr, //mp2 48
// /* 0x73 */ mp2_TipsyTourneyStr, //mp2 49
// /* 0x74 */ HoneycombHavocStr, //mp2 50
// /* 0x75 */ HexagonHeatStr, //mp2 51
// /* 0x76 */ mp2_SkateboardScamperStr, //mp2 52
// /* 0x77 */ mp2_SlotCarDerbyStr, //mp2 53
// /* 0x78 */ mp2_ShyGuySaysStr, //mp2 54
// /* 0x79 */ SneakNSnoreStr, //mp2 55
// /* 0x7A */ DriversEdStr, //mp2 57
// /* 0x7B */ ChanceTimeStr, //mp2 58
// /* 0x7C */ WesternLandDuelStr, //mp2 59
// /* 0x7D */ PirateLandDuelStr, //mp2 60
// /* 0x7E */ HorrorLandDuelStr, //mp2 61
// /* 0x7F */ SpaceLandDuelStr, //mp2 62
// /* 0x80 */ MysteryLandDuelStr, //mp2 63
// /* 0x81 */ KoopaLandDuelStr, //mp2 64
// /* 0x82 */ BowsersBigBlastStr, //mp2 65
// /* 0x83 */ LooneyLumberjacksStr, //mp2 66
// /* 0x84 */ TorpedoTargetsStr, //mp2 67
// /* 0x85 */ DestructionDuetStr, //mp2 68
// /* 0x86 */ DizzyDancingStr, //mp2 69
// /* 0x87 */ TileDriverStr, //mp2 70
// /* 0x88 */ QuicksandCacheStr, //mp2 71
// /* 0x89 */ DeepSeaSalvageStr, //mp2 72
// #ifdef MP1
// /* 0x8A */ MemoryMatchStr, //mp1 00
// /* 0x8B */ ChanceTimeMp1Str, //mp1 01
// /* 0x8C */ SlotMachineStr, //mp1 02
// /* 0x8D */ BuriedTreasureStr, //mp1 03
// /* 0x8E */ TreasureDiversStr, //mp1 04
// /* 0x8F */ ShellGameStr, //mp1 05
// /* 0x90 */ SameGameStr, //mp1 06
// /* 0x91 */ mp1_HotBobOmbStr, //mp1 07
// /* 0x92 */ YoshisToungueStr, //mp1 08
// /* 0x93 */ PipeMazeStr, //mp1 09
// /* 0x94 */ GhostGuestStr, //mp1 10
// /* 0x95 */ MusicalMushroomStr, //mp1 11
// /* 0x96 */ PedalPowerStr, //mp1 12
// /* 0x97 */ mp1_CrazyCutterStr, //mp1 13
// /* 0x98 */ mp1_FaceLiftStr, //mp1 14
// /* 0x99 */ WhackAPlantStr, //mp1 15
// /* 0x9A */ BashNCashStr, //mp1 16
// /* 0x9B */ mp1_BowlOverStr, //mp1 17
// /* 0x9C */ GroundPoundStr, //mp1 18
// /* 0x9D */ BalloonBurstStr, //mp1 19
// /* 0x9E */ CoinBlockBlitzStr, //mp1 20
// /* 0x9F */ CoinBlockBashStr, //mp1 21
// /* 0xA0 */ mp1_SkateboardScamperStr, //mp1 22
// /* 0xA1 */ BoxMountainMayhemStr, //mp1 23
// /* 0xA2 */ mp1_PlatformPerilStr, //mp1 24
// /* 0xA3 */ TeeteringTowersStr, //mp1 25
// /* 0xA4 */ MushroomMixupStr, //mp1 26
// /* 0xA5 */ HammerDropStr, //mp1 27
// /* 0xA6 */ mp1_GrabBagStr, //mp1 28
// /* 0xA7 */ mp1_BobsledRunStr, //mp1 29
// /* 0xA8 */ mp1_BumperBallsStr, //mp1 30
// /* 0xA9 */ TightropeTreacheryStr, //mp1 31
// /* 0xAA */ KnockBlockTowerStr, //mp1 32
// /* 0xAB */ mp1_TipsyTourneyStr, //mp1 33
// /* 0xAC */ mp1_BombsAwayStr, //mp1 34
// /* 0xAD */ mp1_CraneGameStr, //mp1 35
// /* 0xAE */ CoinShowerFlowerStr, //mp1 36
// /* 0xAF */ mp1_SlotCarDerbyStr, //mp1 37
// /* 0xB0 */ mp1_BandStandStr, //mp1 38
// /* 0xB1 */ DesertDashStr, //mp1 39
// /* 0xB2 */ mp1_ShyGuySaysStr, //mp1 40
// /* 0xB3 */ LimboDanceStr, //mp1 41
// /* 0xB4 */ BombsketballStr, //mp1 42
// /* 0xB5 */ CastAwaysStr, //mp1 43
// /* 0xB6 */ KeyPaWayStr, //mp1 44
// /* 0xB7 */ RunningOfTheBulbStr, //mp1 45
// /* 0xB8 */ mp1_HotRopeJumpStr, //mp1 46
// /* 0xB9 */ mp1_HandcarHavocStr, //mp1 47
// /* 0xBA */ DeepSeaDiversStr, //mp1 48
// /* 0xBB */ PiranhaPursuitStr, //mp1 49
// /* 0xBC */ TugOWarStr, //mp1 50
// /* 0xBD */ PaddleBattleStr, //mp1 51
// #endif
// (void*)-1 //end of list
// };



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

void GetNewMinigameString1(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = arg1 - 0x46FF;

    s32 i;
    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            mp3_func_8005B43C_5C03C(arg0, minigameLUT[i].minigameStr, arg2, arg3);
            return;
        }
    }
    mp3_func_8005B43C_5C03C(arg0, (char*)arg1, arg2, arg3);
}