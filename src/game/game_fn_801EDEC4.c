typedef struct StateRegion {
    char pad[0x22F8];
    int values0[16];
    int values1[16];
    int values2[16];
} StateRegion;

extern StateRegion lbl_80639260;
extern void fn_80225FE8(int, int, int, int, int, int);

void fn_801EDEC4(int index, int value0, int value1, int value2)
{
    StateRegion* state = &lbl_80639260;
    int* values1 = state->values1;

    if (values1[index] != value1 || state->values0[index] != value0 ||
        state->values2[index] != value2) {
        fn_80225FE8(index, value0, value1, value2, 0, 125);
        values1[index] = value1;
        state->values0[index] = value0;
        state->values2[index] = value2;
    }
}
