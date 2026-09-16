typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern u8 lbl_80607120[];
extern int lbl_8064D738;

extern int fn_80180430(void*, u8);
extern u8 fn_801911B0(void*, int);
extern void fn_8018D020(void);
extern void fn_80188A7C(void*, void*, void*);
extern void fn_8018E0D8(void*, void*, void*);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_80188868(void*, void*, void*, float);

void fn_80191034(u8* data)
{
    u8* table = lbl_80607120;
    int i;
    u8 count = data[1];
    u16 index_count = *(u16*)(table + 2);
    u16 size_a = *(u16*)(table + 0xA);
    u16 size_c = *(u16*)(table + 0xE);
    u16 size_b = *(u16*)(table + 0xC);
    u8* element;
    u8* buffer_a = *(u8**)(data + 0x50);
    u8* buffer_b = *(u8**)(data + 0x54);
    u8* buffer_c = *(u8**)(data + 0x58);
    u8* output;
    int buffer_offset;
    int j;
    int token;

    if (lbl_8064D738 != 0) {
        buffer_b += index_count * 4;
        buffer_a += index_count * 6;
        buffer_c += index_count * 4;
    }

    element = *(u8**)(data + 0x4C);
    output = buffer_c;
    i = 0;
    buffer_offset = 0;
    while (i < count) {
        if (!fn_80180430(data + 0x24, (u8)i) || fn_801911B0(data, i)) {
            fn_80188A7C(element, buffer_a + buffer_offset, fn_8018D020);
        } else {
            fn_8018E0D8(element, buffer_a + buffer_offset, fn_8018D020);
        }

        j = 0;
        while (j < element[0x20]) {
            output[3] = element[0x2B];
            j++;
            output += 4;
        }
        element += 0x38;
        buffer_offset += 0x18;
        i++;
    }

    DCFlushRange(buffer_a, size_a);
    DCFlushRange(buffer_b, size_c);
    DCFlushRange(buffer_c, size_b);
    token = fn_801ED57C(0);
    fn_8018D0D0(data, data + 0x5C, *(s16*)(data + 0xE));
    fn_80188868(buffer_a, buffer_b, buffer_c, *(float*)(data + 0x3C));
    *(float*)(data + 0x3C) += *(float*)(data + 0x40);
    fn_801ED57C(token);
}
