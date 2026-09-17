typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Buffers { u8* vertices; u8* colors; u8* indices; } Buffers;

extern u8 lbl_80607120[], lbl_80606AE0[];
extern int lbl_8064D738, lbl_8064D24C;
extern void fn_8018D788(int, u8*, Buffers*, u16);
extern void* memcpy(void*, const void*, unsigned int);
extern void DCFlushRange(void*, unsigned int);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16), fn_801ED468(int);
extern int fn_8017FFB8(void), fn_8017FFB0(void), fn_8017FF98(void);
extern void fn_80225F4C(int, void*, u8), fn_801ECEC8(int, int, int);
extern void fn_8022B448(void*, int);

void fn_8018D7DC(u8* object)
{
    Buffers buffers;
    u8* state;
    u8* self;
    u8* config;
    int zero1;
    int zero2;
    int i;
    int copies;
    u8* object_data;
    u8* destination;
    u8* source;
    u8* color;
    int saved;

    state = object + 0x8C;
    self = object;
    config = lbl_80607120;
    object_data = *(u8**)(self + 0x4C);
    fn_8018D788(lbl_8064D738, self, &buffers, *(u16*)(config + 2));
    color = buffers.indices;
    i = 0;
    while (i < self[1]) {
        memcpy(buffers.vertices + i * 6, object_data + 0xA, 6);
        color[3] = object_data[0x2B];
        object_data += 0x38;
        i++;
        color += 4;
    }
    i = 0;
    zero1 = 0;
    zero2 = 0;
    source = buffers.vertices + (self[1] - 2) * 6;
    destination = buffers.vertices + self[1] * 6;
    color = buffers.indices + (u16)self[1] * 4;
    copies = ((int)*(u16*)(config + 2) - self[1]) >> 1;
    while (i < copies) {
        memcpy(destination, source, 6);
        memcpy(destination + 6, source + 6, 6);
        color[3] = zero1;
        color[7] = zero2;
        i++;
        destination += 12;
        color += 8;
    }
    DCFlushRange(buffers.vertices, *(u16*)(config + 0xA));
    DCFlushRange(buffers.colors, *(u16*)(config + 0xE));
    DCFlushRange(buffers.indices, *(u16*)(config + 0xC));
    saved = fn_801ED57C(0);
    fn_8018D0D0(self, state, *(s16*)(self + 0xE));
    fn_801ED468(0x1B);
    fn_80225F4C(9, buffers.vertices, (u8)fn_8017FFB8());
    fn_80225F4C(13, buffers.colors, (u8)fn_8017FFB0());
    fn_80225F4C(11, buffers.indices, (u8)fn_8017FF98());
    fn_801ECEC8(1, 3, 1);
    fn_8022B448(lbl_80606AE0, lbl_8064D24C);
    fn_801ED57C(saved);
}
