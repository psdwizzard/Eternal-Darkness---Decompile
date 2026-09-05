typedef struct CallbackEntry {
    int value;
    int kind;
    int unknown;
} CallbackEntry;

typedef struct EffectState {
    int timer;
    unsigned char pad[0x3F];
    signed char kind;
} EffectState;

extern void fn_80204810(void);
extern int fn_800A8040(void);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80128C44(void*, void (*)(void), int);
extern void fn_80128C28();
extern void fn_801292E0(void*, int*, CallbackEntry**);
extern void fn_801287C4(void*, int (*)(void), int, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

void fn_800A80CC(int index, void* object, void* source, EffectState* state)
{
    int tag;
    void* handle;
    CallbackEntry* entries;
    int count;
    int i;
    int found;

    handle = fn_801294DC(source, state->kind == 2 ? 0x4D : 0x4F, 0x20, 6);
    if (handle != 0) {
        tag = index << 8;
        found = 0;
        fn_80128C44(handle, fn_80204810, tag | 7);
        fn_80128C28(handle, fn_80204810, tag | 0xC);
        fn_801292E0(source, &count, &entries);

        for (i = 0; i < count; i++) {
            if (entries[i].kind == 1) {
                fn_801287C4(handle, fn_800A8040, 0, entries[i].value >> 17);
                found = 1;
            }
        }

        if (!found) {
            fn_801287C4(handle, fn_800A8040, 0, 30);
        }

        state->timer = 0x480;
        fn_80201D2C(object, 0x40);
        fn_80201D14(object, 1);
    } else {
        fn_80201D2C(object, 1);
        fn_80201D14(object, 1);
    }
}
