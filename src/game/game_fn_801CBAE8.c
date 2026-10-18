typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 _GetInputValue(u8*, u8*, u8, u8);

u16 inpGetModulation(u8* voice)
{
    u32 flags = *(u32*)(voice + 0x214);

    if (!(flags & 0x20)) {
        return *(u16*)(voice + 0x2EC);
    }
    *(u32*)(voice + 0x214) = flags & ~0x20;
    return _GetInputValue(voice, voice + 0x2CC, voice[0x121], voice[0x122]);
}
