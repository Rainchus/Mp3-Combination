System_DisableInterrupts:
  /* Zero some COP0 registers to disable threads */
  mfc0 a0, $12
  li a1, 0xfffffffe
  and a0, a1
  mtc0 a0, $12

  mtc0 zero, $9
  mtc0 zero, $11
  mtc0 zero, $13

  /* Disable interrupts */
  la   a1, 0xa4300000
  ori  a0, zero, 0x0555
  jr   ra
   sw  a0, 0x0c(a1)

ComboGameSwitch2ToMp3:
  la sp,0xa0800000
  la t0,(ComboSwitchGame3ToMp3 + 0x20000000) //points to uncached ram
  jr t0
   nop

ComboGameSwitch2ToMp2:
  la sp,0xa0800000
  la t0,(ComboSwitchGame3ToMp2 + 0x20000000) //points to uncached ram
  jr t0
   nop

ComboGameSwitch4:
  /* Reset the icache */
  la t0,0x80000000
  la t1,0x80004000
.LicacheLoop:
  cache 0,(t0)
  addiu t0,0x20
  bne t0,t1,.LicacheLoop
   nop

  /* Reset the dcache */
  la t0,0x80000000
  la t1,0x80002000
.LdcacheLoop:
  cache 1,(t0)
  addiu t0,0x10
  bne t0,t1,.LdcacheLoop
   nop

  /* Execute the game */
  jr a0
   nop