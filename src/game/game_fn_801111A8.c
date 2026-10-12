typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;
typedef struct RangeControl RangeControl;
typedef union Color {
    u32 value;
    struct { u8 r, g, b, a; } channel;
} Color;

typedef struct MenuData {
    u8 image[0x3D0];
    u8 mask[0x134];
    u8 chapterData[0xA10];
    const char* labels[14];
} MenuData;

extern MenuData lbl_8024B6B0;
extern RangeControl* lbl_80331738[];
extern u32 lbl_8064C2A8;
extern u32 lbl_8064CCF8;
extern u32 lbl_8064CD80;
extern const float lbl_8064FF3C;
extern const Color lbl_8064FF48;
extern const Color lbl_8064FF4C;

extern int fn_801E8D34(RangeControl* control);
extern u32 fn_801ED3F4(u32 value);
extern void fn_801A8D38(s32 mode);
extern void fn_801A90BC(void* image, void* mask);
extern void fn_801A852C(u32* value, int index, u16 replacement, u32 word6);
extern void fn_801A9118(s32 index, s32 coordinate, void* palette);
extern void fn_801E3AA4(int index);
extern void fn_801E5430(short x, short y);
extern u32 fn_801E3A34(Color* color);
extern void fn_801E56AC(float scale, const char* format, ...);

void fn_801111A8(int active)
{
    u32 imageColor;
    Color selectedColor;
    Color normalColor;
    register u8* __restrict data;
    register int i;
    register int visibleIndex;
    register int selected;

    {
        register RangeControl* control;
        data = (u8*)&lbl_8024B6B0;
        visibleIndex = 0;
        /* ASM: lis, addi and lwz retain the range-control address in r4.
         * MWCC folds the C array access into r3 and reschedules its load,
         * changing the retail address and initialization sequence. */
        asm {
            lis r4, lbl_80331738@ha
            addi r4, r4, lbl_80331738@l
            lwz control, 4(r4)
        }
        selected = fn_801E8D34(control);
    }

    fn_801ED3F4(lbl_8064CD80);
    fn_801A8D38(6);
    {
        register void* image;
        register void* mask;
        /* ASM: addi preserves the zero-offset image address calculation.
         * MWCC folds the C expression into mr and propagates the base
         * address separately for the mask. */
        asm {
            addi image, data, 0
            addi mask, data, 0x3D0
        }
        fn_801A90BC(image, mask);
    }
    imageColor = lbl_8064C2A8;
    fn_801A852C(&imageColor, 0, 0x31, 0x80000000);
    fn_801A9118(0, 20, (void*)5);
    fn_801E3AA4(1);
    fn_801E5430(300, 130);
    data += 0xF14;
    for (i = 0; i < 14; i++, data += sizeof(const char*)) {
        if (lbl_8064CCF8 & (1 << i)) {
            if (active && visibleIndex == selected) {
                selectedColor = lbl_8064FF48;
                fn_801E3A34(&selectedColor);
            } else {
                normalColor = lbl_8064FF4C;
                fn_801E3A34(&normalColor);
            }
            fn_801E56AC(lbl_8064FF3C, *(const char**)data);
            visibleIndex++;
        }
    }
}
