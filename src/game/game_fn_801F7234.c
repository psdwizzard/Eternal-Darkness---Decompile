typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    Vec3 position;
    unsigned char pad0c[0x28];
    float field_34;
    unsigned char pad38[8];
    int field_40;
    unsigned char pad44[4];
    Vec3 vector;
    float field_54;
    unsigned char pad58[0x10];
    void* field_68;
    void (*callback)(struct State*);
    void* field_70;
    unsigned char pad74[0x14];
} State;

extern unsigned char lbl_8063C6B8[];
extern float lbl_80651478;

extern void fn_801FA354(State*);
extern void fn_801F692C(Vec3);
extern void fn_801F6998(Vec3);
extern void fn_801F69E0(float);
extern void fn_801F6950(Vec3);
extern void fn_801F69BC(Vec3);
extern void fn_80211AAC(Vec3*, Vec3*);

#pragma use_lmw_stmw on
void fn_801F7234(int flags)
{
    State* base = (State*)lbl_8063C6B8;
    State* first;
    State* second;
    int enabled = flags & 1;
    int i;

    if (enabled) {
        {
            State* state = &base[24];
            if (state->callback != 0) {
                state->callback(state);
            }
        }
        {
            State* state = &base[25];
            if (state->callback != 0) {
                state->callback(state);
            }
        }
    }

    if (flags & 2) {
        first = &base[0];
        second = &base[12];

        for (i = 0; i < 12; i++, first++, second++) {
            if (first->callback != 0) {
                first->callback(first);
            }
            if (second->callback != 0) {
                second->callback(second);
            }
        }
    }

    if (enabled) {
        {
            State* state = &base[24];
            if (state->field_40 != 0) {
                fn_801FA354(state);
            }
        }
        {
            State* state = &base[25];
            if (state->field_40 != 0) {
                fn_801FA354(state);
            }
        }
    }

    {
        State* first_special = &base[24];
        State* second_special = &base[25];
        if (first_special->position.x == second_special->position.x &&
            first_special->position.y == second_special->position.y &&
            first_special->position.z == second_special->position.z) {
            second_special->position.x += lbl_80651478;
        }
    }

    fn_801F692C(base[24].position);
    fn_801F6998(base[25].position);
    fn_801F69E0(base[24].field_34);
    fn_801F6950(base[24].vector);

    {
        Vec3 delta;
        delta.x = base[25].position.x - base[24].position.x;
        delta.y = base[25].position.y - base[24].position.y;
        delta.z = base[25].position.z - base[24].position.z;
        fn_80211AAC(&delta, &delta);
        fn_801F69BC(delta);
    }
}
#pragma use_lmw_stmw reset
