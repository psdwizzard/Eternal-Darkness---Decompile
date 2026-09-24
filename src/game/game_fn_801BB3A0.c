typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[0x14];
    u32 cache;
} StreamSlot;

extern StreamSlot lbl_8061AE48[];
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern u32 fn_801B9D1C(u32);
extern void fn_801C20C8(u32);

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

void fn_801BB3A0(u32 id)
{
    StreamSlot* slots = lbl_8061AE48;
    u32 index;
    u32 offset;
    u8* state_base;
    u8* state;
    u8* cache_base;
    volatile u32* cache_slot;
    volatile u32* voice_slot;
    u32 cache;

    fn_801CE2B8();
    index = find_stream(id);
    if (index != (u32)-1) {
        offset = index * sizeof(StreamSlot);
        state_base = (u8*)slots + 8;
        state = state_base + offset;
        if (*state != 1 && *state == 2) {
            voice_slot = (volatile u32*)((u8*)slots + offset + 0x48);
            fn_801C20C8(*voice_slot);
            *state = 3;
        }
        cache_base = (u8*)slots + 0x60;
        cache_slot = (volatile u32*)(cache_base + offset);
        cache = *cache_slot;
        if (cache != (u32)-1) {
            fn_801CE2B8();
            index = fn_801B9D1C(cache);
            if (index != (u32)-1) {
                offset = index * sizeof(StreamSlot);
                state_base += offset;
                state = state_base;
                if (*state != 1 && *state == 2) {
                    voice_slot = (volatile u32*)((u8*)slots + offset + 0x48);
                    fn_801C20C8(*voice_slot);
                    *state = 3;
                }
                cache_slot = (volatile u32*)(cache_base + offset);
                cache = *cache_slot;
                if (cache != (u32)-1) {
                    fn_801BB3A0(cache);
                }
            }
            fn_801CE280();
        }
    }
    fn_801CE280();
}
