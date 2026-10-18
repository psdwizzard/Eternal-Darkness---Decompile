typedef struct Object Object;
typedef struct Entry80201814 Entry80201814;

typedef int (*Fn80130428Callback)(void *);

extern int fn_800460EC(void);
extern void *fn_8004918C(void);
extern void *fn_80049194(void);
extern unsigned int rand(void);
extern int fn_8011EB04(Object *);
extern int fn_8011EB14(Object *);
extern int fn_80128EAC(void *);
extern unsigned char *fn_8012965C(void *, int, int, int);
extern void *fn_80130428(Object *);
extern void fn_80130434(Object *, int);
extern int fn_801A5CE0(void);
extern int fn_801A6D94(void *);
extern unsigned int fn_801A77B0(void *);
extern int fn_801D10B8(void);
extern Entry80201814 *fn_80201814(int);
extern int fn_80201A84(void *);
extern int fn_80201B64(int *);
extern int lbl_8064D6EC;

int fn_800C2180(void *object, int mode) {
    int sound;
    Object *obj;
    int notExcluded;
    int result;
    int state;
    int kind;
    int blocked;
    int anim;
    int isSpecial;
    int level;
    Entry80201814 *entry;
    Fn80130428Callback callback;
    int allowed;

    obj = object;
    result = 1;
    if (mode != 0) {
        if (fn_80128EAC(obj) == 0xF) {
            entry = fn_80201814(fn_80201A84(obj));
            level = rand() & 0xFF;
            isSpecial = fn_80201B64((int *)entry) == 0x52;
            notExcluded = 1;
            if (fn_80201B64((int *)entry) != 0x45 && fn_80201B64((int *)entry) != 0x43) {
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
                    callback = (Fn80130428Callback)fn_80130428(obj);
                    if (callback != 0 && callback(obj) != 0) {
                        fn_80130434(obj, 1);
                    }
                }
            }
        }
    } else {
        if (fn_801A6D94(fn_80049194()) != 0) {
            sound = fn_801A77B0(fn_8004918C());
        } else {
            sound = 0xF;
        }
        fn_8012965C(obj, sound, 0x21, 1);
    }
    return result;
}
