.headersize 0x8011C230 - 0x34BE70
.org 0x8011BFEC //item check for COM using an item
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011C1AC
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x8011BD44
    SLT v0, a0, gp //SLTI v0, a0, 3

//if plunder chest found player had max items, set to either 3 or 5
.org 0x80117B48
    ADDU s0, r0, gp //ADDIU s0, r0, 3
    