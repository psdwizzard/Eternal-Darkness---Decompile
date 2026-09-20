typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u8 lbl_80607120[];
extern s16 lbl_80607900[];
extern int lbl_8064D738;
extern u32 lbl_80651D70;
extern u16 lbl_80651D74;

extern int fn_80180430(void*, u8);
extern void fn_80181808(void*, int, int);
extern void fn_8018168C(void*, void*, s16, u16);
extern void fn_8018A574(void*, void*, void*, s16*);
extern void fn_80211A48(void*, void*, void*);
extern void fn_80211380(void*, void*, float);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_8018865C(void*, void*, void*);

void fn_8018DC24(u8* object)
{
    int i;
    int phase;
    u8 count;
    u16 vertex_size;
    u16 index_size;
    u16 color_size;
    u8* object_data;
    u8* color;
    u16 offset;
    register u8* vertex_data;
    register u8* index_data;
    register u8* color_data;
    register u8* transform;
    register u8* self;

    self = object;
    count = object[1];
    offset = *(u16*)(lbl_80607120 + 2);
    transform = object + 0x8C;
    vertex_size = *(u16*)(lbl_80607120 + 0xA);
    phase = 0;
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

    object_data = *(u8**)(self + 0x4C);
    color = color_data;
    i = 0;
    for (; i < count; i++) {
        struct { u32 word; u16 half; } point;
        int shade;
        point.word = lbl_80651D70;
        point.half = lbl_80651D74;
        shade = (int)((float)phase * *(float*)(transform + 0x30)) & 0x3F;
        if ((transform[5] & 0x40) != 0 || i < transform[0]) {
            if (fn_80180430(self + 0x24, (u8)i) != 0) {
                fn_80181808(transform, i, 1);
                *(s16*)(object_data + 0xE) += *(s16*)(object_data + 0x14);
            }
        }
        fn_8018168C(object_data, &point, (s16)shade, ((u16*)transform)[i + 7]);
        *(u32*)&lbl_80607900[i * 3] = *(u32*)(object_data + 0xA);
        lbl_80607900[i * 3 + 2] = *(u16*)(object_data + 0xE);
        {
            int j;
            for (j = 0; j < object_data[0x20]; j++) {
                color[3] = object_data[0x2B];
                color += 4;
            }
        }
        phase++;
        object_data += 0x38;
        if (phase >= transform[3]) {
            phase = 0;
        }
    }

    fn_8018A574(transform, self, lbl_80607900, (s16*)vertex_data);
    fn_80211A48(transform + 0x60, transform + 0x6C, transform + 0x60);
    {
        float value = *(float*)(transform + 0x68);
        if (value < 0.0f) value = -value;
        if (value > 360.0f) *(float*)(transform + 0x68) = *(float*)(transform + 0x74);
    }
    {
        float value = *(float*)(transform + 0x68);
        if (value < 0.0f) value = -value;
        fn_80211380(transform + 0x78, transform + 0x60, 0.017453292f * value);
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
