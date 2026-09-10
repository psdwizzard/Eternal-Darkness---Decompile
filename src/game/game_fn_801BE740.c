typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct MSTEP {
    u32 para1;
    u32 para2;
} MSTEP;

#pragma pack(4)
typedef struct SYNTH_VOICE {
    u8 pad_000[0x114];
    u64 cflags;
    u8 pad_11C[5];
    u8 midi;
    u8 midiSet;
    u8 pad_123[0xF1];
    u32 midiDirtyFlags;
} SYNTH_VOICE;
#pragma pack()

extern void fn_801CB2B8(void*, u8, s32, u8, u32);
extern void fn_801CA798(u8, u8, u32);

void fn_801BE740(SYNTH_VOICE* svoice, void* dest, MSTEP* cstep, u64 tstflag, u32 dirtyFlag)
{
    s32 scale;
    u8 combineMode;

    if (!(svoice->cflags & tstflag)) {
        combineMode = 0;
        svoice->cflags |= tstflag;
    } else {
        combineMode = (u8)cstep->para2;
    }

    scale = (s16)(cstep->para1 >> 16);
    scale = (scale << 16) / 100;
    if (scale < 0) {
        scale -= ((s8)(cstep->para2 >> 0x10) << 8) / 100;
    } else {
        scale += ((s8)(cstep->para2 >> 0x10) << 8) / 100;
    }

    fn_801CB2B8(dest, (u8)(cstep->para1 >> 8), scale, combineMode, (u8)(cstep->para2 >> 8) != 0);

    if ((dirtyFlag & 0x80000000) != 0) {
        fn_801CA798(svoice->midi, svoice->midiSet, dirtyFlag);
    } else {
        svoice->midiDirtyFlags |= dirtyFlag;
    }
}
