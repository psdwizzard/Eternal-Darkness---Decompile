typedef struct State {
    unsigned char pad0[0x204];
    int active;
} State;

extern State lbl_8063C6B8;
extern State lbl_8063CD18;
extern int fn_801F85A4(void);
extern void fn_801FA354(void);

int fn_801F86F4(int unused)
{
    int result = fn_801F85A4();

    if (result != 0) {
        fn_801FA354();
        lbl_8063CD18.active = 0;
        lbl_8063C6B8.active = 0;
    }
    return result;
}
