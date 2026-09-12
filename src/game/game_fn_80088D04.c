typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Global {
    u8 pad[8];
    u8* owner;
} Global;

typedef struct Positions {
    s16 x[10];
    s16 y[10];
    s16 z[10];
} Positions;

extern Positions lbl_8031D3B8;
extern Global lbl_80606328;
extern char lbl_802515D0[];
extern u8 lbl_8064C91C;
extern u8 lbl_8064C91D;
extern void* lbl_8064D224;
extern u32 lbl_8064EB90;
extern u8 lbl_8064B5C8;
extern int lbl_8064C8C4;

extern void fn_801A8D38(int);
extern void fn_801ED3F4(void*);
extern void fn_80225F4C(int, void*, int);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801A8F08(s16, s16, s16, s16, int, int, int);

void fn_80088D04(void)
{
    Positions* positions = &lbl_8031D3B8;
    s16* xs;
    s16* ys;
    s16* zs;
    int i;
    u8 count;
    s16 x;
    s16 y;
    s16 z;
    u8 flags = lbl_8064C91D;
    count = lbl_8064C91C;

    if (flags & 2) {
        xs = positions->x;
        ys = positions->y;
        zs = positions->z;

        for (i = 0; i < count; i++) {
            u32 config;
            x = *xs;
            y = *ys;
            z = *zs;
            fn_801A8D38(5);
            fn_801ED3F4(lbl_8064D224);
            fn_80225F4C(13, lbl_802515D0, 4);
            *(u32*)(lbl_80606328.owner + 0xB18) = 0x80000000;
            config = lbl_8064EB90;
            ((u8*)&config)[3] = lbl_8064B5C8;
            *(u32*)(lbl_80606328.owner + 0xB1C) = config;
            fn_801EDA7C(lbl_80606328.owner + 0xB00, 0, 0x2BF, 0);
            fn_801A8F08(x, y, (s16)(x + z), (s16)(y + z), -1, 0, 5);
            xs++;
            ys++;
            zs++;
        }
        if (lbl_8064C91D & 4) {
            if (lbl_8064B5C8 == 0) {
                lbl_8064C8C4 = 0;
                lbl_8064B5C8 = 0xFC;
            }
            lbl_8064B5C8 -= 4;
        }
    }
}
