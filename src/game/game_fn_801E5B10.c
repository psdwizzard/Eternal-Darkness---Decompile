typedef unsigned char u8;
typedef unsigned int u32;

extern void* lbl_8064D568;
extern void* lbl_8064D570;
extern u32 lbl_8064D580;
extern u32 lbl_8064D584;
extern u32 lbl_8064D588;
extern void* lbl_8064D58C;
extern u32 lbl_8064D594;
extern u32 lbl_8064D598;
extern u32 lbl_8064D59C;
extern volatile u32 lbl_80651290;
extern u8 lbl_8064C31A;
extern u8 lbl_80633418[];

extern void fn_8022C40C(void**, void*);
extern void* memset(void*, int, unsigned long);
extern void fn_801E5AE0(void);

void fn_801E5B10(void* first, void* second, u32 value, void* callback)
{
    u32 current_time;

    lbl_8064D598 = 0;
    lbl_8064D588 = 0;

    if (first != 0 && lbl_8064D568 == 0) {
        fn_8022C40C(&lbl_8064D568, first);
    }
    if (second != 0 && lbl_8064D570 == 0) {
        fn_8022C40C(&lbl_8064D570, second);
    }

    lbl_8064D59C = value;
    current_time = lbl_80651290;
    lbl_8064D594 = current_time;
    lbl_8064D580 = 0;
    lbl_8064C31A = 110;
    lbl_8064D584 = 0;
    lbl_8064D58C = callback;
    memset(lbl_80633418, 0, 0x28);
    fn_801E5AE0();
}
