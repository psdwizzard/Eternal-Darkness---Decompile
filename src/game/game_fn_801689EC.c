int luaU_endianess(void)
{
    union {
        int word;
        signed char byte;
    } value;

    value.word = 1;
    return value.byte;
}
