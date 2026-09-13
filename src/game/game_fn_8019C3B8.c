typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern u8 lbl_80607120[];
extern int lbl_8064D738;

extern void fn_80188A7C(void*, void*, void*);
extern void fn_8018D020(void);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_8018865C(void*, void*, void*);

void fn_8019C3B8(u8* object)
{
    register u8* self;
    register u8* color_data;
    register u8* index_data;
    register u8* vertex_data;
    int vertex_offset;
    int i;
    u8 count;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    u8* object_data;
    u8* color;
    u16 offset;

    self = object;
    count = self[1];
    offset = *(u16*)(lbl_80607120 + 2);
    vertex_size = *(u16*)(lbl_80607120 + 0xA);
    index_size = *(u16*)(lbl_80607120 + 0xE);
    color_size = *(u16*)(lbl_80607120 + 0xC);
    vertex_data = *(u8**)(self + 0x50);
    index_data = *(u8**)(self + 0x54);
    color_data = *(u8**)(self + 0x58);
    if (lbl_8064D738 != 0) {
        index_data += offset * 4;
        vertex_data += offset * 6;
        color_data += offset * 4;
    }

    object_data = *(u8**)(self + 0x4C);
    color = color_data;
    i = 0;
    vertex_offset = 0;
    for (; i < count; i++) {
        int j;
        fn_80188A7C(object_data, vertex_data + vertex_offset, fn_8018D020);
        for (j = 0; j < object_data[0x20]; j++) {
            color[3] = object_data[0x2B];
            color += 4;
        }
        object_data += 0x38;
        vertex_offset += 0x18;
    }

    DCFlushRange(vertex_data, vertex_size);
    DCFlushRange(index_data, index_size);
    DCFlushRange(color_data, color_size);
    {
        int saved = fn_801ED57C(0);
        fn_8018D0D0(self, self + 0x5C, *(s16*)(self + 0xE));
        fn_8018865C(vertex_data, index_data, color_data);
        fn_801ED57C(saved);
    }
}
