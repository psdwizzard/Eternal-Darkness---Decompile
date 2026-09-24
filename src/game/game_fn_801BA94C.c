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

/* Externalized to the retail stream table by this TU's build registration. */
static StreamSlot streamInfo[64];
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
        if (streamInfo[i].state != 0 && streamInfo[i].id == id) {
            return i;
        }
    }
    return -1;
}

void fn_801BA94C(u32 id, u8 volume, u8 left, u8 right, u8 aux_left, u8 aux_right)
{
    u32 offset;
    u8* state_base;
    u8* cache_base;
    u32 index;
    u32 cache;
    u8 actual_left;
    u8 actual_right;

    fn_801CE2B8();
    index = find_stream(id);
    if (index != (u32)-1) {
        offset = index * sizeof(StreamSlot);
        streamInfo[index].saved_left = left;
        streamInfo[index].saved_right = right;
        actual_right = right;
        actual_left = left;
        if (lbl_8064D3CC & 1) {
            actual_left = 0x40;
            actual_right = 0;
        } else if (!(lbl_8064D3CC & 2)) {
            actual_right = 0;
        }
        streamInfo[index].volume = volume;
        streamInfo[index].left = actual_left;
        streamInfo[index].right = actual_right;
        streamInfo[index].aux_left = aux_left;
        streamInfo[index].aux_right = aux_right;
        state_base = (u8*)streamInfo + 8;
        if (state_base[offset] == 2) {
            fn_801CCCC4(streamInfo[index].voice, 0, (u32)streamInfo[index].left << 16,
                        (u32)streamInfo[index].right << 16,
                        (float)streamInfo[index].volume * (1.0f / 127.0f),
                        (float)streamInfo[index].aux_left * (1.0f / 127.0f),
                        (float)streamInfo[index].aux_right * (1.0f / 127.0f));
        }
        /* Each 0x64-byte slot is word aligned. Keep the shared cache-field base. */
        cache_base = (u8*)streamInfo + 0x60;
        offset = ((u32*)cache_base)[offset / sizeof(u32)];
        if (offset != (u32)-1) {
            fn_801CE2B8();
            index = fn_801B9D1C(offset);
            if (index != (u32)-1) {
                StreamSlot* linked_slot;
                u8 linked_left;
                u8 linked_right;

                linked_right = right;
                linked_left = left;

                offset = index * sizeof(StreamSlot);
                linked_slot = (StreamSlot*)((u8*)streamInfo + offset);
                linked_slot->saved_left = linked_left;
                linked_slot->saved_right = linked_right;
                fn_801BA128(&linked_left, &linked_right);
                linked_slot->volume = volume;
                linked_slot->left = linked_left;
                linked_slot->right = linked_right;
                linked_slot->aux_left = aux_left;
                linked_slot->aux_right = aux_right;
                if (state_base[offset] == 2) {
                    fn_801CCCC4(linked_slot->voice, 0, (u32)linked_slot->left << 16,
                                (u32)linked_slot->right << 16,
                                (float)linked_slot->volume * (1.0f / 127.0f),
                                (float)linked_slot->aux_left * (1.0f / 127.0f),
                                (float)linked_slot->aux_right * (1.0f / 127.0f));
                }
                cache = ((u32*)cache_base)[offset / sizeof(u32)];
                if (cache != (u32)-1) {
                    fn_801BA94C(cache, volume, left, right,
                                aux_left, aux_right);
                }
            }
            fn_801CE280();
        }
    }
    fn_801CE280();
}
