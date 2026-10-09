typedef struct Object Object;

typedef struct InstanceList {
    unsigned char count;
    unsigned char padding[0x87];
    void *instances[1];
} InstanceList;

extern void *fn_80156938(Object *object);
extern int fn_801800F8(void *object);
extern void fn_80188268(void *object);
extern void fn_801ECEC8(unsigned char first, int second,
                        unsigned char third);
extern void fn_801ED468(int value);

void fn_801487AC(Object *object)
{
    unsigned char *current;
    int count;
    int i;
    InstanceList *list;

    list = fn_80156938(object);
    count = *(unsigned char *)list;
    fn_801ED468(0x3C);
    fn_801ECEC8(1, 3, 0);
    current = (unsigned char *)list;

    for (i = 0; i < count; current += 4, i++) {
        void *instance = *(void **)(current + 0x88);
        if (fn_801800F8(instance))
            fn_80188268(*(void **)(current + 0x88));
    }
}
