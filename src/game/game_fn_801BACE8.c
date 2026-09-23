typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[4];
    u32 parameter;
    u8 pad54[0xC];
    u32 cache;
} StreamSlot;

extern StreamSlot lbl_8061AE48[];
extern struct {
    u32 rate;
    u8 rest[0x210];
} lbl_80619C20;

extern float lbl_80650F18;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern int fn_801B9D1C(u32);
extern void fn_801CCB98(u32, u32);

static inline u32 find_stream(u32 id)
{
    u32 i;

    for (i = 0; i < 64; i++) {
        if (lbl_8061AE48[i].state != 0 && lbl_8061AE48[i].id == id) {
            return i;
        }
    }
    return -1;
}

void fn_801BACE8(u32 id, u32 parameter)
{
    StreamSlot* slots = lbl_8061AE48;
    u32 offset;
    u8* parameter_base;
    u8* state_base;
    u8* cache_base;
    int index;
    u32 cache;

    fn_801CE2B8();
    index = find_stream(id);
    if (index != (u32)-1) {
        offset = index * sizeof(StreamSlot);
        parameter_base = (u8*)slots + 0x50;
        state_base = (u8*)slots + 8;
        *(u32*)(parameter_base + offset) = parameter;
        /* Retail scales parameter by the global rate, in this operand order. */
        if (state_base[offset] == 2) {
            fn_801CCB98(((StreamSlot*)((u8*)slots + offset))->voice,
                        (int)(lbl_80650F18 * (float)parameter /
                              (float)lbl_80619C20.rate));
        }
        cache_base = (u8*)slots + 0x60;
        cache = *(u32*)(cache_base + offset);
        if (cache != (u32)-1) {
            fn_801CE2B8();
            index = fn_801B9D1C(cache);
            if (index != (u32)-1) {
                offset = index * sizeof(StreamSlot);
                *(u32*)(parameter_base + offset) = parameter;
                if (state_base[offset] == 2) {
                    fn_801CCB98(((StreamSlot*)((u8*)slots + offset))->voice,
                                (int)(lbl_80650F18 * (float)parameter /
                                      (float)lbl_80619C20.rate));
                }
                cache = *(u32*)(cache_base + offset);
                if (cache != (u32)-1) {
                    fn_801BACE8(cache, parameter);
                }
            }
            fn_801CE280();
        }
    }
    fn_801CE280();
}
