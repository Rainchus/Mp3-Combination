#include "marioparty.h"

void WaitForSubSystems(void) {
    u32 tmp;

    for (;;)
    {
        tmp = IO_READ(SP_STATUS_REG);
        if ((tmp & 2) && (tmp & 1) && !(tmp & (SP_STATUS_DMA_BUSY | SP_STATUS_DMA_FULL)))
            break;
    }
    IO_WRITE(SP_STATUS_REG, SP_SET_HALT | SP_CLR_BROKE | SP_CLR_INTR | SP_CLR_SSTEP | SP_CLR_INTR_BREAK | SP_CLR_SIG0 | SP_CLR_SIG1 | SP_CLR_SIG2 | SP_CLR_SIG3 | SP_CLR_SIG4 | SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
    IO_WRITE(SP_SEMAPHORE_REG, 0);
    IO_WRITE(SP_PC_REG, 0);

    for (;;)
    {
        tmp = IO_READ(DPC_STATUS_REG);
        if (!(tmp & 0x170))
            break;
    }
    IO_WRITE(MI_BASE_REG, 0x800);

    for (;;)
    {
        tmp = IO_READ(AI_STATUS_REG);
        if (!(tmp & 0xc0000001))
            break;
    }
    IO_WRITE(AI_STATUS_REG, 0);
    IO_WRITE(AI_CONTROL_REG, 0);

    for (;;)
    {
        tmp = IO_READ(PI_STATUS_REG);
        if (!(tmp & 3))
            break;
    }
    IO_WRITE(PI_STATUS_REG, 3);

    for (;;)
    {
        tmp = IO_READ(SI_STATUS_REG);
        if (!(tmp & 3))
            break;
    }
    IO_WRITE(SI_STATUS_REG, 0);

    /* Disable VI */
    IO_WRITE(VI_CONTROL_REG, 0);
    IO_WRITE(VI_CURRENT_REG, 0);
}

static void waitForPi(void) {
    u32 status;

    for (;;)
    {
        status = IO_READ(PI_STATUS_REG);
        if ((status & 3) == 0)
            return;
    }
}

void comboDma_NoCacheInval(void* dramAddr, u32 cartAddr, u32 size) {
    u32 tmp;

    waitForPi();
    while (size)
    {
        tmp = size;
        if (tmp > 0x2000)
            tmp = 0x2000;
        IO_WRITE(PI_DRAM_ADDR_REG, (u32)dramAddr & 0x1fffffff);
        IO_WRITE(PI_CART_ADDR_REG, cartAddr | PI_DOM1_ADDR2);
        IO_WRITE(PI_WR_LEN_REG, tmp - 1);
        waitForPi();
        size -= tmp;
        dramAddr = (void*)((u32)dramAddr + tmp);
        cartAddr += tmp;
    }
}