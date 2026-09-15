typedef unsigned int u32;

extern u32 lbl_8064EEAC;
extern u32 lbl_8064EEB0;
extern u32 lbl_8064EEB4;
extern u32 lbl_8064EEB8;
extern u32 lbl_8064EEBC;
extern u32 lbl_8064EEC0;
extern u32 lbl_8064EEC4;
extern u32 lbl_80651A28;

extern void* fn_8012C62C(void*, void*, float*, float*, float*, int);
extern void fn_8012C478(void*, void*, int);
extern void fn_8012F58C(void*, void*, int, int, int, int);

/* Three-mode vector/action dispatch. */
void fn_800A3C84(void* object, void* runtime, int first, int second)
{
    u32 first_x;
    u32 first_y;
    u32 first_z;
    u32 second_x;
    u32 second_y;
    u32 second_z;
    u32 third_x;
    u32 third_y;
    u32 third_z;
    volatile u32 third_w;

    if (first != 0) {
        first_z = lbl_8064EEB4;
        first_y = lbl_8064EEB0;
        first_x = lbl_8064EEAC;
        fn_8012C62C(object, runtime, (float*)&first_x, (float*)&first_y,
                     (float*)&first_z, 4);
        fn_8012C478(object, runtime, 1);
    } else if (second != 0) {
        second_z = lbl_8064EEC0;
        second_y = lbl_8064EEBC;
        second_x = lbl_8064EEB8;
        fn_8012C62C(object, runtime, (float*)&second_x, (float*)&second_y,
                     (float*)&second_z, 4);
        fn_8012F58C(object, runtime, 0, 0, 0, 0x40);
    } else {
        third_w = lbl_8064EEC4;
        third_z = lbl_8064EEC4;
        third_y = lbl_80651A28;
        third_x = lbl_8064EEC4;
        fn_8012C62C(object, runtime, (float*)&third_x, (float*)&third_y,
                     (float*)&third_z, 4);
        fn_8012C478(object, runtime, 0);
    }
}
