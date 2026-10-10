typedef signed int s32;
typedef unsigned int u32;
#define NULL ((void *)0)

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct QueryResult {
    s32 word0;
    s32 word4;
    Vec3 position;
    unsigned char pad14[0x14];
} QueryResult;

extern s32 fn_801A7498(void *);
extern s32 fn_801A7490(void *);
extern void *fn_80201814(s32);
extern u32 fn_801A7570(void *);
extern s32 fn_801A7468(void *);
extern s32 fn_8011F6A4(void *, s32, s32, s32, QueryResult *, s32);
extern Vec3 fn_801A75C0(void *, s32, Vec3 *);
extern s32 fn_8003BAD8(void *, void *);

s32 fn_8003B8A0(void *self, void *target) {
    u32 flags;
    s32 type;
    s32 firstA;
    s32 firstB;
    s32 secondA;
    s32 secondB;
    s32 first;
    s32 second;
    void *object;

    first = fn_801A7498(target);
    second = fn_801A7490(target);
    object = fn_80201814(first);
    fn_80201814(second);
    if (object != NULL) {
        flags = fn_801A7570(target);
        if ((flags & 0x80) != 0 || (flags & 0x100) != 0) {
            QueryResult result;

            type = fn_801A7468(target);
            if (type == 4 && (flags & 0x80) != 0) {
                secondB = 3;
                firstB = 3;
                firstA = 3;
                secondA = 2;
            } else if (type == 5 && (flags & 0x80) != 0) {
                secondB = 2;
                firstB = 2;
                firstA = 3;
                secondA = 2;
            } else if (type == 6 && (flags & 0x80) != 0) {
                firstB = 3;
                secondB = 2;
                firstA = 2;
                secondA = 2;
            } else if (type == 0x19) {
                secondB = -1;
                firstB = -1;
                firstA = 3;
                secondA = 2;
            } else {
                secondB = 8;
                firstB = 8;
                firstA = 3;
                secondA = 2;
            }
            if (fn_8011F6A4(self, firstA, firstB, -1, &result, 1) != -1) {
                fn_801A75C0(target, 0, &result.position);
            }
            if (fn_8011F6A4(self, secondA, secondB, -1, &result, 1) != -1) {
                fn_801A75C0(target, 1, &result.position);
            }
        } else if (flags & 0x40) {
            fn_8003BAD8(self, target);
        } else if (flags & 0x200000) {
            QueryResult result;

            if (fn_8011F6A4(self, 3, 3, -1, &result, 1) != -1) {
                fn_801A75C0(target, 0, &result.position);
            }
            if (fn_8011F6A4(self, 2, 3, -1, &result, 1) != -1) {
                fn_801A75C0(target, 1, &result.position);
            }
        }
    }
    return 1;
}
