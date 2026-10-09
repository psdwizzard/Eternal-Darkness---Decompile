typedef struct RuntimeState {
    unsigned char pad[0xAC];
    int pool_index;
    int slot_index;
} RuntimeState;

typedef struct Pool {
    unsigned char pad[0x334];
    unsigned char flags;
    unsigned char tail[3];
} Pool;

extern Pool lbl_80320FD0[];
extern int fn_80201B54();
extern void fn_800BD0F0(int, int);
extern void fn_800BD23C(void);

int fn_800BD194(void *object, RuntimeState *runtime)
{
    int i;
    int object_id;
    Pool *pool;

    object_id = fn_80201B54(object);
    if (runtime->pool_index != -1) {
        return runtime->pool_index;
    }

    pool = lbl_80320FD0;
    for (i = 0; i < 20;) {
        if (!(pool->flags & 1)) {
            fn_800BD0F0(i, object_id);
            runtime->pool_index = i;
            runtime->slot_index = i;
            return i;
        }
        pool++;
        i++;
    }

    fn_800BD23C();
    runtime->pool_index = -1;
    runtime->slot_index = -1;
    fn_800BD23C();
    return -1;
}
