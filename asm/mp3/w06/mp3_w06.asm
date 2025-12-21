.headersize 0x8011B144 - 0x3B04C4
.org 0x8011AF00
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011B0C0
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x8011AC58
    SLT v0, a0, gp //SLTI v0, a0, 3

//if plunder chest found player had max items, set to either 3 or 5
.org 0x80119370
    ADDU s0, r0, gp //ADDIU s0, r0, 3