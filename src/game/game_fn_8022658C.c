typedef unsigned short u16;

extern volatile u16 *__peReg;

/* Read the pixel engine's draw-sync token. */
u16 GXReadDrawSync(void)
{
    return __peReg[7];
}
