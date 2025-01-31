/*
in this, we move
| 0x1B | u8 bowser_suit_flags;
| 0x1C | u8 turn_status; //space type landed on (blue, red, etc.)

to
| 0x1E | u8 bowser_suit_flags;
| 0x1F | u8 turn_status; //space type landed on (blue, red, etc.)
*/

//new offsets for struct members
bowser_suit_flags_indirect_new   equ 0x1E
bowser_suit_flags_direct_new   equ 0x1126 //0x1123 -> 0x1126

turn_status_indirect_new   equ 0x1F
turn_status_direct_new   equ 0x1127 //0x1124 -> 0x1127

//bowser_suit_flags patches first

/*
//indirect access from a pointer
| 105F70 800F2350 8202001B |  lb         $v0, 0x1B($s0)//
| 106020 800F2400 8202001B |  lb         $v0, 0x1B($s0)//
| 10CC14 800F8FF4 A060001B |  sb        $zero, 0x1B($v1)//
| 105EF4 800F22D4 8062001B |  lb         $v0, 0x1B($v1)
| 105E9C 800F227C 8062001B |  lb         $v0, 0x1B($v1)


//access directly into GwPlayer[x].bowser_suit_flags
| F81D0 800E45B0 80221123 |  lb         $v0, %lo(GwPlayer + 0x1B)($at)//
| 3200F0 8010A580 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 339D24 8010A0E4 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 348290 80118650 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 348660 80118A20 80221123 |  lb         $v0, %lo(GwPlayer + 0x1B)($at)//
| 3488D0 80118C90 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 353224 8010A3B4 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 36C0B0 8010A120 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 384108 80109B28 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 3A0C90 8010B910 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 467B48 80105F18 80E71123 |  lb         $a3, %lo(GwPlayer + 0x1B)($a3)//
| 10C708 800F8AE8 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 112E14 800FF1F4 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| 113BD4 800FFFB4 80221123 |  lb         $v0, %lo(GwPlayer + 0x1B)($at)//
| 113DC8 801001A8 80221123 |  lb         $v0, %lo(GwPlayer + 0x1B)($at)//
| EDD04 800DA0E4 80221123 |  lb         $v0, %lo(GwPlayer + 0x1B)($at)//
| F6E54 800E3234 A0231123 |  sb         $v1, %lo(GwPlayer + 0x1B)($at)//
| F853C 800E491C 80421123 |  lb         $v0, %lo(GwPlayer + 0x1B)($v0)//
| F8560 800E4940 A0201123 |  sb         $zero, %lo(GwPlayer + 0x1B)($at)//
*/

//indirect references
.headersize 0x800F2350 - 0x105F70
.org 0x800F2350
    LB v0, bowser_suit_flags_indirect_new (s0)
.org 0x800F2400
    LB v0, bowser_suit_flags_indirect_new (s0)

.headersize 0x800F8FF4 - 0x10CC14
.org 0x800F8FF4
    SB r0, bowser_suit_flags_indirect_new (v1)

.headersize 0x800F22D4 - 0x105EF4
.org 0x800F22D4
    LB v0, bowser_suit_flags_indirect_new (v1)

.org 0x800F227C
    LB v0, bowser_suit_flags_indirect_new (v1)



//direct references
.headersize 0x800E45B0 - 0xF81D0
//implemented by func_800E455C_F817C_shared_board hook instead
//.org 0x800E45B0
    //LB v0, bowser_suit_flags_direct_new(at)
//new hook
.org 0x800E455C
    J func_800E455C_F817C_shared_board
    NOP

.headersize 0x8010A580 - 0x3200F0
.org 0x8010A580
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x8010A0E4 - 0x339D24
.org 0x8010A0E4
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x80118650 - 0x348290
.org 0x80118650
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x80118A20 - 0x348660
.org 0x80118A20
    LB v0, bowser_suit_flags_direct_new(at)

.headersize 0x80118C90 - 0x3488D0
.org 0x80118C90
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x8010A3B4 - 0x353224
.org 0x8010A3B4
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x8010A120 - 0x36C0B0
.org 0x8010A120
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x80109B28 - 0x384108
.org 0x80109B28
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x8010B910 - 0x3A0C90
.org 0x8010B910
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x80105F18 - 0x467B48
.org 0x80105F18
    LB a3, bowser_suit_flags_direct_new(a3)

.headersize 0x800F8AE8 - 0x10C708
.org 0x800F8AE8
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x800FF1F4 - 0x112E14
.org 0x800FF1F4
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x800FFFB4 - 0x113BD4
.org 0x800FFFB4
    LB v0, bowser_suit_flags_direct_new(at)

.headersize 0x801001A8 - 0x113DC8
.org 0x801001A8
    LB v0, bowser_suit_flags_direct_new(at)

.headersize 0x800DA0E4 - 0xEDD04
.org 0x800DA0E4
    LB v0, bowser_suit_flags_direct_new(at)

.headersize 0x800E3234 - 0xF6E54
.org 0x800E3234
    SB v1, bowser_suit_flags_direct_new(at)

.headersize 0x800E491C - 0xF853C
.org 0x800E491C
    LB v0, bowser_suit_flags_direct_new(v0)

.headersize 0x800E4940 - 0xF8560
.org 0x800E4940
    SB r0, bowser_suit_flags_direct_new(at)




//turn_status patches now

/*
//indirect access from a pointer
    | 110944 800FCD24 9045001C |  lbu        $a1, 0x1C($v0)
    | 111E70 800FE250 9245001C |  lbu       $a1, 0x1C($s2)
    | 100A58 800ECE38 A062001C |  sb         $v0, 0x1C($v1)
    | 110714 800FCAF4 A040001C |   sb        $zero, 0x1C($v0)
//access directly into GwPlayer[x].turn_status
    | 3C5800 801089E0 90A51124 |  lbu        $a1, %lo(GwPlayer + 0x1C)($a1)
    | 467B54 80105F24 90421124 |  lbu        $v0, %lo(GwPlayer + 0x1C)($v0)
    | 109AA8 800F5E88 90A51124 |  lbu        $a1, %lo(GwPlayer + 0x1C)($a1)
*/


.headersize 0x800FCD24 - 0x110944
.org 0x800FCD24
    LBU a1, turn_status_indirect_new(v0)

.headersize 0x800FE250 - 0x111E70
.org 0x800FE250
    LBU a1, turn_status_indirect_new(s2)

.headersize 0x800ECE38 - 0x100A58
.org 0x800ECE38
    SB v0, turn_status_indirect_new(v1)

.headersize 0x800FCAF4 - 0x110714
.org 0x800FCAF4
    SB r0, turn_status_indirect_new(v0)



.headersize 0x801089E0 - 0x3C5800
.org 0x801089E0
    LBU a1, turn_status_direct_new(a1)

.headersize 0x80105F24 - 0x467B54
.org 0x80105F24
    LBU v0, turn_status_direct_new(v0)

.headersize 0x800F5E88 - 0x109AA8
.org 0x800F5E88
    LBU a1, turn_status_direct_new(a1)

.headersize 0x800F8FDC - 0x10CBFC
.org 0x800F8FDC
    SLTI v0, a0, 5 //initialize 5 item slots to -1 (instead of the normal 3)
