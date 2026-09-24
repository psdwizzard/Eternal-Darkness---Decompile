typedef signed int s32;

typedef struct Entry80201814 Entry80201814;

extern s32 *fn_800681C8(void);
extern Entry80201814 *fn_80201814(int id);
extern int fn_80201B64(int *object);
extern int fn_80201B54(int *object);

s32 fn_80068674(void *object, s32 excluded_id)
{
    s32 *objects;
    s32 i;
    s32 total;

    objects = fn_800681C8();
    total = 0;
    if (objects != 0) {
        for (i = 0; i < 12; i++) {
            Entry80201814 *candidate;
            s32 object_id;

            object_id = objects[(unsigned int)i];
            if (object_id == 0 || excluded_id == object_id) {
                continue;
            }
            candidate = fn_80201814(object_id);
            if (candidate != 0) {
                total += fn_80201B64((int *)candidate) == 0x22;
                total += fn_80068674(candidate, fn_80201B54((int *)object));
            } else {
                objects[(unsigned int)i] = 0;
            }
        }
    } else {
        total = 0;
    }
    return total;
}
