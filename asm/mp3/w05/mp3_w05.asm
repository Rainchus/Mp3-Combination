.headersize 0x8011CC0C - 0x3971EC
.org 0x8011C9C8 //item check for COM using an item
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011CB88
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x8011C720
    SLT v0, a0, gp //SLTI v0, a0, 3

//if plunder chest found player had max items, set to either 3 or 5
.org 0x8011758C
    ADDU s0, r0, gp //ADDIU s0, r0, 3