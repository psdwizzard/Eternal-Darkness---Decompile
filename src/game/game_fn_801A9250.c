typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Color801A9250 {
    u32 value;
} Color801A9250;

extern volatile Color801A9250 lbl_80650E28;
extern u8 lbl_802515D0[];
extern u8 lbl_802515E0[];

extern void fn_801A852C(Color801A9250*, int, u32, u32);
extern void fn_801A8FE8(void*, void*, int, int, int);

void fn_801A9250(u32 value, u8 alpha, u32 index)
{
    Color801A9250 argument;
    Color801A9250 color = lbl_80650E28;

    ((u8*)&color)[3] = alpha;
    argument = color;
    fn_801A852C(&argument, 0, value, 0x80000000);
    fn_801A8FE8(lbl_802515D0, lbl_802515E0 + (index + 2) * 24, 0, 0, 5);
}
