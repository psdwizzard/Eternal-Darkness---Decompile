typedef unsigned int u32;

void LCStoreBlocks(register void* mainAddress, register void* cacheAddress, register u32 blocks)
{
    register u32 control;

    control = (blocks >> 2) & 0x1F;
    mainAddress = (void*)((u32)mainAddress & 0x0FFFFFFF);
    control |= (u32)mainAddress;
    /* ASM: mtspr writes DMA_U, a hardware register unavailable in C. */
    asm { mtspr 922, control }

    control = ((blocks & 3) << 2) | (u32)cacheAddress;
    control |= 2;
    /* ASM: mtspr writes DMA_L to start the transfer; C cannot write it. */
    asm { mtspr 923, control }
}
