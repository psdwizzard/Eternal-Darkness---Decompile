typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct QueryResult {
    unsigned char pad0[8];
    Vec3 position;
    unsigned char pad14[0x14];
} QueryResult;

extern Vec3 lbl_8023986C;

extern void *fn_80201B9C(void);
extern void *fn_80204844(void *, int);
extern void *fn_8006D444(void *);
extern int fn_8006D344(void *, int, int);
extern int fn_80088528(void *, Vec3 *);
extern void *fn_80201BC8(void *);
extern s32 fn_801A7770(void *);
extern u32 fn_801A7570(void *);
extern void *fn_801A7778(void *);
extern u32 fn_80157C80(void *);
extern s32 fn_8011F6A4(void *, s32, s32, s32, QueryResult *, s32);
extern int fn_8012FD1C(void *, s32, Vec3 *);
extern void fn_80049194(void);
extern int fn_801A6D94(void);
extern void fn_801A76C0(void *, s16 *, s16 *);
extern void fn_8012B690(void *, Vec3 *, Vec3 *);

int fn_800C44C0(void *object, void *target, void *actor, Vec3 *position, int *found)
{
    s16 dx;
    s16 dy;
    Vec3 offset;
    QueryResult result;
    s32 index;
    void *targetObject;
    u32 flags;
    u32 mask;
    int handled;
    void *context;
    int done;

    index = -1;
    targetObject = 0;
    flags = 0;
    handled = 0;
    done = 0;
    *found = 0;

    context = fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
    if (fn_8006D344(context, 0xC0, 0) != 0 && fn_80088528(context, position) != 0) {
        done = 1;
        handled = 1;
    }

    if (done == 0) {
        if (target != 0) {
            targetObject = fn_80201BC8(target);
            if (targetObject != 0) {
                index = fn_801A7770(actor);
            }
        }

        mask = (fn_801A7570(actor) & 0x90038) != 0;
        if (index != -1) {
            flags = fn_80157C80(fn_801A7778(actor));
            *found = 1;
            if (mask != 0 || (flags & 0xA0)) {
                if (fn_8011F6A4(targetObject, 0, index, -1, &result, 1) != -1) {
                    handled = 1;
                    *position = result.position;
                } else if (fn_8012FD1C(targetObject, index, &result.position) != 0) {
                    handled = 1;
                    *position = result.position;
                }
            }
        }

        if (handled == 0 && (mask != 0 || (flags & 0xA0))) {
            offset = lbl_8023986C;
            fn_80049194();
            if (fn_801A6D94() != 0) {
                fn_801A76C0(actor, &dx, &dy);
                offset.x -= (float)(dx * 4);
                offset.z += (float)(dy * 4);
            }
            fn_8012B690(fn_80201BC8(object), &offset, position);
            handled = 1;
        }
    }
    return handled;
}
