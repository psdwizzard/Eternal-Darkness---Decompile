typedef unsigned int u32;

typedef struct RequestGlobals {
    int current;
    char pad04[8];
    void* states[4];
} RequestGlobals;

extern RequestGlobals lbl_805B6FE0;
extern int lbl_80651C98;
extern int lbl_8064C4F4;
extern int __OSCurrHeap;
extern int lbl_8064D158;
extern int lbl_8064D15C;
extern int lbl_8064D180;
extern u32 lbl_8064D184;
extern int lbl_8064D188;
extern int lbl_8064D704;
extern float lbl_80650630;

extern void* fn_80201B3C();
extern void fn_801ED57C(int);
extern void fn_801ED3F4(void*);
extern void fn_801EB2FC(int);
extern void fn_8011E174(int, int);
extern void fn_8013F878(void);
extern void fn_801AB154(void*);
extern void fn_801A9DCC(int, int, int);
extern void fn_800BC74C(int);
extern void fn_80046B0C(void*);
extern void fn_8015AC3C(int);
extern int fn_8015E4E8(void);
extern int fn_80201B44();
extern unsigned long long fn_8020123C();
extern void fn_80200EAC(int, int, int, float, int);
extern void fn_800474D8(void);
extern void fn_8015E788(void);
extern void fn_800477F8(int, int);
extern void fn_801F6DE4(void);
extern void fn_8011E1C4(void);
extern void fn_8016B030(int);
extern void* fn_8015AB00(int);
extern void fn_801EB9F0(void);
extern void fn_801EBA58(void*);
extern void fn_801EBDDC(void*);
extern void fn_8015C8A4(int, int);
extern void fn_802020B4(void*, int);
extern void fn_801801D0(void);
extern void fn_801F348C(int*, int);
extern u32 fn_801E7998(int);
extern void fn_801E7974(int, u32);
extern void fn_801F0294(int, float);
extern void OSCheckHeap(int);

void fn_80159184(u32 flags)
{
    int saved;
    volatile int* savedp = &saved;
    void* state = lbl_805B6FE0.states[lbl_805B6FE0.current];
    void* token;
    *savedp = lbl_80651C98;
    token = fn_80201B3C();

    fn_801ED57C(1);
    fn_801ED3F4(*(void**)((char*)state + 0x813C));
    fn_801EB2FC(0);
    fn_8011E174(0x10000, 0);
    fn_8013F878();
    if (!(flags & 0x20)) {
        fn_801AB154(state);
    }
    fn_801A9DCC(0, 100, 0);
    fn_801A9DCC(1, 100, 0);
    fn_800BC74C(0);
    fn_80046B0C(state);
    if (!(flags & 0x10)) {
        fn_8015AC3C((flags & 0x44) == 0);
    }

    if (lbl_8064C4F4 == 0) {
        int mode = (flags >> 7) & 1;
        lbl_8064D15C = 1;
        if (fn_8015E4E8() == 0) {
            fn_8020123C(61, 0, fn_80201B44(), 0);
        }
        fn_80200EAC(61, 0, 0, lbl_80650630, lbl_8064D180);
        lbl_8064D15C = 0;
        fn_800474D8();
        if (mode != 0) {
            fn_8015E788();
        }
        fn_800477F8(0, mode);
        fn_801F6DE4();
    } else {
        lbl_8064C4F4 = 0;
    }

    if (!(flags & 4)) {
        fn_8011E1C4();
        fn_8016B030(1);
    }
    if (!(flags & 8)) {
        void* object = fn_8015AB00(lbl_805B6FE0.current);
        if (object != 0) {
            fn_801EB9F0();
            fn_801EBA58(object);
            fn_801EBDDC(object);
        }
    }

    lbl_8064D704 = 0;
    fn_8015C8A4(-1, 0);
    fn_802020B4(token, 1);
    fn_801801D0();
    {
        int value = *savedp;
        fn_801F348C(&value, 10);
    }
    if (lbl_8064D188 == 0 && lbl_8064D184 < fn_801E7998(lbl_8064D158)) {
        fn_801E7974(lbl_8064D158, lbl_8064D184);
    }
    fn_801F0294(0, lbl_80650630);
    OSCheckHeap(__OSCurrHeap);
}
