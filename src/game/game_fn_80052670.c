typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct TypeDescriptor {
    const char* name;
    u8 pad04[8];
    s16 value0C;
    s16 value0E;
    s16 value10;
    s16 value12;
    s16 value14;
    s16 value16;
} TypeDescriptor;

typedef struct TransitionState {
    u8 pad00[0x1D2];
    s16 timer;
    u8 pad1D4[2];
    s16 value1D6;
    s8 countdown;
    u8 flag1D9;
    u8 type;
    u8 flag1DB;
    s8 option;
    u8 pad1DD;
    u8 flag1DE;
    u8 flag1DF;
    u8 pad1E0;
    s8 copy_template;
} TransitionState;

typedef struct Template32 {
    u32 words[8];
} Template32;

typedef struct TemplateDestination {
    u8 pad00[0x20];
    Template32 first;
    Template32 second;
} TemplateDestination;

typedef struct GlobalTable {
    u8 pad0000[0x2120];
    TemplateDestination destination;
} GlobalTable;

extern s32 fn_80052900(void);
extern void fn_800AFEC0(void);
extern void fn_8015C7D8(s16 value);
extern void fn_801ACC94(s32 value);
extern void fn_801AC350(s32, s32, s32);
extern void fn_801B0D30(void);
extern void fn_801B2348(s32 value);
extern void fn_801ACD8C(void);
extern void fn_801AD404(s32, s32, s32);
extern void fn_801AD490(void);
extern void sprintf(char* output, const char* format, ...);
extern s32 fn_80144628(s32, void*, s32);
extern void fn_80144430(s32, s32);
extern void fn_801F3528(u32* value);
extern void fn_801F348C(u32* value, s32 count);
extern void fn_8015AD00(s32 value);
extern int fn_80201B44();
extern void fn_801D0D30(void);
extern void fn_800EE5A0(void);

extern TransitionState lbl_8030F540;
extern GlobalTable lbl_802417D0;
extern const Template32 lbl_80238F40;
extern const Template32 lbl_80238F60;
extern s32 lbl_8064D18C;
extern char lbl_803282E0[];
extern char lbl_80328360[];
extern s32 lbl_8064C85C;
extern s32 lbl_8064C84C;
extern s32 lbl_8064C850;
extern u32 lbl_8064E4C8;
extern u32 lbl_80651940;
extern s32 lbl_8064C600;

void fn_80052670(void)
{
    TypeDescriptor* types = (TypeDescriptor*)&lbl_802417D0;

    if (lbl_8030F540.copy_template != 0) {
        TemplateDestination* data = (TemplateDestination*)types;
        data = (TemplateDestination*)((u8*)data + 0x2120);
        data->first = lbl_80238F40;
        data->second = lbl_80238F60;
    }

    if (fn_80052900() == 0) {
        if (lbl_8030F540.timer == 0 && lbl_8030F540.option != 0) {
            fn_800AFEC0();
            lbl_8030F540.timer = lbl_8064D18C;
        }

        {
            TypeDescriptor* descriptor = types;
            descriptor += lbl_8030F540.type;
            if (descriptor->value14 != -1) {
                fn_8015C7D8(descriptor->value14);
            }
        }

        fn_801ACC94(0);
        fn_801AC350(0, 0, 1);
        fn_801B0D30();
        fn_801B2348(1);
        fn_801ACD8C();
        fn_801AD404(0, 0, 3);
        fn_801AD490();
        fn_801AD404(100, 100, 1);

        sprintf(lbl_803282E0, (char*)types + 0x2180,
                    types[lbl_8030F540.type].name);
        sprintf(lbl_80328360, (char*)types + 0x2190,
                    types[lbl_8030F540.type].value0C);

        lbl_8064C85C = fn_80144628(3, (u8*)types + 0x2120, 0);
        lbl_8030F540.flag1DF = 0;
        lbl_8064C84C = 0;
        lbl_8030F540.flag1D9 = 0;
        lbl_8030F540.flag1DB = 0;
        lbl_8030F540.value1D6 = 0;
        lbl_8030F540.countdown = -1;
        lbl_8030F540.flag1DE = 0;
        lbl_8064C850 = 0;
        lbl_8030F540.flag1DF = 0;
        fn_80144430(2, 1);

        if (lbl_8030F540.type != 0x25 && lbl_8030F540.type != 0x26 &&
            lbl_8030F540.type != 0x27) {
            u32 value1 = lbl_8064E4C8;
            u32 value2;
            fn_801F3528(&value1);
            value2 = lbl_80651940;
            fn_801F348C(&value2, 10);
        } else {
            lbl_8064C600 = 10000;
        }

        if (lbl_8030F540.option != 0) {
            fn_8015AD00(2);
            fn_80201B44();
            fn_801D0D30();
        }
        fn_800EE5A0();
    }
}
