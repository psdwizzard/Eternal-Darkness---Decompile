typedef signed long s32;
typedef unsigned char u8;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Mtx[3][4];
typedef struct Entry801F10BC {
    Vec3 position;
    u8 pad[0xC];
    void* object;
    float value;
} Entry801F10BC;

extern s32 lbl_8064D6F4;
extern s32 lbl_8064D754;
extern s32 lbl_8064D750;
extern volatile s32 lbl_8064D6F0;
extern s32 lbl_8064C378;
extern s32 lbl_8064D18C;
extern u8 lbl_802FC5BC[];
extern Entry801F10BC lbl_8063C4F8[];
extern Mtx lbl_8063C068;
extern float lbl_80651348;
extern float lbl_806513B4;

extern void fn_8022806C(s32, s32, s32, s32, s32, s32, s32);
extern void fn_80227EB8(s32, s32*);
extern void fn_80227D50(s32, s32*);
extern void fn_80210FB0(Mtx);
extern void fn_802114E0(Mtx, void*);
extern void fn_80210FDC(Mtx, Mtx, Mtx);
extern void fn_802111A0(Mtx, Mtx);
extern void fn_8022B748(Mtx, s32, s32);
extern void fn_801ED434(s32);

void fn_801F10BC(s32 first, s32 mask, s32 unused)
{
    s32 color0;
    s32 color1;
    s32 color2;
    s32 color3;
    s32 color4;
    s32 color5;
    s32 color6;
    s32 color7;
    s32 best;
    Entry801F10BC* entry;
    s32 i;
    Mtx matrix;
    Mtx position;

    (void)unused;
    lbl_8064D6F4 = 0;
    lbl_8064D754 = first;
    fn_8022806C(0, 1, 0, 0, first, 2, 1);
    fn_8022806C(2, 0, 0, 0, 0, 0, 2);

    if (first == 0) {
        fn_8022806C(0, 0, 0, 0, 0, 0, 2);
        color0 = *(s32*)(lbl_802FC5BC + 0x0);
        fn_80227EB8(0, &color0);
        if ((lbl_8064C378 | 2) == 0) {
            color1 = *(s32*)(lbl_802FC5BC + 0xC);
            fn_80227EB8(0, &color1);
        }
    } else {
        color2 = *(s32*)(lbl_802FC5BC + 0xC);
        fn_80227EB8(0, &color2);
    }

    color3 = *(s32*)(lbl_802FC5BC + 0x38);
    fn_80227D50(0, &color3);
    lbl_8064D750 = mask;
    fn_8022806C(1, 1, 0, 0, mask, 0, 0);
    fn_8022806C(3, 0, 0, 0, 0, 0, 2);

    if (mask == 0) {
        fn_8022806C(1, 0, 0, 0, 0, 0, 2);
        color4 = *(s32*)(lbl_802FC5BC + 0x0);
        fn_80227EB8(1, &color4);
        if ((lbl_8064C378 | 2) == 0) {
            color5 = *(s32*)(lbl_802FC5BC + 0xC);
            fn_80227EB8(1, &color5);
        }
        lbl_8064D6F0 = 0;
    } else {
        entry = lbl_8063C4F8;
        best = -1;
        for (i = 0; i < 8; entry++, i++) {
            if ((mask & (1 << i)) != 0 && entry->object != 0 &&
                (best == -1 || entry->value < lbl_80651348)) {
                entry->value = lbl_80651348;
                best = i;
            }
        }
        if (best != -1) {
            fn_80210FB0(position);
            position[0][0] = lbl_806513B4 * lbl_8063C4F8[best].position.x;
            position[0][1] = lbl_806513B4 * lbl_8063C4F8[best].position.y;
            position[0][2] = lbl_806513B4 * lbl_8063C4F8[best].position.z;
            fn_802114E0(matrix, lbl_8063C4F8[best].object);
            fn_80210FDC(lbl_8063C068, matrix, matrix);
            fn_802111A0(matrix, matrix);
            fn_80210FDC(position, matrix, matrix);
            fn_8022B748(matrix, 0x2D, 1);
        }
        color6 = *(s32*)(lbl_802FC5BC + 0xC);
        fn_80227EB8(1, &color6);
        lbl_8064D6F0 = 1;
        color7 = *(s32*)(lbl_802FC5BC + 0x38);
        fn_80227D50(1, &color7);
    }

    if (lbl_8064D18C == 0x32) {
        fn_801ED434(2);
        fn_8022806C(1, 1, 0, 0, lbl_8064D750, 0, 0);
    } else if (lbl_8064D6F0 != 0) {
        fn_801ED434(2);
        fn_8022806C(1, 1, 0, 0, lbl_8064D750, 0, 0);
    } else {
        fn_801ED434(1);
        fn_8022806C(1, 0, 0, 0, 0, 0, 2);
    }
}
