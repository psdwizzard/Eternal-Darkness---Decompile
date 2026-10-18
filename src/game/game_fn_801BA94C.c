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
    unsigned long cache;
} StreamSlot;

/* Externalized to the retail stream table by this TU's build registration. */
static StreamSlot streamInfo[64];
extern u32 synthFlags;
extern void hwDisableIrq(void);
void sndStreamMixParameterEx(u32 id, u8 volume, u8 left, u8 right, u8 aux_left, u8 aux_right);
extern void hwEnableIrq(void);
extern int GetPrivateIndex(u32);
extern void CheckOutputMode(u8*, u8*);
extern void hwSetVolume(u32, u32, u32, u32, float, float, float);

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

static inline void check_output_mode(u8* left, u8* right)
{
    if (synthFlags & 1) {
        *left = 0x40;
        *right = 0;
    } else if (!(synthFlags & 2)) {
        *right = 0;
    }
}

static inline void set_mix(StreamSlot* slot)
{
    hwSetVolume(slot->voice, 0, (u32)slot->left << 16, (u32)slot->right << 16,
                (float)slot->volume * (1.0f / 127.0f), (float)slot->aux_left * (1.0f / 127.0f),
                (float)slot->aux_right * (1.0f / 127.0f));
}

static inline void setup_mix(StreamSlot* slot, u8 volume, u8 left, u8 right, u8 aux_left,
                             u8 aux_right)
{
    slot->saved_left = left;
    slot->saved_right = right;
    check_output_mode(&left, &right);
    slot->volume = volume;
    slot->left = left;
    slot->right = right;
    slot->aux_left = aux_left;
    slot->aux_right = aux_right;
}

static inline void setup_mix_linked(StreamSlot* slot, u8 volume, u8 left, u8 right,
                                    u8 aux_left, u8 aux_right)
{
    slot->saved_left = left;
    slot->saved_right = right;
    CheckOutputMode(&left, &right);
    slot->volume = volume;
    slot->left = left;
    slot->right = right;
    slot->aux_left = aux_left;
    slot->aux_right = aux_right;
}

static inline void mix_linked(u32 id, u8 volume, u8 left, u8 right, u8 aux_left, u8 aux_right)
{
    u32 i;

    hwDisableIrq();
    i = GetPrivateIndex(id);
    if (i != -1) {
        setup_mix_linked(&streamInfo[i], volume, left, right, aux_left, aux_right);
        if (streamInfo[i].state == 2) {
            set_mix(&streamInfo[i]);
        }
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            sndStreamMixParameterEx(streamInfo[i].cache, volume, left, right, aux_left, aux_right);
        }
    }
    hwEnableIrq();
}

void sndStreamMixParameterEx(u32 id, u8 volume, u8 left, u8 right, u8 aux_left, u8 aux_right)
{
    u32 i;

    hwDisableIrq();
    i = find_stream(id);
    if (i != -1) {
        setup_mix(&streamInfo[i], volume, left, right, aux_left, aux_right);
        if (streamInfo[i].state == 2) {
            set_mix(&streamInfo[i]);
        }
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            mix_linked(streamInfo[i].cache, volume, left, right, aux_left, aux_right);
        }
    }
    hwEnableIrq();
}
