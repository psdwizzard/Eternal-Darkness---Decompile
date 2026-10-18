typedef unsigned char u8;
typedef unsigned int u32;

typedef struct LoadState {
    u8 reserved[0x10];
    u32 flags;
    void *text;
} LoadState;

typedef struct GameState {
    u8 reserved[0x1DA];
    u8 chapter;
} GameState;

extern void fn_8001D9FC(int);
extern void fn_80045A24(u32, u32);
extern int fn_800462C8(u32);
extern void fn_80046B68(void);
extern void fn_80047494(u32);
extern void *fn_80047AFC(int);
extern void *fn_80047B98(int);
extern void fn_80047DF8(void *, void *, int);
extern void fn_80047F5C(void *, void *, int);
extern void fn_80052580(int, u8, u8, unsigned short, u32);
extern void fn_800E7950(int);
extern void fn_80118670(void);
extern int fn_801358B4(int);
extern void fn_80144C40(void);
extern int fn_80155D9C(int);
extern void fn_801593AC(int);
extern void fn_80159440(int, int);
extern void *fn_8015C28C(int);
extern void fn_8015C880(void);
extern void fn_80180BE4(void);
extern int fn_801A98F4(int, int);
extern void fn_801A9964(u32);
extern void fn_801A9DCC(int, u8, int);
extern void fn_801AB154(void *);
extern void fn_801ACC94(int);
extern void fn_801E5FB0(void *);
extern void fn_801E79A0(void *, u32);
extern int fn_801E79FC(void *, u32);
extern void fn_801E81C0(int);
extern void fn_801E8328(int, void *);
extern int fn_801E855C(int, void *, void *);
extern void fn_801EA9F8(void);
extern void fn_801EF35C(int);
extern int fn_801F85A4(void);
extern void fn_801FA354(void);
/* Event dispatch passes time in f1 and its integer fields in r3-r6.
 * The float-first order is also used by fn_80006D50 and fn_800B002C. */
extern void fn_80200EAC(float, int, int, int, int);
extern int fn_80201AE4(void);

extern u8 lbl_80303CA0[];
extern u32 lbl_80303D18[];
extern GameState lbl_8030F540;
extern LoadState lbl_80332140;
extern u32 lbl_8064B998;
extern void *lbl_8064C4E0;
extern int lbl_8064C4F4;
extern void (*lbl_8064CD88)(void);
extern volatile int lbl_8064CDA0;
extern volatile int lbl_8064CDA4;
extern volatile int lbl_8064CDA8;
extern volatile int lbl_8064CDAC;
extern int lbl_8064CDC8;
extern int lbl_8064CDCC;
extern int lbl_8064CDD4;
extern int lbl_8064D18C;
extern float lbl_8064FFA0;

void fn_801187F4(void)
{
    void *manager;

    while (lbl_8064CDA8 == 0 || lbl_8064CDA4 == 0 ||
           lbl_8064CDAC == 0 || lbl_8064CDA0 == 0) {
    }
    fn_8001D9FC(lbl_8064CDC8);
    if (fn_800462C8(0) == 0) {
        fn_801A98F4(0x239, 100);
    }
    fn_80180BE4();
    if (lbl_8064CD88 != 0) {
        lbl_8064CD88();
        lbl_8064CD88 = 0;
    }
    if (lbl_80332140.text != 0) {
        fn_801E5FB0(lbl_80332140.text);
    }
    fn_801F85A4();
    fn_801FA354();
    fn_80155D9C(0);
    fn_80046B68();
    fn_801E81C0(lbl_8064CDCC);
    fn_801358B4(lbl_8064CDD4);
    fn_80144C40();
    fn_8015C880();
    lbl_8064C4F4 = 1;
    fn_801593AC(1);
    fn_80159440(lbl_8064D18C, 0x4C);
    fn_801593AC(0);
    fn_80200EAC(lbl_8064FFA0, 0x1C, 0, 0, lbl_8064D18C);
    lbl_80332140.flags &= ~1U;
    fn_80118670();
    if (fn_801E79FC(lbl_8064C4E0, 0x299)) {
        if (fn_801E855C(0x14, &lbl_80303D18, 0) == 0) {
            fn_801E8328(0x14, &lbl_80303D18);
        }
        fn_801E79A0(lbl_8064C4E0, 0x299);
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x48)) {
        fn_80047F5C(fn_80047B98(fn_80201AE4()), &lbl_80303CA0, 0);
        fn_801E79A0(lbl_8064C4E0, 0x48);
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x29A)) {
        fn_80047DF8(fn_80047AFC(fn_80201AE4()), &lbl_80303D18, 0);
        fn_801E79A0(lbl_8064C4E0, 0x29A);
    }
    fn_801E79A0(lbl_8064C4E0, 0x29B);
    fn_801A9DCC(2, 100, 5);
    manager = fn_8015C28C(2);
    fn_801ACC94(1);
    fn_801AB154(manager);
    if (fn_801E79FC(lbl_8064C4E0, 0x2ED)) {
        lbl_8064B998 = fn_801A98F4(0x1FD, 100);
    } else if (lbl_8064B998 != -1U) {
        fn_801A9964(lbl_8064B998);
        lbl_8064B998 = -1U;
    }
    fn_801EF35C(0);
    if (lbl_8064CDC8 == 4) {
        fn_80052580(2, lbl_8030F540.chapter, 1, 1, 0);
    } else if (lbl_8064CDC8 == 6) {
        fn_80045A24(1, 1);
    } else {
        fn_800E7950(0);
    }
    fn_80047494(5);
    fn_801EA9F8();
}
