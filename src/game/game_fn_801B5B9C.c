typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

void synthInitPortamento(u8* state)
{
    u64 flags = *(u64*)(state + 0x114);

    if (flags & 0x20000ULL)
        return;

    if (state[0x131] == 1) {
        if (!(flags & 0x1000ULL))
            *(u32*)(state + 0x13C) = 0;
        else
            *(u32*)(state + 0x13C) = *(u32*)(state + 0x134);
    } else {
        *(u32*)(state + 0x13C) = *(u32*)(state + 0x134);
    }

    *(u32*)(state + 0x138) = state[0x130] << 16;
}
