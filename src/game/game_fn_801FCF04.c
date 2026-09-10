typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Block48 { u32 word[12]; } Block48;
typedef struct Block52 { u32 word[13]; } Block52;
typedef struct Block64 { u32 word[16]; } Block64;

extern u32 lbl_8064D7C4;
extern u8 lbl_802FC808[];
extern const float lbl_80651520;
extern const float lbl_80651524;
extern const float lbl_80651528;
extern const float lbl_8065152C;
extern const float lbl_80651530;
extern const float lbl_80651534;
extern const float lbl_80651538;

extern int fn_801EF384(void);
extern int fn_801ED57C(int);
extern void fn_801ECEC8(int, int, int);
extern void fn_8022A5D8(int, int, int, int);
extern void fn_802119B0(void*, float, float, float, float, float, float);
extern void fn_8022B4B8(void*, int);
extern void fn_80210FB0(void*);
extern void fn_80211484(void*, float, float, float);
extern void fn_8022B690(void*, int);
extern void fn_801ED468(int);
extern void fn_80226D28(int);
extern void fn_8022A6DC(int);
extern void fn_801ECC4C(void);
extern void fn_801ECF50(int);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801ECD74(void*);
extern void fn_80226AB4(int, int, int);
extern void fn_801FD22C(int, int, int);
extern void fn_801FD21C(float, float);
extern void fn_801FD218(void);
extern void fn_801F683C(Block52*);
extern void fn_801F03F0(Block52*, int);

void fn_801FCF04(void)
{
    u32 marker;
    u32 argument;
    int mode;
    int old;
    Block64 a;
    Block48 b;
    Block52 copy;
    Block52 source;

    marker = lbl_8064D7C4;
    mode = fn_801EF384();
    old = fn_801ED57C(0);
    ((u8*)&marker)[3] = 0x69;
    if (mode != 0) ((u8*)&marker)[1] = 0xff;
    fn_801ECEC8(0, 3, 0);
    fn_8022A5D8(1, 4, 5, 0);
    fn_802119B0(&a, lbl_80651520, lbl_80651528, lbl_80651520,
               lbl_8065152C, lbl_80651520, lbl_80651530);
    fn_8022B4B8(&a, 1);
    fn_80210FB0(&b);
    fn_80211484(&b, lbl_80651534, lbl_80651538, lbl_80651520);
    fn_8022B690(&b, 0);
    fn_801ED468(0);
    fn_80226D28(0);
    fn_8022A6DC(1);
    fn_801ECC4C();
    fn_801ECF50(8);
    fn_80226D28(0);
    fn_8022A5D8(1, 7, 6, 0);
    fn_801EDA7C(lbl_802FC808, 0, 0xabf, 0);
    argument = marker;
    fn_801ECD74(&argument);

    if (mode == 0) {
        fn_80226AB4(0x80, 2, 4);
        fn_801FD22C(-0x2800, -0x1e00, 0);
        fn_801FD21C(lbl_80651520, lbl_80651520);
        fn_801FD22C(0x2800, -0x1e00, 0);
        fn_801FD21C(lbl_80651524, lbl_80651520);
        fn_801FD22C(0x2800, 0x1e00, 0);
        fn_801FD21C(lbl_80651524, lbl_80651524);
        fn_801FD22C(-0x2800, 0x1e00, 0);
        fn_801FD21C(lbl_80651520, lbl_80651524);
        fn_801FD218();
    } else {
        fn_80226AB4(0x80, 2, 4);
        fn_801FD22C(-0x2800, -0x1e00, 0);
        fn_801FD21C(lbl_80651520, lbl_80651520);
        fn_801FD22C(0x2800, -0x1e00, 0);
        fn_801FD21C(lbl_80651524, lbl_80651520);
        fn_801FD22C(0x2800, 0x1e00, 0);
        fn_801FD21C(lbl_80651524, lbl_80651524);
        fn_801FD22C(-0x2800, 0x1e00, 0);
        fn_801FD21C(lbl_80651520, lbl_80651524);
        fn_801FD218();
    }
    fn_80226D28(1);
    fn_801ED57C(old);
    fn_8022A5D8(1, 4, 5, 0);
    fn_801F683C(&source);
    copy = source;
    fn_801F03F0(&copy, 0);
    fn_801ECEC8(1, 3, 1);
}
