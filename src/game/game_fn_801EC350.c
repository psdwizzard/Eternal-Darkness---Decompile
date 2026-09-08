typedef unsigned char u8;
typedef signed char s8;

extern u8 fn_801EC304(u8*, int, int);
extern void fn_801EC318(u8*, int, int, int);
extern int fn_800FBFB0(void);

void fn_801EC350(u8* data, int x, int y, int width, int height)
{
    u8 top_left = fn_801EC304(data, x, y);
    u8 bottom_left = fn_801EC304(data, x, y + height);
    u8 bottom_right = fn_801EC304(data, x + width, y + height);
    u8 top_right = fn_801EC304(data, x + width, y);
    int average;
    s8 offset;
    int half_height;
    int half_width;
    int mid_y;
    int mid_x;
    int value;

    average = (top_left + bottom_left) >> 1;
    value = fn_800FBFB0() % height;
    half_height = height >> 1;
    mid_y = y + half_height;
    offset = value - half_height;
    if (fn_801EC304(data, x, mid_y) == 0) {
        value = average + offset;
        if (value > 255)
            value = 255;
        else
            value &= ~(value >> 31);
        fn_801EC318(data, x, mid_y, value);
    }

    average = (top_left + top_right) >> 1;
    half_width = width >> 1;
    mid_x = x + half_width;
    if (fn_801EC304(data, mid_x, y) == 0) {
        offset = fn_800FBFB0() % width - half_width;
        value = average + offset;
        if (value > 255)
            value = 255;
        else
            value &= ~(value >> 31);
        fn_801EC318(data, mid_x, y, value);
    }

    average = (bottom_left + bottom_right) >> 1;
    if (fn_801EC304(data, mid_x, y + height) == 0) {
        offset = fn_800FBFB0() % width - half_width;
        value = average + offset;
        if (value > 255)
            value = 255;
        else
            value &= ~(value >> 31);
        fn_801EC318(data, mid_x, y + height, value);
    }

    average = (top_right + bottom_right) >> 1;
    if (fn_801EC304(data, x + width, mid_y) == 0) {
        offset = fn_800FBFB0() % height - half_height;
        value = average + offset;
        if (value > 255)
            value = 255;
        else
            value &= ~(value >> 31);
        fn_801EC318(data, x + width, mid_y, value);
    }

    average = (top_left + bottom_left + top_right + bottom_right) >> 2;
    if (fn_801EC304(data, mid_x, mid_y) == 0) {
        int span = (height + width) >> 1;
        offset = fn_800FBFB0() % span - (span >> 1);
        value = average + offset;
        if (value > 255)
            value = 255;
        else
            value &= ~(value >> 31);
        fn_801EC318(data, mid_x, mid_y, value);
    }

    if (width > 1 || height > 1) {
        fn_801EC350(data, x, y, half_width, half_height);
        fn_801EC350(data, mid_x, y, half_width, half_height);
        fn_801EC350(data, x, mid_y, half_width, half_height);
        fn_801EC350(data, mid_x, mid_y, half_width, half_height);
    }
}
