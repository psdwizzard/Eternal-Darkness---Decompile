typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Runtime {
    unsigned char pad50[0x50];
    void *link;
    unsigned char pad8c[0x38];
    void *resource;
} Runtime;
typedef struct Wrapper { void *object; } Wrapper;

extern int lbl_8064C55C, lbl_8064C56C, lbl_8064D18C;
extern float lbl_8064EC10, lbl_8064EC28, lbl_8064EC50, lbl_8064EC54;

extern int fn_80036E50(void *);
extern int fn_800460EC(void);
extern void fn_80048708(Vec3 *);
extern void fn_80068994(void *, int);
extern void fn_80072618(Vec3 *, Vec3 *, int, int);
extern void fn_8008F064(void *, void *, void *, Vec3 *, void *, void *, void *);
extern void fn_8008F5B4(void *, void *, void *, Vec3 *, void *, void *, void *, void *, void *, void *);
extern void fn_8008F860(void *);
extern void fn_800902D0(void *, void *, void *, void *, void *, void *, void *);
extern void fn_8009050C(void *, void *, void *, void *, void *, void *, void *);
extern void fn_8009073C(void *, void *, void *);
extern Wrapper *fn_800BC100(int, int, int *, int, int, int, int);
extern void fn_800BCCC4(void *, Vec3 *);
extern int fn_800BCE94(void *, int);
extern int fn_800BD2DC(void *, void *);
extern void fn_800BDEE4(void *, void *);
extern void fn_800BE010(void *, void *);
extern void fn_800BE8D4(int);
extern int fn_800C9E50(void *);
extern int fn_800DD284(void);
extern int fn_800DE298(void *);
extern void fn_800DE468(int);
extern void fn_800DE648(void *, Vec3, void *);
extern void fn_800DFD54(int, void *, void *, void *);
extern void fn_8011F0E8(Vec3 *, Vec3 *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern unsigned int fn_8011FA8C(void *, unsigned int, unsigned int);
extern unsigned int fn_8011FAEC(void *);
extern void fn_8011FB54(void *, void *);
extern void fn_801261F4(void *);
extern unsigned short fn_8012DBE8(unsigned char *, unsigned int, unsigned char *);
extern void fn_801A7228(void *);
extern int fn_801AAE68(unsigned short, unsigned char, unsigned char, float,
                       Vec3 *, signed char, unsigned char, unsigned char,
                       unsigned short, unsigned int);
extern int fn_801E8328(unsigned int, unsigned int);
extern float fn_80200534(int, int, int);
extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern void *fn_80200C38(void *);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_80201138(int, void *, int, int, int, float);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void *fn_80201814(int);
extern void *fn_80201B3C(void);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern Runtime *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C48(void *);
extern void fn_80201D1C(void *, unsigned char);
extern void fn_80201D34(void *, int);
extern void fn_80201E78(Vec3 *, void *);
extern int fn_80201EB8(void *);

int fn_800907FC(void *object, int action, void *event, int *result)
{
    Vec3 position;
    Vec3 destination;
    Vec3 collision;
    Vec3 launch_position;
    Vec3 return_position;
    Vec3 target_position;
    Vec3 fallback;
    Vec3 source;
    unsigned char state[4];
    unsigned char other_state[4];
    int id;
    int found;
    Wrapper *wrapper;
    Runtime *runtime;
    void *link;
    void *resource;
    void *secondary;
    void *primary;
    int owner;
    int kind;
    int associated;

    kind = fn_80200C10(event);
    primary = fn_80201BC8(object);
    runtime = fn_80201B8C(object);
    link = runtime->link;
    resource = runtime->resource;
    secondary = fn_80201B94(object);
    owner = fn_80201B54(object);
    fn_8011F114(&position, (Vec3 *)primary);
    associated = fn_80201EB8(object);

    if (kind == 3) {
        if (fn_8011FAEC(primary) & 0x10) {
            fn_8011FA8C(primary, 0x10, 0);
            ((unsigned char *)runtime->resource)[0x167]++;
        }
            fn_8012DBE8((unsigned char *)primary, 15, state);
        if (state[3] < 20) {
            fn_800BE8D4(owner);
        }
    }

    if (action == 0) {
        if (kind == 1) {
            fn_800902D0(object, primary, event, resource, secondary, runtime, link);
            return 1;
        }
        if (kind == 0x39) {
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, (unsigned int)object);
            return 1;
        }
        if (kind == 0x1B) {
            fn_800DFD54(1, object, primary, event);
            return 1;
        }
        if (kind == 0x3B) {
            int value = fn_80200C20(event);
            void *entity = fn_80201814(value);
            fn_8012DBE8((unsigned char *)primary, 15, other_state);
            if (other_state[3] > 20 && value == fn_80201B44() &&
                fn_80036E50(entity) != 6 && result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x17) {
            fn_8009050C(object, primary, event, resource, secondary, runtime, link);
            return 1;
        }
        if (kind == 0x3E) {
            lbl_8064C56C = 0;
            launch_position = position;
            fn_8008F5B4(object, primary, (void *)owner, &launch_position, link,
                            secondary, event, runtime, resource,
                            (void *)lbl_8064D18C);
            fn_800C9E50(object);
            if (fn_800DE298(object)) {
                fn_801261F4(primary);
                fn_8020123C(0x1B, owner, owner, 1);
            }
            return 1;
        }
        if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event),
                            (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event),
                            (int)fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        }
        if (kind == 0xB) {
            if (fn_800460EC() == 0) {
                fn_80201D34(object, 9);
                fn_80201D1C(object, 1);
                if (result != 0) *result = 0;
            }
            return 1;
        }
        if (kind == 0xC9) {
            float intensity;
            fn_8011FA8C(primary, 0, 0x20000000);
            intensity = lbl_8064EC28;
            fn_801AAE68(0x1F1, 100, 0, intensity, &position,
                          2, 2, 0, (unsigned short)lbl_8064D18C, 0);
            return 1;
        }
        if (kind == 0xE) {
            fn_80068994(object, (int)event);
            return 1;
        }
        if (kind == 0x27) {
            if (fn_800460EC() == 0) {
                fn_80201D34(object, 9);
                fn_80201D1C(object, 1);
            }
            return 1;
        }
        if (kind == 0xE6) {
            if (fn_800460EC() == 0) {
                fn_80201D34(object, 9);
                fn_80201D1C(object, 1);
            }
            return 1;
        }
        if (kind == 0x35) {
            if (fn_800460EC() == 0) {
                fn_80201D34(object, 9);
                fn_80201D1C(object, 1);
            }
            return 1;
        }
        if (kind == 0x3D) {
            lbl_8064C56C = 0;
            fn_800BD2DC(object, resource);
            if (lbl_8064EC10 == fn_80200534(owner, -1, 0x17)) {
                fn_8008F860((void *)owner);
                fn_8020104C(0x17, owner, owner, -1, lbl_8064EC50);
            }
            return 1;
        }
        if (kind == 0x7B) {
            fn_8009073C(object, primary, event);
            return 1;
        }
        goto unhandled;
    }
    if (action == 1) {
        if (kind == 3) {
            void *entity;
            entity = fn_80201814((int)fn_80201C48(secondary));
            if (entity && lbl_8064C55C && associated == lbl_8064D18C) {
                return_position = position;
                fn_800DE648(primary, return_position, entity);
            }
            return 1;
        }
        goto unhandled;
    }
    if (action == 0x39) {
        if (kind == 0x17) {
            if (lbl_8064D18C == 0xEC || lbl_8064D18C == 0x53) {
                fn_80201138(0x17, object, 0x39, 0x49, 0, lbl_8064EC54);
            } else {
                fn_80201E78(&source, fn_80201B3C());
                found = 0;
                destination = source;
                id = fn_800DD284();
                if (id != -1) {
                    wrapper = fn_800BC100(0, 0, &id, 0x10, 0, 0, 0);
                    if (wrapper && wrapper->object) {
                        fn_800BCCC4(wrapper->object, &collision);
                        found = 1;
                    }
                }
                if (found == 0) {
                    fn_80072618(&destination, &collision, 0xC8, 2);
                }
                fn_8011F0E8((Vec3 *)primary, &collision);
                fn_8011FB54(primary, (void *)lbl_8064D18C);
                fn_80048708((Vec3 *)primary);
                fn_800DE468(1);
                fn_80201D34(object, 9);
                fn_80201D1C(object, 1);
                if (fn_800DE298(object)) {
                    fn_801261F4(primary);
                    fn_800DFD54(1, object, primary, 0);
                }
            }
            return 1;
        }
        if (kind == 0x3D) return 1;
        if (kind == 0x3E) return 1;
        if (kind == 0x1B) return 1;
        if (kind == 0x7B) return 1;
        goto unhandled;
    }
    if (action == 3) {
        if (kind == 3) {
            void *entity;
            entity = fn_80201814((int)fn_80201C48(secondary));
            if (entity && lbl_8064C55C && associated == lbl_8064D18C) {
                target_position = position;
                fn_800DE648(primary, target_position, entity);
            } else {
                fn_800BE010(object, resource);
                fn_800BDEE4(object, resource);
                fn_800BCE94(object, 10);
                fallback = position;
                fn_8008F064(object, primary, (void *)owner, &fallback, link,
                                secondary, event);
            }
            return 1;
        }
        return 0;
    }
unhandled:
    return 0;
}
