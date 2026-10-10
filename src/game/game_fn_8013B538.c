typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct TriggerObject {
    char pad00[0x68];
    int flags;              /* 0x68 */
    short type;             /* 0x6C */
    short value;            /* 0x6E */
    short active;           /* 0x70 */
    char pad72[2];
} TriggerObject;

typedef struct Mover {
    Vec3 prev;              /* 0x00 */
    Vec3 pos;               /* 0x0C */
    Vec3 delta;             /* 0x18 */
    float limit;            /* 0x24 */
} Mover;

extern int fn_801A7DFC(void);
extern int fn_8011EB04(void*);
extern void fn_8011F114(Vec3*, void*);
extern Vec3* fn_8011F130(void*);
extern void fn_8013B24C(void*, void*, int, void*, int, short*, int*, int, int);
extern void fn_8016B400(int, int, int);
extern int fn_80201BD0(void*);
extern void* lbl_8064C4E4;
extern int lbl_8064D18C;
extern float lbl_80650304;

void fn_8013B538(void* object, TriggerObject* item, unsigned short count, Mover* mover)
{
    int different;
    int mode;
    int i;
    int limit;
    int skip;
    int kind;
    short value;
    Vec3 saved;
    Vec3* cur;

    if (object == lbl_8064C4E4) {
        different = 0;
    } else {
        different = 1;
    }
    mode = different;

    if (fn_801A7DFC() != 0) {
        kind = 0;
        skip = 0;
        if (fn_8011EB04(object) == 2) {
            /* ASM: nop preserves a stripped debug breakpoint; an empty C branch is removed. */
            asm { nop }
        }
        limit = count;
        for (i = 0; i < limit; i++) {
            Vec3 pos;

            fn_8011F114(&pos, object);
            saved = pos;
            value = 0;
            kind = 0;
            fn_8013B24C(item, mover, mode, object, skip, &value, &kind, 1, 0);
            if (value > 0) {
                int phase = lbl_8064D18C;

                fn_8016B400(value, (int)item, fn_80201BD0(object));
                if (phase != lbl_8064D18C) {
                    return;
                }
                if (item->active != 0 && kind != 1) {
                    skip = 1;
                }
            }
            cur = fn_8011F130(object);
            if (cur->x != saved.x || cur->y != saved.y || cur->z != saved.z) {
                mover->prev = *cur;
                mover->pos = *cur;
                mover->limit = lbl_80650304;
                return;
            }
            item++;
        }
    } else {
        int mask = ~(1 << different);
        for (i = 0; i < count; i++) {
            item->flags &= mask;
            item++;
        }
    }
}
