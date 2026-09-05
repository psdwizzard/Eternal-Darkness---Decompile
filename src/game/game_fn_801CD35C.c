typedef unsigned int u32;

extern void fn_801CDB14(void* value, u32 size);

void fn_801CD35C(u32* link, void* value)
{
    u32 packed = link[1];
    u32 kind = packed >> 24;
    u32 size = packed & 0xFFFFFF;

    switch (kind) {
    case 0:
    case 1:
    case 4:
    case 5:
        size = (((size + 13) / 7) << 2) & ~7;
        break;
    case 2:
        size *= 2;
        break;
    }

    fn_801CDB14(value, size);
}
