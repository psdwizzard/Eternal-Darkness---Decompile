typedef unsigned char u8;
typedef signed short s16;

typedef struct InstanceList {
    u8 count;
    u8 pad1[3];
    unsigned short mask;
    unsigned short state;
    u8 pad8[0x80];
    void *instances[1];
} InstanceList;

typedef struct Item Item;
extern int fn_80147E64(s16);
/* This call site supplies the source data in r4; the callee currently ignores it. */
extern Item *fn_80156DA0(int, void *);
extern void fn_801568FC(void *, void *);
extern void fn_801568C0(void *, void *);
extern void fn_801568B8(void *, void *);
extern void fn_8015690C(void *, void *);
extern void fn_80156918(void *, void *);
extern void fn_80180374(void *, u8);

extern int fn_80148650(void *, void *, int);
extern void fn_80148730(void *);
extern void fn_8014883C(void *);

void *fn_8014856C(void *data, InstanceList *list, s16 type, int value)
{
    Item *object;
    int i;
    int count;

    object = fn_80156DA0(fn_80147E64(type), data);
    if (object != 0) {
        count = list->count;
        for (i = 0; i < count; i++) {
            if (list->instances[i] != 0) {
                fn_80180374(list->instances[i], (u8)(0 > value - 10 ? 0 : value - 10));
            }
        }

        fn_801568FC(object, (void *)fn_80148650);
        fn_801568C0(object, 0);
        fn_801568B8(object, (void *)fn_80148730);
        fn_8015690C(object, (void *)fn_8014883C);
        fn_80156918(object, list);
    }
    return object;
}
