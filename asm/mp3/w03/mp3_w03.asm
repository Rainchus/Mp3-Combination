.headersize 0x8011BCE0 - 0x364B50
.org 0x8011BA9C //item check for COM using an item
    SLT v0, a0, gp //SLTI v0, a0, 3

.org 0x8011BC5C
    SLT v0, s1, gp //SLTI v0, s1, 3

.org 0x8011B7F4
    SLT v0, a0, gp //SLTI v0, a0, 3

//if plunder chest found player had max items, set to either 3 or 5
.org 0x801180B8
    ADDU s0, r0, gp //ADDIU s0, r0, 3