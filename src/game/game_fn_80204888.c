extern int fn_80201B44(void);
extern void *fn_80158598(int object, int index);
extern int fn_80157E1C(void *collection);
extern void *fn_80157E24(void *collection, int index);
extern void *fn_80201814(void *object);
extern void *fn_80201C24(void *object);
extern int fn_8015821C(void *object);

int fn_80204888(int value)
{
    int index;
    void *collection;

    collection = fn_80158598(fn_80201B44(), 1);

    if (collection != 0) {
        int count = fn_80157E1C(collection);

        for (index = 0; index < count; index++) {
            void *object = fn_80201814(fn_80157E24(collection, index));

            if (object != 0 && value == fn_8015821C(fn_80201C24(object))) {
                return 1;
            }
        }
    }
    return 0;
}
