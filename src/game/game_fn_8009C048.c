typedef struct ActionEntry {
    int type;
    int arg;
    unsigned int param;
} ActionEntry;

typedef struct ActionState {
    ActionEntry primary[8];
    ActionEntry alternate[10];
    char pad_d8[8];
    int index;
    char pad_e4[0x18];
    int result;
    unsigned short flags;
} ActionState;

extern int fn_8009C28C(void *);
extern int fn_800CA3A0(void *, int, int, int);
extern int fn_800CA6DC(void *, int, unsigned int, void *, int);
extern int fn_800CD84C(void *);
extern int fn_8011F130(void *);
extern int fn_801D6F34(int, int);
extern int fn_80201B54(void *);
extern void *fn_80201BC8(void *);

int fn_8009C048(void *object, ActionState *state) {
    ActionEntry *entries;
    unsigned int param;
    int type;
    int a;
    int b;

    entries = state->primary;
    if (state->flags & 2) {
        entries = state->alternate;
    }
    type = entries[state->index].type;
    param = entries[state->index].param;

    switch (type) {
    case 0x820:
        if (fn_8009C28C(object) != 0) {
            state->result = fn_800CA3A0(object, entries[state->index].arg, 0, 0);
            return state->result != 0;
        }
        return 0;
    case 0x300:
        return 0;
    case 0x500:
        state->result = fn_800CA6DC(object, 0x500, param, 0, 0);
        return state->result != 0;
    case 0x1010:
        state->result = fn_800CA6DC(object, 0x1010, param, 0, 0);
        return state->result != 0;
    case 0x410:
        a = fn_80201B54(object);
        b = fn_8011F130(fn_80201BC8(object));
        if (fn_800CD84C(object) < 3 && fn_801D6F34(a, b) == 0) {
            state->result = fn_800CA6DC(object, 0x410, param, 0, 0);
            return state->result != 0;
        }
        return 0;
    case 0x480:
        state->result = fn_800CA6DC(object, 0x480, param, 0, 0);
        return state->result != 0;
    case 0x1040:
        state->result = fn_800CA6DC(object, 0x1040, param, 0, 0);
        return state->result != 0;
    }
    return 0;
}
