typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct StreamFile {
    u8 pad0[0x34];
    s32 length;
} StreamFile;

typedef struct StreamBuffer {
    u8 data[0x4000];
    u8 file[0x538];
    u8 messages[0x20];
    u8 queue;
} StreamBuffer;

extern void fn_8020D1F0(void *queue, void *messages, int count);
extern int fn_80213394(void *name, void *file);
extern int fn_80213704(void *file, void *addr, u32 length, u32 offset, void (*callback)(void), u32 prio);
extern void fn_80237E7C(void);

static inline s32 StreamFile_GetLength(StreamFile *file) {
    return file->length;
}

extern StreamBuffer lbl_80643C20;
extern s32 lbl_8064DC30;
extern s32 lbl_8064DC3C;
extern s32 lbl_8064DC48;
extern s32 lbl_8064DC50;
extern s32 lbl_8064DC54;
extern s32 lbl_8064DC74;

void fn_80237DB4(void *name) {
    StreamBuffer *work = &lbl_80643C20;

    fn_8020D1F0(&work->queue, work->messages, 8);
    lbl_8064DC3C = 0;
    fn_80213394(name, work->file);
    lbl_8064DC54 = StreamFile_GetLength((StreamFile *)work->file);
    lbl_8064DC50 = 0;
    while (fn_80213704(work->file, work->data, 0x2000, lbl_8064DC50, fn_80237E7C, 2) == 0) {
    }
    lbl_8064DC30 = 0x2000;
    lbl_8064DC50 += 0x2000;
    lbl_8064DC54 -= 0x2000;
    lbl_8064DC48 = 0;
    lbl_8064DC74 = 0;
}
