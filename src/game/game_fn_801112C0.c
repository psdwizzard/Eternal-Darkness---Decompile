typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RangeControl RangeControl;
typedef struct Entry80201814 Entry80201814;
typedef union Color {
    u32 value;
    struct { u8 r, g, b, a; } channel;
} Color;

extern RangeControl* lbl_80331738[];
extern u8 lbl_8024B6B0[];
extern u8 lbl_8024BA80[];
extern u32 lbl_8064CD80;
extern u32 lbl_8064CCF8;
extern u32 lbl_8064C2A8;
extern const Color lbl_8064FF50;

extern int fn_801E8D34(RangeControl* control);
extern u32 fn_801ED3F4(u32 value);
extern void fn_801A8D38(int mode);
extern void fn_801A90BC(void* image, void* mask);
extern u32 fn_801E7578(u32 value);
extern int fn_80201B44(void);
extern Entry80201814* fn_80201814(int id);
extern u32 fn_8020216C(Entry80201814* object);
extern void fn_801A852C(u32* value, int index, int replacement, int word6);
extern void fn_801A9118(int index, int coordinate, int palette);

void fn_801112C0(int active)
{
    u32 backgroundColor;
    u32 imageColor;
    Color color;
    int count;
    int selected = fn_801E8D34(lbl_80331738[0]);

    fn_801ED3F4(lbl_8064CD80);
    fn_801A8D38(6);
    fn_801A90BC(lbl_8024B6B0, lbl_8024BA80);
    count = fn_801E7578(lbl_8064CCF8);
    if (count != 0 ||
        (fn_8020216C(fn_80201814(fn_80201B44())) & 0x8000) != 0) {
        backgroundColor = lbl_8064C2A8;
        fn_801A852C(&backgroundColor, 0, 60, 0x80000000);
        fn_801A9118(0, 16, 5);
    }
    color = lbl_8064FF50;
    color.channel.a = active ? 255 : 100;
    imageColor = color.value;
    fn_801A852C(&imageColor, 5, selected + 47, 0x80000000);
    fn_801A9118(0, ((u16)(selected + 3) & 0x3FFF) * 4, 5);
}
