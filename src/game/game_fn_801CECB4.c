typedef unsigned int u32;
typedef unsigned short u16;
typedef signed short s16;

extern s16 fn_801CEB2C(u32);
extern u16 fn_801D3A6C(u32, u32);

void fn_801CECB4(u32 flags, u16* output)
{
    s16 kind = fn_801CEB2C(flags);
    int index;

    switch (flags & 0x1F0) {
    case 0x10:
        output[0] = fn_801D3A6C(flags, 0x10);
        break;
    case 0x20:
        output[0] = fn_801D3A6C(flags, 0x20);
        break;
    case 0x40:
        output[0] = fn_801D3A6C(flags, 0x40);
        break;
    case 0x80:
        output[0] = fn_801D3A6C(flags, 0x80);
        break;
    case 0x100:
        output[0] = fn_801D3A6C(flags, 0x100);
        break;
    }

    index = 1;
    if (kind >= 5) {
        output[index++] = fn_801D3A6C(flags, 0x2000);
    }
    if (kind == 9) {
        output[index++] = fn_801D3A6C(flags, 0x2000);
    }

    switch (flags & 0x1E00) {
    case 0x200:
        output[index] = fn_801D3A6C(flags, 0x200);
        break;
    case 0x400:
        output[index] = fn_801D3A6C(flags, 0x400);
        break;
    case 0x800:
        output[index] = fn_801D3A6C(flags, 0x800);
        break;
    case 0x1000:
        output[index] = fn_801D3A6C(flags, 0x1000);
        break;
    }
    index++;

    if (kind >= 7) {
        output[index] = fn_801D3A6C(flags, 0x2000);
        *(u16*)((u32)output + ((index + 1) << 1)) = fn_801D3A6C(flags, 0x2000);
        index += 2;
    }

    switch (flags & 0xF) {
    case 1:
        output[index] = 0x18;
        break;
    case 4:
        output[index] = 0x1A;
        break;
    case 2:
        output[index] = 0x19;
        break;
    case 8:
        output[index] = 0x1B;
        break;
    }
    index++;

    if (kind >= 5) {
        output[index++] = fn_801D3A6C(flags, 0x2000);
    }
    if (kind == 9) {
        output[index] = fn_801D3A6C(flags, 0x2000);
    }
}
