typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Marker {
    float dir[3];
    float pos[3];
} Marker;

extern Color lbl_802FC5BC[];
extern s16 lbl_802FC53C[];
extern Marker lbl_805B0EA8[];
extern u8 lbl_8064D019;
extern u8 lbl_8064D01A;
extern float lbl_806503E8;
extern float lbl_806503EC;

extern void fn_801ED468(int);
extern void fn_80226D28(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(u32);
extern void fn_80226C18(u8, int);
extern void fn_801ECD74(Color*);
extern void fn_80226AB4(int, int, u16);
extern void fn_801409AC(float, float, float);
extern void fn_801409A8(void);

void fn_8014064C(void)
{
    Color tmp;
    Color c1;
    Color c2;
    Color c3;
    Color c4;
    Color c5;
    float* cur_pos;
    Marker* m2;
    Marker* cur;
    float* pos2;
    u8 j;
    u8 i;
    float* pos;
    Marker* m;
    float far;
    float near;
    float s1;
    u8 sel;

    sel = lbl_8064D019 - 1;
    if (lbl_8064D019 == 0)
        sel = lbl_8064D01A;

    fn_801ED468(0x1B);
    fn_80226D28(0);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    fn_80226C18(0x12, 0);

    tmp = lbl_802FC5BC[8];
    tmp.a = 0xFF;
    c1 = tmp;
    fn_801ECD74(&c1);
    fn_80226AB4(0xA8, 3, lbl_8064D01A * 2);
    s1 = lbl_806503E8;
    for (i = 0; i < lbl_8064D01A; i++) {
        m = &lbl_805B0EA8[i];
        pos = m->pos;
        fn_801409AC(pos[0], pos[1], pos[2]);
        fn_801409AC(s1 * m->dir[0] + pos[0], s1 * m->dir[1] + pos[1], s1 * m->dir[2] + pos[2]);
    }
    fn_801409A8();

    tmp = lbl_802FC5BC[9];
    tmp.a = 0xFF;
    c2 = tmp;
    fn_801ECD74(&c2);
    fn_80226AB4(0xA8, 3, lbl_8064D01A * 2);
    near = lbl_806503E8;
    far = lbl_806503EC;
    for (j = 0; j < lbl_8064D01A; j++) {
        m2 = &lbl_805B0EA8[j];
        pos2 = m2->pos;
        fn_801409AC(near * m2->dir[0] + pos2[0], near * m2->dir[1] + pos2[1], near * m2->dir[2] + pos2[2]);
        fn_801409AC(far * m2->dir[0] + pos2[0], far * m2->dir[1] + pos2[1], far * m2->dir[2] + pos2[2]);
    }
    fn_801409A8();

    tmp = lbl_802FC5BC[5];
    tmp.a = 0xFF;
    c3 = tmp;
    fn_801ECD74(&c3);
    cur = &lbl_805B0EA8[sel];
    cur_pos = cur->pos;
    fn_80226AB4(0xA8, 3, 2);
    fn_801409AC(cur_pos[0], cur_pos[1], cur_pos[2]);
    fn_801409AC(lbl_806503E8 * cur->dir[0] + cur_pos[0], lbl_806503E8 * cur->dir[1] + cur_pos[1], lbl_806503E8 * cur->dir[2] + cur_pos[2]);
    fn_801409A8();

    tmp = lbl_802FC5BC[6];
    tmp.a = 0xFF;
    c4 = tmp;
    fn_801ECD74(&c4);
    fn_80226AB4(0xA8, 3, 2);
    fn_801409AC(lbl_806503E8 * cur->dir[0] + cur_pos[0], lbl_806503E8 * cur->dir[1] + cur_pos[1], lbl_806503E8 * cur->dir[2] + cur_pos[2]);
    fn_801409AC(lbl_806503EC * cur->dir[0] + cur_pos[0], lbl_806503EC * cur->dir[1] + cur_pos[1], lbl_806503EC * cur->dir[2] + cur_pos[2]);
    fn_801409A8();

    fn_80226D28(1);
    c5 = lbl_802FC5BC[3];
    fn_801ECD74(&c5);
}
