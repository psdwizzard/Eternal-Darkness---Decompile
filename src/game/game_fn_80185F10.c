typedef unsigned char u8;
typedef unsigned short u16;

extern void fn_8018163C(void*, void*, u8, int);
extern const double lbl_80650A10;

void fn_80185F10(u8* state, u8* self, u16 count, void* setup)
{
    u8* local_state = state;
    void* local_setup = setup;
    register u16 local_count;
    int i;
    u16 limit = self[1];
    u8* entry = *(u8**)(self + 0x4C);

    local_count = count;
    *(u16*)(state + 0xE) = local_count;
    for (i = 0; i < limit - 1; i++) {
        fn_8018163C(entry, local_setup,
                    (int)(i * *(float*)(local_state + 0x30)) & 0x3F,
                    local_count);
        entry += 0x38;
    }
    fn_8018163C(entry, local_setup, 0, local_count);
}
