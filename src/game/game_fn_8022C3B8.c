typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16 *__cpReg;

/* Read the four command processor counters, high halves first. */
void fn_8022C3B8(u32 *counter2, u32 *counter3, u32 *counter0, u32 *counter1)
{
    u32 high0, high1, low;

    high0 = __cpReg[33];
    low = __cpReg[32];
    *counter0 = (high0 << 16) | low;
    high1 = __cpReg[35];
    low = __cpReg[34];
    *counter1 = (high1 << 16) | low;
    high0 = __cpReg[37];
    low = __cpReg[36];
    *counter2 = (high0 << 16) | low;
    *counter3 = ((u32)__cpReg[39] << 16) | __cpReg[38];
}
