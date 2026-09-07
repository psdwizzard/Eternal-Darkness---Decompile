typedef unsigned char u8;

void fn_801DABFC(u8* object)
{
    u8* state = *(u8**)(object + 0xBC);

    if (state != 0)
        state[0] &= ~1;
}
