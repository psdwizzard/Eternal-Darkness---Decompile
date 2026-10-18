typedef unsigned char u8;

typedef struct GameState {
    int f0;
    int f4;
    int f8;
    char pad_C[0x10];
    int f1C;
    char pad_20[0x18F4];
    u8 f1914;
    u8 pad_1915;
    unsigned short f1916;
    char pad_1918[4];
    int f191C;
} GameState;

char lbl_8023DD88[] = "SkEngine_FileRead.c";
char lbl_8023DD9C[] =
    "ED_Reset.c\0\0"
    "RecordP.bin\0"
    "RecordA.bin\0"
    "RecordJ.bin\0"
    "EBootPak.bin\0\0\0\0"
    "EFonts.tpl\0\0"
    "FontBack.tpl\0\0\0\0"
    "InvS.bin\0\0\0\0"
    "InvU.bin\0\0\0\0"
    "InvE.bin\0\0\0\0"
    "ScrLvl-1.gpk\0\0\0\0"
    "Camera01\0\0\0";

extern int lbl_8023D5B8[];
extern GameState lbl_803003C8;
extern char lbl_8030F540[];
extern char lbl_803003AC[];
extern char lbl_80301D3C[];
extern char lbl_80606334[];
extern char lbl_806391F0[];
extern char lbl_80639228[];
extern char lbl_8063CD18[];

extern int lbl_8064B2B8, lbl_8064B4D8, lbl_8064B818, lbl_8064B820;
extern int lbl_8064B2E0, lbl_8064B2E8;
extern int lbl_8064C4E4, lbl_8064C4F0, lbl_8064C4F4;
extern void *lbl_8064C4E0, *lbl_8064C4E8, *lbl_8064C4F8, *lbl_8064C4FC;
extern void *lbl_8064C504, *lbl_8064C508, *lbl_8064C50C, *lbl_8064C510, *lbl_8064C514, *lbl_8064C518;
extern int lbl_8064C51C, lbl_8064C53C, lbl_8064C540, lbl_8064C544, lbl_8064C548, lbl_8064C54C;
extern u8 lbl_8064C550;
extern int lbl_8064C58C, lbl_8064C594, lbl_8064C598, lbl_8064C59C;
extern u8 lbl_8064C590;
extern int lbl_8064C5A4, lbl_8064C5AC;
extern void *lbl_8064C5B0;
extern int lbl_8064C5BC, lbl_8064C5C0, lbl_8064C5D8, lbl_8064C5DC, lbl_8064C5E0, lbl_8064C5E4, lbl_8064C5E8;
extern void *lbl_8064C5D0;
extern void *lbl_8064C6E0;
extern int lbl_8064C6F8, lbl_8064C6FC, lbl_8064C7CC, lbl_8064C868, lbl_8064C86C, lbl_8064C8E8;
extern int lbl_8064C9E8, lbl_8064C9FC, lbl_8064CA50, lbl_8064CA54, lbl_8064CA58, lbl_8064CA5C;
extern int lbl_8064CA60, lbl_8064CA64, lbl_8064CA68, lbl_8064CAB4, lbl_8064CB00;
extern int lbl_8064CCF4, lbl_8064CD34, lbl_8064D180, lbl_8064D18C;
extern void *lbl_8064D68C;
extern int lbl_8064DF40, lbl_8064DF44;
extern float lbl_8064DF48, lbl_8064DF4C;

extern void *memset(void *, int, unsigned int);
extern void *fn_801E8660(char *);
extern void *fn_801E86A0(void *, int);
extern void *fn_801E78DC(int);
extern void *fn_80157760(int, int);
extern void *fn_80156DA0(int, int);
extern int fn_800474C8(void);
extern int fn_8002487C(int, int);
extern int fn_80052218(int);
extern int fn_801A94E4(void *, int, int, int);
extern void *fn_801E741C(char *);

