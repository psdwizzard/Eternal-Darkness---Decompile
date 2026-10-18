typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 _GetInputValue(u8*, u8*, u8, u8);

u16 inpGetTremolo(u8* voice)
{
    u32 flags = *(u32*)(voice + 0x214);

    if (!(flags & 0x1000)) {
        return *(u16*)(voice + 0x3E8);
    }
    *(u32*)(voice + 0x214) = flags & ~0x1000;
    return _GetInputValue(voice, voice + 0x3C8, voice[0x121], voice[0x122]);
}
