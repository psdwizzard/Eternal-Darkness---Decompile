typedef int (*Fn80130428Callback)(int);

extern int fn_800460EC(void);
extern void fn_8004918C(void);
extern void fn_80049194(void);
extern int fn_800FBFB0(void);
extern int fn_8011EB04(int);
extern int fn_8011EB14(int);
extern int fn_80128EAC(void);
extern void fn_8012965C(int, int, int, int);
extern Fn80130428Callback fn_80130428(int);
extern void fn_80130434(int, int);
extern int fn_801A5CE0(void);
extern int fn_801A6D94(void);
extern int fn_801A77B0(void);
extern int fn_801D10B8(void);
extern void *fn_80201814(void);
extern void fn_80201A84(int);
extern int fn_80201B64(void *);
extern int lbl_8064D6EC;

int fn_800C2180(int obj, int mode) {
    Fn80130428Callback callback;
    void *entry;
    int level;
    int isSpecial;
    int notExcluded;
    int allowed;
    int anim;
    int state;
    int kind;
    int blocked;
    int result;
    int sound;

    result = 1;
    if (mode != 0) {
        if (fn_80128EAC() == 0xF) {
            fn_80201A84(obj);
            entry = fn_80201814();
            level = (unsigned char)fn_800FBFB0();
            isSpecial = fn_80201B64(entry) == 0x52;
            notExcluded = 1;
            if (fn_80201B64(entry) != 0x45 && fn_80201B64(entry) != 0x43) {
                notExcluded = 0;
            }
            if (level < 0xD && fn_800460EC() == 0 && lbl_8064D6EC == 0 &&
                fn_801A5CE0() != 0 && fn_801D10B8() == 0 && isSpecial == 0 &&
                notExcluded == 0) {
                allowed = 1;
                anim = 0x10;
                state = fn_8011EB14(obj);
                if (state == 5 || state == 2) {
                    allowed = 0;
                }
                if (level < 4) {
                    anim = 0x11;
                    allowed = 1;
                    kind = fn_8011EB04(obj);
                    blocked = kind == 0x55 || kind == 0x77 || kind == 0x78 || kind == 0x79 ||
                              kind == 0x7A || kind == 0x65 || kind == 0x90 || kind == 0x91 ||
                              kind == 0x92 || kind == 0x93 || kind == 0x8F || kind == 0x8E ||
                              kind == 0x51 || kind == 0x49 || kind == 0x4C || kind == 0x4A ||
                              kind == 0x96;
                    if (blocked != 0 || (state != 0 && state != 1)) {
                        allowed = 0;
                    }
                }
                if (allowed != 0) {
                    fn_8012965C(obj, anim, 0x20, 1);
                    result = 0;
                    callback = fn_80130428(obj);
                    if (callback != 0 && callback(obj) != 0) {
                        fn_80130434(obj, 1);
                    }
                }
            }
        }
    } else {
        fn_80049194();
        if (fn_801A6D94() != 0) {
            fn_8004918C();
            sound = fn_801A77B0();
        } else {
            sound = 0xF;
        }
        fn_8012965C(obj, sound, 0x21, 1);
    }
    return result;
}
