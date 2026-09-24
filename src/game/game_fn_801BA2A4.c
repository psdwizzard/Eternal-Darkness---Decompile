typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 positional;
    u8 pad0A[2];
    void (*callback)(void);
    u32 source;
    u32 samples;
    u32 buffer_bytes;
    u32 last;
    unsigned short numCoef;
    u8 pad22[6];
    s16 position[8][2];
    u32 voice;
    u32 callback_arg;
    u32 voice_flags;
    u8 format;
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
extern u32 lbl_8064D3EC;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern u32 fn_801BA6C4(u32, u32);
extern u8 fn_801CD1C0(u32, u32, u32, u32);
extern u32 fn_801BB1A0(u32);

/* Skip the reserved ID and reject IDs held by active slots. */
static inline u32 NextStreamId(StreamSlot* slots)
{
    u32 id;
    u32 found;
    do {
        id = lbl_8064D3EC++;
        if (id == (u32)-1) {
            id = lbl_8064D3EC++;
        }
        for (found = 0; found < 64; found++) {
            if (slots[found].state != 0 && slots[found].id == id) {
                break;
            }
        }
    } while (found != 64);

    return id;
}

u32 fn_801BA2A4(u8 format, u32 source, u32 samples, u32 voice_flags,
                u8 volume, u8 left, u8 right, u8 aux_left,
                u8 aux_right, u8 priority, u32 flags,
                void (*callback)(void), u32 callback_arg, s16* position)
{
    StreamSlot* slots = lbl_8061AE48;
    u32 slot_index;
    u32 id;
    u32 bytes;
    u8 cache_id;
    u32 effective_left;
    u32 effective_right;

    fn_801CE2B8();

    {
        StreamSlot* scan = slots;
        for (slot_index = 0; slot_index < 64; scan++, slot_index++) {
            if (scan->state == 0) {
                break;
            }
        }
    }
    if (slot_index != 64) {

        id = NextStreamId(slots);

        slots[slot_index].id = id;
        slots[slot_index].flags = flags;
        bytes = fn_801BA6C4(samples, flags);
        slots[slot_index].source = source;
        slots[slot_index].samples = samples;
        slots[slot_index].buffer_bytes = bytes;
        slots[slot_index].callback = callback;
        slots[slot_index].voice = (u32)-1;

        if (flags & 1) {
            if (position != 0) {
                int i;
                for (i = 0; i < 8; i++) {
                    slots[slot_index].position[i][0] = position[i * 2];
                    slots[slot_index].position[i][1] = position[i * 2 + 1];
                }
                slots[slot_index].numCoef = 8;
            }
            slots[slot_index].positional = 1;
        } else {
            slots[slot_index].positional = 0;
        }

        slots[slot_index].voice_flags = voice_flags;
        slots[slot_index].priority = priority;
        slots[slot_index].format = format;
        slots[slot_index].saved_left = left;
        slots[slot_index].saved_right = right;

        /* Preserve the auxiliary channels while adjusting the main channels. */
        effective_right = right;
        effective_left = left;

        if (lbl_8064D3CC & 1) {
            effective_left = 0x40;
            effective_right = 0;
        } else if (!(lbl_8064D3CC & 2)) {
            effective_right = 0;
        }

        slots[slot_index].volume = volume;
        slots[slot_index].left = effective_left;
        slots[slot_index].right = effective_right;
        slots[slot_index].aux_left = aux_left;
        slots[slot_index].aux_right = aux_right;
        slots[slot_index].callback_arg = callback_arg;
        slots[slot_index].cache = (u32)-1;
        slots[slot_index].state = 3;
        cache_id = fn_801CD1C0(bytes, slots[slot_index].cache, effective_left, effective_right);
        slots[slot_index].cache_id = cache_id;

        if (cache_id != 0xFF) {
            if (!(flags & 0x10000) && fn_801BB1A0(id) == 0) {
                id = (u32)-1;
            }
        } else {
            id = (u32)-1;
        }
        if (id == (u32)-1) {
            slots[slot_index].state = 0;
        }
    } else {
        id = (u32)-1;
    }
    fn_801CE280();
    return id;
}
