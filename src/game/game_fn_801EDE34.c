typedef struct StateRegion {
    char pad[0x2938];
    int values0[16];
    int values1[16];
    int values2[16];
} StateRegion;

extern StateRegion lbl_80639260;
extern void fn_8022A118(int, int, int, int);

void fn_801EDE34(int index, int value0, int value1, int value2)
{
    StateRegion* state = &lbl_80639260;
    int* values0 = state->values0;

    if (values0[index] != value0 || state->values1[index] != value1 ||
        state->values2[index] != value2) {
        fn_8022A118(index, value0, value1, value2);
        values0[index] = value0;
        state->values1[index] = value1;
        state->values2[index] = value2;
    }
}
