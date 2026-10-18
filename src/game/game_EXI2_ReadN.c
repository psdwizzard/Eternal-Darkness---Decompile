/* EXI2_ReadN (0x8022E350, 700 bytes) */

typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern s32 AmcEXISelect(u32 freq);
extern int AmcEXIImm(void* buf, s32 len, u32 mode, EXICallback cb);
extern void AmcEXISync(void);
extern s32 AmcEXIDeselect(void);
extern int printf(const char* fmt, ...);

extern char lbl_802FF820[];
extern u8* pucEXI2InputPending;
extern int fExi2Selected;

static inline void EXI2_WriteCmd(u32 cmd) {
    AmcEXIImm(&cmd, 2, 1, 0);
    AmcEXISync();
}

static inline int EXI2_Begin(u32* status) {
    int ok;
    int r;

    if (fExi2Selected != 0) {
        ok = 1;
    } else {
        r = 0;
        while (r == 0) {
            r = AmcEXISelect(5);
        }
        ok = r;
        if (r == 0) {
            printf(lbl_802FF820);
            ok = 0;
        } else {
            fExi2Selected = 1;
            EXI2_WriteCmd(0);
            AmcEXIImm(status, 2, 0, 0);
            AmcEXISync();
        }
    }
    return ok;
}

int EXI2_ReadN(u8* buf, u32 len) {
    u32 word;
    u32 status;
    u32 words;
    u32 n;
    u32 tail;
    int rem;
    int i;

    if (EXI2_Begin(&status) == 0) {
        return 1;
    }

    words = len / 4 + ((len & 3) ? 1 : 0);
    tail = (len & 3) + (len & 1);
    rem = (int)len % 4;
    for (i = 0, n = 0; i < len; n++, i += 4) {
        int j;
        int count;

        AmcEXIImm(&word, (n < words - 1) ? 4 : (tail == 2) ? 2 : 4, 0, 0);
        AmcEXISync();
        if (len - i >= 4) {
            count = 4;
        } else {
            count = rem;
        }
        for (j = 0; j < count; j++) {
            buf[i + j] = word >> ((3 - j) * 8);
        }
    }
    AmcEXIDeselect();
    fExi2Selected = 0;
    *pucEXI2InputPending = 0;
    return 0;
}
