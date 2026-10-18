typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u64 fn_8020123C(s32, s32, s32, s32);
extern s32 fn_80201B44(void);
extern s32 fn_80201B4C(int *);
extern s32 fn_80201B54(int *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
typedef struct Object80201EB8 Object80201EB8;
extern s32 fn_80201EB8(Object80201EB8 *);

s32 fn_800467F0(s32 kind, s32 use_current)
{
    void *object;
    s32 count;
    s32 object_id;

    object = fn_80201B9C();
    count = 0;
    while (object != 0) {
        s32 object_kind = fn_80201EB8(object);
        if (object_kind == kind) {
            if (fn_80201B4C(object) == 1) {
                object_id = fn_80201B54(object);
                if (use_current != 0) {
                    if ((u32)(fn_8020123C(0x3B, fn_80201B44(), object_id, 0) & 0xFFFFFFFFULL) == 1) {
                        count++;
                    }
                } else if ((u32)(fn_8020123C(0x3B, object_id, object_id, 0) & 0xFFFFFFFFULL) == 1) {
                    count++;
                }
            }
        }
        object = fn_80201BC0(object);
    }
    return count;
}
