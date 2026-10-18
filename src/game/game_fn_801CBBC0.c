typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 _GetInputValue(u8*, u8*, u8, u8);

u16 inpGetReverb(u8* voice)
{
    u32 flags = *(u32*)(voice + 0x214);

    if (!(flags & 0x200)) {
        return *(u16*)(voice + 0x37C);
    }
    *(u32*)(voice + 0x214) = flags & ~0x200;
    return _GetInputValue(voice, voice + 0x35C, voice[0x121], voice[0x122]);
}
