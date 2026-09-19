extern void* lbl_8064C504;
extern int lbl_80331A08[];

typedef signed short s16;
typedef struct TextDescriptor TextDescriptor;

extern double fn_8016A694(void*, int);
extern unsigned int fn_800F5C54(double);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern int fn_801E8D24(int);
extern s16 fn_801E63F0(TextDescriptor*);
extern int fn_801E6350(void*);
extern void fn_801E6328(void*, short, int);
extern void fn_80027730(void*, int, int);

#pragma opt_lifetimes off
int fn_80112754(void* object)
{
    int mode;
    TextDescriptor* item;

    mode = fn_801E8D24(lbl_80331A08[5]);
    item = fn_801E6CA0(lbl_8064C504,
                      fn_800F5C54(fn_8016A694(object, 1)),
                      fn_800F5C54(fn_8016A694(object, 2)), 0, 1);

    switch (mode) {
    case 0:
        fn_801E6328(item,
                    (short)(fn_801E6350(item) + (fn_801E63F0(item) >> 1)),
                    0x118);
        break;
    case 1:
        fn_801E6328(item,
                    (short)(fn_801E6350(item) + (fn_801E63F0(item) >> 1)),
                    0x64);
        break;
    default:
        fn_801E6328(item,
                    (short)(fn_801E6350(item) + (fn_801E63F0(item) >> 1)),
                    0xB4);
        break;
    }

    fn_80027730(item, (int)fn_8016A694(object, 3), 0);
    return 0;
}
#pragma opt_lifetimes reset
