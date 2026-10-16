/* EXI2_ReadN (0x8022E350, 700 bytes) */

typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern s32 fn_8022DF68(u32 freq);
extern int fn_8022DAE0(void* buf, s32 len, u32 mode, EXICallback cb);
extern void fn_8022DD24(void);
extern s32 fn_8022DFE8(void);
extern int fn_800F9FE4(const char* fmt, ...);

extern char lbl_802FF820[];
extern u8* lbl_8064C4C0;
extern int lbl_8064DBFC;

static inline void EXI2_WriteCmd(u32 cmd) {
    fn_8022DAE0(&cmd, 2, 1, 0);
    fn_8022DD24();
}

static inline int EXI2_Begin(u32* status) {
    int ok;
    int r;

    if (lbl_8064DBFC != 0) {
        ok = 1;
    } else {
        r = 0;
        while (r == 0) {
            r = fn_8022DF68(5);
        }
        ok = r;
        if (r == 0) {
            fn_800F9FE4(lbl_802FF820);
            ok = 0;
        } else {
            lbl_8064DBFC = 1;
            EXI2_WriteCmd(0);
            fn_8022DAE0(status, 2, 0, 0);
            fn_8022DD24();
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

        fn_8022DAE0(&word, (n < words - 1) ? 4 : (tail == 2) ? 2 : 4, 0, 0);
        fn_8022DD24();
        if (len - i >= 4) {
            count = 4;
        } else {
            count = rem;
        }
        for (j = 0; j < count; j++) {
            buf[i + j] = word >> ((3 - j) * 8);
        }
    }
    fn_8022DFE8();
    lbl_8064DBFC = 0;
    *lbl_8064C4C0 = 0;
    return 0;
}
