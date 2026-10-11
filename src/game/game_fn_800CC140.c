typedef struct Collection Collection;
typedef struct Object Object;

struct Object {
    unsigned char pad[0x18];
    int flags;
};

extern Collection *fn_80158598(int object_id, int create);
extern int fn_80158514(Collection *collection, int value);
extern int fn_80157FE0(Collection *collection, int mask, int index);
extern int fn_80157E1C(Collection *collection);
extern void *fn_80157E24(Collection *collection, int index);
/* The original call supplies a fifth argument, which this callee ignores. */
extern int fn_80157E34();
extern void fn_80158038(Collection *collection, int value);
extern int fn_801579EC(void *object);
extern int fn_801579F4(void *object);
extern void *fn_80201814(int object_id);
extern void *fn_80201BC8(void *object);
extern void *fn_80201C24(void *object);

void fn_800CC140(int owner_id, int object_id, int unused, int mask, int flags)
{
    Collection *collection;
    Collection *owner_collection;
    Object **link;
    void *object;
    int value;

    collection = fn_80158598(owner_id, 0);
    link = 0;
    fn_80201BC8(fn_80201814(owner_id));
    object = fn_80201814(object_id);
    if (object != 0) {
        link = fn_80201C24(object);
    }

    owner_collection = fn_80158598(owner_id, 0);
    if (fn_80158514(owner_collection, object_id) != -1) {
        if (link != 0) {
            value = fn_801579F4(link);
            if (value != 0) {
                fn_80158038(collection, value);
            }
        }
        fn_80158038(collection, object_id);
        if (link != 0) {
            value = fn_801579EC(link);
            if (value != 0) {
                fn_80158038(collection, value);
            }
        }
    } else if (object != 0) {
        while ((value = fn_80157FE0(collection, mask, 0)) >= 0) {
            fn_80158038(collection, value);
        }
        fn_80157E34(collection, object_id, mask, (*link)->flags, flags);
        if (link != 0) {
            value = fn_801579F4(link);
            if (value != 0) {
                fn_800CC140(owner_id, value, 0, 1, 0);
            }
        }
    } else {
        int entry;
        Collection *cleanup_collection = fn_80158598(owner_id, 0);
        while (cleanup_collection != 0 && fn_80157E1C(cleanup_collection) != 0) {
            entry = (int)fn_80157E24(cleanup_collection, 0);
            fn_80158038(cleanup_collection, entry);
        }
    }
}
