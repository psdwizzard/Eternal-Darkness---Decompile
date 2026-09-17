typedef signed int s32;

extern s32 *fn_800681C8(void);
extern void *fn_80201814();
extern s32 fn_80201B64(void *object);
extern int fn_80201B54();

s32 fn_80068674(void *object, s32 excluded_id)
{
    s32 *objects;
    s32 total;
    s32 i;

    objects = fn_800681C8();
    total = 0;
    if (objects != 0) {
        for (i = 0; i < 12; i++) {
            void *candidate;
            s32 object_id;

            object_id = objects[i];
            if (object_id == 0 || excluded_id == object_id) {
                continue;
            }
            candidate = fn_80201814(object_id);
            if (candidate != 0) {
                total += fn_80201B64(candidate) == 0x22;
                total += fn_80068674(candidate, fn_80201B54(object));
            } else {
                objects[i] = 0;
            }
        }
    }
    return total;
}
