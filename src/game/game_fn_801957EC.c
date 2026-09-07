typedef unsigned char u8;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

void fn_801957EC(u8 width, u8 index, Color* data)
{
    u8 span = width - 4;

    switch (index) {
    case 0:
        data[0].a = 0;
        data += span * 4 + 3;
        data[0].a = 0;
        return;
    case 1:
        data[1].a = 0;
        data++;
        data += span * 4 + 4;
        data[0].a = 0;
        data[1].a = 0;
        data[2].a = 0;
        data += 2;
        data += span * 4 + 3;
        data[0].a = 0;
        data[1].a = 0;
        return;
    }
    if (index == width - 1) {
        data += span * 2 + 2;
        data[0].a = 0;
        return;
    }
    if (index == width - 2) {
        data += span * 2 + 3;
        data[0].a = 0;
        data += span * 4 + 5;
        data[0].a = 0;
        data[1].a = 0;
        return;
    }
    if (index >= width)
        return;

    data += (index - 1) * 2;
    data[0].a = 0;
    data[1].a = 0;
    data++;
    data += (span - index + 2) * 4 - 1;
    data[0].a = 0;
    data[1].a = 0;
    data++;
    data += (index - 2) * 4 + 5;
    data[0].a = 0;
    data[1].a = 0;
    data++;
    data += (span - index + 2) * 4 - 1;
    data[0].a = 0;
    data[1].a = 0;
}
