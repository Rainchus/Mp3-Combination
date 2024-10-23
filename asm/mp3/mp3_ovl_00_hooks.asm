.headersize 0x80106B34 - 0x1174B4
.org 0x80106B34 //remove drawing
    JAL InvalidEepCheck
    NOP

.org 0x80106B88
    JAL InvalidEepCheck
    NOP

.org 0x80105B54 //remove control of debug menu hopefully
    JAL InvalidEep3
    ADDIU a3, r0, 0xFFFF

.org 0x80106BB8
    JAL InvalidEep2
    SRA a2, a2, 16