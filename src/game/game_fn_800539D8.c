typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct TransitionState {
    u8 pad000[0x1C8];
    s32 elapsed;
    s32 offset;
    u8 pad1D0[6];
    s16 selection;
    s8 countdown;
    s8 next;
    u8 type;
    u8 pad1DB[3];
    s8 delayed;
    u8 pad1DF[5];
    s8 cancel;
} TransitionState;

typedef struct TransitionDescriptor {
    u8 pad00[0x20];
    s16 restore;
    u8 pad22[6];
} TransitionDescriptor;

typedef struct TransitionData {
    u8 pad000[0x618];
    TransitionDescriptor descriptors[1];
} TransitionData;

extern TransitionState lbl_8030F540;
extern TransitionData lbl_802417D0;
extern u8 lbl_806391F0[];
extern u8 lbl_80639228[];
extern void* lbl_8064D74C;
extern s32 lbl_8064C84C;
extern s32 lbl_8064C854;
extern volatile s32 lbl_8064C600;
extern void* lbl_8064C85C;
extern void* lbl_8064C4E4;
extern s32 lbl_8064D6E8;
extern void* lbl_8064D6EC;
extern s32 lbl_8064D6C4;
extern s32 lbl_8064CB64;
extern s32 lbl_8064C850;
extern float lbl_8064E4CC;
extern float lbl_8064E4D8;

extern void fn_80045A24(s32, s32);
extern void fn_800B9474(s32);
extern void fn_800243E8(void);
extern void fn_801EF530(void);
extern s32 fn_801F3B80(void);
extern void fn_801EF580(void*);
extern void fn_801F59A0(void);
extern void fn_801EC9E4(void);
extern void fn_80024434(void);
extern void fn_8014426C(void);
extern void fn_8015CA08(void);
extern void fn_80156E50(s32);
extern void fn_8014B610(void);
extern void fn_801237F0(s32);
extern void fn_8018807C(float, float);
extern void fn_80029358(void);
extern void fn_80131460(void);
extern void fn_80156EBC(void);
extern void fn_801F7234(s32);
extern void fn_80200E1C(void);
extern void fn_800E4B1C(void);
extern void fn_8013196C(void);
extern s32 fn_80133300(void);
extern void fn_80008154(void);
extern void fn_801A99B4(void);
extern s32 fn_800EB744(void);
extern void fn_80144C4C(void*);
extern void fn_801E83A8(void);
extern void fn_8015C194(void*);
extern void fn_801A8D38(s32);
extern void fn_801F3158(void*);
extern void fn_801F3240(void);
extern void fn_801F55A0(void);
extern void fn_801F35A8(void);
extern void fn_801F33E8(void);
extern s32 fn_802365D4(void);
extern void fn_801313EC(s32*, s32*, s32*);
extern s32 fn_802365C0(void);
extern void fn_801E3AA4(s32);
extern void fn_801E5430(s32, s32);
extern void fn_801E56AC(void*, s32, s32, s32, ...);
extern void fn_801E5FE4(void);
extern void fn_800EB74C(void);
extern void fn_80053600(s16, s32);
extern void fn_80027F10(void);
extern void fn_80156B1C(s32);
extern void fn_801571C4(void);
extern void fn_80024468(void);
extern s32 fn_8023657C(void);
extern void fn_80132D50(void);
extern void fn_801EB194(s32);
extern s32 fn_800473A4(void);
extern s32 fn_80047364(void);
extern void fn_8004736C(void);
extern u32 fn_8022658C(void);
extern void fn_8005391C(s16, s32);
extern void fn_8020F088(void*);
extern void fn_8020EFBC(void*);
extern void fn_8020F0F8(void*);
extern void fn_8020EF80(void*);

