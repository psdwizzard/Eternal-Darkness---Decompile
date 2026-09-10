typedef unsigned char u8;

static u8 clipTable[0x200];
static int divTable[0x10];
static int mcdivTable[0x200];

static inline int saturate(int x)
{
    if (x < 0) {
        return 0;
    } else if (x > 0xFF) {
        return 0xFF;
    } else {
        return x;
    }
}

void fn_8010242C(void)
{
    int i;
    int n;

    for (i = 0, n = -0x80; i < 0x200; i++, n++) {
        clipTable[i] = saturate(n);
    }

    divTable[0] = 0;
    for (i = 1; i < 0x10; i++) {
        divTable[i] = 0x1000 / (i * 16) * 16;
    }

    mcdivTable[0] = 0;
    for (i = 1; i < 0x200; i++) {
        mcdivTable[i] = 0x1000 / i;
    }
}
