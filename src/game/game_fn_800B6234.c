extern int lbl_8064C6BC[2];

extern int fn_800B6908(void);
extern void fn_800B2548(int, int);
extern int fn_800B1944(void);
extern int fn_8017B47C(int, int*, int*);
extern int CARDFreeBlocks(int, int*, int*);
extern void fn_800B669C(int, int);
extern void fn_800B5E90(int, int);

void fn_800B6234(int value, int status)
{
    int mode = status;

    status = fn_800B6908();

    switch (mode) {
    case -6:
        fn_800B2548(21, value);
        if (fn_800B1944() == 2) {
            lbl_8064C6BC[value] = 2;
        }
        break;
    case -4:
        if (fn_800B1944() == 2) {
            int primary_value;
            int primary_level;
            int fallback_value;
            int fallback_level;
            int result = fn_8017B47C(value, &primary_value, &primary_level);

            if (result == 0) {
                result = CARDFreeBlocks(value, &fallback_value, &fallback_level);
            }
            lbl_8064C6BC[value] = 2;
            if (result == 0) {
                if (fallback_level < 1) {
                    fn_800B2548(39, value);
                } else if (fallback_value < 0x1E000) {
                    fn_800B2548(38, value);
                } else {
                    fn_800B669C(value, 0);
                }
            } else {
                fn_800B5E90(value, result);
            }
        } else if (status == 0) {
            fn_800B2548(22, value);
        } else {
            fn_800B2548(65, value);
        }
        break;
    case -3:
    case -1:
        fn_800B2548(62, value);
        break;
    case -10:
        fn_800B2548(64, value);
        break;
    case 0:
        break;
    default:
        fn_800B2548(63, value);
        break;
    }
}
