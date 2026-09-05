typedef unsigned int u32;

extern void* fn_801CDA24(void* value, u32 size);

void fn_801CD2C8(void** link, void** value)
{
    u32 packed = *(u32*)((u32*)*link + 1);
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

    *value = fn_801CDA24(*value, size);
}
