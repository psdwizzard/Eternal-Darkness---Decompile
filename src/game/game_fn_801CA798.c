typedef unsigned char u8;
typedef unsigned int u32;

extern u32 inpGlobalMIDIDirtyFlags[][16];

void inpSetGlobalMIDIDirtyFlag(u32 entry, u32 row, u32 flags)
{
    inpGlobalMIDIDirtyFlags[(u8)row][(u8)entry] |= flags;
}
