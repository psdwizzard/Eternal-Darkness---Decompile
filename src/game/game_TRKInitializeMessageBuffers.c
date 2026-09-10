typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 mutex;
    u32 in_use;
    u32 length;
    u32 position;
    u8 data[0x880];
} TRKBuffer;

extern TRKBuffer lbl_80328610[3];
extern void fn_800F34CC(void *);
extern void fn_800F34C4(void *);
extern void fn_800F34BC(void *);

static inline void TRKSetBufferUsed(TRKBuffer* buffer, int used)
{
    buffer->in_use = used;
}

int TRKInitializeMessageBuffers(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        fn_800F34CC(&lbl_80328610[i]);
        fn_800F34C4(&lbl_80328610[i]);
        TRKSetBufferUsed(&lbl_80328610[i], 0);
        fn_800F34BC(&lbl_80328610[i]);
    }
    return 0;
}
