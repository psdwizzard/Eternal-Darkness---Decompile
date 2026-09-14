typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct GeneratedVertex {
    s16 x;
    s16 y;
    s16 z;
} GeneratedVertex;

enum { QUAD_VERTEX_COUNT = 4 };

extern u8 lbl_80607120[];
extern int lbl_8064D738;
extern void fn_801895E8(void*, void*,
                        void (*)(void*, float, float, float, float, float));
extern void fn_8018D020(void*, float, float, float, float, float);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_801889D8(void*, void*, void*);

void fn_8018BC68(u8* object)
{
    u16 offset;
    int i;
    u8 count;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    u8* object_data;
    u8* vertex_data;
    u8* index_data;
    u8* color_data;
    u8* color;

    count = object[1];
    offset = *(u16*)(lbl_80607120 + 2);
    vertex_size = *(u16*)(lbl_80607120 + 0xA);
    index_size = *(u16*)(lbl_80607120 + 0xE);
    color_size = *(u16*)(lbl_80607120 + 0xC);
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
    i = 0;
    for (; i < count; i++) {
        int j;

        fn_801895E8(object_data,
                    vertex_data + i * QUAD_VERTEX_COUNT * sizeof(GeneratedVertex),
                    fn_8018D020);
        for (j = 0; j < object_data[0x20]; j++) {
            color[3] = object_data[0x2B];
            color += 4;
        }
        object_data += 0x38;
    }
    DCFlushRange(vertex_data, vertex_size);
    DCFlushRange(index_data, index_size);
    DCFlushRange(color_data, color_size);
    {
        int saved = fn_801ED57C(0);
        fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
        fn_801889D8(vertex_data, index_data, color_data);
        fn_801ED57C(saved);
    }
}
