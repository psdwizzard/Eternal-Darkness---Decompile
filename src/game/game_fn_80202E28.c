typedef unsigned int u32;
typedef signed short s16;

typedef struct EventData80202E28 {
    char pad[0x1C];
    u32 value;
} EventData80202E28;

typedef struct State80202E28 {
    char pad0[8];
    u32 flags;
    char pad1[0x28];
    s16 counter;
} State80202E28;

extern int lbl_8064D18C;
extern void *lbl_8064D8A8;

extern int fn_800073D8();
extern int fn_800459E0();
extern int fn_800C96D4();
extern int fn_8011EB04();
extern int fn_8011EBFC();
extern int fn_8011F950();
extern int fn_8011FB4C();
extern int fn_8011FCEC();
extern int fn_8011FE54();
extern int fn_8011FE5C();
extern int fn_801261F4();
extern int fn_8012880C();
extern int fn_80128A84();
extern int fn_80128C34();
extern int fn_80128E30();
extern int fn_80128EAC();
extern int fn_80128F74();
extern int fn_801290D0();
extern int fn_801294DC();
extern int fn_80129FD0();
extern int fn_8012A100();
extern int fn_8012A1BC();
extern int fn_8012A1FC();
extern int fn_8012B344();
extern int fn_8012C478();
extern int fn_8015917C();
extern int fn_8016B400();
extern int fn_801A6F94();
extern int fn_801AC980();
extern int fn_801E8328();
extern int fn_80200C10();
extern int fn_80200C38();
extern int fn_8020123C();
extern int fn_80201B54();
extern int fn_80201B94();
extern int fn_80201BC8();
extern int fn_80201C7C();
extern int fn_80201CDC();
extern int fn_80201D14();
extern int fn_80201D2C();
extern int fn_80201E50();
extern int fn_80201EB8();
extern int fn_8020228C();
extern int fn_802022B4();
extern int fn_80202440();
extern int fn_802025D8();
extern int fn_802028AC();
extern int fn_80202C00();
extern int fn_80203D94();

static void set_result(int object, int result)
{
    fn_80201D2C(object, result);
    fn_80201D14(object, 1);
}

static void send_counter(int kind, int other, State80202E28 *state, int check_busy)
{
    int value = state->counter;
    if (value != 0 && fn_8020228C() == 0 &&
        (!check_busy || fn_8015917C() == 0)) {
        if (value > 0)
            value--;
        state->counter = value;
        fn_8020123C(kind, other, other, 0);
    }
}

