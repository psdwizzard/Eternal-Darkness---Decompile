/* EXI2_WriteN (0x8022E60C, 432 bytes) */

typedef unsigned int u32;

extern int fn_8022DF68(int chan);
extern int fn_8022DAE0(void* buf, int len, int mode, void* cb);
extern int fn_8022DD24(void);
extern int fn_8022DFE8(void);

static inline void EXI2_WriteCmd(u32 cmd) {
    u32 data = cmd;
    fn_8022DAE0(&data, 2, 1, 0);
    fn_8022DD24();
}

static inline int EXI2_Select(void) {
    int r = 0;
    while (r == 0) {
        r = fn_8022DF68(5);
    }
    return r;
}

int EXI2_WriteN(u32* buf, u32 len) {
    u32 n;
    u32 status;
    u32 i;
    u32 words;
    u32* p = buf;

    n = len;
    if (EXI2_Select() == 0) {
        return 1;
    }
    EXI2_WriteCmd(0x80000000);
    fn_8022DAE0(&n, 4, 1, 0);
    fn_8022DD24();

    words = n / 4 + ((n & 3) ? 1 : 0);
    for (i = 0; i < words; i++) {
        fn_8022DAE0(p++,(i < words - 1) ? 4 : ((n & 3) + (n & 1) == 2) ? 2 : 4, 1, 0);
        fn_8022DD24();
    }
    fn_8022DFE8();

    if (EXI2_Select() == 0) {
        return 1;
    }
    EXI2_WriteCmd(0x10000);
    fn_8022DAE0(&status, 2, 0, 0);
    fn_8022DD24();
    do {
        fn_8022DAE0(&status, 2, 0, 0);
        fn_8022DD24();
    } while (((status >> 16) & 1) == 0);
    fn_8022DFE8();
    return 0;
}
