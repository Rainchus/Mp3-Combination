.headersize 0x8011B30C - 0x37D29C
.org 0x8011B0C8 //item check for COM using an item
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011B288
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x8011AE20
    SLT v0, a0, gp //SLTI v0, a0, 3

//if plunder chest found player had max items, set to either 3 or 5
.org 0x80117B80
    ADDU s0, r0, gp //ADDIU s0, r0, 3