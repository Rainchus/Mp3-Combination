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
// u8 minigameBlacklistIDs[] = {
//     0x48, 0x52, 0x61, 0x65, 0x6A, 0x77, 0x80
// };

typedef struct mp3MinigameIndexTable {
    u8 minigameIndex; //index for string look up and id tracking
    char* minigameStr;
    u8 gameOverlayID; //actual overlay index in the game
} mp3MinigameIndexTable;

//combined minigame ids
enum MinigameIDs {
    NONE = 0,
    HAND_LINE_AND_SINKER,
    COCONUT_CONK,
    SPOTLIGHT_SWIM,
    BOULDER_BALL,
    CRAZY_COGS,
    HIDE_AND_SNEAK,
    RIDICULOUS_RELAY,
    THWOMP_PULL,
    RIVER_RAIDERS,
    TIDAL_TOSS,
    EATSA_PIZZA,
    BABY_BOWSER_BROADSIDE,
    PUMP_PUMP_AND_AWAY,
    HYPER_HYDRANTS,
    PICKING_PANIC,
    COSMIC_COASTER,
    PUDDLE_PADDLE,
    ETCH_N_CATCH,
    LOG_JAM,
    SLOT_SYNC,
    TREADMILL_GRILL,
    TOADSTOOL_TITAN,
    ACES_HIGH,
    BOUNCE_N_TROUNCE,
    ICE_RINK_RISK,
    LOCKED_OUT,
    CHIP_SHOT_CHALLENGE,
    PARASOL_PLUMMET,
    MESSY_MEMORY,
    PICTURE_IMPERFECT,
    MARIOS_PUZZLE_PARTY,
    THE_BEAT_GOES_ON,
    MPIQ,
    CURTAIN_CALL,
    WATER_WHIRLED,
    FRIGID_BRIDGES,
    AWFUL_TOWER,
    CHEEP_CHEEP_CHASE,
    PIPE_CLEANERS,
    SNOWBALL_SUMMIT,
    ALL_FIRED_UP,
    STACKED_DECK,
    THREE_DOOR_MONTY,
    ROCKIN_RACEWAY,
    MERRY_GO_CHOMP,
    SLAP_DOWN,
    STORM_CHASERS,
    EYE_SORE,
    VINE_WITH_ME,
    POPGUN_PICK_OFF,
    END_OF_THE_LINE,
    BOWSER_TOSS,
    BABY_BOWSER_BONKERS,
    MOTOR_ROOTER,
    SILLY_SCREWS,
    CROWD_COVER,
    TICK_TOCK_HOP,
    FOWL_PLAY,
    WINNERS_WHEEL,
    HEY_BATTER_BATTER,
    BOBBING_BOW_LOONS,
    DORRIE_DIP,
    SWINGING_WITH_SHARKS,
    SWING_N_SWIPE,
    MP3_CHANCE_TIME,
    STARDUST_BATTLE,
    GAME_GUYS_ROULETTE,
    GAME_GUYS_LUCKY_7,
    GAME_GUYS_MAGIC_BOXES,
    GAME_GUYS_SWEET_SURPRISE,
    DIZZY_DINGHIES,
    MARIO_PUZZLE_PARTY_PRO,
    //mp2 0
    BOWSER_SLOTS, //mp2 1
    ROLL_OUT_THE_BARRELS, //mp2 2
    COFFIN_CONGESTION, //mp2 3
    HAMMER_SLAMMER, //mp2 4
    GIVE_ME_A_BRAKE, //mp2 5
    MALLET_GO_ROUND, //mp2 6
    MP2_GRAB_BAG, //mp2 7
    BUMPER_BALLOON_CARS, //mp2 8
    RAKIN_EM_IN, //mp2 9
    //mp2 10
    DAY_AT_THE_RACES, //mp2 11
    MP2_FACE_LIFT, //mp2 12
    MP2_CRAZY_CUTTERS, //mp2 13
    MP2_HOT_BOB_OMB, //mp2 14
    MP2_BOWL_OVER, //mp2 15
    RAINBOW_RUN, //mp2 16
    MP2_CRANE_GAME, //mp2 17
    MOVE_TO_THE_MUSIC, //mp2 18
    BOB_OMB_BARRAGE, //mp2 19
    LOOK_AWAY, //mp2 20
    SHOCK_DROP_OR_ROLL, //mp2 21
    LIGHTS_OUT, //mp2 22
    FILET_RELAY, //mp2 23
    ARCHERIVAL, //mp2 24
    //mp2 25
    TOAD_BANDSTAND, //mp2 26
    MP2_BOBSLED_RUN, //mp2 27
    MP2_HANDCAR_HAVOC, //mp2 28
    //mp2 29
    MP2_BALLOON_BURST, //mp2 30
    SKY_PILOTS, //mp2 31
    SPEED_HOCKEY, //mp2 32
    CAKE_FACTORY, //mp2 33
    //mp2 34
    DUNGEON_DASH, //mp2 35
    MAGNET_CARTA, //mp2 36
    LAVA_TILE_ISLE, //mp2 37
    MP2_HOT_ROPE_JUMP, //mp2 38
    SHELL_SHOCKED, //mp2 39
    TOAD_IN_THE_BOX, //mp2 40
    MECHA_MARATHON, //mp2 41
    ROLL_CALL, //mp2 42
    ABANDON_SHIP, //mp2 43
    MP2_PLATFORM_PERIL, //mp2 44
    TOTEM_POLE_POUND, //mp2 45
    MP2_BUMPER_BALLS, //mp2 46
    //mp2 47
    MP2_BOMBS_AWAY, //mp2 48
    MP2_TIPSY_TOURNEY, //mp2 49
    HONEYCOMB_HAVOC, //mp2 50
    HEXAGON_HEAT, //mp2 51
    MP2_SKATEBOARD_SCAMPER, //mp2 52
    MP2_SLOT_CAR_DERBY, //mp2 53
    MP2_SHY_GUY_SAYS, //mp2 54
    SNEAK_N_SNORE, //mp2 55
    //mp2 56
    DRIVERS_ED, //mp2 57
    MP2_CHANCE_TIME, //mp2 58
    WESTERN_LAND_DUEL, //mp2 59
    PIRATE_LAND_DUEL, //mp2 60
    HORROR_LAND_DUEL, //mp2 61
    SPACE_LAND_DUEL, //mp2 62
    MYSTERY_LAND_DUEL, //mp2 63
    KOOPA_LAND_DUEL, //mp2 64
    BOWSERS_BIG_BLAST, //mp2 65
    LOONEY_LUMBERJACKS, //mp2 66
    TORPEDO_TARGETS, //mp2 67
    DESTRUCTION_DUET, //mp2 68
    DIZZY_DANCING, //mp2 69
    TILE_DRIVER, //mp2 70
    QUICKSAND_CACHE, //mp2 71
    DEEP_SEA_SALVAGE, //mp2 72
    //mp1 0
    MEMORY_MATCH, //mp1 0
    MP1_CHANCE_TIME, //mp1 1
    SLOT_MACHINE, //mp1 2
    BURIED_TREASURE, //mp1 3
    TREASURE_DIVERS, //mp1 4
    SHELL_GAME, //mp1 5
    SAME_GAME, //mp1 6
    MP1_HOT_BOB_OMB, //mp1 7
    YOSHIS_TONGUE_MEETING, //mp1 8
    PIPE_MAZE, //mp1 9
    GHOST_GUESS, //mp1 10
    MUSICAL_MUSHROOM, //mp1 11
    PEDAL_POWER, //mp1 12
    MP1_CRAZY_CUTTER, //mp1 13
    MP1_FACE_LIFT, //mp1 14
    WHACKA_A_PLANT, //mp1 15
    BASH_N_CASH, //mp1 16
    MP1_BOWL_OVER, //mp1 17
    GROUND_POUND, //mp1 18
    MP1_BALLOON_BURST, //mp1 19
    COIN_BLOCK_BLITZ, //mp1 20
    COIN_BLOCK_BASH, //mp1 21
    MP1_SKATEBOARD_SCAMPER, //mp1 22
    BOX_MOUNTAIN_MAYHEM, //mp1 23
    MP1_PLATFORM_PERIL, //mp1 24
    TEETERING_TOWER, //mp1 25
    MUSHROOM_MIXUP, //mp1 26
    HAMMER_DROP, //mp1 27
    MP1_GRAB_BAG, //mp1 28
    MP1_BOBSLED_RUN, //mp1 29
    MP1_BUMPER_BALLS, //mp1 30
    TIGHTROPE_TREACHERY, //mp1 31
    KNOCK_BLOCK_TOWER, //mp1 32
    MP1_TIPSY_TOURNEY, //mp1 33
    MP1_BOMBS_AWAY, //mp1 34
    MP1_CRANE_GAME, //mp1 35
    COIN_SHOWER_FLOWER, //mp1 36
    MP1_SLOT_CAR_DERBY, //mp1 37
    MARIO_BANDSTAND, //mp1 38
    DESERT_DASH, //mp1 39
    MP1_SHY_GUY_SAYS, //mp1 40
    LIMBO_DANCE, //mp1 41
    BOMBSKETBALL, //mp1 42
    CAST_AWAYS, //mp1 43
    KEY_PA_WAY, //mp1 44
    RUNNING_OF_THE_BULB, //mp1 45
    MP1_HOT_ROPE_JUMP, //mp1 46
    MP1_HANDCAR_HAVOC, //mp1 47
    DEEP_SEA_DIVERS, //mp1 48
    PIRANHA_PURSUIT, //mp1 49
    TUG_O_WAR, //mp1 50
    PADDLE_BATTLE, //mp1 51
    //BUMPER_BALL_MAZE_0, //mp1 52
};

