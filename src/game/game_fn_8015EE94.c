extern unsigned int previous_instruction(void*);

int luaK_lastisopen(void* object)
{
    unsigned int entry = previous_instruction(object);
    if ((int)(entry & 0x3F) == 2 && (int)((entry >> 6) & 0x1FF) == 0xFF)
        return 1;
    return 0;
}
