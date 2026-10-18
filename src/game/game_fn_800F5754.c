typedef void (*DBCommCallback)(void);

extern DBCommCallback gDBCommTable[];

void EnableEXI2Interrupts(void)
{
    gDBCommTable[1]();
}