mp3MinigameIndexTable minigameLUT[] = {
    {0, 0}, //blank
    {HAND_LINE_AND_SINKER, HookLineAndSinkerStr, 1},
    {COCONUT_CONK, CoconutConkStr, 2},
    {SPOTLIGHT_SWIM, SpotlightSwimStr, 3},
    {BOULDER_BALL, BoulderBallStr, 4},
    {CRAZY_COGS, CrazyCogsStr, 5},
    {HIDE_AND_SNEAK, HideAndSneakStr, 6},
    {RIDICULOUS_RELAY, RidiculousRelayStr, 7},
    {THWOMP_PULL, ThwompPullStr, 8},
    {RIVER_RAIDERS, RiverRaidersStr, 9},
    {TIDAL_TOSS, TidalTossStr, 10},
    {EATSA_PIZZA, EatsaPizzaStr, 11},
    {BABY_BOWSER_BROADSIDE, BabyBowserBroadsideStr, 12},
    {PUMP_PUMP_AND_AWAY, PumpPumpAndAwayStr, 13},
    {HYPER_HYDRANTS, HyperHydrantsStr, 14},
    {PICKING_PANIC, PickingPanicStr, 15},
    {COSMIC_COASTER, CosmicCoasterStr, 16},
    {PUDDLE_PADDLE, PuddlePaddleStr, 17},
    {ETCH_N_CATCH, EtchNCatchStr, 18},
    {LOG_JAM, LogJamStr, 19},
    {SLOT_SYNC, SlotSyncStr, 20},
    {TREADMILL_GRILL, TreadmillGrillStr, 21},
    {TOADSTOOL_TITAN, ToadstoolTitanStr, 22},
    {ACES_HIGH, AcesHighStr, 23},
    {BOUNCE_N_TROUNCE, BounceNTrounceStr, 24},
    {ICE_RINK_RISK, IceRinkRiskStr, 25},
    {LOCKED_OUT, LockedOutStr, 26},
    {CHIP_SHOT_CHALLENGE, ChipShotChallengeStr, 27},
    {PARASOL_PLUMMET, ParasolPlummetStr, 28},
    {MESSY_MEMORY, MessoryMemoryStr, 29},
    {PICTURE_IMPERFECT, PictureImperfectStr, 30},
    {MARIOS_PUZZLE_PARTY, MariosPuzzlePartyStr, 31},
    {THE_BEAT_GOES_ON, TheBeatGoesOnStr, 32},
    {MPIQ, MPIQStr, 33},
    {CURTAIN_CALL, CurtainCallStr, 34},
    {WATER_WHIRLED, WaterWhirledStr, 35},
    {FRIGID_BRIDGES, FrigidBridgesStr, 36},
    {AWFUL_TOWER, AwfulTowerStr, 37},
    {CHEEP_CHEEP_CHASE, CheepCheepChaseStr, 38},
    {PIPE_CLEANERS, PipeCleanersStr, 39},
    {SNOWBALL_SUMMIT, SnowballSummitStr, 40},
    {ALL_FIRED_UP, AllFiredUpStr, 41},
    {STACKED_DECK, StackedDeckStr, 42},
    {THREE_DOOR_MONTY, ThreeDoorMontyStr, 43},
    {ROCKIN_RACEWAY, RockinRacewayStr, 44},
    {MERRY_GO_CHOMP, MerryGoChompStr, 45},
    {SLAP_DOWN, SlapDownStr, 46},
    {STORM_CHASERS, StormChasersStr, 47},
    {EYE_SORE, EyeSoreStr, 48},
    {VINE_WITH_ME, VineWithMeStr, 49},
    {POPGUN_PICK_OFF, PopgunPickOffStr, 50},
    {END_OF_THE_LINE, EndOfTheLinerStr, 51},
    {BOWSER_TOSS, BowserTossStr, 52},
    {BABY_BOWSER_BONKERS, BabyBowserBonkersStr, 53},
    {MOTOR_ROOTER, MotorRooterStr, 54},
    {SILLY_SCREWS, SillyScrewsStr, 55},
    {CROWD_COVER, CrowdCoverStr, 56},
    {TICK_TOCK_HOP, TickTockHopStr, 57},
    {FOWL_PLAY, FowlPlayStr, 58},
    {WINNERS_WHEEL, WinnersWheelStr, 59},
    {HEY_BATTER_BATTER, HeyBatterBatterStr, 60},
    {BOBBING_BOW_LOONS, BobbingBowloonsStr, 61},
    {DORRIE_DIP, DorrieDipStr, 62},
    {SWINGING_WITH_SHARKS, SwingingWithSharksStr, 63},
    {SWING_N_SWIPE, SwingNSwipeStr, 64},
    {MP3_CHANCE_TIME, ChanceTimeStr, 65},
    {STARDUST_BATTLE, StardustBattleStr, 66},
    {GAME_GUYS_ROULETTE, GameGuysRouletteStr, 67},
    {GAME_GUYS_LUCKY_7, GameGuysLucky7Str, 68},
    {GAME_GUYS_MAGIC_BOXES, GameGuysMagicBoxesStr, 69},
    {GAME_GUYS_SWEET_SURPRISE, GameGuysSweetSurpriseStr, 70},
    {DIZZY_DINGHIES, DizzyDinghiesStr, 71},
    {MARIO_PUZZLE_PARTY_PRO, MariosPuzzlePartyPro2Str, 72},
    //mp2 0
    {BOWSER_SLOTS, BowserSlotsStr, 1}, //mp2 1
    {ROLL_OUT_THE_BARRELS, RollOutTheBarrelsStr, 2}, //mp2 2
    {COFFIN_CONGESTION, CoffinCongestionStr, 3}, //mp2 3
    {HAMMER_SLAMMER, HammerSlammerStr, 4}, //mp2 4
    {GIVE_ME_A_BRAKE, GiveMeABrakeStr, 5}, //mp2 5
    {MALLET_GO_ROUND, MalletGoRoundStr, 6}, //mp2 6
    {MP2_GRAB_BAG, mp2_GrabBagStr, 7}, //mp2 7
    {BUMPER_BALLOON_CARS, BumperBalloonCarsStr, 8}, //mp2 8
    {RAKIN_EM_IN, RakinEmInStr, 9}, //mp2 9
    //mp2 10
    {DAY_AT_THE_RACES, DayAtTheRacesStr, 11}, //mp2 11
    {MP2_FACE_LIFT, mp2_FaceLiftStr, 12}, //mp2 12
    {MP2_CRAZY_CUTTERS, mp2_CrazyCuttersStr, 13}, //mp2 13
    {MP2_HOT_BOB_OMB, mp2_HotBobombStr, 14}, //mp2 14
    {MP2_BOWL_OVER, mp2_BowlOverStr, 15}, //mp2 15
    {RAINBOW_RUN, RainbowRunStr, 16}, //mp2 16
    {MP2_CRANE_GAME, mp2_CraneGameStr, 17}, //mp2 17
    {MOVE_TO_THE_MUSIC, MoveToTheMusicStr, 18}, //mp2 18
    {BOB_OMB_BARRAGE, BobOmbBarrageStr, 19}, //mp2 19
    {LOOK_AWAY, LookAwayStr, 20}, //mp2 20
    {SHOCK_DROP_OR_ROLL, ShockDropOrRollStr, 21}, //mp2 21
    {LIGHTS_OUT, LightsOutStr, 22}, //mp2 22
    {FILET_RELAY, FiletRelayStr, 23}, //mp2 23
    {ARCHERIVAL, ArcherivalStr, 24}, //mp2 24
    //mp2 25
    {TOAD_BANDSTAND, ToadBandstandStr, 26}, //mp2 26
    {MP2_BOBSLED_RUN, mp2_BobsledRunStr, 27}, //mp2 27
    {MP2_HANDCAR_HAVOC, mp2_HandcarHavocStr, 28}, //mp2 28
    //mp2 29
    {MP2_BALLOON_BURST, mp2_BalloonBurstStr, 30}, //mp2 30
    {SKY_PILOTS, SkyPilotsStr, 31}, //mp2 31
    {SPEED_HOCKEY, SpeedHockeyStr, 32}, //mp2 32
    {CAKE_FACTORY, CakeFactoryStr, 33}, //mp2 33
    //mp2 34
    {DUNGEON_DASH, DungeonDashStr, 35}, //mp2 35
    {MAGNET_CARTA, MagnetCartaStar, 36}, //mp2 36
    {LAVA_TILE_ISLE, LavaTileIsleStr, 37}, //mp2 37
    {MP2_HOT_ROPE_JUMP, mp2_HotRopeJumpStr, 38}, //mp2 38
    {SHELL_SHOCKED, ShellShockedStr, 39}, //mp2 39
    {TOAD_IN_THE_BOX, ToadInTheBoxStr, 40}, //mp2 40
    {MECHA_MARATHON, MechaMarathonStr, 41}, //mp2 41
    {ROLL_CALL, RollCallStr, 42}, //mp2 42
    {ABANDON_SHIP, AbandonShipStr, 43}, //mp2 43
    {MP2_PLATFORM_PERIL, mp2_PlatformPerilStr, 44}, //mp2 44
    {TOTEM_POLE_POUND, TotemPolePoundStr, 45}, //mp2 45
    {MP2_BUMPER_BALLS, mp2_BumperBallsStr, 46}, //mp2 46
    //mp2 47
    {MP2_BOMBS_AWAY, mp2_BombsAwayStr, 48}, //mp2 48
    {MP2_TIPSY_TOURNEY, mp2_TipsyTourneyStr, 49}, //mp2 49
    {HONEYCOMB_HAVOC, HoneycombHavocStr, 50}, //mp2 50
    {HEXAGON_HEAT, HexagonHeatStr, 51}, //mp2 51
    {MP2_SKATEBOARD_SCAMPER, mp2_SkateboardScamperStr, 52}, //mp2 52
    {MP2_SLOT_CAR_DERBY, mp2_SlotCarDerbyStr, 53}, //mp2 53
    {MP2_SHY_GUY_SAYS, mp2_ShyGuySaysStr, 54}, //mp2 54
    {SNEAK_N_SNORE, SneakNSnoreStr, 55}, //mp2 55
    //mp2 56
    {DRIVERS_ED, DriversEdStr, 57}, //mp2 57
    {MP2_CHANCE_TIME, ChanceTimeStr, 58}, //mp2 58
    {WESTERN_LAND_DUEL, WesternLandDuelStr, 59}, //mp2 59
    {PIRATE_LAND_DUEL, PirateLandDuelStr, 60}, //mp2 60
    {HORROR_LAND_DUEL, HorrorLandDuelStr, 61}, //mp2 61
    {SPACE_LAND_DUEL, SpaceLandDuelStr, 62}, //mp2 62
    {MYSTERY_LAND_DUEL, MysteryLandDuelStr, 63}, //mp2 63
    {KOOPA_LAND_DUEL, KoopaLandDuelStr, 64}, //mp2 64
    {BOWSERS_BIG_BLAST, BowsersBigBlastStr, 65}, //mp2 65
    {LOONEY_LUMBERJACKS, LooneyLumberjacksStr, 66}, //mp2 66
    {TORPEDO_TARGETS, TorpedoTargetsStr, 67}, //mp2 67
    {DESTRUCTION_DUET, DestructionDuetStr, 68}, //mp2 68
    {DIZZY_DANCING, DizzyDancingStr, 69}, //mp2 69
    {TILE_DRIVER, TileDriverStr, 70}, //mp2 70
    {QUICKSAND_CACHE, QuicksandCacheStr, 71}, //mp2 71
    {DEEP_SEA_SALVAGE, DeepSeaSalvageStr, 72}, //mp2 72
    //mp1


    {MEMORY_MATCH, MemoryMatchStr, 0}, //mp1 0
    {MP1_CHANCE_TIME, ChanceTimeMp1Str, 1}, //mp1 1
    {SLOT_MACHINE, SlotMachineStr, 2}, //mp1 2
    {BURIED_TREASURE, BuriedTreasureStr, 3}, //mp1 3
    {TREASURE_DIVERS, TreasureDiversStr, 4}, //mp1 4
    {SHELL_GAME, ShellGameStr, 5}, //mp1 5
    {SAME_GAME, SameGameStr, 6}, //mp1 6
    {MP1_HOT_BOB_OMB, mp1_HotBobOmbStr, 7}, //mp1 7
    {YOSHIS_TONGUE_MEETING, YoshisToungueStr, 8}, //mp1 8
    {PIPE_MAZE, PipeMazeStr, 9}, //mp1 9
    {GHOST_GUESS, GhostGuestStr, 10}, //mp1 10
    {MUSICAL_MUSHROOM, MusicalMushroomStr, 11}, //mp1 11
    {PEDAL_POWER, PedalPowerStr, 12}, //mp1 12
    {MP1_CRAZY_CUTTER, mp1_CrazyCutterStr, 13}, //mp1 13
    {MP1_FACE_LIFT, mp1_FaceLiftStr, 14}, //mp1 14
    {WHACKA_A_PLANT, WhackAPlantStr, 15}, //mp1 15
    {BASH_N_CASH, BashNCashStr, 16}, //mp1 16
    {MP1_BOWL_OVER, mp1_BowlOverStr, 17}, //mp1 17
    {GROUND_POUND, GroundPoundStr, 18}, //mp1 18
    {MP1_BALLOON_BURST, BalloonBurstStr, 19}, //mp1 19
    {COIN_BLOCK_BLITZ, CoinBlockBlitzStr, 20}, //mp1 20
    {COIN_BLOCK_BASH, CoinBlockBashStr, 21}, //mp1 21
    {MP1_SKATEBOARD_SCAMPER, mp1_SkateboardScamperStr, 22}, //mp1 22
    {BOX_MOUNTAIN_MAYHEM, BoxMountainMayhemStr, 23}, //mp1 23
    {MP1_PLATFORM_PERIL, mp1_PlatformPerilStr, 24}, //mp1 24
    {TEETERING_TOWER, TeeteringTowersStr, 25}, //mp1 25
    {MUSHROOM_MIXUP, MushroomMixupStr, 26}, //mp1 26
    {HAMMER_DROP, HammerDropStr, 27}, //mp1 27
    {MP1_GRAB_BAG, mp1_GrabBagStr, 28}, //mp1 28
    {MP1_BOBSLED_RUN, mp1_BobsledRunStr, 29}, //mp1 29
    {MP1_BUMPER_BALLS, mp1_BumperBallsStr, 30}, //mp1 30
    {TIGHTROPE_TREACHERY, TightropeTreacheryStr, 31}, //mp1 31
    {KNOCK_BLOCK_TOWER, KnockBlockTowerStr, 32}, //mp1 32
    {MP1_TIPSY_TOURNEY, mp1_TipsyTourneyStr, 33}, //mp1 33
    {MP1_BOMBS_AWAY, mp1_BombsAwayStr, 34}, //mp1 34
    {MP1_CRANE_GAME, mp1_CraneGameStr, 35}, //mp1 35
    {COIN_SHOWER_FLOWER, CoinShowerFlowerStr, 36}, //mp1 36
    {MP1_SLOT_CAR_DERBY, mp1_SlotCarDerbyStr, 37}, //mp1 37
    {MARIO_BANDSTAND, mp1_BandStandStr, 38}, //mp1 38
    {DESERT_DASH, DesertDashStr, 39}, //mp1 39
    {MP1_SHY_GUY_SAYS, mp1_ShyGuySaysStr, 40}, //mp1 40
    {LIMBO_DANCE, LimboDanceStr, 41}, //mp1 41
    {BOMBSKETBALL, BombsketballStr, 42}, //mp1 42
    {CAST_AWAYS, CastAwaysStr, 43}, //mp1 43
    {KEY_PA_WAY, KeyPaWayStr, 44}, //mp1 44
    {RUNNING_OF_THE_BULB, RunningOfTheBulbStr, 45}, //mp1 45
    {MP1_HOT_ROPE_JUMP, mp1_HotRopeJumpStr, 46}, //mp1 46
    {MP1_HANDCAR_HAVOC, mp1_HandcarHavocStr, 47}, //mp1 47
    {DEEP_SEA_DIVERS, DeepSeaDiversStr, 48}, //mp1 48
    {PIRANHA_PURSUIT, PiranhaPursuitStr, 49}, //mp1 49
    {TUG_O_WAR, TugOWarStr, 50}, //mp1 50
    {PADDLE_BATTLE, PaddleBattleStr, 51}, //mp1 51
};

