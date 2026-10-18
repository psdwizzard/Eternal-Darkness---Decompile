typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Matrix8009FD08 {
    u8 bytes[0x40];
} Matrix8009FD08;

extern void fn_801A8D38(int);
extern void C_MTXOrtho(Matrix8009FD08*, float, float, float, float, float, float);
extern void GXSetProjection(Matrix8009FD08*, int);
extern void fn_801A8660(short, short, short, short, int, u32*);
extern int lbl_8064C938;
extern int lbl_8064C93C;
extern int lbl_8064CBA4;
extern u32 lbl_8064EDE4;
extern u32 lbl_8064EDE8;
extern u32 lbl_8064EDEC;
extern u32 lbl_8064EDF0;
extern u32 lbl_8064EDF4;
extern float lbl_8064EDB0;
extern float lbl_8064EDB8;
extern float lbl_8064EDF8;
extern float lbl_8064EDFC;
extern float lbl_8064EE00;
extern float lbl_8064EE04;
extern float lbl_8064EE08;

void fn_8009FD08(void)
{
    Matrix8009FD08 first;
    Matrix8009FD08 second;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    u32 color4;

    fn_801A8D38(5);
    if (lbl_8064CBA4 == 1) {
        C_MTXOrtho(&first, lbl_8064EDB0, lbl_8064EDF8, lbl_8064EDB0,
                    lbl_8064EDFC, lbl_8064EDB8, lbl_8064EE00);
        GXSetProjection(&first, 1);
    }

    color0 = lbl_8064EDE4;
    fn_801A8660(0, 0, 640, (short)lbl_8064C93C, -1, &color0);

    color1 = lbl_8064EDE8;
    fn_801A8660(0, (short)(480 - lbl_8064C93C), 640,
                (short)lbl_8064C93C, -1, &color1);

    color2 = lbl_8064EDEC;
    fn_801A8660(0, (short)lbl_8064C93C, (short)lbl_8064C938,
                (short)(480 - 2 * lbl_8064C93C), -1, &color2);

    color3 = lbl_8064EDF0;
    fn_801A8660((short)(640 - lbl_8064C938), (short)lbl_8064C93C,
                (short)lbl_8064C938, (short)(480 - 2 * lbl_8064C93C),
                -1, &color3);

    color4 = lbl_8064EDF4;
    fn_801A8660((short)lbl_8064C938, (short)lbl_8064C93C,
                (short)(640 - 2 * lbl_8064C938),
                (short)(480 - 2 * lbl_8064C93C), -1, &color4);

    if (lbl_8064CBA4 == 1) {
        C_MTXOrtho(&second, lbl_8064EDB0, lbl_8064EDF8, lbl_8064EE04,
                    lbl_8064EE08, lbl_8064EDB8, lbl_8064EE00);
        GXSetProjection(&second, 1);
    }
}
