#include "marioparty.h"
#include "mp3.h"

s32 ForeignMinigameIndexToLoad = -1;
//there's probably a better way to track this
s32 mp3_LoadBackFromMp2 = NON_FOREIGN_MINIGAME;

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
char mp2_GrabBagStr[] = {"\x0B""\x5D""MP2""\x5E"" Grab Bag"}; //mp2 7
char BumperBalloonCarsStr[] = {"\x0B""Bumper Balloon Cars"}; //mp2 8
char RakinEmInStr[] = {"\x0B""Rakin""\x5C"" ""\x5C""em In"}; //mp2 9
//mp2 10 blank
char DayAtTheRacesStr[] = {"\x0B""Day At The Races"}; //mp2 11
char mp2_FaceLiftStr[] = {"""\x5D""MP2""\x5E"" Face Lift"}; //mp2 12
char mp2_CrazyCuttersStr[] = {"""\x5D""MP2""\x5E"" Crazy Cutters"}; //mp2 13
char mp2_HotBobombStr[] = {"\x0B""\x5D""MP2""\x5E"" Hot Bob""\x3D""omb"}; //mp2 14
char mp2_BowlOverStr[] = {"\x0B""\x5D""MP2""\x5E"" Bowl Over"}; //mp2 15
char RainbowRunStr[] = {"\x0B""Rainbow Run"}; //mp2 16
char mp2_CraneGameStr[] = {"\x0B""\x5D""MP2""\x5E"" Crane Game"}; //mp2 17
char MoveToTheMusicStr[] = {"\x0B""Move To The Music"}; //mp2 18
char BobOmbBarrageStr[] = {"\x0B""Bob""\x3D""omb Barrage"}; //mp2 19
char LookAwayStr[] = {"\x0B""Look Away"}; //mp2 20
char ShockDropOrRollStr[] = {"\x0B""Shock""\x82"" Drop or Roll"}; //mp2 21
char LightsOutStr[] = {"\x0B""Lights Out"}; //mp2 22
char FiletRelayStr[] = {"\x0B""Filet Relay"}; //mp2 23
char ArcherivalStr[] = {"\x0B""Archer""\x3D""ival"}; //mp2 24
//mp2 25 blank
char ToadBandstandStr[] = {"\x0B""Toad Bandstand"}; //mp2 26
char mp2_BobsledRunStr[] = {"\x0B""\x5D""MP2""\x5E"" Bobsled Run"}; //mp2 27
char mp2_HandcarHavocStr[] = {"\x0B""\x5D""MP2""\x5E"" Handcar Havoc"}; //mp2 28
//mp2 29 blank
char mp2_BalloonBurstStr[] = {"\x0B""\x5D""MP2""\x5E"" Balloon Burst"}; //mp2 30
char SkyPilotsStr[] = {"\x0B""Sky Pilots"}; //mp2 31
char SpeedHockeyStr[] = {"\x0B""Speed Hockey"}; //mp2 32
char CakeFactoryStr[] = {"\x0B""Cake Factory"}; //mp2 33
//mp2 34
char DungeonDashStr[] = {"\x0B""Dungeon Dash"}; //mp2 35
char MagnetCartaStar[] = {"\x0B""Magnet Carta"}; //mp2 36
char LavaTileIsleStr[] = {"\x0B""Lava Tile Isle"}; //mp2 37
char mp2_HotRopeJumpStr[] = {"\x0B""\x5D""MP2""\x5E"" Hot Rope Jump"}; //mp2 38
char ShellShockedStr[] = {"\x0B""Shell Shocked"}; //mp2 39
char ToadInTheBoxStr[] = {"\x0B""TOAD In The Box"}; //mp2 40
char MechaMarathonStr[] = {"\x0B""Mecha""\x3D""Marathon"}; //mp2 41
char RollCallStr[] = {"\x0B""Roll Call"}; //mp2 42
char AbandonShipStr[] = {"\x0B""Abandon Ship"}; //mp2 43
char mp2_PlatformPerilStr[] = {"\x0B""\x5D""MP2""\x5E"" Platform Peril"}; //mp2 44
char TotemPolePoundStr[] = {"\x0B""Totem Pole Pound"}; //mp2 45
char mp2_BumperBallsStr[] = {"\x0B""\x5D""MP2""\x5E"" Bumper Balls"}; //mp2 46
//mp2 47
char mp2_BombsAwayStr[] = {"\x0B""\x5D""MP2""\x5E"" Bombs Away"}; //mp2 48
char mp2_TipsyTourneyStr[] = {"\x0B""\x5D""MP2""\x5E"" Tipsy Tourney"}; //mp2 49
char HoneycombHavocStr[] = {"\x0B""Honeycomb Havoc"}; //mp2 50
char HexagonHeatStr[] = {"\x0B""Hexagon Heat"}; //mp2 51
char mp2_SkateboardScamperStr[] = {"\x0B""\x5D""MP2""\x5E"" Skateboard Scamper"}; //mp2 52
char mp2_SlotCarDerbyStr[] = {"\x0B""\x5D""MP2""\x5E"" Slot Car Derby"}; //mp2 53
char mp2_ShyGuySaysStr[] = {"\x0B""\x5D""MP2""\x5E"" Shy Guy Says"}; //mp2 54
char SneakNSnoreStr[] = {"\x0B""Sneak ""\x5C""n""\x5C"" Snore"}; //mp2 55
//mp2 56
char DriversEdStr[] = {"\x0B""Driver""\x5C""s Ed"}; //mp2 57
char mp2_ChanceTimeStr[] = {"\x0B""\x5D""MP2""\x5E"" Chance Time"}; //mp2 58
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
char mp1_HotBobOmbStr[] = {"\x0B""\x5D""MP1""\x5E"" Hot Bob""\x3D""omb"}; //mp1 09
//mp1 10
char PipeMazeStr[] = {"\x0B""Pipe Maze"}; //mp1 11
char GhostGuestStr[] = {"\x0B""Ghost Guess"}; //mp1 12
char MusicalMushroomStr[] = {"\x0B""Mushroom Musical"}; //mp1 13
char PedalPowerStr[] = {"\x0B""Pedal Power"}; //mp1 14
char mp1_CrazyCutterStr[] = {"\x0B""\x5D""MP1""\x5E"" Crazy Cutter"}; //mp1 15
char mp1_FaceLiftStr[] = {"\x0B""\x5D""MP1""\x5E"" Face Lift"}; //mp1 16
char WhackAPlantStr[] = {"\x0B""Whack""\x3D""a""\x3D""Plant"}; //mp1 17
//mp1 18
//mp1 19
char BashNCashStr[] = {"\x0B""Bash ""\x5C""n""\x5C"" Cash"}; //mp1 20
char mp1_BowlOverStr[] = {"\x0B""\x5D""MP1""\x5E"" Bowl Over"}; //mp1 21
char GroundPoundStr[] = {"\x0B""Ground Pound"}; //mp1 22
char BalloonBurstStr[] = {"\x0B""Balloon Burst"}; //mp1 23
char CoinBlockBlitzStr[] = {"\x0B""Coin Block Blitz"}; //mp1 24
char CoinBlockBashStr[] = {"\x0B""Coin Block Bash"}; //mp1 25
char mp1_SkateboardScamperStr[] = {"\x0B""\x5D""MP1""\x5E"" Skateboard Scamper"}; //mp1 26
//mp1 27
char BoxMountainMayhemStr[] = {"\x0B""Box Mountain Mayhem"}; //mp1 28
char mp1_PlatformPerilStr[] = {"\x0B""\x5D""MP1""\x5E"" Platform Peril"}; //mp1 29
char TeeteringTowersStr[] = {"\x0B""Teetering Towers"}; //mp1 30
char MushroomMixupStr[] = {"\x0B""Mushroom Mix""\x3D""Up"}; //mp1 31
//mp1 32
//mp1 33
char HammerDropStr[] = {"\x0B""Hammer Drop"}; //mp1 34
char mp1_GrabBagStr[] = {"\x0B""\x5D""MP1""\x5E"" Grab Bag"}; //mp1 35
char mp1_BobsledRunStr[] = {"\x0B""\x5D""MP1""\x5E"" Bobsled Run"}; //mp1 36
char mp1_BumperBallsStr[] = {"\x0B""\x5D""MP1""\x5E"" Bumper Balls"}; //mp1 37
char TightropeTreacheryStr[] = {"\x0B""Tightrope Treachery"}; //mp1 38
char KnockBlockTowerStr[] = {"\x0B""Knock Block Tower"}; //mp1 39
char mp1_TipsyTourneyStr[] = {"\x0B""\x5D""MP1""\x5E"" Tipsey Tourney"}; //mp1 40
char mp1_BombsAwayStr[] = {"\x0B""\x5D""MP1""\x5E"" Bombs Away"}; //mp1 41
char mp1_CraneGameStr[] = {"\x0B""\x5D""MP1""\x5E"" Crane Game"}; //mp1 42
//mp1 43
//mp1 44
//mp1 45
char CoinShowerFlowerStr[] = {"\x0B""Coin Shower Flower"}; //mp1 46
//mp1 47
//mp1 48
char mp1_SlotCarDerbyStr[] = {"\x0B""\x5D""MP1""\x5E"" Slot Car Derby"}; //mp1 49
char mp1_BandStandStr[] = {"\x0B""\x5D""MP1""\x5E"" Mario Bandstand"}; //mp1 50
char DesertDashStr[] = {"\x0B""Desert Dash"}; //mp1 51
char mp1_ShyGuySaysStr[] = {"\x0B""\x5D""MP1""\x5E"" Shy Guy Says"}; //mp1 52
//mp1 53
char LimboDanceStr[] = {"\x0B""Limbo Dance"}; //mp1 54
char BombsketballStr[] = {"\x0B""Bombsketball"}; //mp1 55
char CastAwaysStr[] = {"\x0B""Cast Aways"}; //mp1 56
char KeyPaWayStr[] = {"\x0B""Key""\x3D""pa""\x3D""Way"}; //mp1 57
char RunningOfTheBulbStr[] = {"\x0B""Running Of The Bulb"}; //mp1 58
char mp1_HotRopeJumpStr[] = {"\x0B""\x5D""MP1""\x5E"" Hot Rope Jump"}; //mp1 59
//mp1 60
//mp1 61
//mp1 62
char mp1_HandcarHavocStr[] = {"\x0B""\x5D""MP1""\x5E"" Handcar Havoc"}; //mp1 63
//mp1 64
char DeepSeaDiversStr[] = {"\x0B""Deep Sea Divers"}; //mp1 65
char PiranhaPursuitStr[] = {"\x0B""Piranha Pursuit"}; //mp1 66
char TugOWarStr[] = {"\x0B""Tug o""\x5C"" War"}; //mp1 67
char PaddleBattleStr[] = {"\x0B""Paddle Battle"}; //mp1 68

u8 minigameTextColor[] = {
    [NONE] TEXT_ADJUST_WHITE,
    [HAND_LINE_AND_SINKER] TEXT_ADJUST_WHITE,
    [COCONUT_CONK] TEXT_ADJUST_WHITE,
    [SPOTLIGHT_SWIM] TEXT_ADJUST_WHITE,
    [BOULDER_BALL] TEXT_ADJUST_WHITE,
    [CRAZY_COGS] TEXT_ADJUST_WHITE,
    [HIDE_AND_SNEAK] TEXT_ADJUST_WHITE,
    [RIDICULOUS_RELAY] TEXT_ADJUST_WHITE,
    [THWOMP_PULL] TEXT_ADJUST_WHITE,
    [RIVER_RAIDERS] TEXT_ADJUST_YELLOW,
    [TIDAL_TOSS] TEXT_ADJUST_WHITE,
    [EATSA_PIZZA] TEXT_ADJUST_WHITE,
    [BABY_BOWSER_BROADSIDE] TEXT_ADJUST_WHITE,
    [PUMP_PUMP_AND_AWAY] TEXT_ADJUST_WHITE,
    [HYPER_HYDRANTS] TEXT_ADJUST_WHITE,
    [PICKING_PANIC] TEXT_ADJUST_WHITE,
    [COSMIC_COASTER] TEXT_ADJUST_WHITE,
    [PUDDLE_PADDLE] TEXT_ADJUST_YELLOW,
    [ETCH_N_CATCH] TEXT_ADJUST_WHITE,
    [LOG_JAM] TEXT_ADJUST_WHITE,
    [SLOT_SYNC] TEXT_ADJUST_WHITE,
    [TREADMILL_GRILL] TEXT_ADJUST_WHITE,
    [TOADSTOOL_TITAN] TEXT_ADJUST_WHITE,
    [ACES_HIGH] TEXT_ADJUST_WHITE,
    [BOUNCE_N_TROUNCE] TEXT_ADJUST_WHITE,
    [ICE_RINK_RISK] TEXT_ADJUST_WHITE,
    [LOCKED_OUT] TEXT_ADJUST_WHITE,
    [CHIP_SHOT_CHALLENGE] TEXT_ADJUST_WHITE,
    [PARASOL_PLUMMET] TEXT_ADJUST_YELLOW,
    [MESSY_MEMORY] TEXT_ADJUST_WHITE,
    [PICTURE_IMPERFECT] TEXT_ADJUST_WHITE,
    [MARIOS_PUZZLE_PARTY] TEXT_ADJUST_WHITE,
    [THE_BEAT_GOES_ON] TEXT_ADJUST_WHITE,
    [MPIQ] TEXT_ADJUST_WHITE,
    [CURTAIN_CALL] TEXT_ADJUST_WHITE,
    [WATER_WHIRLED] TEXT_ADJUST_WHITE,
    [FRIGID_BRIDGES] TEXT_ADJUST_WHITE,
    [AWFUL_TOWER] TEXT_ADJUST_WHITE,
    [CHEEP_CHEEP_CHASE] TEXT_ADJUST_WHITE,
    [PIPE_CLEANERS] TEXT_ADJUST_WHITE,
    [SNOWBALL_SUMMIT] TEXT_ADJUST_WHITE,
    [ALL_FIRED_UP] TEXT_ADJUST_WHITE,
    [STACKED_DECK] TEXT_ADJUST_WHITE,
    [THREE_DOOR_MONTY] TEXT_ADJUST_WHITE,
    [ROCKIN_RACEWAY] TEXT_ADJUST_WHITE,
    [MERRY_GO_CHOMP] TEXT_ADJUST_WHITE,
    [SLAP_DOWN] TEXT_ADJUST_WHITE,
    [STORM_CHASERS] TEXT_ADJUST_WHITE,
    [EYE_SORE] TEXT_ADJUST_WHITE,
    [VINE_WITH_ME] TEXT_ADJUST_WHITE,
    [POPGUN_PICK_OFF] TEXT_ADJUST_WHITE,
    [END_OF_THE_LINE] TEXT_ADJUST_WHITE,
    [BOWSER_TOSS] TEXT_ADJUST_WHITE,
    [BABY_BOWSER_BONKERS] TEXT_ADJUST_WHITE,
    [MOTOR_ROOTER] TEXT_ADJUST_WHITE,
    [SILLY_SCREWS] TEXT_ADJUST_WHITE,
    [CROWD_COVER] TEXT_ADJUST_WHITE,
    [TICK_TOCK_HOP] TEXT_ADJUST_WHITE,
    [FOWL_PLAY] TEXT_ADJUST_WHITE,
    [WINNERS_WHEEL] TEXT_ADJUST_WHITE,
    [HEY_BATTER_BATTER] TEXT_ADJUST_WHITE,
    [BOBBING_BOW_LOONS] TEXT_ADJUST_WHITE,
    [DORRIE_DIP] TEXT_ADJUST_WHITE,
    [SWINGING_WITH_SHARKS] TEXT_ADJUST_WHITE,
    [SWING_N_SWIPE] TEXT_ADJUST_WHITE,
    [MP3_CHANCE_TIME] TEXT_ADJUST_WHITE,
    [STARDUST_BATTLE] TEXT_ADJUST_WHITE,
    [GAME_GUYS_ROULETTE] TEXT_ADJUST_WHITE,
    [GAME_GUYS_LUCKY_7] TEXT_ADJUST_WHITE,
    [GAME_GUYS_MAGIC_BOXES] TEXT_ADJUST_WHITE,
    [GAME_GUYS_SWEET_SURPRISE] TEXT_ADJUST_WHITE,
    [DIZZY_DINGHIES] TEXT_ADJUST_WHITE,
    [MARIO_PUZZLE_PARTY_PRO] TEXT_ADJUST_WHITE,
    [BOWSER_SLOTS] TEXT_ADJUST_WHITE,
    [ROLL_OUT_THE_BARRELS] TEXT_ADJUST_WHITE,
    [COFFIN_CONGESTION] TEXT_ADJUST_WHITE,
    [HAMMER_SLAMMER] TEXT_ADJUST_WHITE,
    [GIVE_ME_A_BRAKE] TEXT_ADJUST_WHITE,
    [MALLET_GO_ROUND] TEXT_ADJUST_WHITE,
    [MP2_GRAB_BAG] TEXT_ADJUST_WHITE,
    [BUMPER_BALLOON_CARS] TEXT_ADJUST_WHITE,
    [RAKIN_EM_IN] TEXT_ADJUST_WHITE,
    [DAY_AT_THE_RACES] TEXT_ADJUST_WHITE,
    [MP2_FACE_LIFT] TEXT_ADJUST_WHITE,
    [MP2_CRAZY_CUTTERS] TEXT_ADJUST_WHITE,
    [MP2_HOT_BOB_OMB] TEXT_ADJUST_WHITE,
    [MP2_BOWL_OVER] TEXT_ADJUST_WHITE,
    [RAINBOW_RUN] TEXT_ADJUST_WHITE,
    [MP2_CRANE_GAME] TEXT_ADJUST_WHITE,
    [MOVE_TO_THE_MUSIC] TEXT_ADJUST_WHITE,
    [BOB_OMB_BARRAGE] TEXT_ADJUST_WHITE,
    [LOOK_AWAY] TEXT_ADJUST_WHITE,
    [SHOCK_DROP_OR_ROLL] TEXT_ADJUST_WHITE,
    [LIGHTS_OUT] TEXT_ADJUST_WHITE,
    [FILET_RELAY] TEXT_ADJUST_WHITE,
    [ARCHERIVAL] TEXT_ADJUST_WHITE,
    [TOAD_BANDSTAND] TEXT_ADJUST_WHITE,
    [MP2_BOBSLED_RUN] TEXT_ADJUST_WHITE,
    [MP2_HANDCAR_HAVOC] TEXT_ADJUST_WHITE,
    [MP2_BALLOON_BURST] TEXT_ADJUST_WHITE,
    [SKY_PILOTS] TEXT_ADJUST_WHITE,
    [SPEED_HOCKEY] TEXT_ADJUST_WHITE,
    [CAKE_FACTORY] TEXT_ADJUST_WHITE,
    [DUNGEON_DASH] TEXT_ADJUST_WHITE,
    [MAGNET_CARTA] TEXT_ADJUST_YELLOW,
    [LAVA_TILE_ISLE] TEXT_ADJUST_WHITE,
    [MP2_HOT_ROPE_JUMP] TEXT_ADJUST_WHITE,
    [SHELL_SHOCKED] TEXT_ADJUST_WHITE,
    [TOAD_IN_THE_BOX] TEXT_ADJUST_WHITE,
    [MECHA_MARATHON] TEXT_ADJUST_WHITE,
    [ROLL_CALL] TEXT_ADJUST_WHITE,
    [ABANDON_SHIP] TEXT_ADJUST_WHITE,
    [MP2_PLATFORM_PERIL] TEXT_ADJUST_WHITE,
    [TOTEM_POLE_POUND] TEXT_ADJUST_WHITE,
    [MP2_BUMPER_BALLS] TEXT_ADJUST_WHITE,
    [MP2_BOMBS_AWAY] TEXT_ADJUST_WHITE,
    [MP2_TIPSY_TOURNEY] TEXT_ADJUST_WHITE,
    [HONEYCOMB_HAVOC] TEXT_ADJUST_WHITE,
    [HEXAGON_HEAT] TEXT_ADJUST_WHITE,
    [MP2_SKATEBOARD_SCAMPER] TEXT_ADJUST_WHITE,
    [MP2_SLOT_CAR_DERBY] TEXT_ADJUST_WHITE,
    [MP2_SHY_GUY_SAYS] TEXT_ADJUST_WHITE,
    [SNEAK_N_SNORE] TEXT_ADJUST_WHITE,
    [DRIVERS_ED] TEXT_ADJUST_WHITE,
    [MP2_CHANCE_TIME] TEXT_ADJUST_WHITE,
    [WESTERN_LAND_DUEL] TEXT_ADJUST_WHITE,
    [PIRATE_LAND_DUEL] TEXT_ADJUST_WHITE,
    [HORROR_LAND_DUEL] TEXT_ADJUST_WHITE,
    [SPACE_LAND_DUEL] TEXT_ADJUST_WHITE,
    [MYSTERY_LAND_DUEL] TEXT_ADJUST_WHITE,
    [KOOPA_LAND_DUEL] TEXT_ADJUST_WHITE,
    [BOWSERS_BIG_BLAST] TEXT_ADJUST_WHITE,
    [LOONEY_LUMBERJACKS] TEXT_ADJUST_WHITE,
    [TORPEDO_TARGETS] TEXT_ADJUST_WHITE,
    [DESTRUCTION_DUET] TEXT_ADJUST_WHITE,
    [DIZZY_DANCING] TEXT_ADJUST_WHITE,
    [TILE_DRIVER] TEXT_ADJUST_WHITE,
    [QUICKSAND_CACHE] TEXT_ADJUST_YELLOW,
    [DEEP_SEA_SALVAGE] TEXT_ADJUST_YELLOW,
    #ifdef MP1
    [MEMORY_MATCH] TEXT_ADJUST_WHITE,
    [MP1_CHANCE_TIME] TEXT_ADJUST_WHITE,
    [SLOT_MACHINE] TEXT_ADJUST_WHITE,
    [BURIED_TREASURE] TEXT_ADJUST_WHITE,
    [TREASURE_DIVERS] TEXT_ADJUST_YELLOW,
    [SHELL_GAME] TEXT_ADJUST_WHITE,
    [SAME_GAME] TEXT_ADJUST_WHITE,
    [MP1_HOT_BOB_OMB] TEXT_ADJUST_WHITE,
    [YOSHIS_TONGUE_MEETING] TEXT_ADJUST_WHITE,
    [PIPE_MAZE] TEXT_ADJUST_WHITE,
    [GHOST_GUESS] TEXT_ADJUST_WHITE,
    [MUSICAL_MUSHROOM] TEXT_ADJUST_WHITE,
    [PEDAL_POWER] TEXT_ADJUST_WHITE,
    [MP1_CRAZY_CUTTER] TEXT_ADJUST_WHITE,
    [MP1_FACE_LIFT] TEXT_ADJUST_WHITE,
    [WHACKA_A_PLANT] TEXT_ADJUST_WHITE,
    [BASH_N_CASH] TEXT_ADJUST_WHITE,
    [MP1_BOWL_OVER] TEXT_ADJUST_WHITE,
    [GROUND_POUND] TEXT_ADJUST_WHITE,
    [MP1_BALLOON_BURST] TEXT_ADJUST_WHITE,
    [COIN_BLOCK_BLITZ] TEXT_ADJUST_YELLOW,
    [COIN_BLOCK_BASH] TEXT_ADJUST_WHITE,
    [MP1_SKATEBOARD_SCAMPER] TEXT_ADJUST_WHITE,
    [BOX_MOUNTAIN_MAYHEM] TEXT_ADJUST_YELLOW,
    [MP1_PLATFORM_PERIL] TEXT_ADJUST_WHITE,
    [TEETERING_TOWER] TEXT_ADJUST_WHITE,
    [MUSHROOM_MIXUP] TEXT_ADJUST_WHITE,
    [HAMMER_DROP] TEXT_ADJUST_YELLOW,
    [MP1_GRAB_BAG] TEXT_ADJUST_YELLOW,
    [MP1_BOBSLED_RUN] TEXT_ADJUST_WHITE,
    [MP1_BUMPER_BALLS] TEXT_ADJUST_WHITE,
    [TIGHTROPE_TREACHERY] TEXT_ADJUST_WHITE,
    [KNOCK_BLOCK_TOWER] TEXT_ADJUST_WHITE,
    [MP1_TIPSY_TOURNEY] TEXT_ADJUST_WHITE,
    [MP1_BOMBS_AWAY] TEXT_ADJUST_WHITE,
    [MP1_CRANE_GAME] TEXT_ADJUST_WHITE,
    [COIN_SHOWER_FLOWER] TEXT_ADJUST_YELLOW,
    [MP1_SLOT_CAR_DERBY] TEXT_ADJUST_WHITE,
    [MARIO_BANDSTAND] TEXT_ADJUST_WHITE,
    [DESERT_DASH] TEXT_ADJUST_WHITE,
    [MP1_SHY_GUY_SAYS] TEXT_ADJUST_WHITE,
    [LIMBO_DANCE] TEXT_ADJUST_WHITE,
    [BOMBSKETBALL] TEXT_ADJUST_WHITE,
    [CAST_AWAYS] TEXT_ADJUST_YELLOW,
    [KEY_PA_WAY] TEXT_ADJUST_WHITE,
    [RUNNING_OF_THE_BULB] TEXT_ADJUST_WHITE,
    [MP1_HOT_ROPE_JUMP] TEXT_ADJUST_WHITE,
    [MP1_HANDCAR_HAVOC] TEXT_ADJUST_WHITE,
    [DEEP_SEA_DIVERS] TEXT_ADJUST_WHITE,
    [PIRANHA_PURSUIT] TEXT_ADJUST_WHITE,
    [TUG_O_WAR] TEXT_ADJUST_WHITE,
    [PADDLE_BATTLE] TEXT_ADJUST_WHITE,
    //BUMPER_BALL_MAZE_0] 7, //mp1 27
    //BUMPER_BALL_MAZE_1] 7, //mp1 36
    //BUMPER_BALL_MAZE_2] 7, //mp1 48
    //BUMPER_BALL_MAZE_3] 7, //mp1 53
    #endif
};

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
    {COIN_SHOWER_FLOWER, CoinShowerFlowerStr, 54, PLAYERS_1V3}, //mp1 54
    {MP1_CRANE_GAME, mp1_CraneGameStr, 35, PLAYERS_1V3}, //mp1 35
    {PADDLE_BATTLE, PaddleBattleStr, 52, PLAYERS_1V3}, //mp1 52
    {PIPE_MAZE, PipeMazeStr, 9, PLAYERS_1V3}, //mp1 9
    {PIRANHA_PURSUIT, PiranhaPursuitStr, 50, PLAYERS_1V3}, //mp1 50
    {TIGHTROPE_TREACHERY, TightropeTreacheryStr, 31, PLAYERS_1V3}, //mp1 31
    {TUG_O_WAR, TugOWarStr, 51, PLAYERS_1V3}, //mp1 51
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
    
    //mp2 2v2 minigames
    {TORPEDO_TARGETS, TorpedoTargetsStr, 67, PLAYERS_2V2}, //mp2 67
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
    {DEEP_SEA_DIVERS, DeepSeaDiversStr, 49, PLAYERS_2V2}, //mp1 49
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
    {BOWSERS_BIG_BLAST, BowsersBigBlastStr, 65, PLAYERS_BATTLE}, //mp2 65
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

u8 new4PMinigameListEasyMp3[] = {0x15, 0x19, 0x1C, 0x1D, 0x1E, 0x21, 0x22, 0x26, 0x28};
u8 new1v3MinigameListEasyMp3[] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x09, 0x0A};
u8 new2v2MinigameListEasyMp3[] = {0x0B, 0x0C, 0x10, 0x11, 0x13};
u8 newBattleMinigameListEasyMp3[] = {0x2A, 0x2B, 0x2D, 0x2E};
u8 newItemMinigameListEasyMp3[] = {0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40};
u8 newDuelMinigameListEasyMp3[] = {0x31, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39};

//at 80100EF4 originally (easy minigame list, amount of minigames in each category)
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