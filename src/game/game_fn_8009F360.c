typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Global8009F360 {
    u8 pad00[8];
    u8* owner;
} Global8009F360;

extern Global8009F360 lbl_80606328;
extern void* lbl_8064D224;
extern char lbl_802515D0[];
extern u32 lbl_8064EDDC;
extern u32 lbl_8064EDE0;

extern void fn_801A8D38(int);
extern void fn_801A8660(int, int, int, int, int, const u32*);
extern void fn_801ED3F4(void*);
extern void GXSetArray(int, void*, int);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801A8F08(s16, s16, s16, s16, int, int, int);

void fn_8009F360(void)
{
    u32 color;
    u8* owner;
    u32 config;

    fn_801A8D38(5);
    color = lbl_8064EDDC;
    fn_801A8660(0, 215, 640, 50, -1, &color);
    fn_801ED3F4(lbl_8064D224);
    GXSetArray(13, lbl_802515D0, 4);
    *(u32*)(lbl_80606328.owner + 0x58) = 0x80000000;
    owner = *(u8* volatile*)((u8*)&lbl_80606328 + 8);
    config = lbl_8064EDE0;
    *(u32*)(owner + 0x5C) = config;
    fn_801EDA7C(lbl_80606328.owner + 0x40, 0, 0x2BF, 0);
    fn_801A8F08(60, 220, 580, 260, -1, 0, 5);
}
