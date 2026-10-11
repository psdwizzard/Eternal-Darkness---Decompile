typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Registry {
    u8 reserved[0x54];
    unsigned short state;
} Registry;

typedef struct CameraState {
    u8 reserved[0x40];
    int active;
} CameraState;

typedef struct DisplaySize DisplaySize;
typedef struct TextDescriptor TextDescriptor;

extern void* fn_8015C348(int);
extern void fn_801EF530(void);
extern void fn_801EF580(DisplaySize*);
extern void fn_801EB194(int);
extern void fn_800E7950(int);
extern void fn_801180A8(void);
extern void fn_801F8620(void);
extern int fn_801FA410(int);
extern void fn_801F10BC(long, long, long);
extern void fn_80046B68(void);
extern void* fn_801E5D20(void*);
extern void fn_801E6228(TextDescriptor*, const char*, ...);
extern void fn_801ACC94(int);
extern void fn_801AC350(signed char, int, int);
extern void fn_801B0D30(void);
extern void fn_801A9DCC(int, u8, int);
extern void fn_80126084(void);
extern void fn_8012BD4C(void);
extern int fn_80155D9C(int);
extern void fn_801E81C0(int);
extern int fn_801358B4(int);
extern void fn_8011857C(void);
extern void fn_801E7974(u8*, u32);
extern void fn_801A9964(void);
extern void fn_801EF35C(int);
extern int fn_801A98F4(int, void*);

extern int lbl_8064B990;
extern DisplaySize* lbl_8064D74C;
extern int lbl_8064CCC0;
extern CameraState lbl_8063D378;
extern TextDescriptor* lbl_8064C8EC;
extern char lbl_8064B99C;
extern int lbl_8064CDC8;
extern int lbl_8064CDCC;
extern int lbl_8064D5A8;
extern int lbl_8064CDD4;
extern int lbl_8064CDD8;
extern int lbl_80332140[];
extern int lbl_8064CDBC;
extern int lbl_8064C5E8;
extern int lbl_8064CDD0;
extern int lbl_8064CDDC;
extern int lbl_8064CDB4;
extern int lbl_8064CDB0;
extern int lbl_8064C5D8;
extern int lbl_8064CD70;
extern u8* lbl_8064C4E0;
extern u32 lbl_8064B998;

void fn_80118AC4(void)
{
    Registry* registry;
    u32* flags;
    int previous;

    registry = fn_8015C348(2);
    lbl_8064B990 = 1;
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_801EB194(1);
    fn_800E7950(1);
    fn_801180A8();
    lbl_8064CCC0 = 0;
    fn_801F8620();
    fn_801FA410(8);
    fn_801F10BC(0, 0, 0);
    lbl_8063D378.active = 1;
    fn_80046B68();
    registry->state = 0;
    if (lbl_8064C8EC != 0) {
        flags = fn_801E5D20(lbl_8064C8EC);
        *flags &= ~1U;
        fn_801E6228(lbl_8064C8EC, &lbl_8064B99C);
    }
    fn_801ACC94(0);
    fn_801AC350(5, 0, 1);
    fn_801B0D30();
    fn_801A9DCC(2, 0x28, 5);
    fn_80126084();
    fn_8012BD4C();
    fn_80155D9C(1);
    lbl_8064CDC8 = 3;
    lbl_8064CDCC = lbl_8064D5A8;
    fn_801E81C0(0);
    previous = fn_801358B4(0);
    lbl_8064CDD4 = previous;
    lbl_8064CDD8 = 1;
    lbl_80332140[0] = 0;
    lbl_80332140[1] = 0;
    lbl_8064CDBC = 0;
    if (lbl_8064C5E8 == 3) {
        fn_8011857C();
    }
    lbl_8064CDD0 = 0;
    lbl_8064CDDC = 0;
    lbl_8064CDB4 = 0;
    lbl_8064CDB0 = 0;
    lbl_8064C5D8 = 0;
    lbl_8064CD70 = 0;
    fn_801E7974(lbl_8064C4E0, 0x29B);
    if (lbl_8064B998 != ~0U) {
        fn_801A9964();
        lbl_8064B998 = ~0U;
    }
    fn_801EF35C(1);
    if (lbl_8064C5E8 == 3) {
        fn_801A98F4(0x238, (void*)0x64);
    }
}
