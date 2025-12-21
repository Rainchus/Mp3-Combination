.headersize 0x8010AE2C - 0x32099C
.org 0x8011CC0C //item check for COM using an item
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011CDCC
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x8011C964
    SLT v0, a0, gp //SLTI v0, a0, 3


//if plunder chest found player had max items, set to either 3 or 5
.org 0x80117FE0
    ADDU s0, r0, gp //ADDIU s0, r0, 3
