typedef unsigned char u8;

extern int lbl_8064D18C;
extern void *fn_80201B9C();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern void *fn_80201BC0(void *object);
extern int fn_80201EB8();
extern unsigned long long fn_8020123C();

int fn_80078608(void *object, int *total, void **type3, void **type4,
                void **type6, int *count3, int *count4, int *count6)
{
    void *item = fn_80201B9C(object);
    int found = 0;
    int limit;
    void *owner = (void *)fn_80201B54(object);
    u8 *state = fn_80201B8C(object);

    *type6 = 0;
    *type4 = 0;
    *type3 = 0;
    *count6 = 0;
    *count4 = 0;
    *count3 = 0;

    while (item != 0) {
        u8 *info = fn_80201B8C(item);
        if (info != 0 && fn_80201EB8(item) == lbl_8064D18C &&
            info[0x9E] == 2) {
            void *entry = (void *)fn_80201B54(item);
            if ((unsigned int)(fn_8020123C(0x4E, owner, entry, 0) & 0xFFFFFFFF) != 0) {
                switch (info[0x9F]) {
                case 3:
                    *type3 = entry;
                    found++;
                    (*count3)++;
                    break;
                case 4:
                    *type4 = entry;
                    found++;
                    (*count4)++;
                    break;
                case 6:
                    *type6 = entry;
                    found++;
                    (*count6)++;
                    break;
                }
            }
        }
        item = fn_80201BC0(item);
    }
    limit = *(int *)(*(u8 **)(state + 0xC) + 0x34);
    *total = found;
    return found >= limit;
}
