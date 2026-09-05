typedef unsigned char u8;
typedef unsigned int u32;

typedef struct State80096A44 {
    u8 pad00[0x28];
    u32 value28;
    u32 flags;
} State80096A44;

extern int lbl_8064D18C;
extern void* lbl_8064C4F0;

extern int fn_80200C10(void*);
extern int fn_80200C38();
extern u32 fn_80200C20(void*);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern int fn_80201EB8();
extern unsigned int fn_8011FA8C(void*, int, u32);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_8011FE5C(void*, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_80095D10(void*);
extern int fn_80095E64(void*, unsigned int);
extern void fn_8012B324(void*);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern int fn_801E8328();
extern void fn_80094DD0(void*, void*, void*);
extern void fn_80095FDC(void*, void*, void*, State80096A44*, int);
extern void fn_80096208(void*, void*, void*, State80096A44*, int);
extern void fn_80096348(void*, void*, void*, State80096A44*, void*);
extern void fn_801B05B0(void*, int);
extern unsigned long long fn_8020123C();

int fn_80096A44(register void* object, register int event,
                register void* resource, register u32* result)
{
    register int kind;
    register State80096A44* state;
    register void* action_owner;
    register void* linked;
    register int ok;
    register int found;

    kind = fn_80200C10(resource);
    action_owner = fn_80201BC8(object);
    linked = ((void*)fn_80201B54(object));
    state = *(State80096A44**)((u8*)fn_80201B8C(object) + 0x68);

    if (event == 0) {
        if (kind == 1) {
            fn_8011FA8C(action_owner, 0xC0, 0);
            if (fn_80201EB8(object) == lbl_8064D18C) {
                fn_801294DC(action_owner, 0x11, 0x25, 0xA);
            }
            fn_8011FE5C(action_owner, 0x11);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 0x93) {
            found = fn_80095D10(object);
            ok = fn_80095E64(object, found);
            if (found != 0 && ok != 0) {
                if (fn_80200C38(resource) == 1) {
                    state->value28 = fn_80200C20(resource);
                    fn_80201D2C(object, 0x47);
                    fn_80201D14(object, 1);
                    if (result != 0) {
                        *result = 1;
                    }
                } else if (result != 0) {
                    *result = 1;
                }
            }
            return 1;
        }
        if (kind == 0x3E) {
            fn_801294DC(action_owner, 0x11, 0x25, 0xA);
            return 1;
        }
        if (kind == 0x39) {
            fn_8012B324(action_owner);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            fn_801E8328(2, object);
            return 1;
        }
    } else if (event == 1) {
        if (kind == 3) {
            fn_80094DD0(object, action_owner, resource);
            return 1;
        }
    } else if (event == 0x47) {
        if (kind == 1) {
            fn_80095FDC(object, action_owner, linked, state, 0);
            return 1;
        }
        if (kind == 3) {
            fn_80096208(object, action_owner, linked, state, 0);
            return 1;
        }
        if (kind == 0x5B) {
            fn_80096348(object, action_owner, linked, state, resource);
            return 1;
        }
        if (kind == 0x5C) {
            fn_801B05B0(lbl_8064C4F0, 0);
            return 1;
        }
        if (kind == 6) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        }
        if (kind == 2) {
            fn_8020123C(0x5C, linked, state->value28, 0);
            state->value28 = 0;
            state->flags &= ~2u;
            return 1;
        }
        if (kind == 0x93) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
