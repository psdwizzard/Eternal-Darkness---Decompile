typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void *fn_80201BC8(void *);
extern int fn_80201B5C(void *);
extern int fn_80201B64(void *);
extern int fn_801A7770(void *);
extern int fn_801A7570(void *);
extern u16 fn_801A7580(void *);
extern void *fn_801A7778(void *);
extern int fn_80157C80(void);
extern int fn_8004914C(void *);
extern int fn_800460EC(void);
extern void fn_800BED54(void *, void *, int *);
extern int fn_800C44C0(void *, void *, void *, Vec3 *, int *);
extern void fn_800C4718(void *, int, void *, Vec3 *);
extern int fn_8012F2DC(void *, const Vec3 *, int, int, int);
extern void fn_8011FA8C(void *, int, int);
extern void fn_800C438C(void *);
extern void fn_8012FB50(void *, int);
extern void fn_800C43AC(Vec3 *, void *);
extern Vec3 *fn_8011F130(void *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern u32 fn_8020499C(void *);
extern void fn_801225DC(void *, s8);

void fn_800C3FE4(void *self, void *other, void *event)
{
    int arg;
    int active;
    Vec3 goal;
    Vec3 pos;
    void *selfContext;
    void *otherContext;
    int handled;
    int target;
    u32 dist;
    u32 range;
    int kind;
    int type;
    int buttons;
    u32 flags;
    s8 dir;
    u32 special;
    void *source;

    otherContext = 0;
    dir = 2;
    special = 0;
    selfContext = fn_80201BC8(self);
    if (other != 0) {
        otherContext = fn_80201BC8(other);
    }
    if (otherContext != 0) {
        arg = fn_801A7770(event);
        fn_800BED54(other, event, &arg);
    }
    handled = fn_800C44C0(self, other, event, &goal, &active);
    flags = fn_801A7570(event) & 0x90018;
    source = fn_801A7778(event);
    buttons = fn_80157C80();
    if ((flags != 0 || (buttons & 0xA0)) && fn_801A7580(event) != 0) {
        target = fn_8004914C(event);
        if (handled != 0) {
            fn_800C4718(selfContext, target, event, &goal);
            fn_8012F2DC(selfContext, &goal, 1, target, 4);
        }
    }
    if (active != 0) {
        type = fn_80201B64(other);
        kind = fn_80201B5C(other);
        otherContext = fn_80201BC8(other);
        if (type != 8 && type != 0x1F && kind != 0x15 && fn_800460EC() == 0) {
            fn_8011FA8C(otherContext, 0, 0x40000);
            if (fn_80201B5C(other) == 0x50 || fn_80201B5C(other) == 0x55 || fn_80201B5C(other) == 0x39) {
                fn_800C438C(otherContext);
            }
            fn_8012FB50(otherContext, arg);
            if (flags != 0) {
                dir <<= 3;
            } else {
                fn_800C43AC(&pos, other);
                dist = fn_80178E94(fn_8011F130(selfContext), &pos);
                range = 0x76;
                if (source != 0) {
                    special = fn_8020499C(source);
                }
                if (special != 0) {
                    range = 0xDA;
                }
                if (dist < range) {
                    dir <<= 3;
                }
            }
            fn_801225DC(otherContext, dir);
        } else {
            fn_8011FA8C(otherContext, 0x40000, 0);
        }
    }
}
