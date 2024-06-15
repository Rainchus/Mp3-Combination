#include "mp3.h"

enum MinigameNameStringIDs {
    STR_HAND_LINE_AND_SINKER = 0x4700,
    STR_COCONUT_CONK = 0x4701,
    STR_SPOTLIGHT_SWIM = 0x4702,
    STR_BOULDER_BALL = 0x4703,
    STR_CRAZY_COGS = 0x4704,
    STR_HIDE_AND_SNEAK = 0x4705,
    STR_RIDICULOUS_RELAY = 0x4706,
    STR_THWOMP_PULL = 0x4707,
    STR_RIVER_RAIDERS = 0x4708,
    STR_TIDAL_TOSS = 0x4709,
    STR_EATSA_PIZZA = 0x470A,
    STR_BABY_BOWSER_BROADSIDE = 0x470B,
    STR_PUMP_PUMP_AND_AWAY = 0x470C,
    STR_HYPER_HYDRANTS = 0x470D,
    STR_PICKING_PANIC = 0x470E,
    STR_COSMIC_COASTER = 0x470F,
    STR_PUDDLE_PADDLE = 0x4710,
    STR_ETCH_N_CATCH = 0x4711,
    STR_LOG_JAM = 0x4712,
    STR_SLOT_SYNCH = 0x4713,
    STR_TREADMILL_GRILL = 0x4714,
    STR_TOADSTOOL_TITAN = 0x4715,
    STR_ACES_HIGH = 0x4716,
    STR_BOUNCE_N_TROUNCE = 0x4717,
    STR_ICE_RINK_RISK = 0x4718,
    STR_LOCKED_OUT = 0x4719,
    STR_CHIP_SHOT_CHALLENGE = 0x471A,
    STR_PARASOL_PLUMMET = 0x471B,
    STR_MESSY_MEMORY = 0x471C,
    STR_PICTURE_IMPERFECT = 0x471D,
    STR_MARIOS_PUZZLE_PARTY = 0x471E,
    STR_THE_BEAT_GOES_ON = 0x471F,
    STR_MPIQ = 0x4720,
    STR_CURTAIN_CALL = 0x4721,
    STR_WATER_WHIRLED = 0x4722,
    STR_FRIGID_BRIDGES = 0x4723,
    STR_AWFUL_TOWER = 0x4724,
    STR_CHEEP_CHEEP_CHASE = 0x4725,
    STR_PIPE_CLEANERS = 0x4726,
    STR_SNOWBALL_SUMMIT = 0x4727,
    STR_ALL_FIRED_UP = 0x4728,
    STR_STACKED_DECK = 0x4729,
    STR_THREE_DOOR_MONTY = 0x472A,
    STR_ROCKIN_RACEWAY = 0x472B,
    STR_MERRY_GO_CHOMP = 0x472C,
    STR_SLAP_DOWN = 0x472D,
    STR_STORM_CHASERS = 0x472E,
    STR_EYE_SORE = 0x472F,
    STR_VINE_WITH_ME = 0x4730,
    STR_POPGUN_PICK_OFF = 0x4731,
    STR_END_OF_THE_LINE = 0x4732,
    STR_BOWSER_TOSS = 0x4733,
    STR_BABY_BOWSER_BONKERS = 0x4734,
    STR_MOTOR_ROOTER = 0x4735,
    STR_SILLY_SCREWS = 0x4736,
    STR_CROWD_COVER = 0x4737,
    STR_TICK_TOCK_HOP = 0x4738,
    STR_FOWL_PLAY = 0x4739,
    STR_WINNERS_WHEEL = 0x473A,
    STR_HEY_BATTER_BATTER = 0x473B,
    STR_BOBBING_BOW_LOONS = 0x473C,
    STR_DORRIE_DIP = 0x473D,
    STR_SWINGING_WITH_SHARKS = 0x473E,
    STR_SWING_N_SWIPE = 0x473F,
    STR_CHANCE_TIME = 0x4740,
    STR_STARDUST_BATTLE = 0x4741,
    STR_GAME_GUYS_ROULETTE = 0x4742,
    STR_GAME_GUYS_LUCKY_7 = 0x4743,
    STR_GAME_GUYS_MAGIC_BOXES = 0x4744,
    STR_GAME_GUYS_SWEET_SURPRISE = 0x4745,
    STR_DIZZY_DINGHIES = 0x4746,
    STR_MARIO_PUZZLE_PARTY_PRO = 0x4747,
    STR_QUESTION_MARKS = 0x4748,
};

