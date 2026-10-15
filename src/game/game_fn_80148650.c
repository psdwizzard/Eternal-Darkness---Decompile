typedef struct Object Object;

extern void *fn_80156938(Object *);
extern int fn_80156FF4(Object *);
extern int fn_801800F8(void *);
extern int fn_80180114(void *);
extern int fn_8018E934(unsigned char *);

typedef struct InstanceList {
    unsigned char count;
    unsigned char pad1[3];
    unsigned short mask;
    unsigned short state;
    unsigned char pad8[0x80];
    void *instances[1];
} InstanceList;

int fn_80148650(Object *object, void *unused, int enabled)
{
    unsigned char count;
    unsigned short bit;
    int result;
    int i;
    InstanceList *list;

    list = fn_80156938(object);
    result = 0;
    if (enabled == 0)
        return 0;

    count = list->count;
    bit = 1;
    i = 0;
    for (; i < count; i++) {
        if ((list->mask & bit) != 0) {
            if (fn_801800F8(list->instances[i])) {
                fn_8018E934(list->instances[i]);
                result = 2;
            }
            if (fn_80180114(list->instances[i]))
                list->mask &= ~bit;
        }
        bit = bit << 1;
    }

    if (list->state == 1 || list->mask == 0) {
        fn_80156FF4(object);
        result = 4;
    }
    return result;
}
