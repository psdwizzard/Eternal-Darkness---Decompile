typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern int fn_80200C10(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201B94(void *);
extern int fn_80201B54(void *);
extern void fn_8011F114(Vec3 *, void *);
extern u32 fn_80201CCC(void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, u8);
extern void fn_80201CE8(void *, u32, u32);
extern void *fn_8011F950(void *);
extern u8 *fn_801294DC(void *, int, int, int);
extern int fn_800DE354(void);
extern void *fn_80201814(int);
extern int fn_80201EB8(void *);
extern void fn_80201E78(void *, void *);
extern int fn_80179004(const float *, const float *);
extern void fn_80201DE8(void *, void *);
extern void fn_80201DF0(void *, void *);
extern int fn_8012A100(void *, int);
extern int fn_80128EAC(void *);
extern int fn_8012A1BC(void *, int);
extern void fn_80129FD0(void *, int, int);
extern void fn_80128A84(void *, u16, u32);
extern void *fn_80201C84(void *);
extern void fn_801287C4(void *, void *, u32, u32);
extern int fn_80204810(void *, int);
extern void fn_801B0DD4(int);
extern u16 fn_8004A608(u32, int, u8 *, u8 *, u16 *, u32 *);
extern int fn_801B08BC();
extern int fn_8012A1FC(void *, int);
extern int lbl_8064D18C;

int fn_800DDAD0(void *context, int phase, void *message)
{
    void *queue;
    int kind;
    void *owner;
    void *object;
    int id;
    Vec3 position;

    kind = fn_80200C10(message);
    object = fn_80201BC8(context);
    owner = fn_80201B94(context);
    id = fn_80201B54(context);
    fn_8011F114(&position, object);

    if (phase == 0) {
        if (kind == 1) {
            if (fn_80201CCC(owner) & 0x80) {
                fn_80201D2C(context, 13);
                fn_80201D14(context, 1);
                fn_80201CE8(context, 0x80, 0);
            } else {
                fn_80201D2C(context, 14);
                fn_80201D14(context, 1);
            }
            return 1;
        }
    } else if (phase == 14) {
        if (kind == 1) {
            if (fn_8011F950(object) != 0)
                fn_801294DC(object, 27, 33, 8);
            return 1;
        }
        if (kind == 18) {
            fn_80201D2C(context, 15);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 3) {
            void *other = fn_80201814(fn_800DE354());
            if (other != 0 && lbl_8064D18C == fn_80201EB8(other)) {
                Vec3 copy;
                Vec3 target;
                fn_80201E78(&target, other);
                copy = target;
                if ((u32)fn_80179004((const float *)&position, (const float *)&copy) < 200) {
                    fn_80201D2C(context, 15);
                    fn_80201D14(context, 1);
                }
            }
            return 1;
        }
    } else if (phase == 13) {
        if (kind == 1) {
            if (fn_8011F950(object) != 0)
                fn_801294DC(object, 26, 33, 8);
            return 1;
        }
        if (kind == 19) {
            fn_80201DE8(owner, 0);
            fn_80201DF0(owner, 0);
            fn_80201D2C(context, 16);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 62) {
            if (fn_8012A100(object, 26) != 0) {
                queue = fn_801294DC(object, 26, 33, 8);
                if (queue != 0) {
                    int value;
                    fn_80128EAC(object);
                    value = fn_8012A1BC(object, 26);
                    fn_80129FD0(object, value << 17, 0);
                    fn_80128A84(queue, 0, value);
                }
            }
            return 1;
        }
    } else if (phase == 15) {
        if (kind == 1) {
            void *queue = fn_801294DC(object, 25, 32, 8);
            if (queue != 0) {
                int value = fn_8012A1BC(object, 25);
                fn_80201C84(owner);
                fn_801287C4(queue, fn_80204810, (id << 8) | 20, value);
                fn_801B0DD4((int)object);
            } else {
                fn_80201D2C(context, 14);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 61) {
            u32 flags;
            u16 handle = fn_8004A608((u32)object, 75, 0, 0, 0, &flags);
            if (handle != 0xFFFF && (flags & 0x10))
                fn_801B08BC(-1, handle, 0);
            return 1;
        }
        if (kind == 20) {
            fn_80201D2C(context, 13);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 21) {
            fn_80201D2C(context, 14);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (phase == 16) {
        if (kind == 1) {
            void *queue = fn_801294DC(object, 25, 34, 8);
            if (queue != 0) {
                fn_801287C4(queue, fn_80204810, (id << 8) | 21, fn_8012A1FC(object, 25));
            } else {
                fn_80201D2C(context, 13);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 20) {
            fn_80201D2C(context, 13);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 21) {
            fn_80201D2C(context, 14);
            fn_80201D14(context, 1);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
