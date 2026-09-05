typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Color801A91D4 {
    u32 value;
} Color801A91D4;

extern volatile Color801A91D4 lbl_80650E24;
extern u8 lbl_802515D0[];
extern u8 lbl_802515E0[];

extern void fn_801A852C(Color801A91D4*, int, u32, u32);
extern void fn_801A8FE8(void*, void*, int, int, int);

void fn_801A91D4(u32 value, u8 alpha, u32 index)
{
    Color801A91D4 argument;
    Color801A91D4 color = lbl_80650E24;

    ((u8*)&color)[3] = alpha;
    argument = color;
    fn_801A852C(&argument, 0, value, 0x80000000);
    fn_801A8FE8(lbl_802515D0, lbl_802515E0 + index * 24, 0, 0, 5);
}
