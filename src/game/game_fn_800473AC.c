typedef struct GlobalState {
    char pad_00[8];
    int mode;
} GlobalState;

extern GlobalState lbl_803003C8;
extern int lbl_8064D18C;
extern int fn_800ACFE0(void);
extern int fn_800A3564(void);

int fn_800473AC(void)
{
    int result = 0;

    switch (lbl_803003C8.mode) {
    case 5:
        if (lbl_8064D18C == 0x124) {
            result = 1;
        }
        break;
    case 13:
        result = fn_800ACFE0();
        break;
    case 10:
    case 15:
        if (lbl_8064D18C == 0x27) {
            result = fn_800A3564();
        }
        break;
    }

    return result;
}