void fn_800539D8(void)
{
    s32 stamp;
    s32 delta;
    s32 third;
    s32 second;
    s32 first;
    s32 new_stamp;
    s32 current;
    TransitionData* base = &lbl_802417D0;

    if (lbl_8030F540.cancel == 1) {
        u8 type = lbl_8030F540.type;
        TransitionDescriptor* descriptors = base->descriptors;
        descriptors += type;
        if (descriptors->restore == -1) {
            lbl_8030F540.cancel = 0;
            fn_80045A24(0, 0);
            fn_800B9474(0x7F);
            return;
        }
    }

    fn_800243E8();
    fn_801EF530();
    stamp = fn_801F3B80();
    fn_801EF580(lbl_8064D74C);
    fn_801F59A0();
    fn_801EC9E4();
    fn_80024434();
    fn_8014426C();
    fn_8015CA08();
    fn_80156E50(1);
    fn_8014B610();
    fn_80156E50(0);
    fn_801237F0(0);
    fn_8018807C(lbl_8064E4CC, lbl_8064E4CC);
    fn_80029358();
    fn_80131460();
    fn_80156EBC();
    if (lbl_8030F540.selection == -1) {
        fn_801F7234(3);
    } else {
        fn_801F7234(1);
    }
    fn_80200E1C();
    fn_801EC9E4();
    fn_800E4B1C();
    fn_8013196C();
    if (lbl_8030F540.elapsed > -2) {
        delta = fn_80133300();
    }
    lbl_8064C854 = 1;
    if (lbl_8064C84C > 3 && lbl_8064C600 == 0) {
        if (stamp == 0 && delta != 0) {
            fn_80008154();
        }
    } else {
        lbl_8064C84C++;
    }
    fn_801A99B4();
    if (fn_800EB744() == 0) {
        fn_80144C4C(lbl_8064C85C);
    }
    fn_801E83A8();
    fn_8015C194(lbl_8064C4E4);
    lbl_8064D6E8 = 1;
    fn_801A8D38(6);
    fn_801F3158(lbl_8064D6EC);
    fn_801F3240();
    fn_801F55A0();
    fn_801F35A8();
    if (lbl_8064D6C4 != 0) {
        lbl_8064D6C4 = 0;
        fn_801F33E8();
    }
    new_stamp = fn_802365D4();
    fn_801313EC(&third, &second, &first);
    stamp = new_stamp;
    if (fn_802365C0() != 0) {
        delta = stamp - (lbl_8030F540.elapsed + lbl_8030F540.offset);
    } else {
        delta = 0;
    }
    if (lbl_8064CB64 != 0) {
        s32 minutes;
        s32 hours;
        fn_801E3AA4(0);
        fn_801E5430(10, 50);
        fn_801E56AC((u8*)base + 0x2208, stamp, lbl_8030F540.elapsed,
                    lbl_8030F540.offset, lbl_8064E4D8);
        minutes = stamp / 60;
        hours = minutes / 60;
        fn_801E56AC((u8*)base + 0x221C, hours, minutes - hours * 60,
                    (stamp - minutes * 60) >> 1, lbl_8064E4D8);
        fn_801E56AC((u8*)base + 0x223C, first, second, third,
                    lbl_8064E4D8);
    }
    if (delta > 0 && fn_802365C0() != 0) {
        lbl_8064C850 = delta;
    } else if (delta < -2) {
        lbl_8064C850 = -1;
    }
    fn_801E5FE4();
    fn_800EB74C();
    if (lbl_8030F540.delayed == 1 && lbl_8030F540.elapsed > 180 &&
        lbl_8030F540.selection != -1) {
        lbl_8030F540.delayed = 0;
        fn_80053600(1, 0);
    }
    lbl_8064D6E8 = 0;
    fn_80027F10();
    fn_80156B1C(0);
    fn_801571C4();
    fn_800B9474(0x7F);
    fn_80024468();
    if (fn_8023657C() != 0) {
        fn_80132D50();
        if (lbl_8064C600 <= 0) {
            lbl_8064C600 = 2;
        }
    }
    if (lbl_8064C600 > 0) {
        lbl_8064C600--;
        fn_801EB194(0);
    } else {
        fn_801EB194(1);
    }
    stamp = fn_800473A4();
    current = fn_80047364();
    if (current != stamp) {
        fn_80047364();
        fn_8004736C();
    }
    if (lbl_8030F540.countdown != -1) {
        if (lbl_8030F540.countdown == 0) {
            lbl_8030F540.countdown = -1;
            while ((fn_8022658C() & 0xFFFF) != 0xBEEF) {
            }
            fn_8005391C(lbl_8030F540.next, 0);
        } else {
            lbl_8030F540.countdown--;
        }
    }
    fn_8020F088(lbl_806391F0);
    fn_8020EFBC(lbl_806391F0);
    fn_8020F0F8(lbl_806391F0);
    fn_8020EFBC(lbl_80639228);
    fn_8020F0F8(lbl_80639228);
    fn_8020EF80(lbl_80639228);
}
