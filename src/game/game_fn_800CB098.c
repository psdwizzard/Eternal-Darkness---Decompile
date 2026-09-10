typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RuntimeState {
    u8 pad[0x94];
    int state;
    u8 pad98[6];
    u8 kind;
    u8 subtype;
} RuntimeState;

extern int lbl_8064D18C;
extern void *fn_80201B9C();
extern void *fn_80201B8C();
extern int fn_80201EB8();
extern int fn_80201B54();
extern void *fn_80201BC0(void *);
extern unsigned long long fn_8020123C();

#pragma use_lmw_stmw on
int fn_800CB098(s8 kind, s8 subtype, int state, int owner, int dispatch,
                int *different_owner_handle)
{
    void *object = fn_80201B9C();
    int count = 0;
    s8 wanted_kind;
    s8 wanted_subtype;

    if (different_owner_handle != 0) {
        *different_owner_handle = 0;
    }
    wanted_kind = kind;
    wanted_subtype = subtype;

    while (object != 0) {
        RuntimeState *runtime = ((RuntimeState *)fn_80201B8C(object));
        if (runtime != 0) {
            int object_owner = fn_80201EB8(object);
            int owner_matches;
            int kind_matches = kind == -1 ? 1 : wanted_kind == runtime->kind;
            int subtype_matches = subtype == -1 ? 1 : wanted_subtype == runtime->subtype;
            int state_matches = state == -1 ? 1 : state == runtime->state;

            owner_matches = owner == -1 ? 1 : (owner == object_owner && object_owner != -1) != 0;
            if (kind_matches && subtype_matches && state_matches && owner_matches) {
                u32 handle = ((u32)fn_80201B54(object));
                int accepted;
                if (dispatch != 0) {
                    accepted = (unsigned int)(fn_8020123C(59, 0, handle, 0) & 0xFFFFFFFF);
                } else {
                    accepted = 1;
                }
                if (accepted != 0) {
                    if (different_owner_handle != 0 &&
                        *different_owner_handle == 0 &&
                        object_owner != lbl_8064D18C) {
                        *different_owner_handle = handle;
                    }
                    count++;
                }
            }
        }
        object = fn_80201BC0(object);
    }
    return count;
}
