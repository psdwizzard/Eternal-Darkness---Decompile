typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    short x;
    short y;
    short z;
} ShortCoord3;

typedef struct Coord3 {
    float x;
    float y;
    float z;
} Coord3;

typedef struct GameState {
    u8 pad[0x1DA];
    u8 scene;
} GameState;

typedef struct MovieState {
    u8 pad[0x174];
    volatile u32 frame;
} MovieState;

typedef float Mtx[3][4];
typedef float Mtx44[4][4];

extern GameState lbl_8030F540;
extern int lbl_8064CC0C[2];
extern Mtx44 lbl_8024A620[4];
typedef struct GXTexObjInt GXTexObjInt;
extern GXTexObjInt lbl_803281C0;
extern u8 lbl_803281E0[];
extern MovieState *lbl_8064CC14;

extern int lbl_8064B828;
extern int lbl_8064B82C;
extern int lbl_8064B830;
extern int lbl_8064B834;
extern int lbl_8064CBA4;
extern int lbl_8064CBD8;
extern int lbl_8064CBDC;
extern int lbl_8064CBE0;
extern float lbl_8064CBE4;
extern u32 lbl_8064CBEC;
extern int lbl_8064CBF0;
extern int lbl_8064CBF4;

extern float lbl_8064F8F8;
extern float lbl_8064F8FC;
extern float lbl_8064F900;
extern float lbl_8064F904;
extern float lbl_8064F90C;
extern float lbl_8064F910;
extern float lbl_8064F914;
extern float lbl_8064F918;
extern float lbl_8064F91C;

extern ShortCoord3 lbl_80651B78;
extern ShortCoord3 lbl_80651B80;
extern ShortCoord3 lbl_80651B88;
extern ShortCoord3 lbl_80651B90;

extern void fn_800ED98C(float);
extern void fn_800EE3F4(void);
extern void fn_800EE3F8(u8);
extern void fn_800EE404(u8);
extern void fn_800EE410(u8);
extern void fn_800EE41C(int, int, int, int);
extern void fn_80179814(ShortCoord3 *, ShortCoord3 *, ShortCoord3 *,
                        ShortCoord3 *, Coord3 *, float);
