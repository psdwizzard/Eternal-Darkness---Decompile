typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern u8 lbl_80607120[];
extern int lbl_8064D738;
extern s16 lbl_80607900[];

extern void fn_8018A3D8(u8*, void*, s16*, int);
extern void fn_80188B44(u8*, void*,
                        void (*)(void*, float, float, float, float, float));
extern void fn_8018D020(s16*, float, float, float, float, float);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(u8*, unsigned int*, int);
extern void fn_8018865C(void*, void*, void*);

void fn_8018AA30(u8* object)
{
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
    u16 offset;

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
    if (count > 3) {
        int j;

        for (i = 0; i < count; i++) {
            *(int*)&lbl_80607900[i * 3] = *(int*)(object_data + 0xA);
            lbl_80607900[i * 3 + 2] = *(u16*)(object_data + 0xE);
            for (j = 0; j < object_data[0x20]; j++) {
                color[3] = object_data[0x2B];
                color += 4;
            }
            object_data += 0x38;
        }
        fn_8018A3D8(*(u8**)(object + 0x4C), lbl_80607900, (s16*)vertex_data, count);
    } else {
        i = 0;
        for (; i < count; i++) {
            /* Four vertices, each with three 16-bit coordinates. */
            fn_80188B44(object_data, vertex_data + (i << 3) * 3,
                        (void (*)(void*, float, float, float, float, float))fn_8018D020);
            {
                int j;
                for (j = 0; j < object_data[0x20]; j++) {
                    color[3] = object_data[0x2B];
                    color += 4;
                }
            }
            object_data += 0x38;
        }
    }

    DCFlushRange(vertex_data, vertex_size);
    DCFlushRange(index_data, index_size);
    DCFlushRange(color_data, color_size);
    {
        int saved = fn_801ED57C(0);
        fn_8018D0D0(object, (unsigned int*)(object + 0x5C), *(s16*)(object + 0xE));
        fn_8018865C(vertex_data, index_data, color_data);
        fn_801ED57C(saved);
    }
}
