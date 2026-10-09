typedef struct SavedState {
    float first_value;
    float second_value;
    unsigned int first_handle;
    unsigned int second_handle;
    int token;
} SavedState;

typedef struct LiveState {
    unsigned char pad0[0x30];
    float value;
    unsigned char pad34[0x3C];
    unsigned int handle;
    unsigned char pad74[0x14];
} LiveState;

extern unsigned char lbl_8063C6B8[];
extern int lbl_8064D7BC;
extern int fn_801FA410(int);

int fn_801F85A4(void)
{
    register unsigned char* base = lbl_8063C6B8;
    register int count;
    int result = 0;

    count = lbl_8064D7BC;
    if (count > 0) {
        register volatile SavedState* saved;
        register volatile LiveState* first;
        register volatile LiveState* second;
        float second_value;
        float first_value;
        unsigned int first_handle;
        unsigned int second_handle;
        int token;

        count--;
        /* ASM: addi/mulli/addi/addi preserve the three retail base pointers,
           which MWCC otherwise folds into large field displacements. */
        asm {
            addi saved, base, 0xDD0
            mulli r0, count, 0x14
            addi first, base, 0xCC0
            addi second, base, 0xD48
        }
        lbl_8064D7BC = count;
        /* ASM: add completes the indexed saved-state address after the count store. */
        asm {
            add saved, saved, r0
        }
        first_value = saved->first_value;
        second_value = saved->second_value;
        first_handle = saved->first_handle;
        second_handle = saved->second_handle;
        first->value = first_value;
        token = saved->token;
        second->value = second_value;
        first->handle = first_handle;
        second->handle = second_handle;
        fn_801FA410(token);
        result = 1;
    }
    return result;
}
