typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;

extern u32 lbl_8064D564;
extern s16 lbl_8064D574;
extern s16 lbl_8064D578;
extern u32 lbl_8064D57C;
extern u32 lbl_8064D580;
extern u32 lbl_8064D594;
extern void* lbl_806333C8[];
extern void* lbl_806333F0[];

extern void fn_801E4188(void);
extern void fn_801E418C(u32);
extern void fn_801E4198(s16, s16, s16);
extern void fn_801ED3F4(void*);
extern void fn_801A852C(u32*, u32, void*, u32);
extern void fn_801E7DCC(char*, ...);

/*
 * Speculative NonMatching reconstruction. The switch cases and diagnostic
 * text below are working hypotheses, not semantics verified against retail.
 */
char* fn_801E3B08(char* text)
{
    s8 command = *text;
    u32 value = 0;
    int digits = 0;

    switch (command) {
    case 'r':
    case 'n':
    case 'x':
        text++;
        while (*text >= '0' && *text <= '9' && digits < 3) {
            value = value * 10 + *text++ - '0';
            digits++;
        }
        if (command == 'r') {
            value = lbl_8064D564 + 26;
            text++;
        }
        if (value < 32) {
            u32 color = lbl_8064D594;
            fn_801ED3F4(lbl_806333C8[lbl_8064D580]);
            fn_801A852C(&color, 0, lbl_806333F0[lbl_8064D580], 0x80000000);
            fn_801E4198(lbl_8064D574, lbl_8064D578, -1);
            fn_801E418C((value << 2) + 3);
            fn_801E4188();
        }
        break;
    case 'c':
        lbl_8064D594 = *(u32*)(text + 1);
        text += 5;
        break;
    case 's':
        lbl_8064D57C = 1;
        text += 2;
        break;
    case '\\':
        text += 2;
        break;
    default:
        fn_801E7DCC("unknown control sequence %c", command);
        break;
    }
    return text;
}
