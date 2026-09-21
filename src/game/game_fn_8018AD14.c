typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u8 lbl_80607120[];
extern s16 lbl_80607900[];
extern int lbl_8064D738;

extern void fn_8018A310(u8*, void*, void*, int);
extern void fn_80188A7C(void*, void*,
                        void (*)(void*, float, float, float, float, float));
extern void fn_8018D020(void*, float, float, float, float, float);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_80188868(void*, void*, void*, float);

void fn_8018AD14(u8* object)
{
    int count;
    u16 offset;
    u8 raw_count;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    int j;
    u8* object_data;
    u8* vertex_data;
    u8* index_data;
    u8* color_data;
    u8* color;

    raw_count = object[1];
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
    count = raw_count;
    {
        int i;
        for (i = 0; i < count; i++) {
            *(u32*)&lbl_80607900[i * 3] = *(u32*)(object_data + 0xA);
            lbl_80607900[i * 3 + 2] = *(u16*)(object_data + 0xE);
            for (j = 0; j < object_data[0x20]; j++) {
                color[3] = object_data[0x2B];
                color += 4;
            }
            object_data += 0x38;
        }
    }

    if (raw_count > 3) {
        fn_8018A310(*(u8**)(object + 0x4C), lbl_80607900, vertex_data, count);
    } else {
        int i;
        i = 0;
        object_data = *(u8**)(object + 0x4C);
        for (; i < count; i++) {
            fn_80188A7C(object_data, vertex_data + i * 0x18, fn_8018D020);
            object_data += 0x38;
        }
    }

    DCFlushRange(vertex_data, vertex_size);
    DCFlushRange(index_data, index_size);
    DCFlushRange(color_data, color_size);
    {
        int saved = fn_801ED57C(0);
        fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
        fn_80188868(vertex_data, index_data, color_data, *(float*)(object + 0x3C));
        *(float*)(object + 0x3C) += *(float*)(object + 0x40);
        fn_801ED57C(saved);
    }
}
