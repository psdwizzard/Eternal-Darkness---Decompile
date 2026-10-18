typedef struct FadeState {
    char pad0[0x6C];
    void *handle;
    char pad70[0x10];
    int color;
    int active;
    char pad88[0xA];
    short enable;
    int unk94;
    int unk98;
} FadeState;

typedef struct Entry {
    char pad[0x1C];
    unsigned int flags;
} Entry;

extern FadeState lbl_8024B3E4;
extern const char lbl_8024B544[];
extern void *lbl_80331720[6];
extern void *lbl_8064CCC8;
extern int lbl_8064CCDC;
extern unsigned int lbl_8064CCE0;
extern int lbl_8064CD88;
extern void *lbl_8064CDB0;
extern void *lbl_8064CDB4;
extern Entry *lbl_8064CDBC;
extern Entry *lbl_8064CDC0;
extern int lbl_8064D5A8;

extern void fn_80117EF0(void);
extern void fn_80144680(Entry *);
/* This wrapper forwards the sound token in r3 to sndFXKeyOff. Its
 * existing C definition omits the parameter, so leave it unprototyped. */
extern void fn_801A9964();
extern int fn_801AF85C(int);
extern void fn_801B05B0(int, int);
extern void fn_801E5FB0(void *);
extern void fn_801E7FDC(const char *, ...);
extern void fn_801E8AC4(void *);

void fn_8010BFF0(void)
{
    int i;

    fn_801E7FDC(lbl_8024B544, lbl_8064D5A8);
    if (lbl_8064CCE0 != 0) {
        fn_801A9964(lbl_8064CCE0);
        lbl_8064CCE0 = 0;
    }
    if (lbl_8064CCDC != -1 && fn_801AF85C(lbl_8064CCDC) != 0) {
        fn_801B05B0(lbl_8064CCDC, 10);
    }
    lbl_8064CCDC = -1;
    fn_801E5FB0(lbl_8064CCC8);
    lbl_8064CCC8 = 0;
    if (lbl_8064CDBC != 0) {
        fn_80144680(lbl_8064CDBC);
        lbl_8064CDBC = 0;
    }
    fn_801E5FB0(lbl_8024B3E4.handle);
    lbl_8024B3E4.handle = 0;
    fn_801E5FB0(lbl_8064CDB4);
    lbl_8064CDB4 = 0;
    fn_801E5FB0(lbl_8064CDB0);
    lbl_8064CDB0 = 0;
    fn_80117EF0();
    for (i = 0; i < 5; i++) {
        fn_801E8AC4(lbl_80331720[i]);
    }
    fn_80144680(lbl_8064CDC0);
    lbl_8064CD88 = 0;
}
