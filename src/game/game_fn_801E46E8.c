typedef signed short s16;

void fn_801E46E8(s16 first, s16 second)
{
    volatile s16* fifo = (volatile s16*)0xCC008000;
    *fifo = first;
    *fifo = second;
}
