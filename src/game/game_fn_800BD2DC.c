typedef struct RuntimeState {
    unsigned char pad[0xAC];
    int pool_index;
    int slot_index;
} RuntimeState;

typedef struct Slot {
    int state;
    unsigned char pad[20];
} Slot;

typedef struct Pool {
    unsigned char pad[0x334];
    unsigned char flags;
    unsigned char tail[3];
} Pool;

extern Slot lbl_80320DF0[];
extern Pool lbl_80320FD0[];
extern int fn_80201B54(int *object);
extern void *memset(void *, int, unsigned int);

int fn_800BD2DC(int *object, RuntimeState *runtime)
{
    fn_80201B54(object);
    if (runtime->pool_index >= 0 && runtime->pool_index < 20) {
        if (runtime->slot_index >= 0 && runtime->slot_index < 20) {
            memset(&lbl_80320DF0[runtime->slot_index], 0, sizeof(Slot));
            memset(&lbl_80320FD0[runtime->pool_index], 0, sizeof(Pool));
            runtime->slot_index = -1;
            runtime->pool_index = -1;
            return 1;
        }
    }
    return 0;
}
