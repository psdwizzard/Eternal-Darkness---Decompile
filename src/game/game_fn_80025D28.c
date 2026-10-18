typedef signed char s8;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct GameState {
    u8 pad_0000[0x10];
    u32 flags;
    u8 pad_0014[0x1908];
    s32 field_191C;
} GameState;

extern GameState lbl_803003C8;
extern char lbl_8063BEC0[];

extern s32 lbl_8064C644;
extern s32 lbl_8064C64C;
extern s32 lbl_8064C6D8;
extern s32 lbl_8064CA60;
extern s32 lbl_8064CA64;
extern s32 lbl_8064CBA0;
extern s32 lbl_8064CBA4;
extern s32 lbl_8064D294;
extern void* lbl_8064D74C;

extern s32 fn_8001E13C(void);
extern void fn_80024F28(s32);
extern void fn_80025AA4(void);
extern u8 fn_80045230(void);
extern s32 fn_80144470(s32);
extern void fn_8017AF44(void);
extern void fn_8017B294(s32);
extern s32 fn_8017BB60(void);
extern void fn_801A9758(void);
extern void fn_801A9A40(s32, s32, s32);
extern u8 fn_801A9B30(void);
extern void fn_801AC350(s32, s32, s32);
extern void DTKShutdown(void);
extern void fn_801EFE84(int);
extern void fn_801EF530(void);
extern void fn_801EF580(void*);
extern void OSSendMessage(void*, s32, s32);
extern void DVDCancelAll(void);
extern s32 DVDCheckDisk(void);
extern void VIWaitForRetrace(void);
extern void VIFlush(void);
extern void PADRecalibrate(void*);
extern void __GXAbortWaitPECopyDone(void);
extern void GXSetDrawSync(s32);
extern void GXSetDrawDone(void);
extern void fn_80237D84(void);
extern void OSResetSystem(s32, s32, s32);

void fn_80025D28(void)
{
    volatile s8* boot = (volatile s8*)0x81200000;

    if (lbl_8064C6D8 == 1 || lbl_8064C6D8 == 13 || lbl_8064C6D8 == 11) {
        __GXAbortWaitPECopyDone();
        PADRecalibrate((void*)0x80000000);

        while (fn_8017BB60() == 5 || fn_8017BB60() == 6) {
            fn_8017AF44();
        }

        if (lbl_8064CA60 != 0 && --lbl_8064CA60 <= 0) {
            lbl_8064CA60 = 0;
            lbl_8064CA64 = 0;
        }

        fn_8017B294(0);
        fn_8017B294(1);
        boot[-4] = fn_801A9B30();
        boot[-3] = fn_8001E13C();
        *(volatile s32*)(boot - 0x10) = fn_80144470(1);
        boot[-2] = lbl_8064C644;
        fn_801A9A40(0x3C0, 0, 0);
        fn_80237D84();
        fn_801AC350(60, 0, 0);
        fn_80025AA4();
        fn_801AC350(0, 0, 0);
        lbl_8064C64C++;

        if (fn_8001E13C() == 0) {
            lbl_8064C6D8 = 0;
        }

        *(volatile s32*)(boot - 0x14) = lbl_8064C6D8;
        boot[-8] = lbl_8064CBA4;
        if ((lbl_803003C8.flags & 1) != 0) {
            boot[-7] = 1;
        } else {
            boot[-7] = 0;
        }
        boot[-6] = lbl_8064D294;
        boot[-5] = lbl_8064CBA0;
        boot[-1] = fn_80045230();
        *(volatile s32*)(boot - 0xC) = lbl_803003C8.field_191C;
        fn_801EFE84(1);
        VIWaitForRetrace();
        VIFlush();
        fn_801A9758();
        VIWaitForRetrace();
        DVDCancelAll();
        DTKShutdown();

        if (DVDCheckDisk() == 0) {
            OSResetSystem(1, 0, 0);
        } else {
            OSResetSystem(0, 0, 0);
        }
    } else {
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        GXSetDrawDone();
        GXSetDrawSync(0xBEEF);
        OSSendMessage(lbl_8063BEC0, 0, 1);
    }

    fn_80024F28(lbl_8064C6D8);
    lbl_8064C6D8 = 1;
}
