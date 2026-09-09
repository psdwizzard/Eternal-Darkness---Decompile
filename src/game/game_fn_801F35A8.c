typedef unsigned char u8;
typedef unsigned long u32;
typedef signed long s32;

typedef struct ColorF {
    float red, green, blue, alpha;
} ColorF;

extern u8 lbl_8064D704[4];
extern ColorF lbl_8063C608;
extern s32 lbl_8064D770;
extern float lbl_80651348, lbl_80651368;

extern void fn_802119B0();
extern void fn_8022B4B8();
extern void fn_80210FB0();
extern void fn_8022B690();
extern void fn_801ED468();
extern void fn_80226D28();
extern void fn_80228020();
extern void fn_802262B8();
extern void fn_8022A2F4();
extern void fn_801F3938();
extern void fn_8022A118();
extern void fn_80229D8C();
extern void fn_80229E74();
extern void fn_80229C0C();
extern void fn_80229B08();
extern void fn_80229CCC();
extern void fn_80229B88();
extern void fn_8015DB84();
extern void fn_80228AFC();
extern void fn_801ECF50();
extern void fn_80226AB4();
extern void fn_801F3924();
extern void fn_801F3914();
extern void fn_801F0AFC();
extern void fn_801ECC4C();
extern void fn_801A8D38();

void fn_801F35A8(void)
{
    float projection[16];
    float matrix[12];
    u8 color[4];

    if (lbl_8064D770 != 0) {
        float divisor = (float)lbl_8064D770;
        lbl_8063C608.red += ((float)lbl_8064D704[0] - lbl_8063C608.red) / divisor;
        lbl_8063C608.green += ((float)lbl_8064D704[1] - lbl_8063C608.green) / divisor;
        lbl_8063C608.blue += ((float)lbl_8064D704[2] - lbl_8063C608.blue) / divisor;
        lbl_8063C608.alpha += ((float)lbl_8064D704[3] - lbl_8063C608.alpha) / divisor;
        --lbl_8064D770;
    }

    if (lbl_8063C608.alpha > lbl_80651348) {
        color[0] = (u8)lbl_8063C608.red;
        color[1] = (u8)lbl_8063C608.green;
        color[2] = (u8)lbl_8063C608.blue;
        color[3] = (u8)lbl_8063C608.alpha;
        fn_802119B0(projection, lbl_80651348, lbl_80651348,
                    lbl_80651348, lbl_80651348, lbl_80651348, lbl_80651348);
        fn_8022B4B8(projection, 1);
        fn_80210FB0(matrix);
        fn_8022B690(matrix, 0);
        fn_801ED468(0);
        fn_80226D28(0);
        fn_80228020(1);
        fn_802262B8(1);
        fn_8022A2F4(1);
        fn_80226D28(0);
        fn_801F3938(0, 1, 4, 60);
        fn_8022A118(0, 0, 0, 255);
        fn_80229D8C(1, color);
        fn_80229E74(0, 13);
        fn_80229C0C(0, 0, 0, 0, 1, 0);
        fn_80229B08(0, 15, 2, 8, 14);
        fn_80229CCC(0, 0, 0, 0, 1, 0);
        fn_80229B88(0, 7, 7, 7, 1);
        fn_8015DB84((void*)0x802FC2C0, color, 0);
        fn_80228AFC(color, 0);
        fn_801ECF50(8);
        fn_80226AB4(128, 2, 4);
        fn_801F3924(0, 0, 0);
        fn_801F3914(lbl_80651348, lbl_80651348);
        fn_801F3924(0x5000, 0, 0);
        fn_801F3914(lbl_80651368, lbl_80651348);
        fn_801F3924(0x5000, 0x3C00, 0);
        fn_801F3914(lbl_80651368, lbl_80651368);
        fn_801F3924(0, 0x3C00, 0);
        fn_801F3914(lbl_80651348, lbl_80651368);
        fn_801F0AFC();
        fn_80226D28(1);
        fn_801ECC4C();
        fn_801A8D38(5);
    }
}
