typedef signed int s32;

extern void *fn_80158598(s32 object_id, s32 index);
extern s32 fn_80157E1C(void *collection);
extern void *fn_80157E24(void *collection, s32 index);
extern s32 fn_8011EB04(void *object);
extern void *fn_80201814(s32 object_id);
extern void *fn_80201890(s32 object_id);

void *fn_80047B98(s32 object_id)
{
    void *result;
    void *collection;
    s32 count;
    s32 index;

    result = 0;
    if (fn_80201814(object_id) != 0) {
        collection = fn_80158598(object_id, 0);
        if (collection != 0) {
            count = fn_80157E1C(collection);
            for (index = 0; index < count; index++) {
                object_id = (s32)fn_80201890((s32)fn_80157E24(collection, index));
                if (fn_8011EB04((void *)object_id) == 0xF1) {
                    result = (void *)object_id;
                    break;
                }
            }
        }
    }
    return result;
}