extern void fn_801ECC4C(void);
extern void fn_801ECF50(u32);
extern void *fn_801EFE84(void *);
extern void fn_801F0044(void);
extern void fn_80210FB0(Mtx);
extern void fn_802119B0(Mtx44, float, float, float, float, float, float);
extern void fn_80225F4C(int, const void *, u8);
extern void fn_802262B8(u8);
extern void fn_80226AB4(int, int, u16);
extern void fn_80226D28(int);
extern void fn_80228020(u8);
extern void fn_80228AFC(GXTexObjInt *, u32);
extern void fn_80228D9C(void);
extern void fn_80229B08(int, int, int, int, int);
extern void fn_80229B88(int, int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_80229CCC(int, int, int, int, int, int);
extern void fn_80229E74(int, int);
extern void fn_8022A118(int, int, int, int);
extern void fn_8022A2F4(u8);
extern void fn_8022B4B8(Mtx44, int);
extern void fn_8022B690(Mtx, int);
extern void fn_8022B70C(u32);
extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_8022B970(u32, u32, u32, u32);
extern void fn_80237D2C(int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

void fn_800EDA88(u32 frame)
{
    int count;
    float level;
    Coord3 out;
    Mtx44 proj;
    Mtx view;
    Mtx44 *mtx;
    int buffer;
    int i;
    int half;
    u8 *dst;
    int start;
    int pos;

    mtx = lbl_8024A620;
    buffer = -1;
    for (i = 0; i < 2; i++) {
        if ((u32)lbl_8064CC0C[i] <= frame && lbl_8064CC0C[i] >= buffer) {
            buffer = i;
        }
    }
    if (buffer == -1) {
        return;
    }

    if (lbl_8064CBF4 > 1) {
        lbl_8064CBF4--;
        return;
    }
    if (lbl_8064CBF4 == 1) {
        lbl_8064CBF4 = 0;
        if (lbl_8030F540.scene != 0x2D && lbl_8030F540.scene != 0x2E &&
            lbl_8030F540.scene != 0x2F && lbl_8030F540.scene != 0x3C &&
            lbl_8030F540.scene != 0x3D && lbl_8030F540.scene != 0x3E) {
            fn_80237D2C(0);
        }
        if (lbl_8030F540.scene == 0x25 || lbl_8030F540.scene == 0x26 ||
            lbl_8030F540.scene == 0x27) {
            fn_801EFE84(0);
        }
    } else if (lbl_8064CBF4 == 0) {
        lbl_8064CBF4 = -1;
        fn_801EFE84(0);
    }

    fn_8022B94C(lbl_8064F8F8, lbl_8064F8F8, lbl_8064F8FC, lbl_8064F900,
                lbl_8064F8F8, lbl_8064F904);
    fn_8022B970(0, 0, 0x280, 0x1E0);
    fn_80225F4C(9, mtx[1], 6);
    if (lbl_8064CBA4 == 1) {
        fn_802119B0(proj, lbl_8064F8F8, lbl_8064F900, lbl_8064F910,
                    lbl_8064F914, lbl_8064F8F8, lbl_8064F918);
        fn_8022B4B8(proj, 1);
    } else {
        fn_802119B0(proj, lbl_8064F8F8, lbl_8064F900, lbl_8064F8F8,
                    lbl_8064F8FC, lbl_8064F8F8, lbl_8064F918);
        fn_8022B4B8(proj, 1);
    }
    fn_80210FB0(view);
    fn_8022B690(view, 0);
    fn_8022B70C(0);
    fn_80225F4C(0xB, mtx[2], 4);
    fn_80225F4C(0xD, mtx[3], 8);
    fn_80226D28(0);
    fn_80228D9C();

    count = 1;
    /* retail reads the volatile frame counter twice before comparing */
    lbl_8064CC14->frame;
    if (lbl_8064CBEC == lbl_8064CC14->frame) {
        count = lbl_8064CBF0 + 1;
    }
    lbl_8064CBF0 = count;
    lbl_8064CBEC = lbl_8064CC14->frame;

    fn_80228AFC(&lbl_803281C0, 0);
    fn_80229E74(0, 0x10);
    fn_80229B88(0, 7, 7, 7, 6);
    fn_80229CCC(0, 0, 0, 0, 1, 0);
    fn_80229B08(0, 0xF, 0xC, 8, 0xE);
    fn_80229C0C(0, 0, 0, 0, 1, 0);
    fn_800EE41C(0, 1, 4, 0x3C);
    fn_8022A118(0, 0, 0, 0xFF);
    fn_8022A2F4(1);
    fn_802262B8(1);
    fn_80228020(1);
    fn_80226AB4(0x90, 0, 6);
    for (i = 0; i < 6; i++) {
        fn_800EE410(i);
        fn_800EE404(i);
        fn_800EE3F8(i);
    }
    fn_800EE3F4();
    fn_801F0044();
    fn_801ECC4C();
    fn_801ECF50(3);
    fn_801ECC4C();

    if (lbl_8064CBD8 != 0) {
        lbl_8064CBE4 = (float)lbl_8064B82C / lbl_8064F91C;
        fn_800ED98C(lbl_8064CBE4);
        lbl_8064B828 = 0;
        lbl_8064CBDC = 0;
    }

    if (lbl_8064CBE0 == 0) {
        lbl_8064B828 = 1;
        lbl_8064CBDC = 0;
        lbl_8064CBD8 = 0;
        switch (lbl_8030F540.scene) {
        case 0x00: case 0x01:
        case 0x08: case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D:
        case 0x0E: case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
        case 0x1E: case 0x1F: case 0x20:
        case 0x2C:
        case 0x30: case 0x31: case 0x32:
        case 0x3B:
            lbl_8064B82C = 0x28;
            break;
        case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
        case 0x14: case 0x15: case 0x16:
            lbl_8064B82C = 0x19;
            break;
        case 0x17:
            lbl_8064B82C = 0x19;
            if (frame >= 0x249 && frame <= 0x493) {
                lbl_8064B82C = 0x28;
            }
            break;
        case 0x18:
            lbl_8064B82C = 0x19;
            if (frame >= 0x517 && frame <= 0x6B1) {
                lbl_8064B82C = 0x28;
            }
            break;
        case 0x19:
            lbl_8064B82C = 0x19;
            if (frame >= 0x73F && frame <= 0xAA1) {
                lbl_8064B82C = 0x1E;
            }
            break;
        default:
            lbl_8064B82C = 0;
            lbl_8064B828 = 0;
            break;
        }
    }

    if (lbl_8064CBDC != 0) {
        lbl_8064CBE4 = (float)lbl_8064B82C / lbl_8064F91C;
        lbl_8064B834 = -1;
        lbl_8064B830 = lbl_8064F90C * (lbl_8064F904 - lbl_8064CBE4);
        for (i = 0; i < 0x100; i++) {
            if (i < lbl_8064B830) {
                lbl_803281E0[i] = i;
            } else {
                lbl_803281E0[i] = lbl_8064B830;
            }
        }
        if (lbl_8064B828 == 1) {
            lbl_8064CBDC = 0;
        }
        lbl_8064CBD8 = 0;
    } else if (lbl_8064B828 != 0) {
        level = (float)lbl_8064B82C;
        lbl_8064CBE4 = level = level / lbl_8064F91C;
        lbl_8064B830 = (lbl_8064F904 - level) * lbl_8064F90C;
        half = lbl_8064F90C * level;
        if (lbl_8064B834 != lbl_8064B830) {
            for (i = 0; i < 0x100; i++) {
                lbl_803281E0[i] = i;
            }
            start = lbl_8064B830 - (half >> 1);
            dst = lbl_803281E0 + start;
            for (pos = start; pos < 0x100; pos++) {
                ShortCoord3 p0 = lbl_80651B78;
                ShortCoord3 p1 = lbl_80651B80;
                ShortCoord3 p2 = lbl_80651B88;
                ShortCoord3 p3 = lbl_80651B90;
                p0.x = start;
                p0.y = start;
                p1.x = lbl_8064B830;
                p1.y = lbl_8064B830;
                p2.x = p0.x + 0x28;
                p2.y = p0.y + 0x28;
                p3.x = p1.x - 10;
                p3.y = p1.y;
                fn_80179814(&p0, &p1, &p2, &p3, &out,
                            (float)(pos - start) / (float)(0xFF - start));
                *dst++ = out.y;
            }
            lbl_8064B834 = lbl_8064B830;
        }
        lbl_8064CBDC = 0;
        lbl_8064CBD8 = 0;
    } else {
        for (i = 0; i < 0x100; i++) {
            lbl_803281E0[i] = i;
        }
        lbl_8064B830 = 0xFF;
        lbl_8064B834 = 0xFF;
    }

    lbl_8064B830 = MIN(MAX(lbl_8064B830, 10), 0xFF);
}
