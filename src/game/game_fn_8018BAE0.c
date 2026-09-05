typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern u8 lbl_80607130[];
extern int lbl_8064D738;
extern void fn_801ED3F4(void*);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_801ED468(int);
extern void fn_801ECEC8(int, int, int);
extern int fn_8017FFB8(void), fn_8017FFB0(void), fn_8017FF98(void);
extern void fn_80225F4C(int, void*, u8);
extern void fn_80226AB4(int, int, u16);
extern void fn_80188578(u16), fn_8018856C(u16), fn_80188560(u16);
extern void fn_8018855C(void);

#pragma opt_lifetimes off
void fn_8018BAE0(u8* object)
{
    u16 offset;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    u8* vertex_data;
    u8* index_data;
    u8* color_data;
    int saved;
    int i;
    u8* object_data;
    u8* color;

    offset = *(u16*)(lbl_80607130 + 2);
    vertex_size = *(u16*)(lbl_80607130 + 0xA);
    index_size = *(u16*)(lbl_80607130 + 0xE);
    color_size = *(u16*)(lbl_80607130 + 0xC);
    fn_801ED3F4(*(void**)(object + 0x68));
    vertex_data = *(u8**)(object + 0x50);
    index_data = *(u8**)(object + 0x54);
    color_data = *(u8**)(object + 0x58);
    if (lbl_8064D738 != 0) {
        index_data += offset * 4;
        vertex_data += offset * 6;
        color_data += offset * 4;
    }
    object_data = *(u8**)(object + 0x4C);
    color = color_data;
    for (i = 0; (u16)i < object_data[0x20]; i++) {
        color[3] = object_data[0x2B];
        color += 4;
    }
    DCFlushRange(vertex_data, vertex_size);
    DCFlushRange(index_data, index_size);
    DCFlushRange(color_data, color_size);
    saved = fn_801ED57C(0);
    fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
    fn_801ED468(0x1B);
    fn_801ECEC8(1, 3, 0);
    fn_80225F4C(9, vertex_data, (u8)fn_8017FFB8());
    fn_80225F4C(13, index_data, (u8)fn_8017FFB0());
    fn_80225F4C(11, color_data, (u8)fn_8017FF98());
    fn_80226AB4(0x80, 5, offset);
    for (color_data = 0; (u16)color_data < offset; color_data++) {
        object = (u8*)(u16)color_data;
        fn_80188578((u16)object);
        fn_8018856C((u16)object);
        fn_80188560((u16)object);
    }
    fn_8018855C();
    fn_801ED57C(saved);
}
#pragma opt_lifetimes reset
