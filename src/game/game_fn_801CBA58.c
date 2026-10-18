typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 _GetInputValue(u8*, u8*, u8, u8);

u16 inpGetPitchBend(u8* voice)
{
    u32 flags = *(u32*)(voice + 0x214);

    if (!(flags & 8)) {
        return *(u16*)(voice + 0x2A4);
    }
    *(u32*)(voice + 0x214) = flags & ~8;
    return _GetInputValue(voice, voice + 0x284, voice[0x121], voice[0x122]);
}
