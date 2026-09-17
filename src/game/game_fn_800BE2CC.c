typedef struct RuntimeState {
    unsigned char pad[0xAC];
    int pool_index;
    int slot_index;
} RuntimeState;

typedef struct Slot {
    int state;
    unsigned char pad[20];
} Slot;

typedef struct Item {
    void *value;
} Item;

typedef struct Pool {
    Item *items[2][100];
    int cursor[2];
    unsigned char tail[0x10];
} Pool;

extern Slot lbl_80320DF0[];
extern Pool lbl_80320FD0[];
extern int fn_80201B54();
extern void fn_800BCCC4(void *, void *);

int fn_800BE2CC(void *object, RuntimeState *runtime, void *output)
{
    int state;
    int cursor;
    Item *item;
    Pool *pool;

    fn_80201B54(object);
    if (runtime->slot_index < 0 || runtime->pool_index < 0) {
        goto fail;
    }
    state = lbl_80320DF0[runtime->slot_index].state;
    if (state != 0 && state != 1) {
        goto fail;
    }
    pool = &lbl_80320FD0[runtime->pool_index];
    cursor = *(int *)((char *)pool + 0x320 + state * 4);
    item = pool->items[state][cursor];
    if (item == 0 || item->value == 0) {
        goto fail;
    }
    fn_800BCCC4(item->value, output);
    return 1;

fail:
    return 0;
}
