typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;

typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;
typedef struct TextDescriptor TextDescriptor;
typedef struct RangeControl RangeControl;

extern unsigned int* lbl_8024E388[];
extern unsigned char lbl_802515D0[];
extern RangeControl* lbl_80331738[];
extern int lbl_8064B990;
extern u32 lbl_8064C2A8;
extern void* lbl_8064C508;
extern unsigned int lbl_8064CCF8;
extern int lbl_8064CD20;
extern unsigned int lbl_8064CD7C;
extern unsigned int lbl_8064CD80;
extern unsigned int lbl_8064CD84;
extern volatile int lbl_8064CDA4;
extern TextDescriptor* lbl_8064CDB0;
extern TextDescriptor* lbl_8064CDB4;
extern const u32 lbl_8064FF54;

extern void fn_801105D0(int active);
extern void fn_801111A8(int active);
extern void fn_801112C0(int active);
extern int fn_801118E8(void);
extern void fn_80119224(int mode, u8 alpha);
extern void fn_801A852C(u32* value, int index, u16 replacement, u32 word6);
extern void fn_801A8DE8(void* image, s32 x0, s32 y0, s32 x1, s32 y1,
                      s32 depth, s32 index, void* palette);
extern void fn_801A8EDC(void* image);
extern void fn_801A8F08(s32 x0, s32 y0, s32 x1, s32 y1,
                      s32 depth, s32 index, void* palette);
extern void fn_801B2380(int group);
extern TextDescriptor* fn_801E6CA0(void* resource, unsigned int group,
                                 unsigned int index, unsigned int flags,
                                 int compressed);
extern int fn_801E75A4(unsigned int value, int requested);
extern unsigned int fn_801E7A28(unsigned int** sets, int count);
extern int fn_801E8D34(RangeControl* control);
extern unsigned int fn_801ED3F4(unsigned int value);
extern Entry80201814* fn_80201814(int id);
extern int fn_80201B44(void);
extern unsigned int fn_8020216C(Object8020216C* object);
extern int fn_802365C0(void);

void fn_801113C4(u8 alpha)
{
    u32 backgroundColor;
    u32 iconColor;
    u32 imageColor;
    u32 frameColor;
    register int selectedIcon;
    register u16 icon;

    if (lbl_8064CD20 != 4) {
        fn_80119224(4, alpha);
    }
    fn_801ED3F4(lbl_8064CD80);
    if (fn_802365C0() == 0) {
        fn_801B2380(1);
    }

    switch (lbl_8064CD20) {
    case 2:
        fn_801105D0(1);
        fn_801112C0(0);
        break;
    case 1:
        fn_801111A8(1);
        fn_801112C0(0);
        break;
    case 0:
        switch (fn_801E8D34(lbl_80331738[0])) {
        case 0:
            if ((fn_8020216C((Object8020216C*)fn_80201814(fn_80201B44())) & 0x80000) ||
                (int)fn_801E7A28(lbl_8024E388, 3) != 0) {
                fn_801105D0(0);
            }
            break;
        case 1:
            if (lbl_8064CCF8 != 0) {
                fn_801111A8(0);
            }
            break;
        }
        fn_801112C0(1);
        if (lbl_8064B990 != 0) {
            if (lbl_8064CDB0 == 0) {
                if (fn_801118E8() != 0) {
                    lbl_8064CDB0 = fn_801E6CA0(lbl_8064C508, 1, 7, 0, 1);
                } else {
                    lbl_8064CDB0 = fn_801E6CA0(lbl_8064C508, 1, 5, 0, 1);
                }
            }
            if (lbl_8064CDB4 == 0) {
                lbl_8064CDB4 = fn_801E6CA0(lbl_8064C508, 1, 0, 0, 1);
            }
        }
        break;
    case 4:
        while (lbl_8064CDA4 == 0) {
        }
        fn_801ED3F4(lbl_8064CD84);
        fn_801A8EDC(lbl_802515D0);
        backgroundColor = lbl_8064C2A8;
        fn_801A852C(&backgroundColor, 0, 2, 0x80000000);
        iconColor = lbl_8064C2A8;
        selectedIcon = fn_801E75A4(lbl_8064CCF8, fn_801E8D34(lbl_80331738[1]));
        /* ASM: extsh preserves the retail sign-extended argument register.
         * A C conversion to the required u16 parameter adds a zero extension;
         * the callee consumes only the low 16 bits. */
        asm {
            extsh icon, selectedIcon
        }
        fn_801A852C(&iconColor, 0, icon, 0x80000000);
        fn_801A8F08(0x90, 0, 0x23F, 0x1DF, -1, 0, (void*)5);
        fn_801ED3F4(lbl_8064CD7C);
        imageColor = lbl_8064FF54;
        fn_801A852C(&imageColor, 5, 0, 0x80000000);
        fn_801A8DE8(lbl_802515D0, 0x90, 0, 0xC7, 0x1DF, -1, 0, (void*)5);
        frameColor = lbl_8064C2A8;
        fn_801A852C(&frameColor, 0, 3, 0x80000000);
        fn_801A8F08(0x90, 0xB7, 0xA5, 0x130, -1, 0, (void*)5);
        fn_80119224(4, alpha);
        break;
    }
}
