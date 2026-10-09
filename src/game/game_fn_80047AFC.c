typedef signed int s32;

typedef struct ObjectSearchResult {
    void *object;
} ObjectSearchResult;

extern void *fn_80158598(s32 object_id, s32 index);
extern s32 fn_80157E1C(void *collection);
extern void *fn_80157E24(void *collection, s32 index);
extern s32 fn_8011EB04(void *object);
extern s32 fn_80047CB4(void);
extern void *fn_80201814(s32 object_id);
extern void *fn_80201890(s32 object_id);

void *fn_80047AFC(s32 object_id)
{
    ObjectSearchResult result;
    s32 count;
    s32 type;
    void *collection;
    s32 index;
    result.object = 0;

    if (fn_80201814(object_id) != 0) {
        collection = fn_80158598(object_id, 0);
        if (collection != 0) {
            count = fn_80157E1C(collection);
            for (index = 0; index < count; index++) {
                object_id = (s32)fn_80201890((s32)fn_80157E24(collection, index));
                type = fn_8011EB04((void *)object_id);
                if (type == fn_80047CB4()) {
                    result.object = (void *)object_id;
                    break;
                }
            }
        }
    }

    return result.object;
}
