typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 lbl_802FC5BC[];

#define FILL_VALUE (*(u32*)(lbl_802FC5BC + 0xC))

void fn_80194998(u8 width, u16 position, u8* output, u8* state)
{
    int row;
    u8 inner;
    u8 width8;
    u8* second;

    row = ((int)position - *(u16*)(state + 0x26)) >> 1;
    width8 = width;
    inner = width8 - 4;
    if (row < 0) {
        return;
    }

    switch (row) {
    case 0:
        goto done;
    case 1: {
        row = inner * 4;
        output += (row + 9) * 4;
        *(u32*)output = FILL_VALUE;
        second = output;
        second += inner * 16;
        *(u32*)second = FILL_VALUE;
    }
done:
        return;
    default:
        break;
    }

    if (row >= width8 - 1) {
        *(u16*)(state + 0x26) += width8 * 2 + 4;
        return;
    }
    if (row == width8 - 2) {
        return;
    }
    if (row == width8 - 3) {
        output += (inner * 6 + 7) * 4;
        *(u32*)output = FILL_VALUE;
        *(u32*)(output + 0x10) = FILL_VALUE;
        return;
    }

    row -= 2;
    output += (inner * 4 + row * 2 + 9) * 4;
    *(u32*)output = FILL_VALUE;
    output += 8;
    *(u32*)output = FILL_VALUE;
    output += ((inner - row) * 4 - 4) * 4;
    *(u32*)output = FILL_VALUE;
    *(u32*)(output + 8) = FILL_VALUE;
}
