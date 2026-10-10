#include "src/game/types.h"

extern void OSReport(const char *fmt, ...);
extern void fn_80053048(s32 frame);
extern int fn_800ED790(void);
extern void fn_800EE468(void);
extern void fn_801091B0(void *state);
extern int fn_80109628(void *state);
extern void fn_801A8D38(s32);
extern void fn_801A99B4(void);
extern void fn_801E3AA4(s32);
extern void fn_801E5430(s32, s32);
extern void fn_801E56AC(float scale, const char *format, ...);
extern void fn_801E5FE4(void);
extern void fn_801EB194(s32);
extern void fn_801F3158(s32);
extern void fn_801F3240(void);
extern void fn_801F35A8(void);
extern void fn_801F55A0(void);
extern void fn_80226D28(s32);
extern s32 fn_8023657C(void);
extern s32 fn_802365D4(void);

typedef struct GameState {
    u8 pad[0x150];
    s32 start_time;
} GameState;

extern char lbl_8024A620[];
extern char *lbl_8064B82C;
extern volatile s32 lbl_8064C600;
extern s32 lbl_8064CB64;
extern s32 lbl_8064CC08;
extern GameState *lbl_8064CC14;
extern s32 lbl_8064CC20;
extern s32 lbl_8064D780;
extern float lbl_8064F904;

int fn_800EE8F8(void) {
    char *strings = lbl_8024A620;
    int frame;
    u32 status;
    s32 elapsed;
    s32 total;
    s32 secs;
    s32 mins;
    s32 hours;
    s32 emins;
    s32 ehours;

    frame = fn_800ED790();
    if (lbl_8064CC20 == 0) {
        OSReport(strings + 0x100);
        fn_800EE468();
        return 0;
    }
    status = fn_80109628(lbl_8064CC14);
    if ((status & 0x80000000) && (status & 0x20000000)) {
        fn_800EE468();
        return 0;
    }
    if (status == 4) {
        fn_800EE468();
        return 0;
    }
    fn_801091B0(lbl_8064CC14);
    fn_801A99B4();
    fn_801A8D38(6);
    fn_801F3158(1);
    fn_801F3240();
    fn_801F55A0();
    elapsed = fn_802365D4() - lbl_8064CC14->start_time;
    total = fn_800ED790();

    secs = total / 30;
    mins = secs / 60;
    emins = elapsed / 60;
    ehours = emins / 60;
    total = total - secs * 30;
    secs = secs - mins * 60;
    elapsed = elapsed - emins * 60;
    emins = emins - ehours * 60;

    if (lbl_8064CB64 != 0) {
        fn_801E3AA4(0);
        fn_801E5430(10, 50);
        fn_801E56AC(lbl_8064F904, strings + 0x11C, ehours, emins, elapsed >> 1);
        fn_801E56AC(lbl_8064F904, strings + 0x13C, mins, secs, total);
        fn_801E56AC(lbl_8064F904, strings + 0x15C, lbl_8064B82C);
    }

    for (secs = lbl_8064CC08; secs <= frame; secs++) {
        fn_80053048(secs);
    }
    lbl_8064CC08 = frame;

    fn_801E5FE4();
    fn_801F35A8();
    fn_80226D28(1);
    if (fn_8023657C() != 0 && lbl_8064C600 <= 0) {
        lbl_8064C600 = 2;
    }
    if (lbl_8064C600 <= 0 || lbl_8064D780 != 0) {
        fn_801EB194(1);
        lbl_8064C600 = 0;
    } else {
        fn_801EB194(0);
    }
    if (lbl_8064C600 > 0) {
        lbl_8064C600--;
    }
    return 1;
}
