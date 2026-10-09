typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern int lbl_8064D738;
extern u8 lbl_80607120[];
extern u8 lbl_802FC5BC[];
extern const float lbl_80650D34;

extern void fn_8018D020(s16*, float, float, float, float, float);
extern void fn_80188C1C(u8*, void*, void (*)(void*, float, float, float, float, float));
extern void DCFlushRange(void*, unsigned long);
extern int fn_801ED57C(int);
extern void fn_801ECF50(unsigned int);
extern void fn_8018D0D0(u8*, unsigned int*, int);
extern int fn_801EF384(void);
extern void fn_801ED494(int, int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_801ED510(int, int, int);
extern void fn_8018865C(void*, void*, void*);

void fn_801A36C0(u8* object)
{
    u8 count;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    u16 offset;
    int i;
    int saved;
    u8* entries;
    u8* vertex_data;
    register u8* self;
    u8* index_data;
    u8* color_data;
    u8* color;

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

    entries = *(u8**)(self + 0x4C);
    color = color_data;
    for (i = 0; i < count; i++) {
        int j;
        entries[0x21] = (u8)(lbl_80650D34 * *(float*)(self + 0x90));
        /* Four vertices, each with three 16-bit coordinates (24 bytes). */
        fn_80188C1C(entries, vertex_data + (i << 3) * 3, (void (*)(void*, float, float, float, float, float))fn_8018D020);
        for (j = 0; j < entries[0x20]; j++) {
            *(unsigned long*)color = *(unsigned long*)(lbl_802FC5BC + 0xC);
            color += 4;
        }
        entries += 0x38;
    }

    DCFlushRange(vertex_data, vertex_size);
    DCFlushRange(index_data, index_size);
    DCFlushRange(color_data, color_size);
    saved = fn_801ED57C(0);
    fn_801ECF50(3);
    fn_8018D0D0(self, (unsigned int*)(self + 0x5C), *(s16*)(self + 0xE));
    if (fn_801EF384() != 0) {
        fn_801ED494(3, 0, 0, 0, 3);
        fn_80229C0C(0, 0, 1, 2, 1, 0);
        fn_801ED510(0, 3, 3);
    }
    fn_8018865C(vertex_data, index_data, color_data);
    if (fn_801EF384() != 0) {
        fn_80229C0C(0, 0, 0, 0, 1, 0);
        fn_801ED510(0, 0, 0);
        fn_80229C0C(0, 0, 1, 2, 1, 0);
    }
    fn_801ED57C(saved);
}
