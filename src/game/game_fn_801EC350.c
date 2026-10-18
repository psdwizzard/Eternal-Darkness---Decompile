typedef unsigned char u8;
typedef signed char s8;

extern u8 fn_801EC304(u8*, int, int);
extern void fn_801EC318(u8*, int, int, u8);
extern int rand(void);

/* Keep derived coordinates and clamp sums as expressions: MWCC
 * allocates their common subexpressions differently from named locals. */
void fn_801EC350(u8* data, int x, int y, int width, int height)
{
    u8 top_left = fn_801EC304(data, x, y);
    u8 bottom_left = fn_801EC304(data, x, y + height);
    u8 bottom_right = fn_801EC304(data, x + width, y + height);
    u8 top_right = fn_801EC304(data, x + width, y);
    int average;
    int right_average;
    s8 offset;
    int value;
    int span;

    average = (top_left + bottom_left) >> 1;
    value = rand() % height;
    offset = value - (height >> 1);
    if (fn_801EC304(data, x, (y + (height >> 1))) == 0) {
        fn_801EC318(data, x, (y + (height >> 1)),
                    (average + offset) > 255 ? 255
                        : ((average + offset) < 0 ? 0 : (average + offset)));
    }

    average = (top_left + top_right) >> 1;
    if (fn_801EC304(data, (x + (width >> 1)), y) == 0) {
        offset = rand() % width - (width >> 1);
        fn_801EC318(data, (x + (width >> 1)), y,
                    (average + offset) > 255 ? 255
                        : ((average + offset) < 0 ? 0 : (average + offset)));
    }

    average = (bottom_left + bottom_right) >> 1;
    if (fn_801EC304(data, (x + (width >> 1)), y + height) == 0) {
        offset = rand() % width - (width >> 1);
        fn_801EC318(data, (x + (width >> 1)), y + height,
                    (average + offset) > 255 ? 255
                        : ((average + offset) < 0 ? 0 : (average + offset)));
    }

    right_average = (top_right + bottom_right) >> 1;
    if (fn_801EC304(data, x + width, (y + (height >> 1))) == 0) {
        offset = rand() % height - (height >> 1);
        fn_801EC318(data, x + width, (y + (height >> 1)),
                    (right_average + offset) > 255 ? 255
                        : ((right_average + offset) < 0 ? 0 : (right_average + offset)));
    }

    average = (top_left + bottom_left + bottom_right + top_right) >> 2;
    span = (height + width) >> 1;
    if (fn_801EC304(data, (x + (width >> 1)), (y + (height >> 1))) == 0) {
        offset = rand() % span - (span >> 1);
        fn_801EC318(data, (x + (width >> 1)), (y + (height >> 1)),
                    (average + offset) > 255 ? 255
                        : ((average + offset) < 0 ? 0 : (average + offset)));
    }

    if (width > 1 || height > 1) {
        width >>= 1;
        height >>= 1;
        fn_801EC350(data, x, y, width, height);
        fn_801EC350(data, x + width, y, width, height);
        fn_801EC350(data, x, y + height, width, height);
        fn_801EC350(data, x + width, y + height, width, height);
    }
}
