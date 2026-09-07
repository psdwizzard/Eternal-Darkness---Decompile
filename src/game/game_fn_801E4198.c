typedef signed short s16;

void fn_801E4198(s16 first, s16 second, s16 third)
{
    volatile s16* fifo = (volatile s16*)0xCC008000;
    *fifo = first;
    *fifo = second;
    *fifo = third;
}
