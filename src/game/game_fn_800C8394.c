typedef unsigned char u8;
typedef unsigned int u32;

typedef union Color {
    u32 value;
    u8 channel[4];
} Color;

extern unsigned short fn_8012DBE8(void *, int, Color *);
extern void* fn_8012C62C(void *, int, Color *, Color *, Color *, int);
extern u32 lbl_80651A68;
extern u32 lbl_80651A6C;

void fn_800C8394(void *object, u8 alpha)
{
    Color source;
    Color third;
    Color second_copy;
    Color second;
    Color first_copy;
    Color first;

    fn_8012DBE8(object, 0xF, &source);
    first.value = lbl_80651A6C;
    second.value = lbl_80651A68;
    first.channel[0] = source.channel[0];
    first.channel[1] = source.channel[1];
    first.channel[2] = source.channel[2];
    second.channel[3] = alpha;
    first_copy = first;
    second_copy = second;
    third = source;
    fn_8012C62C(object, 0xF, &third, &second_copy, &first_copy, 6);
}
