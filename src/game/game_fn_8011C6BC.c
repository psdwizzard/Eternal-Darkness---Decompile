extern unsigned char lbl_8064CE50;
extern unsigned char lbl_8064CE51;
extern unsigned char lbl_8064CE52;
extern unsigned char lbl_8064CE53;
extern unsigned char lbl_8064CE54;
extern unsigned char lbl_8064CE55;
extern int lbl_8064CE48;
extern int lbl_8064CE4C;
extern int lbl_8064CE58;
extern int lbl_8064CE5C;
extern int lbl_8064CE60;
extern int lbl_8064CE64;
extern int lbl_8064CE68;
extern int lbl_8064C504;

extern int fn_801A98F4(int, int);
extern unsigned char fn_801A9B30(void);
extern int fn_801E6CA0(int, int, int, int, int);
extern void fn_801E6328(int, short, int);
extern int fn_801E8A8C(void);
extern void fn_801E8AEC(int, int, int, int);
extern void fn_801E8B24(int, int, int);

void fn_8011C6BC(int x, int value, unsigned char mode)
{
    unsigned char random;

    lbl_8064CE58 = 0;
    lbl_8064CE54 = 255;
    lbl_8064CE53 = 255;
    lbl_8064CE60 = x;
    lbl_8064CE5C = value;
    random = fn_801A9B30();
    lbl_8064CE55 = random;
    lbl_8064CE64 = random;
    lbl_8064CE52 = 0;
    lbl_8064CE51 = 2;
    lbl_8064CE50 = mode;
    lbl_8064CE4C = 0;
    lbl_8064CE48 = fn_801E6CA0(lbl_8064C504, 0, 52, 0, 1);
    fn_801E6328(lbl_8064CE48, (short)(x + 225), 350);
    lbl_8064CE68 = fn_801E8A8C();
    fn_801E8AEC(lbl_8064CE68, 0, 128, 128);
    fn_801E8B24(lbl_8064CE68, lbl_8064CE64, 0);
    lbl_8064CE4C = fn_801A98F4(688, 100);
}
