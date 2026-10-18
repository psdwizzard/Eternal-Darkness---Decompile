typedef signed char s8;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct OptionStrings {
    char first[12];
    char second[12];
    char third[12];
    char pad[4];
} OptionStrings;

OptionStrings lbl_8023CFF8 = {
    "gamma1_0",
    "gamma1_7",
    "gamma2_2",
};
extern char lbl_802FC500[];
extern char lbl_802FC608[];

extern s32 lbl_8064A998;
extern s32 lbl_8064C5E8;
extern void (*lbl_8064C620)(void);
extern s32 lbl_8064C62C;
extern s32 lbl_8064C630;
extern s32 lbl_8064C634;
extern s32 lbl_8064C638;
extern s32 lbl_8064C63C;
extern s32 lbl_8064C640;
extern s32 lbl_8064C644;
extern u32 lbl_8064C648;
extern s32 lbl_8064C64C;
extern s32 lbl_8064C6D4;
extern s32 lbl_8064CBA0;
extern s32 lbl_8064CBA4;
extern s32 lbl_8064D740;

extern u32 OSGetResetCode(void);
extern void fn_8001D510(void);
extern void fn_8001D91C(void);
extern void fn_8001DB04(s32);
extern void fn_8001E134(s32);
extern void fn_80024F28(s32);
extern void fn_80045220(u8);
extern s32 fn_800FD228(const char*, const char*);
extern void fn_8011B740(void);
extern void fn_80125284(void);
extern void fn_801358D0(void);
extern void fn_80144430(s32, s32);
extern void fn_80145004(void);
extern void fn_8017CF0C(void);
extern void fn_801E7DC8(s32);
extern void fn_801E81C8(void);
extern void fn_801EFA68(char*, s32);
extern void OSSetSaveRegion(void*, void*);
extern u32 OSGetProgressiveMode(void);

int main(s32 argc, char** argv)
{
    u32 reset_code;
    u32 options;
    s32 boot_mode;
    char* executable;
    s32 i;

    options = (u32)&lbl_8023CFF8;
    reset_code = OSGetResetCode();
    lbl_8064C644 = 0;
    lbl_8064A998 = 1;
    executable = lbl_802FC608;
    boot_mode = 0;
    lbl_8064D740 = 0;
    fn_8001E134(0);
    fn_8001D510();
    OSSetSaveRegion((void*)0x80700000, (void*)0x81200000);
    fn_80125284();
    fn_80045220(0);
    lbl_8064C62C = 0;

    if (reset_code == 0x80000000) {
        volatile s8* boot = (volatile s8*)0x81200000;
        s32 boot_kind;

        lbl_8064C6D4 = 1;
        lbl_8064C63C = boot[-7];
        lbl_8064C638 = boot[-6];
        lbl_8064C634 = boot[-5];
        lbl_8064C630 = boot[-4];
        lbl_8064C640 = *(volatile s32*)(boot - 0x10);
        lbl_8064C644 = boot[-2];
        fn_80144430(-1, 0);
        fn_80144430(lbl_8064C640, 1);
        fn_8001E134(boot[-3]);
        boot_mode = 12;
        lbl_8064CBA4 = boot[-8];
        boot_kind = *(volatile s32*)(boot - 0x14);

        switch (boot_kind) {
        case 1:
            lbl_8064A998 = 0;
            fn_80045220(boot[-1]);
            lbl_8064C62C = *(volatile s32*)(boot - 0xC);
            break;
        case 0:
            boot_mode = 0;
            break;
        case 11:
            fn_80045220(boot[-1]);
            lbl_8064C62C = *(volatile s32*)(boot - 0xC);
            break;
        case 13:
            boot_mode = 13;
            break;
        case 12:
            break;
        default:
            fn_80045220(boot[-1]);
            lbl_8064C62C = *(volatile s32*)(boot - 0xC);
            break;
        }

        if (lbl_8064C644 != 0 && OSGetProgressiveMode() == 1) {
            executable = lbl_802FC500;
        }
        lbl_8064CBA0 = lbl_8064C634;
    }

    lbl_8064C648 = reset_code;
    if (argc > 1) {
        argv++;
        for (i = 1; i < argc; argv++, i++) {
            if (fn_800FD228(*argv, (char*)(options + 0)) == 0) {
                lbl_8064D740 = 0;
            } else if (fn_800FD228(*argv, (char*)(options + 12)) == 0) {
                lbl_8064D740 = 1;
            } else if (fn_800FD228(*argv, (char*)(options + 24)) == 0) {
                lbl_8064D740 = 2;
            }
        }
    }

    fn_801E7DC8(0x100);
    if (boot_mode == 0) {
        fn_801EFA68(executable, 0);
        fn_8001DB04(0);
    } else {
        fn_801EFA68(executable, 1);
        fn_8001DB04(1);
    }
    fn_80024F28(boot_mode);

    for (;;) {
        lbl_8064C64C++;
        fn_8001D91C();
        lbl_8064C620();
        fn_8011B740();
        fn_80145004();
        fn_8017CF0C();
        if (lbl_8064C5E8 != 4) {
            fn_801E81C8();
        }
        fn_801358D0();
    }
}
