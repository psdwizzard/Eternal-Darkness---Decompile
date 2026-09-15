typedef unsigned int u32;

extern void *fn_80201BC8();
extern void* fn_80201C24();
extern void *fn_80155DB4(void *);
extern int fn_80201B44();
extern void *fn_80158598(int, int);
extern int fn_80201B54();
extern int fn_80158264(void *, void *, int);
extern int fn_801E1ED4(int);
extern int fn_801E2004(int);
extern void* fn_8012C62C(void *, int, u32 *, u32 *, u32 *, int);
extern void fn_8012F58C(void *, int, int, int, int, int);
extern void *fn_80201814();
extern void fn_8002A754(void *, void *);
extern void fn_800CC140(int, int, int, void *, int);
extern u32 fn_80157864(void *, int);
extern void fn_801568B8(void *, int);
extern u32 lbl_8064F4AC;
extern u32 lbl_8064F4B0;
extern u32 lbl_8064F4B4;
extern u32 lbl_8064F4B8;
extern u32 lbl_8064F4BC;
extern u32 lbl_80651AD0;
extern u32 lbl_80651AD4;
extern u32 lbl_80651AD8;
extern u32 lbl_80651ADC;

void fn_800DB660(void *context, int input_mode)
{
    void *action;
    int owner;
    void *object;
    void *state;
    int mode;
    void *owner_state;
    int kind;
    int index;
    void *linked;
    void *other_action;

    mode = input_mode;
    object = fn_80201BC8(context);
    state = fn_80201C24(context);
    action = fn_80155DB4(context);

    if (mode == 1) {
        owner = fn_80201B44();
        owner_state = fn_80158598(owner, 0);
        kind = fn_80201B54(context);
        index = fn_80158264(owner_state, state, 1);
        linked = (**(void ****)state)[index];

        if (fn_801E1ED4(fn_80201B44()) != 0 && fn_801E2004(fn_80201B44()) == 4) {
            u32 value_z;
            u32 value_y;
            u32 value_x;
            value_x = lbl_8064F4B4;
            value_y = lbl_8064F4B0;
            value_z = lbl_8064F4AC;
            fn_8012C62C(object, 15, &value_z, &value_y, &value_x, 6);
            fn_8012F58C(object, 15, 0, 1, 30, 8);
        } else {
            u32 value_z;
            u32 value_y;
            u32 value_x;
            value_x = lbl_80651AD4;
            value_y = lbl_80651AD0;
            value_z = lbl_8064F4B8;
            fn_8012C62C(object, 15, &value_z, &value_y, &value_x, 0);
        }

        other_action = fn_80155DB4(fn_80201814(owner));
        fn_8002A754(action, other_action);
        fn_800CC140(owner, kind, 0, linked, 0);
    } else {
        if (fn_80157864(state, 0) != 0) {
            u32 value_z;
            u32 value_y;
            u32 value_x;
            value_x = lbl_80651ADC;
            value_y = lbl_80651AD8;
            value_z = lbl_8064F4BC;
            fn_8012C62C(object, 15, &value_z, &value_y, &value_x, 0);
        }
        fn_801568B8(action, 0);
    }
}