s32 ForeignMinigameIDToGame(s32 minigameCombinedIndex) {
    s32 i;
    //find the minigame and get the overlay id for the specific game
    for (i = 0; i < ARRAY_COUNT(minigameLUT); i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            return minigameLUT[i].gameOverlayID;
        }
    }
    return -1; //minigame not found
}

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
/* 0x4E */ mp2_GrabBagStr, //mp2 7
/* 0x4F */ BumperBalloonCarsStr, //mp2 8
/* 0x50 */ RakinEmInStr, //mp2 9
/* 0x51 */ DayAtTheRacesStr, //mp2 11
/* 0x52 */ mp2_FaceLiftStr, //mp2 12
/* 0x53 */ mp2_CrazyCuttersStr, //mp2 13
/* 0x54 */ mp2_HotBobombStr, //mp2 14
/* 0x55 */ mp2_BowlOverStr, //mp2 15
/* 0x56 */ RainbowRunStr, //mp2 16
/* 0x57 */ mp2_CraneGameStr, //mp2 17
/* 0x58 */ MoveToTheMusicStr, //mp2 18
/* 0x59 */ BobOmbBarrageStr, //mp2 19
/* 0x5A */ LookAwayStr, //mp2 20
/* 0x5B */ ShockDropOrRollStr, //mp2 21
/* 0x5C */ LightsOutStr, //mp2 22
/* 0x5D */ FiletRelayStr, //mp2 23
/* 0x5E */ ArcherivalStr, //mp2 24
/* 0x5F */ ToadBandstandStr, //mp2 26
/* 0x60 */ mp2_BobsledRunStr, //mp2 27
/* 0x61 */ mp2_HandcarHavocStr, //mp2 28
/* 0x62 */ mp2_BalloonBurstStr, //mp2 30
/* 0x63 */ SkyPilotsStr, //mp2 31
/* 0x64 */ SpeedHockeyStr, //mp2 32
/* 0x65 */ CakeFactoryStr, //mp2 33
/* 0x66 */ DungeonDashStr, //mp2 35
/* 0x67 */ MagnetCartaStar, //mp2 36
/* 0x68 */ LavaTileIsleStr, //mp2 37
/* 0x69 */ mp2_HotRopeJumpStr, //mp2 38
/* 0x6A */ ShellShockedStr, //mp2 39
/* 0x6B */ ToadInTheBoxStr, //mp2 40
/* 0x6C */ MechaMarathonStr, //mp2 41
/* 0x6D */ RollCallStr, //mp2 42
/* 0x6E */ AbandonShipStr, //mp2 43
/* 0x6F */ mp2_PlatformPerilStr, //mp2 44
/* 0x70 */ TotemPolePoundStr, //mp2 45
/* 0x71 */ mp2_BumperBallsStr, //mp2 46
/* 0x72 */ mp2_BombsAwayStr, //mp2 48
/* 0x73 */ mp2_TipsyTourneyStr, //mp2 49
/* 0x74 */ HoneycombHavocStr, //mp2 50
/* 0x75 */ HexagonHeatStr, //mp2 51
/* 0x76 */ mp2_SkateboardScamperStr, //mp2 52
/* 0x77 */ mp2_SlotCarDerbyStr, //mp2 53
/* 0x78 */ mp2_ShyGuySaysStr, //mp2 54
/* 0x79 */ SneakNSnoreStr, //mp2 55
/* 0x7A */ DriversEdStr, //mp2 57
/* 0x7B */ ChanceTimeStr, //mp2 58
/* 0x7C */ WesternLandDuelStr, //mp2 59
/* 0x7D */ PirateLandDuelStr, //mp2 60
/* 0x7E */ HorrorLandDuelStr, //mp2 61
/* 0x7F */ SpaceLandDuelStr, //mp2 62
/* 0x80 */ MysteryLandDuelStr, //mp2 63
/* 0x81 */ KoopaLandDuelStr, //mp2 64
/* 0x82 */ BowsersBigBlastStr, //mp2 65
/* 0x83 */ LooneyLumberjacksStr, //mp2 66
/* 0x84 */ TorpedoTargetsStr, //mp2 67
/* 0x85 */ DestructionDuetStr, //mp2 68
/* 0x86 */ DizzyDancingStr, //mp2 69
/* 0x87 */ TileDriverStr, //mp2 70
/* 0x88 */ QuicksandCacheStr, //mp2 71
/* 0x89 */ DeepSeaSalvageStr, //mp2 72
#ifdef MP1
/* 0x8A */ MemoryMatchStr, //mp1 00
/* 0x8B */ ChanceTimeMp1Str, //mp1 01
/* 0x8C */ SlotMachineStr, //mp1 02
/* 0x8D */ BuriedTreasureStr, //mp1 03
/* 0x8E */ TreasureDiversStr, //mp1 04
/* 0x8F */ ShellGameStr, //mp1 05
/* 0x90 */ SameGameStr, //mp1 06
/* 0x91 */ mp1_HotBobOmbStr, //mp1 07
/* 0x92 */ YoshisToungueStr, //mp1 08
/* 0x93 */ PipeMazeStr, //mp1 09
/* 0x94 */ GhostGuestStr, //mp1 10
/* 0x95 */ MusicalMushroomStr, //mp1 11
/* 0x96 */ PedalPowerStr, //mp1 12
/* 0x97 */ mp1_CrazyCutterStr, //mp1 13
/* 0x98 */ mp1_FaceLiftStr, //mp1 14
/* 0x99 */ WhackAPlantStr, //mp1 15
/* 0x9A */ BashNCashStr, //mp1 16
/* 0x9B */ mp1_BowlOverStr, //mp1 17
/* 0x9C */ GroundPoundStr, //mp1 18
/* 0x9D */ BalloonBurstStr, //mp1 19
/* 0x9E */ CoinBlockBlitzStr, //mp1 20
/* 0x9F */ CoinBlockBashStr, //mp1 21
/* 0xA0 */ mp1_SkateboardScamperStr, //mp1 22
/* 0xA1 */ BoxMountainMayhemStr, //mp1 23
/* 0xA2 */ mp1_PlatformPerilStr, //mp1 24
/* 0xA3 */ TeeteringTowersStr, //mp1 25
/* 0xA4 */ MushroomMixupStr, //mp1 26
/* 0xA5 */ HammerDropStr, //mp1 27
/* 0xA6 */ mp1_GrabBagStr, //mp1 28
/* 0xA7 */ mp1_BobsledRunStr, //mp1 29
/* 0xA8 */ mp1_BumperBallsStr, //mp1 30
/* 0xA9 */ TightropeTreacheryStr, //mp1 31
/* 0xAA */ KnockBlockTowerStr, //mp1 32
/* 0xAB */ mp1_TipsyTourneyStr, //mp1 33
/* 0xAC */ mp1_BombsAwayStr, //mp1 34
/* 0xAD */ mp1_CraneGameStr, //mp1 35
/* 0xAE */ CoinShowerFlowerStr, //mp1 36
/* 0xAF */ mp1_SlotCarDerbyStr, //mp1 37
/* 0xB0 */ mp1_BandStandStr, //mp1 38
/* 0xB1 */ DesertDashStr, //mp1 39
/* 0xB2 */ mp1_ShyGuySaysStr, //mp1 40
/* 0xB3 */ LimboDanceStr, //mp1 41
/* 0xB4 */ BombsketballStr, //mp1 42
/* 0xB5 */ CastAwaysStr, //mp1 43
/* 0xB6 */ KeyPaWayStr, //mp1 44
/* 0xB7 */ RunningOfTheBulbStr, //mp1 45
/* 0xB8 */ mp1_HotRopeJumpStr, //mp1 46
/* 0xB9 */ mp1_HandcarHavocStr, //mp1 47
/* 0xBA */ DeepSeaDiversStr, //mp1 48
/* 0xBB */ PiranhaPursuitStr, //mp1 49
/* 0xBC */ TugOWarStr, //mp1 50
/* 0xBD */ PaddleBattleStr, //mp1 51
#endif
-1 //end of list
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
    //issues with mp2 battle minigames atm
    // MP2_GRAB_BAG, BUMPER_BALLOON_CARS, RAKIN_EM_IN, DAY_AT_THE_RACES, MP2_FACE_LIFT,
    // MP2_CRAZY_CUTTERS, MP2_HOT_BOB_OMB, BOWSERS_BIG_BLAST,
    0xFF
};
u8 newItemMinigameListNormalMp3[] = {
    //no mp2 minigames currently for these
    WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS,
    SWING_N_SWIPE,
    //issues with mp2 item minigames atm
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

void GetNewMinigameString1(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = arg1 - 0x46FF;

    s32 i;
    for (i = 0; i < ARRAY_COUNT(minigameLUT); i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            func_8005B43C_5C03C(arg0, minigameLUT[i].minigameStr, arg2, arg3);
            return;
        }
    }
    func_8005B43C_5C03C(arg0, arg1, arg2, arg3);
}