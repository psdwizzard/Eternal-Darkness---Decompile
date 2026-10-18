typedef struct StateRegion {
    char pad[0x2938];
    int values0[16];
    int values1[16];
    int values2[16];
} StateRegion;

extern StateRegion lbl_80639260;
extern void GXSetTevOrder(int, int, int, int);

/* Widening and narrowing preserves every 32-bit pointer bit while keeping
 * GC/1.3 from folding the field base into the indexed address. */
#define FIELD_ADDRESS(p) ((int*)(unsigned int)(unsigned long long)(unsigned int)(p))

void fn_801EDE34(int index, int value0, int value1, int value2)
{
    StateRegion* state = &lbl_80639260;
    unsigned int offset = (unsigned int)index * 4;
    int* values0;

    if (*(int*)((char*)FIELD_ADDRESS(values0 = state->values0) + offset) != value0 ||
        value1 != *(int*)((char*)FIELD_ADDRESS(state->values1) + offset) ||
        value2 != *(int*)((char*)FIELD_ADDRESS(state->values2) + offset)) {
        GXSetTevOrder(index, value0, value1, value2);
        *(int*)((char*)FIELD_ADDRESS(values0) + offset) = value0;
        *(int*)((char*)FIELD_ADDRESS(state->values1) + offset) = value1;
        *(int*)((char*)FIELD_ADDRESS(state->values2) + offset) = value2;
    }
}
