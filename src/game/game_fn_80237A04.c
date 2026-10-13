typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct StreamBuffer {
    u8 data[0x4000];
    u8 file[0x558];
    u8 queue;
} StreamBuffer;

extern void DCFlushRange(void*, u32);
extern void OSReport(const char*, ...);
extern int fn_8020D318(void*, void*, int);
extern int fn_80213704(void*, void*, u32, u32, void (*)(void), u32);
extern void* memcpy(void*, const void*, u32);
extern void* memset(void*, int, u32);

extern void fn_80237E7C(void);
extern StreamBuffer lbl_80643C20;
extern s32 lbl_8064DC30;
extern s32 lbl_8064DC48;
extern s32 lbl_8064DC50;
extern s32 lbl_8064DC54;
extern s32 lbl_8064DC74;

u32 fn_80237A04(void* dst, u32 size) {
    StreamBuffer* work = &lbl_80643C20;
    s32 message;
    s32 chunk;
    u32 result;
    u32 copy;

    result = size;
    if ((lbl_8064DC74 >= 0x2000) == lbl_8064DC48) {
        chunk = 0x2000;
        if (lbl_8064DC54 > 0) {
            do {
                fn_8020D318(&work->queue, &message, 1);
                if (lbl_8064DC30 != message) {
                    OSReport("Error detected. Resumbitting job!\n");
                    while (fn_80213704(work->file, work->data + (lbl_8064DC48 << 13),
                                       lbl_8064DC30, lbl_8064DC50 - lbl_8064DC30,
                                       fn_80237E7C, 2) == 0) {
                    }
                }
            } while (lbl_8064DC30 != message);
        }
        lbl_8064DC48 ^= 1;
        if (lbl_8064DC54 < 0x2000) {
            chunk = (lbl_8064DC54 + 0x1F) & ~0x1F;
            lbl_8064DC54 = 0;
        } else {
            lbl_8064DC54 -= 0x2000;
        }
        memset(work->data + (lbl_8064DC48 << 13), 0, 0x2000);
        DCFlushRange(work->data + (lbl_8064DC48 << 13), 0x2000);
        if (chunk != 0) {
            while (fn_80213704(work->file, work->data + (lbl_8064DC48 << 13), chunk,
                               lbl_8064DC50, fn_80237E7C, 2) == 0) {
            }
            lbl_8064DC30 = chunk;
            lbl_8064DC50 += chunk;
        }
    }
    copy = 0x4000 - lbl_8064DC74;
    if (copy <= size) {
        memcpy(dst, &work->data[lbl_8064DC74], copy);
        if (size == 0 && lbl_8064DC74 <= 0 && lbl_8064DC54 == 0) {
            result = 0;
        }
        size -= copy;
        lbl_8064DC74 = 0;
    }
    if (size != 0) {
        memcpy(dst, &work->data[lbl_8064DC74], size);
        lbl_8064DC74 += size;
    }
    return result;
}
