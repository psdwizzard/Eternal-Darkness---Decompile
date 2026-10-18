/* EXI2_WriteN (0x8022E60C, 432 bytes) */

typedef unsigned int u32;

extern int AmcEXISelect(int chan);
extern int AmcEXIImm(void* buf, int len, int mode, void* cb);
extern int AmcEXISync(void);
extern int AmcEXIDeselect(void);

static inline void EXI2_WriteCmd(u32 cmd) {
    u32 data = cmd;
    AmcEXIImm(&data, 2, 1, 0);
    AmcEXISync();
}

static inline int EXI2_Select(void) {
    int r = 0;
    while (r == 0) {
        r = AmcEXISelect(5);
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
    AmcEXIImm(&n, 4, 1, 0);
    AmcEXISync();

    words = n / 4 + ((n & 3) ? 1 : 0);
    for (i = 0; i < words; i++) {
        AmcEXIImm(p++,(i < words - 1) ? 4 : ((n & 3) + (n & 1) == 2) ? 2 : 4, 1, 0);
        AmcEXISync();
    }
    AmcEXIDeselect();

    if (EXI2_Select() == 0) {
        return 1;
    }
    EXI2_WriteCmd(0x10000);
    AmcEXIImm(&status, 2, 0, 0);
    AmcEXISync();
    do {
        AmcEXIImm(&status, 2, 0, 0);
        AmcEXISync();
    } while (((status >> 16) & 1) == 0);
    AmcEXIDeselect();
    return 0;
}
