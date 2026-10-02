typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[0x11];
    u8 hwStreamHandle;
    u8 pad5E[2];
    unsigned long cache;
} StreamSlot;

static StreamSlot streamInfo[64];
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern int fn_801B9D1C(u32);
extern void fn_801BB3A0(u32);
extern void fn_801CD1E0(u8);
void fn_801BAF90(u32 id);

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

static inline void free_linked(u32 id)
{
    u32 i;

    fn_801CE2B8();
    i = fn_801B9D1C(id);
    if (i != -1) {
        fn_801BB3A0(id);
        fn_801CD1E0(streamInfo[i].hwStreamHandle);
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            fn_801BAF90(streamInfo[i].cache);
        }
        streamInfo[i].state = 0;
    }
    fn_801CE280();
}

void fn_801BAF90(u32 id)
{
    u32 i;

    fn_801CE2B8();
    i = find_stream(id);
    if (i != -1) {
        fn_801BB3A0(id);
        fn_801CD1E0(streamInfo[i].hwStreamHandle);
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            free_linked(streamInfo[i].cache);
        }
        streamInfo[i].state = 0;
    }
    fn_801CE280();
}