extern void fn_800069FC(); extern void fn_80008134(); extern void fn_80008738(); extern void fn_80008D0C();
extern void fn_80018ED4(); extern void fn_8001D4C4(); extern void fn_8001D9FC(int); extern void fn_8001E144();
extern void fn_8002476C(); extern void fn_80024794(); extern void fn_800248C0(); extern void fn_8002495C();
extern void fn_80024B74(); extern void fn_80024B78(); extern void fn_80024D08(); extern void fn_80024D3C();
extern void fn_80025F48(); extern void fn_80026060(); extern void fn_80028098(); extern void fn_800280FC();
extern void fn_80028E88(); extern void fn_8002B688(); extern void fn_80034114(); extern void fn_800427E0();
extern void fn_80042810(); extern void fn_800432F4(); extern void fn_80045980(); extern void fn_800459A0();
extern void fn_80045A24(); extern void fn_80045DBC(); extern void fn_80046C98(); extern void fn_80047248();
extern void fn_8004736C(); extern void fn_80048620(); extern void fn_80048A70(); extern void fn_8004919C();
extern void fn_800542B4(); extern void fn_80054758(); extern void fn_8006B21C(); extern void fn_800721B0();
extern void fn_8007EC28(); extern void fn_8007EDF0(); extern void fn_80086218(); extern void fn_80086B38();
extern void fn_800A3570(); extern void fn_800AFC30(); extern void fn_800B0704(); extern void fn_800B16F4();
extern void fn_800B7C6C(); extern void fn_800B84A8(); extern void fn_800B8F6C(); extern void fn_800B92A0();
extern void fn_800B9454(); extern void fn_800BC6D8(); extern void fn_800BD384(); extern void fn_800C94FC();
extern void fn_800C96B4(); extern void fn_800DE8C8(); extern void fn_800E463C(); extern void fn_800E790C();
extern void fn_800E9F10(); extern void fn_800EB438(); extern void srand(); extern void fn_8010F404();
extern void fn_80113AB8(); extern void fn_80117E60(); extern void fn_8011B734(); extern void fn_8011E19C();
extern void fn_8011E234(); extern void fn_8011E87C(); extern void fn_8011FF30(); extern void fn_80125D88();
extern void fn_80125DC8(); extern void fn_80125FE4(); extern void fn_801285F8(); extern void fn_80128610();
extern void fn_80135510(); extern void fn_80137E04(); extern void fn_8013816C(); extern void fn_80138F78();
extern void fn_80139298(); extern void fn_80140E60(float); extern void fn_80142944(); extern void fn_80144178();
extern void fn_801443F4(); extern void fn_8014447C(); extern void fn_801445EC(); extern void fn_801445F4();
extern void fn_80149EFC(); extern void fn_80149F9C(); extern void fn_8014B76C(); extern void fn_80155B5C();
extern void fn_801568B8(void*, void*); extern void fn_801569A0(); extern void fn_80157504(); extern void fn_8015761C();
extern void fn_8015AA28(); extern void fn_8015AEB8(); extern void fn_8015CA00(); extern void fn_8015CB00();
extern void fn_8015D414(); extern void fn_8015DAB0(); extern void fn_8016AD28(); extern void fn_8016B3A4();
extern void fn_8016B400(int, int, int); extern void fn_8017AE20(); extern void fn_8017AE90(); extern void fn_8017D0D8();
extern void fn_8017FFC0(); extern void fn_801801A4(); extern void fn_80180C54(); extern void fn_8018807C(float, float);
extern void fn_80188384(); extern void fn_801A58FC(); extern void fn_801A5910(); extern void fn_801A6E34();
extern void fn_801A6F64(); extern void fn_801A7D20(); extern void fn_801A7D44(); extern void fn_801A83A4();
extern void fn_801D1054(); extern void fn_801D1388(); extern void fn_801E5AE0(); extern void fn_801E5B10();
extern void fn_801E5BD8(); extern void fn_801E7944(); extern void fn_801E79A0();
extern void fn_801E7DC8(); extern void fn_801E81C0(); extern void fn_801E81E4(); extern void fn_801E85A8();
extern void fn_801E8A0C(); extern void fn_801EBA58(); extern void fn_801EBEDC(); extern void fn_801EF35C();
extern void fn_801EF36C(); extern void fn_801EF38C(); extern void fn_801F0044(); extern void fn_801F3444();
extern void fn_801F3F88(); extern void fn_801F455C(); extern void fn_801F58F8(); extern void fn_801F5980();
extern void fn_801F7C78(); extern void fn_801FA198(); extern void fn_801FCCEC(); extern void fn_80200338();
extern void fn_802012A0(); extern void fn_802012F8(); extern void fn_802014F0(); extern void fn_80204A14();
extern void OSInitStopwatch();

