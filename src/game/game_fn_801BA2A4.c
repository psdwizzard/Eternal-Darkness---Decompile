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

static StreamSlot lbl_8061AE48[64];
extern u32 synthFlags;
extern u32 nextPublicID;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern u32 sndStreamAllocLength(u32, u32);
/* Only the buffer size is consumed by the stream-buffer allocator. */
extern u8 hwInitStream();
extern u32 sndStreamActivate(u32);

/* Skip the reserved ID and reject IDs held by active slots. */
static inline u32 NextStreamId(void)
{
    u32 id;
    u32 found;
    do {
        id = nextPublicID++;
        if (id == (u32)-1) {
            id = nextPublicID++;
        }
        for (found = 0; found < 64; found++) {
            if (lbl_8061AE48[found].state != 0 && lbl_8061AE48[found].id == id) {
                break;
            }
        }
    } while (found != 64);

    return id;
}

u32 sndStreamAllocEx(u8 format, u32 source, u32 samples, u32 voice_flags,
                u8 volume, u8 left, u8 right, u8 aux_left,
                u8 aux_right, u8 priority, u32 flags,
                void (*callback)(void), u32 callback_arg, s16* position)
{
    u32 slot_index;
    u32 id;
    u32 bytes;
    u8 cache_id;
    u8 effective_left;
    u8 effective_right;

    hwDisableIrq();

    for (slot_index = 0; slot_index < 64; slot_index++) {
        if (lbl_8061AE48[slot_index].state == 0) {
            break;
        }
    }
    if (slot_index != 64) {
        id = NextStreamId();

        lbl_8061AE48[slot_index].id = id;
        lbl_8061AE48[slot_index].flags = flags;
        bytes = sndStreamAllocLength(samples, flags);
        lbl_8061AE48[slot_index].source = source;
        lbl_8061AE48[slot_index].samples = samples;
        lbl_8061AE48[slot_index].buffer_bytes = bytes;
        lbl_8061AE48[slot_index].callback = callback;
        lbl_8061AE48[slot_index].voice = (u32)-1;

        if (flags & 1) {
            if (position != 0) {
                int i;
                for (i = 0; i < 8; i++) {
                    lbl_8061AE48[slot_index].position[i][0] = position[i * 2];
                    lbl_8061AE48[slot_index].position[i][1] = position[i * 2 + 1];
                }
                lbl_8061AE48[slot_index].numCoef = 8;
            }
            lbl_8061AE48[slot_index].positional = 1;
        } else {
            lbl_8061AE48[slot_index].positional = 0;
        }

        lbl_8061AE48[slot_index].voice_flags = voice_flags;
        lbl_8061AE48[slot_index].priority = priority;
        lbl_8061AE48[slot_index].format = format;
        lbl_8061AE48[slot_index].saved_left = left;
        lbl_8061AE48[slot_index].saved_right = right;

        /* Preserve the auxiliary channels while adjusting the main channels. */
        effective_right = right;
        effective_left = left;

        if (synthFlags & 1) {
            effective_left = 0x40;
            effective_right = 0;
        } else if (!(synthFlags & 2)) {
            effective_right = 0;
        }

        lbl_8061AE48[slot_index].volume = volume;
        lbl_8061AE48[slot_index].left = effective_left;
        lbl_8061AE48[slot_index].right = effective_right;
        lbl_8061AE48[slot_index].aux_left = aux_left;
        lbl_8061AE48[slot_index].aux_right = aux_right;
        lbl_8061AE48[slot_index].callback_arg = callback_arg;
        lbl_8061AE48[slot_index].cache = (u32)-1;
        lbl_8061AE48[slot_index].state = 3;
        cache_id = hwInitStream(bytes);
        lbl_8061AE48[slot_index].cache_id = cache_id;

        if (cache_id != 0xFF) {
            if (!(flags & 0x10000) && sndStreamActivate(id) == 0) {
                id = (u32)-1;
            }
        } else {
            id = (u32)-1;
        }
        if (id == (u32)-1) {
            lbl_8061AE48[slot_index].state = 0;
        }
    } else {
        id = (u32)-1;
    }
    hwEnableIrq();
    return id;
}
