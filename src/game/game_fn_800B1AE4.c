typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Color {
    u32 value;
} Color;

typedef struct TextDescriptor TextDescriptor;

extern int lbl_8064CDC8;
extern int lbl_8064C538;
extern int lbl_8064CA34;
extern int lbl_8064CA3C;
extern void *lbl_8064C51C;
extern TextDescriptor *lbl_8064CA20;
extern Color lbl_8064C2B0;
extern const Color lbl_8064F014;
extern const Color lbl_8064F018;

extern int fn_800B6908(void);
extern int fn_800B1944(void);
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern void *fn_801E5D08(void *);
extern s16 fn_801E6420(TextDescriptor *);
extern s16 fn_801E6380(TextDescriptor *);
extern s16 fn_801E63F0(TextDescriptor *);
extern s16 fn_801E6350(TextDescriptor *);
extern void fn_801E6454(TextDescriptor *, s16);
extern void fn_800B7C80(int);
extern void fn_800B7DA0(int, int);
extern void fn_800B8660(int, int, int);
extern void fn_800B90B8(int, int, u8);
extern void fn_800B92AC(void);

/* Select the message and its prompt layout for the current menu state. */
void fn_800B1AE4(int message, int selection)
{
    u8 show_prompt;
    int special;

    special = lbl_8064CDC8 == 3;
    show_prompt = (fn_800B6908() == 0 || fn_800B1944() == 2) != 0;

    lbl_8064C538 = selection;
    switch (message) {
    case 1:
    case 2:
        switch (fn_800B1944()) {
        case 0:
        case 2:
            break;
        case 1:
            if (fn_800B6908() == 0) {
                u16 flags = 8;
                Color normal;
                const Color *color;

                if (!special) {
                    flags |= 0x2000;
                }
                lbl_8064CA20 = fn_801E6CA0(lbl_8064C51C, 0, 12, flags, 1);
                if (special) {
                    color = &lbl_8064C2B0;
                } else {
                    normal = lbl_8064F014;
                    color = &normal;
                }
                *(Color *)fn_801E5D08(lbl_8064CA20) = *color;
                fn_800B7C80(0);
                fn_800B7DA0(
                    (s16)(fn_801E6350(lbl_8064CA20) +
                          (fn_801E63F0(lbl_8064CA20) >> 1)),
                    (s16)(fn_801E6380(lbl_8064CA20) +
                          fn_801E6420(lbl_8064CA20) + 15));
                fn_801E6454(lbl_8064CA20, (s16)(fn_801E6420(lbl_8064CA20) + 70));
            }
            break;
        case 3:
            {
                u16 flags = 8;
                Color normal;
                const Color *color;

                if (!special) {
                    flags |= 0x2000;
                }
                lbl_8064CA20 = fn_801E6CA0(lbl_8064C51C, 0, 100, flags, 1);
                if (special) {
                    color = &lbl_8064C2B0;
                } else {
                    normal = lbl_8064F018;
                    color = &normal;
                }
                *(Color *)fn_801E5D08(lbl_8064CA20) = *color;
                fn_800B7C80(0);
                fn_800B7DA0(
                    (s16)(fn_801E6350(lbl_8064CA20) +
                          (fn_801E63F0(lbl_8064CA20) >> 1)),
                    (s16)(fn_801E6380(lbl_8064CA20) +
                          fn_801E6420(lbl_8064CA20) + 15));
                fn_801E6454(lbl_8064CA20, (s16)(fn_801E6420(lbl_8064CA20) + 70));
            }
            break;
        }
        break;
    case 4:
        fn_800B8660(0, 0, 4);
        break;
    case 5:
        fn_800B8660(0, 1, 4);
        break;
    case 6:
        if (lbl_8064CDC8 != 3 || lbl_8064CA34 != 0) {
            fn_800B8660(0, 2, 0);
        } else {
            fn_800B8660(0, 3, 0);
        }
        break;
    case 8:
        fn_800B8660(0, 4, 5);
        break;
    case 9:
        fn_800B8660(0, 19, 5);
        break;
    case 10:
        fn_800B8660(0, 90, 1);
        break;
    case 11:
        fn_800B8660(0, 11, 4);
        break;
    case 12:
        fn_800B8660(0, 95, 4);
        break;
    case 13:
        fn_800B8660(0, 20, 3);
        break;
    case 14:
        fn_800B8660(0, 21, 1);
        break;
    case 26:
        fn_800B8660(0, 51, 1);
        break;
    case 27:
        fn_800B8660(0, 52, 1);
        break;
    case 28:
        fn_800B8660(0, 79, 1);
        break;
    case 29:
        fn_800B8660(0, 78, 1);
        break;
    case 30:
        fn_800B8660(0, 84, 2);
        break;
    case 31:
        fn_800B8660(0, 85, 2);
        break;
    case 32:
        fn_800B8660(0, 102, 3);
        break;
    case 33:
        fn_800B8660(0, 101, 3);
        break;
    case 15:
        fn_800B8660(0, 50, 1);
        break;
    case 16:
        fn_800B8660(0, 72, 5);
        break;
    case 17:
        fn_800B8660(0, 73, 1);
        break;
    case 18:
        fn_800B8660(0, 74, 1);
        break;
    case 19:
        fn_800B8660(0, 79, 1);
        break;
    case 20:
        fn_800B8660(0, 78, 1);
        break;
    case 21:
        fn_800B8660(0, 80, 1);
        break;
    case 22:
        fn_800B8660(0, 81, 1);
        break;
    case 23:
        fn_800B8660(0, 89, 1);
        break;
    case 24:
        fn_800B8660(0, 82, 1);
        break;
    case 25:
        fn_800B8660(0, 83, 1);
        break;
    case 34:
        fn_800B8660(0, 86, 0);
        break;
    case 35:
        fn_800B8660(0, 92, 0);
        break;
    case 36:
        fn_800B8660(0, 93, 1);
        break;
    case 37:
        fn_800B8660(0, 94, 1);
        break;
    case 39:
        fn_800B8660(0, 99, 2);
        break;
    case 38:
        fn_800B8660(0, 98, 2);
        break;
    case 40:
        fn_800B8660(0, 6, 3);
        break;
    case 41:
        fn_800B8660(0, 75, 3);
        break;
    case 42:
        fn_800B8660(0, 76, 3);
        break;
    case 43:
        fn_800B8660(0, 77, 3);
        break;
    case 81:
        fn_800B8660(0, 59, 3);
        break;
    case 82:
        fn_800B8660(0, 60, 3);
        break;
    case 83:
        fn_800B8660(0, 62, 3);
        break;
    case 84:
        fn_800B8660(0, 61, 3);
        break;
    case 85:
        fn_800B8660(0, 63, 3);
        break;
    case 86:
        fn_800B8660(0, 103, 1);
        break;
    case 87:
        fn_800B8660(0, 104, 1);
        break;
    case 88:
        fn_800B8660(0, 105, 1);
        break;
    case 96:
        fn_800B90B8(0, 91, 0);
        break;
    case 46:
        fn_800B90B8(0, 68, show_prompt);
        break;
    case 47:
        fn_800B90B8(0, 69, show_prompt);
        break;
    case 48:
        fn_800B90B8(0, 70, show_prompt);
        break;
    case 49:
        fn_800B90B8(0, 71, show_prompt);
        break;
    case 44:
        fn_800B90B8(0, 38, show_prompt);
        break;
    case 45:
        fn_800B90B8(0, 37, show_prompt);
        break;
    case 50:
        fn_800B90B8(0, 24, show_prompt);
        break;
    case 51:
        fn_800B90B8(0, 25, show_prompt);
        break;
    case 52:
        fn_800B90B8(0, 26, show_prompt);
        break;
    case 53:
        fn_800B90B8(0, 27, show_prompt);
        break;
    case 54:
        fn_800B90B8(0, 28, show_prompt);
        break;
    case 55:
        fn_800B90B8(0, 29, show_prompt);
        break;
    case 56:
        fn_800B90B8(0, 30, show_prompt);
        break;
    case 57:
        fn_800B90B8(0, 31, show_prompt);
        break;
    case 62:
        fn_800B90B8(0, 32, show_prompt);
        break;
    case 63:
        fn_800B90B8(0, 33, show_prompt);
        break;
    case 64:
        fn_800B90B8(0, 34, show_prompt);
        break;
    case 65:
        fn_800B90B8(0, 35, show_prompt);
        break;
    case 66:
        fn_800B90B8(0, 36, show_prompt);
        break;
    case 89:
        fn_800B90B8(0, 13, show_prompt);
        break;
    case 91:
        fn_800B90B8(0, 7, show_prompt);
        break;
    case 92:
        fn_800B90B8(0, 87, show_prompt);
        break;
    case 93:
        fn_800B90B8(0, 88, show_prompt);
        break;
    case 58:
        fn_800B90B8(0, 55, show_prompt);
        break;
    case 59:
        fn_800B90B8(0, 56, show_prompt);
        break;
    case 60:
        fn_800B90B8(0, 58, show_prompt);
        break;
    case 61:
        fn_800B90B8(0, 57, show_prompt);
        break;
    case 67:
        fn_800B90B8(0, 39, show_prompt);
        break;
    case 68:
        fn_800B90B8(0, 40, show_prompt);
        break;
    case 69:
        fn_800B90B8(0, 41, show_prompt);
        break;
    case 70:
        fn_800B90B8(0, 42, show_prompt);
        break;
    case 71:
        fn_800B90B8(0, 43, show_prompt);
        break;
    case 72:
        fn_800B90B8(0, 45, show_prompt);
        break;
    case 73:
        fn_800B90B8(0, 46, show_prompt);
        break;
    case 74:
        fn_800B90B8(0, 47, show_prompt);
        break;
    case 75:
        fn_800B90B8(0, 48, show_prompt);
        break;
    case 76:
        fn_800B90B8(0, 49, show_prompt);
        break;
    case 77:
        fn_800B90B8(0, 66, show_prompt);
        break;
    case 78:
        fn_800B90B8(0, 67, show_prompt);
        break;
    case 79:
        fn_800B90B8(0, 64, show_prompt);
        break;
    case 80:
        fn_800B90B8(0, 65, show_prompt);
        break;
    case 95:
        fn_800B90B8(0, 14, show_prompt);
        break;
    case 97:
        fn_800B90B8(0, 44, show_prompt);
        break;
    case 98:
        if (lbl_8064CA3C == 0) {
            fn_800B92AC();
        }
        break;
    }
}
