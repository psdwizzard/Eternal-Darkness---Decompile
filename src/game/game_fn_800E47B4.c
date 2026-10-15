typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern unsigned int fn_800E4834(void);
extern void fn_800E4840(void);
extern void fn_800E48AC(void);
extern unsigned char lbl_8064D5F8;
extern unsigned char lbl_8064CADD;
extern unsigned char lbl_8064CADC;
extern unsigned short lbl_8064CAEA;
extern unsigned short lbl_8064CAF4;
extern unsigned short lbl_8064CAF2;
extern unsigned short lbl_8064CAF0;
extern unsigned short lbl_8064CAEE;
extern unsigned short lbl_8064CAE8;
extern int lbl_8064CAE0;
extern int lbl_8064CAD8;
extern Vec3 lbl_80325CE0;
extern float lbl_8064F6B0;

void fn_800E47B4(void)
{
    int active = fn_800E4834();

    if (active != 0) {
        fn_800E48AC();
    } else {
        fn_800E4840();
    }

    lbl_8064D5F8 = 0;
    lbl_8064CADD = 0;
    lbl_8064CAEA = 170;
    lbl_8064CAF4 = 0;
    lbl_8064CAF2 = 0;
    lbl_8064CAF0 = 0;
    lbl_8064CAEE = 0;
    lbl_8064CAE0 = 0;
    lbl_8064CADC = 0;
    lbl_8064CAE8 = 12;
    lbl_80325CE0.x = lbl_8064F6B0;
    lbl_80325CE0.y = lbl_8064F6B0;
    lbl_80325CE0.z = lbl_8064F6B0;
    lbl_8064CAD8 = 0;
}
