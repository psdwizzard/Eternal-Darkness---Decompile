typedef signed short s16;
typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;

typedef union Color {
    struct { u8 r, g, b, a; } channels;
    u32 value;
} Color;

typedef struct TextDescriptor {
    float scale;
    u32 color;
    s16 x, y, width, height;
    u32 flags;
} TextDescriptor;

extern TextDescriptor *lbl_8064CA10[2];
extern int lbl_8064CDC8;
extern Color lbl_802FC5BC[];
extern u32 lbl_8064C2BC;
extern u32 lbl_8064C2C4;
extern const u32 lbl_8064F078;
extern float lbl_8064F070;
extern float lbl_8064F01C;

extern int fn_800B7EC0(void);
extern int fn_800AF7E4(int, int *);
extern s16 fn_801E6350(TextDescriptor *);
extern s16 fn_801E6380(TextDescriptor *);
extern s16 fn_801E63F0(TextDescriptor *);
extern s16 fn_801E6420(TextDescriptor *);
extern void *fn_801E5D08(void *);
extern void fn_801A872C(s32, s32, s32, s32, s32, s32, const u32 *);
extern void fn_801A8974(s32, s32, s32, s32, s32, s32);
extern void fn_801ED5F4(int, int, s16, float *, float (*)[4], float);

void fn_800B7EF4(u8 selected, u8 alpha)
{
    int status;
    Color normal;
    Color unavailable;
    int special;
    register int x;
    register s16 returnedX;
    s16 y, width;
    register int height;
    register s16 returnedHeight;
    register int i;
    int result;
    u32 normalValue, unavailableValue;
    register Color *colors;

    special = lbl_8064CDC8 == 3;
    returnedX = fn_801E6350(lbl_8064CA10[fn_800B7EC0()]);
    /* ASM: mr preserves the already sign-extended coordinate returned in r3;
     * MWCC otherwise adds a redundant extsh when promoting the s16 result. */
    asm { mr x, returnedX }
    y = fn_801E6380(lbl_8064CA10[fn_800B7EC0()]) + 3;
    width = fn_801E63F0(lbl_8064CA10[fn_800B7EC0()]) + 5;
    returnedHeight = fn_801E6420(lbl_8064CA10[fn_800B7EC0()]);
    /* ASM: lis begins the color table address before the height move;
     * MWCC cannot schedule its generated address setup across inline asm. */
    asm { lis r4, lbl_802FC5BC@ha }
    i = 0;
    /* ASM: addi, mr finish the table address and preserve the height return;
     * MWCC otherwise inserts a redundant extsh when promoting the s16. */
    asm {
        addi colors, r4, lbl_802FC5BC@l
        mr height, returnedHeight
    }
    normal.value = colors[2].value;
    unavailable.value = colors[3].value;
    normal.channels.a = alpha;
    unavailable.channels.a = alpha;
    normalValue = normal.value;
    unavailableValue = unavailable.value;
    for (; i < 2; i++) {
        result = fn_800AF7E4(i, &status);
        if (result == 1 || (result != 1 && status != -3 && status != -2)) {
            *(u32 *)fn_801E5D08(lbl_8064CA10[i]) = unavailableValue;
        } else {
            *(u32 *)fn_801E5D08(lbl_8064CA10[i]) = normalValue;
        }
    }
    if (alpha == 255) {
        if (selected) {
            if (special) {
                u32 color = lbl_8064C2BC;
                fn_801A872C(x, y, width, height, -1, 3, &color);
            } else {
                u32 color = lbl_8064F078;
                fn_801A872C(x, y, width, height, -1, 3, &color);
            }
        } else if (special) {
            fn_801A8974(x, y, width, height, -1, 3);
        } else {
            u32 color;
            fn_801ED5F4(1, 0x482, 1, 0, 0, lbl_8064F070);
            color = lbl_8064C2C4;
            fn_801A872C(x, y, width, height, -1, 3, &color);
            fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
        }
    }
}
