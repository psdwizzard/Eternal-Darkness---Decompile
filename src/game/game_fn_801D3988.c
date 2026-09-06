typedef unsigned char u8;
typedef unsigned int u32;

extern u8 lbl_802FC5BC[];
extern u32 lbl_802557B8[];

u32 fn_801D3988(int type, int index)
{
    volatile u32 result = *(u32*)(lbl_802FC5BC + 0xC);

    switch (type) {
    case 15: case 17: case 19: case 21:
    case 23: case 24: case 25: case 26: case 27:
    case 29: case 31: case 33: case 35: case 37:
        break;
    default:
        result = lbl_802557B8[index];
    }
    return result;
}
