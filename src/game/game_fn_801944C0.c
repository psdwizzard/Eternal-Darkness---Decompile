typedef unsigned char u8;

extern void fn_8019453C(float*, int, void*);

void fn_801944C0(int limit, float* data, void* unused, void* context)
{
    u8 count;
    int column;
    int row;

    count = limit - 4;
    data += (u8)(limit - 4) * 4 + 9;
    row = 0;
    do {
        column = 0;
        while (column < count) {
            fn_8019453C(data, 20, context);
            data += 2;
            column++;
        }
        row++;
        data += 2;
    } while (row < 2);
}
