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

extern char lbl_802FC500[];
extern DisplayConfig* lbl_8064C38C;
extern DisplayState lbl_8064D71C;
extern u32 lbl_8064D718;
extern void* lbl_8064D74C;
extern float lbl_80651348;
extern float lbl_8065134C;

extern int fn_80218308(void);
extern void fn_801EFE84(int);
extern void fn_802177EC(void);
extern void fn_802180A4(void*);
extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_8022B970(int, int, u16, u16);
extern void fn_80226DE0(int, int, u16, u16);
extern void fn_80226F60(u16, u16);
extern void fn_802271BC(float);
extern void fn_802272F8(u8, void*, int, void*);
extern void fn_8022A814(int, int);
extern void fn_8022A924(int);
extern void fn_8022753C(void*, int);
extern void fn_80217F88(void);
extern void fn_80217324(void);

void fn_801EF5EC(void)
{
    DisplayConfig* config;

    if (!fn_80218308()) {
        return;
    }

    fn_801EFE84(1);
    lbl_8064C38C = (DisplayConfig*)lbl_802FC500;
    fn_802177EC();
    fn_802180A4(lbl_8064D71C.field_0);
    lbl_8064D718 = (u32)lbl_8064D71C.field_4;

    config = lbl_8064C38C;
    fn_8022B94C(lbl_80651348, lbl_80651348, (float)config->width,
                (float)config->height, lbl_80651348, lbl_8065134C);
    config = lbl_8064C38C;
    fn_8022B970(0, 0, config->width, config->field_6);
    config = lbl_8064C38C;
    fn_80226DE0(0, 0, config->width, config->field_6);
    config = lbl_8064C38C;
    fn_80226F60(config->width, config->height);
    config = lbl_8064C38C;
    fn_802271BC((float)config->height / (float)config->field_6);
    config = lbl_8064C38C;
    fn_802272F8(config->field_19, config->field_1A, 1, config->field_32);
    fn_8022A814(1, 0);
    fn_8022A924(1);
    fn_8022753C(lbl_8064D71C.field_0, 1);
    fn_8022753C(lbl_8064D71C.field_0, 1);
    fn_8022753C(lbl_8064D71C.field_4, 1);
    fn_80217F88();
    fn_80217324();
    if (lbl_8064C38C->flags & 1) {
        fn_80217324();
    }
    fn_801EFE84(0);
    lbl_8064D74C = lbl_8064C38C;
}
