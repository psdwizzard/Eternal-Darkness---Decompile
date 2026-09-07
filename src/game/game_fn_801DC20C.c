typedef signed short s16;
typedef unsigned int u32;

extern s16 fn_801CEB2C(u32);
extern int fn_800AD2B4(void);
extern int fn_801D38E8(u32);
extern s16 lbl_8023BA30[][5];

int fn_801DC20C(u32 first, u32 second, int expected)
{
    int result;
    int first_rank;
    int second_rank;
    first_rank = fn_801CEB2C(first) >> 1;
    second_rank = fn_801CEB2C(second) >> 1;
    if (expected == fn_800AD2B4()) {
        result = 1;
    } else {
        result = 0;
        if (!(first & 8)) {
            if (lbl_8023BA30[fn_801D38E8(second)][fn_801D38E8(first)] != -1) {
                goto done;
            }
        }
        if (second_rank <= first_rank) {
            result = 1;
        }
    }
done:
    return result;
}
