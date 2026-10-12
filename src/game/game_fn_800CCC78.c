typedef unsigned int u32;
typedef unsigned long long u64;

extern void *fn_80201B9C(void);
extern int fn_80201B44(void);
extern int fn_80201B54(void *object);
extern void *fn_80201B94(void *object);
extern void *fn_80201C48(void *object);
extern int fn_80201EB8(void *object);
extern void *fn_80201BC0(void *object);
extern int fn_80204180(void *first, void *second);
extern int fn_80204508(void *object, void *other);
extern u64 fn_8020123C(int kind, int source, int target, int value);

int fn_800CCC78(void *object, int limit)
{
    void *current;
    int source_id;
    int count;
    int active_id;
    int environment;

    current = fn_80201B9C();
    count = 0;
    active_id = fn_80201B44();
    source_id = fn_80201B54(object);
    environment = fn_80201EB8(object);

    while (current != 0) {
        void *related = fn_80201B94(current);
        int target_id = fn_80201B54(current);
        int target_environment = fn_80201EB8(current);
        int related_id;
        int distance;

        if (related != 0) {
            related_id = (int)fn_80201C48(related);
        } else {
            related_id = 0;
        }
        distance = fn_80204180(object, current);
        if (source_id != target_id && environment == target_environment &&
            (source_id == related_id || active_id == target_id) &&
            distance <= limit && (unsigned char)fn_80204508(object, current) != 0 &&
            (u32)(fn_8020123C(0x3B, source_id, target_id, 0) & 0xFFFFFFFFULL) == 1) {
            count++;
        }
        current = fn_80201BC0(current);
    }
    return count;
}