int fn_80202E28(int object, int action, EventData80202E28 *data, int extra)
{
    int type = fn_80200C10(data);
    int model = fn_80201BC8(object);
    State80202E28 *state = (State80202E28 *)fn_80201B94(object);
    int other = fn_80201B54(object);
    int event = fn_8011EB04(model);

    if (action == 0) {
        if (type == 1) {
            if (state->flags & 0x80) {
                set_result(object, 0xD);
                state->flags &= ~0x80;
            } else {
                set_result(object, 0xE);
            }
            if (fn_80201EB8(object) == 0xEF) {
                /* The retail function selects one of three constant vectors here. */
                if (event == 0x127 || event == 0x13C || event == 0x13D)
                    fn_8011FE5C(model, event);
            }
            return 1;
        }
        if (type == 6) {
            int value = fn_80201C7C(state);
            if (value != 0)
                fn_8016B400(value, 0, 0);
            return 1;
        }
        if (type == 0x39) {
            fn_801E8328(2, object);
            return 1;
        }
        if (type == 0x3E) {
            if (state->flags & 0x100000) {
                fn_8012C478(model, 0xF, 0);
                state->flags &= ~0x100000;
            }
            if (state->flags & 0x200000)
                state->flags &= ~0x200000;
            fn_80202C00(other, event, object);
            return 1;
        }
        if (type == 0x3D) {
            if (fn_802022B4(object) != 0) {
                if (fn_8011F950(model) != 0) {
                    if (fn_801261F4(model) != 0 && fn_8011FCEC(model) != -1)
                        fn_8011EBFC(model);
                    fn_80128E30(model);
                    state->counter = 0;
                    if (fn_80128E30(model) != 0) {
                        fn_8012B344(model);
                        set_result(object, 0xE);
                    }
                } else {
                    set_result(object, 0xE);
                }
            }
            return 1;
        }
        if (type == 0x9A) {
            state->counter = data->value;
            return 1;
        }
        if (type == 0xB5) {
            int target = fn_80128E30(model);
            fn_80201EB8(object);
            if (target == 0) {
                fn_800073D8(lbl_8064D18C);
                fn_801A6F94();
            } else if (fn_80128C34(target) != 0) {
                fn_802025D8(other, object, model, fn_80128C34(target), state);
            }
            return 1;
        }
        return 0;
    }

    if (action == 0xE) {
        if (type == 1) {
            fn_8011FE5C(model, 0x1B);
            if (fn_8011F950(model) != 0 && fn_8011FB4C(model) == lbl_8064D18C)
                fn_801294DC(model, 0x1B, 0x21, 8);
            return 1;
        }
        if (type == 3) {
            send_counter(0x12, other, state, 1);
            return 1;
        }
        if (type == 0x12) {
            if (fn_802022B4(object) == 0 || fn_8020228C() == 0)
                fn_802028AC(object, other, model, state, data, 0);
            return 1;
        }
        if (type == 0x9A) {
            if (fn_8020228C() == 0) {
                state->counter = data->value;
                fn_8020123C(0x12, other, other, 0);
            }
            return 1;
        }
        if (type == 0x3B || type == 0x85)
            return fn_80203D94(object, action, data, extra);
        return 0;
    }

    if (action == 0xD) {
        if (type == 1) {
            fn_8011FE5C(model, 0x1A);
            if (fn_8011F950(model) != 0 && fn_8011FB4C(model) == lbl_8064D18C)
                fn_801294DC(model, 0x1A, 0x21, 8);
            send_counter(0x13, other, state, 0);
            return 1;
        }
        if (type == 3) {
            send_counter(0x13, other, state, 1);
            return 1;
        }
        if (type == 0x13) {
            if (fn_802022B4(object) == 0 || fn_8020228C() == 0)
                fn_80202440(object, other, model, state, data, 0);
            return 1;
        }
        if (type == 0x3E) {
            if (fn_8012A100(model, 0x1A) != 0) {
                int target = fn_801294DC(model, 0x1A, 0x21, 8);
                if (target != 0) {
                    int slot;
                    fn_80128EAC(model);
                    slot = fn_8012A1BC(model, 0x1A);
                    fn_80129FD0(model, slot << 17, 0);
                    fn_80128A84(target, 0, slot);
                }
            }
            fn_80202C00(other, event, object);
            return 1;
        }
        if (type == 0x9A) {
            if (fn_8020228C() == 0) {
                state->counter = data->value;
                fn_8020123C(0x13, other, other, 0);
            }
            return 1;
        }
        return 0;
    }

    if (action == 0xF) {
        if (type == 1) {
            fn_80201E50(state, fn_80201CDC(object) & ~8);
            return 1;
        }
        if (type == 0x1C) {
            fn_80200C38(data);
            return 1;
        }
        if (type == 0x3E) {
            if (state->flags & 0x100000) {
                fn_8012C478(model, 0xF, 0);
                state->flags &= ~0x100000;
            }
            if (state->flags & 0x200000)
                state->flags &= ~0x200000;
            fn_80202C00(other, event, object);
            return 1;
        }
        if (type == 0x13) {
            if (fn_802022B4(object) == 0 || fn_8020228C() == 0) {
                int mode = fn_8011FE54(model);
                if (fn_80128EAC(model) == mode) {
                    int slot = fn_8012A1BC(model, 0x19);
                    fn_802028AC(object, other, model, state, data, 0);
                    fn_80129FD0(model, slot << 17, 0);
                }
                mode = fn_80128E30(model);
                fn_80128F74(model, fn_801290D0(model) | 2);
                fn_8012880C(mode, 0, 0);
                fn_80202440(object, other, model, state, data, mode);
            }
            return 1;
        }
        if (type == 0x14) {
            fn_800459E0(object);
            set_result(object, fn_802022B4(object) ? 0xE : 0xD);
            return 1;
        }
        if (type == 2)
            return 1;
        return 0;
    }

    if (action == 0x10) {
        if (type == 1) {
            fn_80201E50(state, fn_80201CDC(object) & ~8);
            return 1;
        }
        if (type == 0x1C) {
            fn_80200C38(data);
            return 1;
        }
        if (type == 0x12) {
            if (fn_802022B4(object) == 0 || fn_8020228C() == 0) {
                int mode = fn_8011FE54(model);
                if (fn_80128EAC(model) == mode) {
                    int slot = fn_8012A1FC(model, 0x19);
                    fn_80202440(object, other, model, state, data, 0);
                    fn_80129FD0(model, slot << 17, 0);
                }
                mode = fn_80128E30(model);
                fn_80128F74(model, fn_801290D0(model) & ~2);
                fn_8012880C(mode, 0, 0);
                fn_802028AC(object, other, model, state, data, mode);
            }
            return 1;
        }
        if (type == 0x3E) {
            if (state->flags & 0x100000) {
                fn_8012C478(model, 0xF, 0);
                state->flags &= ~0x100000;
            }
            if (state->flags & 0x200000)
                state->flags &= ~0x200000;
            fn_80202C00(other, event, object);
            return 1;
        }
        if (type == 0x15) {
            set_result(object, 0xE);
            return 1;
        }
        if (type == 2)
            return 1;
        return 0;
    }

    if (action == 0x30) {
        if (type == 1) {
            /* Camera-space position and effect setup; signatures remain unknown. */
            fn_800C96D4(object, 0xFE, -2, 0, 0x64, 1);
            return 1;
        }
        if (type == 3) {
            fn_8020123C(0x39, other, other, 0);
            return 1;
        }
        if (type == 0x3D)
            return fn_80203D94(object, action, data, extra);
        return 0;
    }

    return 0;
}
