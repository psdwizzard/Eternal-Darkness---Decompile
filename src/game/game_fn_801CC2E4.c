typedef unsigned int u32;

extern u32 last_rnd;

u32 sndRand(void)
{
    last_rnd *= 0xA8351D63;
    return (last_rnd >> 6) & 0xFFFF;
}
