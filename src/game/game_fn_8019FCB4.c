typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u8 lbl_80607120[];
extern int lbl_8064D738;
extern float lbl_80650C8C;
extern float lbl_80650C90;
extern u32 fn_801ED3F4(u32);
extern void fn_8019FEE4(s16*, u8*);
extern void DCFlushRange(void*, u32);
extern int fn_801ED57C(int);
extern void fn_801ED5F4(int, int, s16, float*, float (*)[4], float);
extern void fn_80226D28(int);
extern void fn_8018D0D0(u8*, u32*, int);
extern void fn_801ED468(int);
extern void fn_801ECEC8(u8, int, u8);
extern u8 fn_8017FFB8(void);
extern u8 fn_8017FFB0(void);
extern u8 fn_8017FF98(void);
/* Retail uses pre-prototype argument setup for these four calls. */
extern void fn_80225F4C();
extern void fn_80226AB4(int, int, u16);
extern void fn_8019FED8();
extern void fn_8019FECC();
extern void fn_8019FEC0();
extern void fn_8019FEBC(void);

void fn_8019FCB4(u8* object)
{
    u16 i;
    u16 vertex_count;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    u8* entry;
    u8* vertices;
    u8* indices;
    u8* colors;
    u8* color;
    u16 count;
    int saved;

    vertex_count = *(u16*)(lbl_80607120 + 2);
    vertex_size = *(u16*)(lbl_80607120 + 0xA);
    index_size = *(u16*)(lbl_80607120 + 0xE);
    color_size = *(u16*)(lbl_80607120 + 0xC);
    fn_801ED3F4(*(u32*)(object + 0x68));
    vertices = *(u8**)(object + 0x50);
    indices = *(u8**)(object + 0x54);
    colors = *(u8**)(object + 0x58);
    if (lbl_8064D738 != 0) {
        vertices += vertex_count * 6;
        indices += vertex_count * 4;
        colors += vertex_count * 4;
    }
    entry = *(u8**)(object + 0x4C);
    color = colors;
    count = *(u16*)(object + 0x90);
    for (i = 0; i < count; i++) {
        u16 j;
        fn_8019FEE4((s16*)(vertices + ((u16)i << 2) * 6),
                    *(u8**)(object + 0x8C) + i * 0x3C + 0xC);
        for (j = 0; j < entry[0x20]; j++) {
            color[3] = entry[0x2B];
            color += 4;
        }
    }
    DCFlushRange(vertices, vertex_size);
    DCFlushRange(indices, index_size);
    DCFlushRange(colors, color_size);
    saved = fn_801ED57C(0);
    fn_801ED5F4(1, 0x2100, 0x7D0, 0, 0, lbl_80650C8C);
    fn_80226D28(0);
    fn_8018D0D0(object, (u32*)(object + 0x5C), *(s16*)(object + 0xE));
    fn_801ED468(0x1B);
    fn_801ECEC8(1, 3, 0);
    fn_80225F4C(9, vertices, fn_8017FFB8());
    fn_80225F4C(0xD, indices, fn_8017FFB0());
    fn_80225F4C(0xB, colors, fn_8017FF98());
    fn_80226AB4(0x80, 5, vertex_count);
    for (i = 0; i < vertex_count; i++) {
        fn_8019FED8(i);
        fn_8019FECC(i);
        fn_8019FEC0(i);
    }
    fn_8019FEBC();
    fn_801ED5F4(0, 0, 0, 0, 0, lbl_80650C90);
    fn_801ED57C(saved);
}
