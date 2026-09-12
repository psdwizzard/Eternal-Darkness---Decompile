extern int lbl_8064D18C;

typedef struct Object802028AC {
    char pad[0x24];
    void *value;
} Object802028AC;

extern int *fn_80200C38(void *object);
extern void fn_80200C20(void *object);
extern int fn_8011FB4C(void *object);
extern void fn_80201DE8(void *object, int value);
extern void fn_80201DF0(void *object, int value);
extern void *fn_801294DC(void *object, int type, int value, int flags);
extern int fn_8012A1BC(void *object, int type);
extern int fn_8012A1FC(void *object, int type);
extern int fn_800459E0(void *object);
extern int fn_801A717C(void);
extern unsigned int fn_80201CDC(void *object);
extern int fn_8011F130(void *object);
extern void fn_80202354(int manager, int type, int id, int value);
extern void fn_80201E50(void *object, unsigned int flags);
extern unsigned int fn_801A7570(int object);
extern void fn_801A7560(int object, unsigned int flags);
extern void fn_801287C4(void *object, void *callback, int value, int index);
extern void fn_80128C28(void *object, void *callback, int value);
extern void fn_80128C44(void *object, void *callback, int value);
extern void fn_80201D2C(void *object, int value);
extern void fn_80201D14(void *object, int value);
extern void fn_80204810(void);
extern void fn_80203D30(void);
extern void fn_80202678(void);
extern void fn_802027E8(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);

void *fn_802028AC(void *object, int id, void *resource, void *target,
                  void *link, void *created)
{
    int *values;
    int first;
    int second;
    int group;
    int kind;
    int manager;
    int start;
    int end;
    int step;
    int value;
    unsigned int flags;
    void *result;

    values = fn_80200C38(link);
    first = values != 0 ? values[0] : 0;
    second = values != 0 ? values[1] : 0;
    group = fn_8011FB4C(resource);
    fn_80200C20(link);

    if (group == lbl_8064D18C || group == -1) {
        fn_80201DE8(target, second);
        fn_80201DF0(target, first);
        result = created != 0 ? created : fn_801294DC(resource, 0x19, 0x20, 8);
        created = result;
        if (result != 0) {
            fn_8012A1BC(resource, 0x19);
            kind = fn_800459E0(object);

            if (second != 0) {
                value = first == -1 ? fn_8012A1FC(resource, 0x19) : first;
                fn_801287C4(result, fn_80204810, (id << 8) | 6,
                            value == -2 ? fn_8012A1BC(resource, 0x19) : value);
            }

            if ((unsigned int)(kind - 0x1F) <= 2 ||
                (unsigned int)(kind - 0x23) <= 1 || kind == 0x28) {
                manager = fn_801A717C();
                start = 0;
                end = 0;
                step = 0;
                flags = fn_80201CDC(object);
                fn_80202354(manager, 0x14, id, fn_8011F130(resource));

                switch (kind) {
                case 0x1F:
                    start = 10;
                    end = 0x23;
                    step = 2;
                    break;
                case 0x20:
                    start = 4;
                    end = 0x19;
                    step = 2;
                    break;
                case 0x21:
                    start = 3;
                    end = 0x10;
                    step = 1;
                    break;
                case 0x23:
                case 0x24:
                    flags |= 0x10;
                    start = 2;
                    end = 10;
                    step = 1;
                    fn_80201E50(((Object802028AC *)object)->value, flags);
                    fn_801A7560(manager, fn_801A7570(manager) | 0x20000);
                    break;
                case 0x28:
                    flags |= 0x10;
                    start = 0x10;
                    end = 0x18;
                    step = 1;
                    fn_80201E50(((Object802028AC *)object)->value, flags);
                    break;
                }

                if ((unsigned int)(kind - 0x1F) <= 1 || kind == 0x21) {
                    fn_801287C4(result, fn_80203D30, manager, start);
                    start += 2;
                }
                if (lbl_8064D18C == 0xD0)
                    fn_80201E50(((Object802028AC *)object)->value,
                                flags & ~0x10);
                while (start < end) {
                    fn_801287C4(result, fn_80202678, manager, start);
                    start += step;
                }
                if (kind == 0x23 || kind == 0x24)
                    fn_801287C4(result, fn_802027E8, manager, 8);
                fn_80128C28(result, fn_80204230, manager);
                fn_80128C44(result, fn_802042A4, manager);
            } else {
                fn_80128C28(result, fn_80204810, (id << 8) | 0x14);
            }

            fn_80201D2C(object, 0xF);
            fn_80201D14(object, 1);
        }
    }
    return created;
}
