typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 _GetInputValue(u8*, u8*, u8, u8);

u16 inpGetSurPanning(u8* voice)
{
    u32 flags = *(u32*)(voice + 0x214);

    if (!(flags & 4)) {
        return *(u16*)(voice + 0x280);
    }
    *(u32*)(voice + 0x214) = flags & ~4;
    return _GetInputValue(voice, voice + 0x260, voice[0x121], voice[0x122]);
}