enum MinigameIDs {
    HAND_LINE_AND_SINKER = 0,
    COCONUT_CONK = 1,
    SPOTLIGHT_SWIM = 2,
    BOULDER_BALL = 3,
    CRAZY_COGS = 4,
    HIDE_AND_SNEAK = 5,
    RIDICULOUS_RELAY = 6,
    THWOMP_PULL = 7,
    RIVER_RAIDERS = 8,
    TIDAL_TOSS = 9,
    EATSA_PIZZA = 10,
    BABY_BOWSER_BROADSIDE = 11,
    PUMP_PUMP_AND_AWAY = 12,
    HYPER_HYDRANTS = 13,
    PICKING_PANIC = 14,
    COSMIC_COASTER = 15,
    PUDDLE_PADDLE = 16,
    ETCH_N_CATCH = 17,
    LOG_JAM = 18,
    SLOT_SYNC = 19,
    TREADMILL_GRILL = 20,
    TOADSTOOL_TITAN = 21,
    ACES_HIGH = 22,
    BOUNCE_N_TROUNCE = 23,
    ICE_RINK_RISK = 24,
    LOCKED_OUT = 25,
    CHIP_SHOT_CHALLENGE = 26,
    PARASOL_PLUMMET = 27,
    MESSY_MEMORY = 28,
    PICTURE_IMPERFECT = 29,
    MARIOS_PUZZLE_PARTY = 30,
    THE_BEAT_GOES_ON = 31,
    MPIQ = 32,
    CURTAIN_CALL = 33,
    WATER_WHIRLED = 34,
    FRIGID_BRIDGES = 35,
    AWFUL_TOWER = 36,
    CHEEP_CHEEP_CHASE = 37,
    PIPE_CLEANERS = 38,
    SNOWBALL_SUMMIT = 39,
    ALL_FIRED_UP = 40,
    STACKED_DECK = 41,
    THREE_DOOR_MONTY = 42,
    ROCKIN_RACEWAY = 43,
    MERRY_GO_CHOMP = 44,
    SLAP_DOWN = 45,
    STORM_CHASERS = 46,
    EYE_SORE = 47,
    VINE_WITH_ME = 48,
    POPGUN_PICK_OFF = 49,
    END_OF_THE_LINE = 50,
    BOWSER_TOSS = 51,
    BABY_BOWSER_BONKERS = 52,
    MOTOR_ROOTER = 53,
    SILLY_SCREWS = 54,
    CROWD_COVER = 55,
    TICK_TOCK_HOP = 56,
    FOWL_PLAY = 57,
    WINNERS_WHEEL = 58,
    HEY_BATTER_BATTER = 59,
    BOBBING_BOW_LOONS = 60,
    DORRIE_DIP = 61,
    SWINGING_WITH_SHARKS = 62,
    SWING_N_SWIPE = 63,
    CHANCE_TIME = 64,
    STARDUST_BATTLE = 65,
    GAME_GUYS_ROULETTE = 66,
    GAME_GUYS_LUCKY_7 = 67,
    GAME_GUYS_MAGIC_BOXES = 68,
    GAME_GUYS_SWEET_SURPRISE = 69,
    DIZZY_DINGHIES = 70,
    MARIO_PUZZLE_PARTY_PRO = 71,
};

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

char* MinigameList[] = {
    HookLineAndSinkerStr,
    CoconutConkStr,
    SpotlightSwimStr,
    BoulderBallStr,
    CrazyCogsStr,
    HideAndSneakStr,
    RidiculousRelayStr,
    ThwompPullStr,
    RiverRaidersStr,
    TidalTossStr,
    EatsaPizzaStr,
    BabyBowserBroadsideStr,
    PumpPumpAndAwayStr,
    HyperHydrantsStr,
    PickingPanicStr,
    CosmicCoasterStr,
    PuddlePaddleStr,
    EtchNCatchStr,
    LogJamStr,
    SlotSyncStr,
    TreadmillGrillStr,
    ToadstoolTitanStr,
    AcesHighStr,
    BounceNTrounceStr,
    IceRinkRiskStr,
    LockedOutStr,
    ChipShotChallengeStr,
    ParasolPlummetStr,
    MessoryMemoryStr,
    PictureImperfectStr,
    MariosPuzzlePartyStr,
    TheBeatGoesOnStr,
    MPIQStr,
    CurtainCallStr,
    WaterWhirledStr,
    FrigidBridgesStr,
    AwfulTowerStr,
    CheepCheepChaseStr,
    PipeCleanersStr,
    SnowballSummitStr,
    AllFiredUpStr,
    StackedDeckStr,
    ThreeDoorMontyStr,
    RockinRacewayStr,
    MerryGoChompStr,
    SlapDownStr,
    StormChasersStr,
    EyeSoreStr,
    VineWithMeStr,
    PopgunPickOffStr,
    EndOfTheLinerStr,
    BowserTossStr,
    BabyBowserBonkersStr,
    MotorRooterStr,
    SillyScrewsStr,
    CrowdCoverStr,
    TickTockHopStr,
    FowlPlayStr,
    WinnersWheelStr,
    HeyBatterBatterStr,
    BobbingBowloonsStr,
    DorrieDipStr,
    SwingingWithSharksStr,
    SwingNSwipeStr,
    ChanceTimeStr,
    StardustBattleStr,
    GameGuysRouletteStr,
    GameGuysLucky7Str,
    GameGuysMagicBoxesStr,
    GameGuysSweetSurpriseStr,
    DizzyDinghiesStr,
    MariosPuzzlePartyPro2Str
};

char* GetNewMinigameString(s32 minigameIndex) {
    return MinigameList[minigameIndex - 1];
}