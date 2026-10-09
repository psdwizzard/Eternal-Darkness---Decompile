typedef void (*Callback800B16F4)(void);

extern char lbl_803206C0[];
extern char lbl_8032072C[];
extern Callback800B16F4 lbl_8064CA1C;
extern int lbl_8064CA20;
extern void* lbl_8064CA24;
extern void* lbl_8064CA28;
extern void* lbl_8064CA2C;
extern int lbl_8064CA34;
extern int lbl_8064CA38;
extern void* lbl_8064CA3C;
extern int lbl_8064CA40;
extern int lbl_8064CA44;
extern int lbl_8064CA48;
extern int lbl_8064CA60;
extern int lbl_8064CA64;
extern int lbl_8064CA6C;

extern void* memset(void*, int, unsigned long);

void fn_800B16F4(void) {
    lbl_8064CA48 = -1;
    lbl_8064CA6C = 0;
    lbl_8064CA44 = 0;
    lbl_8064CA40 = 0;
    lbl_8064CA3C = 0;
    lbl_8064CA38 = 0;
    lbl_8064CA34 = 0;
    memset(lbl_803206C0, 0, 0x6C);
    memset(lbl_8032072C, 0, 0xC);
    lbl_8064CA2C = 0;
    lbl_8064CA28 = 0;
    lbl_8064CA24 = 0;
    lbl_8064CA20 = 0;
    lbl_8064CA1C = 0;
    lbl_8064CA64 = 0;
    lbl_8064CA60 = 0;
}
