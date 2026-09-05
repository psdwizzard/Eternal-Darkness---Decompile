typedef unsigned char u8;
typedef unsigned short u16;

#pragma opt_propagation off
void fn_8019CE34(u8* object, unsigned int index)
{
    u16* counters = (u16*)(object + 0x8C);
    u8* entries = *(u8**)(object + 0x4C);
    index = (u8)index;
    if (entries[index * 0x38] == 0) {
        counters[index + 20] = 1;
    }
}
#pragma opt_propagation reset
