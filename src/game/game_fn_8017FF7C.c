unsigned int fn_8017FF7C(void* object, int index, int slot)
{
    unsigned char* entries = *(void**)((char*)object + 0x4C);
    unsigned char* entry = entries + index * 0x38 + 0x28;
    return *(unsigned int*)(entry + slot * 4);
}
