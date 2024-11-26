.headersize 0x801112DC - 0x50D53C

//prevent daisy from being chosen
.org 0x80111800
    ORI v0, r0, 0

//prevent waluigi from being chosen
.org 0x80111820
    ORI v0, r0, 0