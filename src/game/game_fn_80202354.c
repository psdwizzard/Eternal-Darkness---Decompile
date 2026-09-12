extern int lbl_8064D18C;

extern void fn_801A7460(void* object, int value);
extern void fn_801A74A0(void* object, int value);
extern void fn_801A74A8(void* object, int value);
extern void fn_801A74C8(void* object, int value);
extern void fn_801A7518(void* object, int value);
extern void fn_801A7538(void* object, int value);
extern void fn_801A7550(void* object, int value);
extern void fn_801A7560(void* object, int value);
extern void fn_801A7598(void* object, int value);
extern void fn_801A764C(void* object, int value);
extern void fn_801A7678(void* object, int value);

void fn_80202354(void* object, int value1, int value2, int value3)
{
    fn_801A7460(object, 0x19);
    fn_801A74A0(object, value2);
    fn_801A74A8(object, 0);
    fn_801A74C8(object, 1);
    fn_801A7560(object, 0xA800);
    fn_801A7538(object, 1);

    if (lbl_8064D18C == 0xD0) {
        fn_801A7678(object, 0xF);
        fn_801A7518(object, 0x7FFF);
    } else {
        fn_801A7518(object, 0xA);
    }

    fn_801A7550(object, value1);
    fn_801A7598(object, 0x320);
    fn_801A764C(object, value3);
}
