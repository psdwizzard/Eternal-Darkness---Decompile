typedef struct Entry80201AF8 Entry80201AF8;

extern int lbl_8064D888;
extern Entry80201AF8 *lbl_8064D88C;

extern Entry80201AF8 *fn_80201814(int);

int fn_80201AF8(int value)
{
    int previous = lbl_8064D888;

    lbl_8064D88C = fn_80201814(value);
    lbl_8064D888 = value;
    return previous;
}
