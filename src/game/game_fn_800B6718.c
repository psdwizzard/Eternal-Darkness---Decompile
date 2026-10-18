typedef unsigned char u8;

extern int lbl_8064CA64;
extern int lbl_8064CA60;
extern u8 lbl_8064CA31;
extern char lbl_80247434[];

extern int fn_8017B1AC(int, void*);
extern void fn_8017B294(int);
extern void fn_800B2548(int, int);
extern int fn_8017B47C(int, int*, int*);
extern int CARDFreeBlocks(int, int*, int*);
extern void fn_800B6024(int, int);
extern void fn_8017B80C(int);
extern void fn_800B261C(int);
extern void fn_800B52C0(void);
extern void fn_800B2624(int, int, void*, int, void (*)(void));

void fn_800B6718(int value)
{
    int primary_value;
    int primary_level;
    int fallback_value;
    int fallback_level;
    int valid = fn_8017B1AC(value, lbl_80247434);
    int result;

    fn_8017B294(value);
    if (valid == 0) {
        fn_800B2548(50, value);
        return;
    }

    result = fn_8017B47C(value, &primary_value, &primary_level);
    if (result == 0) {
        result = CARDFreeBlocks(value, &fallback_value, &fallback_level);
    }
    if (result == 0) {
        if (fallback_level < 1) {
            fn_800B6024(value, -8);
        } else if (fallback_value < 0x1E000) {
            fn_800B6024(value, -9);
        } else {
            lbl_8064CA64 = 1;
            lbl_8064CA60 = 0;
            fn_8017B80C(0x1E000);
            fn_800B261C(0);
            lbl_8064CA31++;
            fn_800B2624(5, value, lbl_80247434, 1, fn_800B52C0);
        }
    } else {
        fn_800B6024(value, result);
    }
}
