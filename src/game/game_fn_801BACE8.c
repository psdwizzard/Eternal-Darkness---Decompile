typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[4];
    u32 frq;
    u8 pad54[0xC];
    unsigned long cache;
} StreamSlot;

typedef struct SynthInfo {
    u32 mixFrq;
    u8 pad04[0x210];
} SynthInfo;

static StreamSlot streamInfo[64];
extern SynthInfo lbl_80619C20;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern int fn_801B9D1C(u32);
extern void fn_801CCB98(u32, u32);
void fn_801BACE8(u32 id, u32 frq);

static inline u32 find_stream(u32 id)
{
    u32 i;

    for (i = 0; i < 64; i++) {
        if (streamInfo[i].state != 0 && id == streamInfo[i].id) {
            return i;
        }
    }
    return -1;
}

static inline void frq_linked(u32 id, u32 frq)
{
    u32 i;
    s32 pitch;

    fn_801CE2B8();
    i = fn_801B9D1C(id);
    if (i != -1) {
        streamInfo[i].frq = frq;
        if (streamInfo[i].state == 2) {
            pitch = (4096.f * frq) / lbl_80619C20.mixFrq;
            fn_801CCB98(streamInfo[i].voice, pitch);
        }
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            fn_801BACE8(streamInfo[i].cache, frq);
        }
    }
    fn_801CE280();
}

void fn_801BACE8(u32 id, u32 frq)
{
    u32 i;
    s32 pitch;

    fn_801CE2B8();
    i = find_stream(id);
    if (i != -1) {
        streamInfo[i].frq = frq;
        if (streamInfo[i].state == 2) {
            pitch = (4096.f * frq) / lbl_80619C20.mixFrq;
            fn_801CCB98(streamInfo[i].voice, pitch);
        }
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            frq_linked(streamInfo[i].cache, frq);
        }
    }
    fn_801CE280();
}
