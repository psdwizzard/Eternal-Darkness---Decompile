typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct SAMPLE_INFO {
    u32 info;
    u32 addr;
    void* extraData;
    u32 offset;
    u32 length;
    u32 loop;
    u32 loopLength;
    u8 compType;
} SAMPLE_INFO;

#pragma pack(4)
typedef struct SYNTH_VOICE {
    u8 pad_000[0xF4];
    u32 id;
    u8 pad_0F8[0x14];
    u8 prio;
    u8 pad_10D[3];
    u32 age;
    u64 cflags;
    u8 pad_11C[8];
    u32 sInfo;
    u32 playFrq;
    u8 pad_12C[0x28];
    u32 volume;
    u8 pad_158[0x3B];
    u8 itdMode;
} SYNTH_VOICE;
#pragma pack()

typedef struct MSTEP {
    u32 para1;
    u32 para2;
} MSTEP;

extern s32 fn_801BCF54(u16, SAMPLE_INFO*);
extern void fn_801BDCEC(SYNTH_VOICE*);
extern void fn_801B7954(SYNTH_VOICE*);
extern void fn_801CC718(u32, u16, SAMPLE_INFO*, u32, u32, u32, u32, u32);


void fn_801BD990(SYNTH_VOICE* svoice, MSTEP* cstep)
{
    static SAMPLE_INFO newsmp;
    u16 smp;

    smp = cstep->para1 >> 8;

    if (fn_801BCF54(smp, &newsmp) != 0) {
        return;
    }
    switch ((u8)(cstep->para1 >> 0x18)) {
    case 0:
        newsmp.offset = cstep->para2;
        break;
    case 1:
        newsmp.offset = ((u8)(0x7f - (svoice->volume >> 0x10)) * cstep->para2) / 0x7f;
        break;
    case 2:
        newsmp.offset = ((u8)(svoice->volume >> 0x10) * cstep->para2) / 0x7f;
        break;
    default:
        newsmp.offset = 0;
        break;
    }

    {
        u32 length = newsmp.length;
        u32* offset = &newsmp.offset;
        if (*offset >= length) {
            *offset = length - 1;
        }
    }

    fn_801CC718(svoice->id & 0xFF, smp, &newsmp, (svoice->cflags & 0x100) == 0,
                ((u32)svoice->prio << 24) | (svoice->age >> 15), svoice->id,
                (svoice->cflags & 0x80000000000ULL) == 0, svoice->itdMode);

    svoice->sInfo = newsmp.info;

    if (svoice->playFrq != 0xffffffff) {
        fn_801BDCEC(svoice);
    }
    svoice->cflags |= 0x20;
    fn_801B7954(svoice);
}
