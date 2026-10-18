typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8* synthVoice;
extern u32 hwIsActive(u32);
extern u16 inpGetPedal(void*);
extern void macSetPedalState(void*, u32);
extern void hwStart(u32, u8);
extern void hwKeyOff(u32);
extern u32 adsrRelease(void*);

#define U8(p, o)  (*(u8*)((p) + (o)))
#define U32(p, o) (*(u32*)((p) + (o)))
#define U64(p, o) (*(u64*)((p) + (o)))

void EventHandler(u32 index)
{
    u8* voice = synthVoice + index * 0x404;

    if (hwIsActive(index) || U32(voice, 0x34) != 0) {
        macSetPedalState(voice, inpGetPedal(voice) > 0x1F80);

        if (U64(voice, 0x114) & 0x20ULL) {
            U64(voice, 0x114) &= ~0x20ULL;
            U64(voice, 0x114) |= 0x10ULL;
            hwStart(index, U8(voice, 0x11F));
        }

        if ((U64(voice, 0x114) & 0x10000000090ULL) == 0x90ULL) {
            U64(voice, 0x114) &= ~0x90ULL;
            hwKeyOff(index);
            if ((U64(voice, 0x114) & 0x20000000000ULL) &&
                adsrRelease(voice + 0x1DC)) {
                U64(voice, 0x114) &= ~0x20000000000ULL;
            }
        }
    }

    if (U8(voice, 0xA8) != 0) {
        U8(voice, 0xA8) = 0;
        U32(voice, 0x214) = 0x1FFF;
    }
}