void fn_80024F28(int mode)
{
    int flag = 0;
    void *archive;
    void *entry;
    char *strings = lbl_8023DD88;

    lbl_8064C9FC = 0;
    fn_801E7DC8(0x100);
    fn_801E81C0(0);
    fn_801443F4();
    fn_80045980();
    lbl_8064C86C = 0;
    lbl_8064C868 = 0;
    lbl_8064C5C0 = 0;
    lbl_8064CAB4 = 0;
    fn_800DE8C8();
    fn_8011FF30(1);
    fn_80137E04();
    fn_8011E19C(1, 0);
    lbl_8064C598 = 1;
    lbl_8064C594 = 1;
    *(int *)(lbl_8030F540 + 0x1C8) = -2;
    lbl_8064C58C = 0;
    lbl_8064C5E8 = -1;
    lbl_8064C5E4 = -1;
    lbl_8064C5D8 = 0;
    lbl_8064B4D8 = 0;
    lbl_8064B820 = 1;
    lbl_8064C4E4 = 0;
    lbl_8064C590 = 0;
    fn_800C94FC();
    { int value = lbl_8064DF40; fn_801FCCEC(&value); }
    { int value = lbl_8064DF44; fn_801F455C(&value); }
    fn_800E9F10();
    fn_8014B76C();
    fn_8018807C(lbl_8064DF48, lbl_8064DF48);
    lbl_8064CB00 = 0;
    fn_800E790C();
    lbl_8064CA68 = 0;
    lbl_8064CA64 = 0;
    lbl_8064CA60 = 0;
    lbl_8064C6FC = 0;
    lbl_8064B818 = -1;
    fn_800542B4();
    fn_80008D0C();
    fn_80046C98(1);
    fn_80128610(-1);
    fn_801285F8(0);
    lbl_8064C9E8 = 0;

    switch (mode) {
    case 0:
        fn_80144178();
    case 12:
    case 13:
        lbl_8064C5BC = 0;
        lbl_8064B2B8 = 1;
        fn_800B92A0(); fn_800B16F4(); fn_800B7C6C(); fn_800B84A8(); fn_800B8F6C(); fn_800B9454(0, 0);
        lbl_8064CA54 = 0; lbl_8064CA50 = 0; lbl_8064CA5C = 0; lbl_8064CA58 = 0; lbl_8064C4E4 = 0;
        lbl_803003C8.f8 = 0; lbl_803003C8.f0 = 0; lbl_803003C8.f4 = 0; lbl_803003C8.f191C = 0;
        fn_800427E0(0); fn_80048620(0); fn_80024794(); fn_8015D414(); fn_80200338(); fn_800E463C();
        fn_801EF38C(0); fn_8015AEB8(fn_80086B38, 0x15F, 1); fn_80138F78(1); fn_800432F4(); fn_800BD384();
        fn_801A94E4(lbl_8064C6E0, 1, -1, 1); fn_8013816C(); fn_8004736C(0); fn_80047248(); fn_801EF36C(0); fn_801EF35C(0);
        fn_801F58F8(0x320);
        archive = fn_801E8660(strings + 0x44);
        lbl_8064C4FC = archive;
        entry = fn_801E86A0(archive, 7);
        fn_801E5B10(strings + 0x54, strings + 0x60, entry, fn_80028E88);
        fn_801E5BD8(fn_801E86A0(lbl_8064C4FC, 0));
        fn_801E5BD8(fn_801E86A0(lbl_8064C4FC, 1));
        lbl_8064C504 = fn_801E86A0(lbl_8064C4FC, 4); fn_801E85A8(lbl_8064C504);
        lbl_8064C508 = fn_801E86A0(lbl_8064C4FC, 6); fn_801E85A8(lbl_8064C508);
        lbl_8064C4E8 = fn_801E86A0(lbl_8064C4FC, 5); fn_8015DAB0(lbl_8064C4E8);
        lbl_8064C50C = fn_801E86A0(lbl_8064C4FC, 8); fn_801E85A8(lbl_8064C50C);
        lbl_8064C510 = fn_801E86A0(lbl_8064C4FC, 9); fn_801E85A8(lbl_8064C510);
        lbl_8064C514 = fn_801E86A0(lbl_8064C4FC, 10); fn_801E85A8(lbl_8064C514);
        lbl_8064C518 = fn_801E86A0(lbl_8064C4FC, 11); fn_801E85A8(lbl_8064C518);
        lbl_8064C5D0 = fn_801E86A0(lbl_8064C4FC, 12); fn_801E85A8(lbl_8064C5D0);
        lbl_8064C51C = 0; lbl_8064C5A4 = 0;
        fn_800EB438(); lbl_8064C4E0 = fn_801E78DC(0x4A0); fn_80024B78(); fn_801F0044(); fn_801F3444(); fn_8017AE20(0xC000);
        fn_80042810(-1); fn_80155B5C(0x113); fn_80140E60(lbl_8064DF4C); fn_801EBEDC(); fn_8015AA28(0);
        OSInitStopwatch(lbl_806391F0, &lbl_8064B2E0); OSInitStopwatch(lbl_80639228, &lbl_8064B2E8); fn_800248C0();
        lbl_8064C544 = 0; fn_80157504(strings + 0x70, strings + 0x7C, strings + 0x88); fn_800C96B4();
        lbl_8064C4F8 = fn_80157760(7, 0x62); fn_8011E234(lbl_8064C508, fn_80028098, fn_800280FC); fn_800E463C(); fn_801569A0(0); fn_800BC6D8(); fn_801F7C78();
        lbl_8064D180 = 0; lbl_8064C5DC = 0; lbl_8064C5E0 = 0; memset(lbl_80301D3C, 0, 0x2D0);
        fn_800721B0(); fn_802012F8(); fn_802012A0(0); fn_802014F0(0); fn_80204A14(0, 100);
        lbl_8064C548 = 0; lbl_8064C5AC = -1; lbl_8064C54C = 0; lbl_8064C550 = 0;
        fn_80034114(); fn_8002495C(); lbl_8064C6F8 = 0; fn_801A58FC(); lbl_8064C8E8 = 0; fn_8014447C(0);
        fn_801445EC(fn_8002476C); fn_801445F4(fn_8011B734, 0x2A30); fn_800069FC(); fn_80048A70(); fn_801E81E4(); fn_801A83A4(0x20);
        lbl_8064C53C = 0; lbl_8064C540 = 0; fn_8017FFC0(); fn_801D1054(12); fn_80149EFC(0x1C, 0x3C);
        fn_80188384(*(void **)(lbl_80606334 + 0x10), 0); fn_8001D4C4(); fn_8016B400(0x5DC, 0, 0); fn_801A7D20(); fn_801E8A0C(); fn_80113AB8();
        lbl_8064CCF4 = 0; fn_80117E60(); fn_80135510(); fn_80024B74(-1); fn_801F3F88(); fn_8006B21C(0);
        lbl_8064C5B0 = fn_80156DA0(4, 0); fn_801568B8(lbl_8064C5B0, fn_8002B688); fn_801EB07C(); fn_80125FE4(); fn_80125D88();
        fn_80125DC8(fn_80045DBC); fn_8007EDF0(); fn_80086218(); fn_80142944(); fn_801EBA58(lbl_8064D68C); fn_80008738();
        break;

    case 1: case 3: case 4: case 5: case 14:
        fn_800BD384(); fn_8015CB00(1); fn_8015AEB8(fn_80086B38, 0x15F, 1); fn_80138F78(1); fn_800432F4(); fn_8015CB00(0);
        fn_80045A24(0, 0); fn_8004736C(0); fn_801EF36C(0); fn_80047248(); fn_801EF35C(0); fn_801EF38C(0); fn_8015AA28(0);
        {
            int zero = 0;
            lbl_8064C4E4 = zero;
            ((volatile GameState *)&lbl_803003C8)->f4 =
                ((volatile GameState *)&lbl_803003C8)->f0 +
                (((volatile GameState *)&lbl_803003C8)->f8 = zero);
        }
        fn_80048620(0); fn_8001D9FC(0); fn_8017AE90();
        fn_801E7944(lbl_8064C4E0); fn_80024B78(); fn_80113AB8(); lbl_8064CCF4 = 0; fn_80117E60(); fn_8007EDF0(); fn_801EBA58(lbl_8064D68C); fn_80008738();
    case 9:
        lbl_8064CD34 = 0; fn_800BD384(); fn_801F5980();
        switch (mode) {
        case 9:
            fn_8015CB00(1); fn_8015AEB8(fn_80086B38, 0x15F, 2); fn_8015CB00(0); fn_8016AD28(); fn_80045A24(0, 0); fn_8001D9FC(1);
            { volatile GameState *reset = (volatile GameState *)&lbl_803003C8; lbl_8064D18C = lbl_8023D5B8[reset->f8]; }
            fn_801A7D44(); flag = 1;
            break;
        case 1: case 3: case 4: case 5: case 14:
            fn_801A94E4(lbl_8064C6E0, 0, 3, 0); fn_8016B3A4(strings + 0x94, 1); fn_8016B400(0x5DC, 0, 0); fn_800427E0(0);
            break;
        }
        fn_8004736C(0); fn_801EF36C(0); fn_80047248(); fn_801EF35C(0);
        strings = (char *)&lbl_803003C8;
        if (fn_801A94E4(lbl_8064C6E0, 1, (u8)fn_80052218(((volatile GameState *)strings)->f8), 0) != 0) {
            switch (mode) {
            case 9: fn_8015AEB8(fn_80086B38, 0x15F, 3); break;
            default: fn_8015AEB8(fn_80086B38, 0x15F, 1); break;
            }
            lbl_8064D18C = lbl_8023D5B8[((volatile GameState *)strings)->f8];
        }
        fn_801EF38C(0); fn_8015AA28(0); fn_8017D0D8(); fn_8011E234(lbl_8064C508, fn_80028098, fn_800280FC); fn_800E463C();
        lbl_8064C4F8 = fn_80157760(7, 0x62); fn_801569A0(1);
        lbl_8064C4F0 = 0; lbl_8064C53C = 0; lbl_8064C540 = 0; lbl_8064D180 = 0; lbl_8064C544 = 0; lbl_8064C4F4 = 0; lbl_8064C5DC = 0; lbl_8064C5E0 = 0;
        memset(lbl_80301D3C, 0, 0x2D0); fn_801F7C78(); fn_800721B0(); fn_802012F8(); fn_802012A0(1); fn_802014F0(1); fn_80204A14(1, 100);
        lbl_8064C548 = 0; lbl_8064C5AC = -1; lbl_8064C54C = 0; lbl_8064C550 = 0; fn_80034114();
        fn_801E79A0(lbl_8064C4E0, 0x29B); fn_801E79A0(lbl_8064C4E0, 0x29A); fn_801E79A0(lbl_8064C4E0, 0x48); fn_801E79A0(lbl_8064C4E0, 0x467);
        fn_801E81E4(); lbl_8064C5B0 = fn_80156DA0(4, 0); fn_801568B8(lbl_8064C5B0, fn_8002B688); lbl_8064C5A4 = 0; lbl_8064C6F8 = 0;
        fn_801A58FC(); lbl_8064C8E8 = 0; fn_8014447C(0); fn_800069FC(); fn_80048A70(); fn_801F3F88(); fn_8006B21C(flag); fn_80135510();
        fn_80125FE4(); fn_80125D88(); fn_80125DC8(fn_80045DBC); fn_80180C54(0xBE); fn_801A6F64(); fn_801A5910(0); fn_801801A4(); fn_801D1388(); fn_80149F9C(); fn_80018ED4(); fn_8015761C();
        if (mode == 9) fn_800AFC30(lbl_803003AC);
        break;

    case 2:
        fn_8002487C(fn_800474C8(), 1); fn_800BD384(); lbl_8064C7CC = -1; fn_80024D3C(1); fn_80139298(); fn_80042810(-1); fn_800432F4();
        lbl_8064D18C = -1; fn_8006B21C(0); fn_8004736C(0); fn_80047248(); fn_801EF35C(0); fn_801EF38C(0); fn_8015AA28(0); fn_80180C54(0xBE); fn_8001D9FC(9);
        break;

    case 10:
        fn_8010F404(); lbl_8064CD34 = 0; fn_8016AD28(); flag = fn_8002487C(fn_800474C8(), 1);
        if (flag != 0) { fn_80139298(); fn_80042810(-1); fn_800432F4(); lbl_8064D18C = -1; }
        fn_80024D3C(flag); fn_8006B21C(1); fn_8004736C(0); fn_80047248(); fn_801EF35C(0); fn_801EF38C(0); fn_8015AA28(0); fn_80200338(); fn_80180C54(0xBE);
        fn_800AFC30(lbl_803003AC); fn_800B0704((char *)&lbl_803003C8 + 0x14, 1); fn_8007EC28();
        fn_801FA198(fn_801E741C(strings + 0xA4), lbl_8063CD18 + 0x110, 0, 2, 0, 0, 0, 0, 0);
        lbl_803003C8.f1914 = 0; lbl_803003C8.f1916 = 0; fn_80025F48(); fn_80054758(lbl_803003C8.f4); fn_8016B400(0x764, 0, 0);
        break;
    }

    fn_800459A0(); fn_80026060(); fn_801A6E34(); fn_8011E87C(fn_8004919C); lbl_8064C59C = 0; fn_80024D08(); fn_801E5AE0();
    fn_8001E144(mode); fn_8015CA00(fn_80008134); fn_800A3570(); fn_801E79A0(lbl_8064C4E0, 0x22B);
}
