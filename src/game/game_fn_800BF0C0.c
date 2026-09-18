typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern float lbl_8064F110;
extern int fn_801A7498(void *);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void *fn_801A7778(void *);
extern u16 fn_80157994(void *);
extern u32 fn_801A76B8(void *);
extern void fn_801A75B0(void *, u8);
extern u32 fn_8020216C(void *);
extern void fn_80157A28(void *, u8);
extern u8 fn_80157A80(void *);
extern void fn_80157A8C(void *, u8);
extern unsigned long long fn_8020123C();
extern void *fn_80201B3C();
extern void *fn_80205288(void);
extern void *fn_802053B0(void *, void *);
extern void *fn_80201BC8();
extern int fn_8011EB04(void *);
extern void fn_80124664(void *, int, int, float);
extern void fn_80157C98(void *, int, int);

void *fn_800BF0C0(void *unused, void *event)
{
    /* Preserve the 32-bit conversion used by GC/1.3 pointer coalescing. */
    void *event_object = (void *)(u32)event;
    void *state;
    void *world;
    int owner;
    int maximum;
    int current;
    void **holder;

    owner = fn_801A7498(event_object);
    world = fn_80201814(owner);
    holder = fn_80201B8C();
    state = fn_801A7778(event_object);
    maximum = fn_80157994(state);
    current = fn_801A76B8(event_object) & 0xFF;

    if (current > maximum) {
        current = maximum;
        fn_801A75B0(event_object, (u8)maximum);
    }

    if ((fn_8020216C(world) & 0x10000) == 0 && maximum != 0) {
        fn_80157A28(state, (u8)(fn_80157994(state) - current));
        fn_80157A8C(state, (u8)(current + fn_80157A80(state)));
    }

    if (holder != 0 && *holder != 0) {
        fn_8020123C(16, owner, *(int *)((u8 *)*holder + 0x70), state);
    }

    if (fn_80157994(state) == 0) {
        void *resource;
        void *resolved;
        void *child;

        fn_80201B3C();
        resource = fn_80205288();
        child = fn_802053B0(world, state);
        resolved = fn_80201BC8(resource);
        if (fn_8011EB04(resolved) == 0x70) {
            fn_80124664(resolved, 0x1A, 8, lbl_8064F110);
        }

        if (child != 0) {
            fn_80157C98(state, 0, 0x20);
        } else {
            fn_80157C98(state, 0, 0x80);
        }
    }

    return (void *)(u32)maximum;
}
