typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DisplayConfig {
    u32 flags;
    u16 width;
    u16 field_6;
    u16 height;
    u8 pad_A[0xF];
    u8 field_19;
    u8 field_1A[0x18];
    u8 field_32[1];
} DisplayConfig;

typedef struct DisplayState {
    void* field_0;
    void* field_4;
} DisplayState;

extern char lbl_802FC2C0[];
extern char lbl_802FC644[];
extern char lbl_802662C0[];
extern u32 lbl_80651358;
extern float lbl_80651348;
extern float lbl_8065134C;
extern DisplayConfig* lbl_8064C38C;
extern DisplayState lbl_8064D71C;
extern u32 lbl_8064D718;
extern void* lbl_8064D714;
extern void* lbl_8064D710;
extern u32 lbl_8064D6D8;
extern void* lbl_8064D74C;

extern void* memset(void*, int, unsigned long);
extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void OSSetArenaLo(void*);
extern void OSInit(void);
extern void DVDInit(void);
extern void OSSetErrorHandler(int, void*);
extern void fn_8015DAB0(char*, int, u32);
extern void fn_80215D2C(int);
extern void fn_801EF788(void);
extern void fn_80216EAC(void);
extern void fn_801EFE84(int);
extern void fn_801EF39C(int);
extern void fn_80217F88(void);
extern void fn_80217324(void);
extern void fn_801EF814(void);
extern void fn_801EF840(void);
extern void fn_801EF89C(void);
extern void fn_801EF8F8(void);
extern void* fn_8020AF08(void*, void*, int);
extern void fn_8020AF78(void*, void*);
extern void fn_8020AEF8(void);
extern void fn_801EF910(void);
extern void fn_802177EC(DisplayConfig*);
extern void fn_802180A4(void*);
extern void* fn_801FEA8C(u32, int, char*, int);
extern void* GXInit(void*, u32);
extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_8022B970(int, int, u16, u16);
extern void fn_80226DE0(int, int, u16, u16);
extern void fn_80226F60(u16, u16);
extern void fn_802271BC(float);
extern void fn_802272F8(u8, void*, int, void*);
extern void fn_8022A814(int, int);
extern void fn_8022A924(int);
extern void fn_80227290(u32*, u32);
extern void fn_8022A6DC(int);
extern void fn_8022A71C(int);
extern void fn_8022753C(void*, int);
extern void fn_80226630(void);
extern void fn_80219640(int);
extern void fn_8020F2DC(void);
extern void fn_800AE254(void);
extern void fn_801A58FC(void);
extern void fn_8014447C(int);
extern void fn_80145004(void);
extern void fn_801EF400(void);

void fn_801EFA68(DisplayConfig* config, int mode)
{
    int unused;
    void* arenaLo;
    void* arenaHi;
    void* newLo;
    DisplayState* state = &lbl_8064D71C;
    u32 gxValue;
    volatile u32 value = lbl_80651358;

    fn_8015DAB0(lbl_802FC2C0, unused, value);
    OSInit();
    DVDInit();
    fn_80215D2C(1);
    fn_801EF788();
    fn_80216EAC();
    fn_801EFE84(1);
    fn_801EF39C(1);
    fn_80217F88();
    fn_80217324();
    OSSetErrorHandler(2, fn_801EF814);
    OSSetErrorHandler(3, fn_801EF840);
    OSSetErrorHandler(7, fn_801EF89C);
    OSSetErrorHandler(15, fn_801EF8F8);

    lbl_8064C38C = config;
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    memset(arenaLo, 0, (u8*)arenaHi - (u8*)arenaLo);
    state->field_0 = lbl_802662C0;
    state->field_4 = (void*)(((u32)arenaLo + 31) & ~31);
    OSSetArenaLo((void*)(((u32)state->field_4 +
        ((((lbl_8064C38C->width + 15) & ~15) * lbl_8064C38C->height) << 1) + 31) & ~31));

    newLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    newLo = fn_8020AF08(newLo, arenaHi, 1);
    OSSetArenaLo(newLo);
    arenaHi = (void*)((u32)arenaHi & ~31);
    newLo = (void*)(((u32)newLo + 31) & ~31);
    memset(newLo, 0, (u8*)arenaHi - (u8*)newLo);
    fn_8020AF78(newLo, arenaHi);
    fn_8020AEF8();
    fn_801EF910();
    OSSetArenaLo(arenaHi);

    fn_802177EC(lbl_8064C38C);
    fn_802180A4(state->field_0);
    lbl_8064D718 = (u32)state->field_4;
    fn_80217F88();
    fn_80217324();
    lbl_8064D714 = fn_801FEA8C(0x30000, 1, lbl_802FC644, 991);
    lbl_8064D710 = GXInit(lbl_8064D714, 0x30000);
    lbl_8064D6D8 = 0;

    fn_8022B94C(lbl_80651348, lbl_80651348, (float)lbl_8064C38C->width,
                (float)lbl_8064C38C->height, lbl_80651348, lbl_8065134C);
    fn_8022B970(0, 0, lbl_8064C38C->width, lbl_8064C38C->field_6);
    fn_80226DE0(0, 0, lbl_8064C38C->width, lbl_8064C38C->field_6);
    fn_80226F60(lbl_8064C38C->width, lbl_8064C38C->height);
    fn_802271BC((float)lbl_8064C38C->height / (float)lbl_8064C38C->field_6);
    fn_802272F8(lbl_8064C38C->field_19, lbl_8064C38C->field_1A, 1,
                lbl_8064C38C->field_32);
    fn_8022A814(1, 0);
    fn_8022A924(1);
    gxValue = value;
    fn_80227290(&gxValue, 0xFFFFFF);
    fn_8022A6DC(1);
    fn_8022A71C(1);
    fn_8022753C(state->field_0, 1);
    fn_8022753C(state->field_0, 1);
    fn_8022753C(state->field_4, 1);
    fn_8022A6DC(1);
    fn_8022A71C(0);
    fn_80217F88();
    fn_802180A4(state->field_4);
    lbl_8064D718 = (u32)state->field_0;
    fn_80217324();
    fn_80226630();
    if (lbl_8064C38C->flags & 1) {
        fn_80217324();
    }
    lbl_8064D74C = config;
    fn_80219640(5);
    fn_8020F2DC();
    fn_800AE254();
    fn_801A58FC();
    fn_8014447C(1);
    fn_80145004();
    fn_801EF400();
}
