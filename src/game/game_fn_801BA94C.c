typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[9];
    u8 volume;
    u8 left;
    u8 right;
    u8 aux_left;
    u8 aux_right;
    u8 saved_left;
    u8 saved_right;
    u8 priority;
    u8 cache_id;
    u8 pad5E[2];
    u32 cache;
} StreamSlot;

extern StreamSlot lbl_8061AE48[];
extern u32 lbl_8064D3CC;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern int fn_801B9D1C(u32);
extern void fn_801BA128(u8*, u8*);
extern void fn_801CCCC4(u32, u32, u32, u32, float, float, float);

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

void fn_801BA94C(u32 id, u32 volume, u32 left, u32 right, u32 aux_left, u32 aux_right)
{
    StreamSlot* slots = lbl_8061AE48;
    u32 offset;
    u8* state_base = (u8*)slots + 8;
    u32 saved_aux_right = aux_right;
    u32 saved_aux_left = aux_left;
    u32 saved_right = right;
    u32 saved_left = left;
    u32 saved_volume = volume;
    u32 index;
    u32 cache;
    u32 actual_left;
    u32 actual_right;

    fn_801CE2B8();
    index = find_stream(id);
    if (index != (u32)-1) {
        offset = index * sizeof(StreamSlot);
        slots[index].saved_left = saved_left;
        slots[index].saved_right = saved_right;
        actual_left = saved_left;
        actual_right = saved_right;
        if (lbl_8064D3CC & 1) {
            actual_left = 0x40;
            actual_right = 0;
        } else if (!(lbl_8064D3CC & 2)) {
            actual_right = 0;
        }
        slots[index].volume = saved_volume;
        slots[index].left = actual_left;
        slots[index].right = actual_right;
        slots[index].aux_left = saved_aux_left;
        slots[index].aux_right = saved_aux_right;
        if (state_base[offset] == 2) {
            fn_801CCCC4(slots[index].voice, 0, (u32)slots[index].left << 16,
                        (u32)slots[index].right << 16,
                        (float)slots[index].volume * (1.0f / 255.0f),
                        (float)slots[index].aux_left * (1.0f / 255.0f),
                        (float)slots[index].aux_right * (1.0f / 255.0f));
        }
        cache = slots[index].cache;
        if (cache != (u32)-1) {
            fn_801CE2B8();
            index = fn_801B9D1C(cache);
            if (index != (u32)-1) {
                u8 linked_left = saved_left;
                u8 linked_right = saved_right;

                offset = index * sizeof(StreamSlot);
                slots = (StreamSlot*)((u8*)slots + offset);
                slots->saved_left = saved_left;
                slots->saved_right = saved_right;
                fn_801BA128(&linked_left, &linked_right);
                slots->volume = saved_volume;
                slots->left = linked_left;
                slots->right = linked_right;
                slots->aux_left = saved_aux_left;
                slots->aux_right = saved_aux_right;
                if (state_base[offset] == 2) {
                    fn_801CCCC4(slots->voice, 0, (u32)slots->left << 16,
                                (u32)slots->right << 16,
                                (float)slots->volume * (1.0f / 255.0f),
                                (float)slots->aux_left * (1.0f / 255.0f),
                                (float)slots->aux_right * (1.0f / 255.0f));
                }
                cache = slots->cache;
                if (cache != (u32)-1) {
                    fn_801BA94C(cache, saved_volume, saved_left, saved_right,
                                saved_aux_left, saved_aux_right);
                }
            }
            fn_801CE280();
        }
    }
    fn_801CE280();
}
