typedef unsigned int u32;

typedef struct Vec800A3C84 {
    u32 z;
    u32 y;
    u32 x;
} Vec800A3C84;

typedef struct Vec4_800A3C84 {
    u32 w;
    u32 z;
    u32 y;
    u32 x;
} Vec4_800A3C84;

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

/*
 * Behavior-complete reconstruction of the three-mode vector/action dispatch.
 * The remaining differences are MWCC's argument-address scheduling and the
 * temporary register selected for the first vector word in the first two
 * arms. Objdiff: 95.58209%, size-exact at 268 bytes.
 */
void fn_800A3C84(void* object, void* runtime, int first, int second)
{
    if (first != 0) {
        Vec800A3C84 values;
        values.z = lbl_8064EEB4;
        values.y = lbl_8064EEB0;
        values.x = lbl_8064EEAC;
        fn_8012C62C(object, runtime, (float*)&values.x, (float*)&values.y,
                     (float*)&values.z, 4);
        fn_8012C478(object, runtime, 1);
    } else if (second != 0) {
        Vec800A3C84 values;
        values.z = lbl_8064EEC0;
        values.y = lbl_8064EEBC;
        values.x = lbl_8064EEB8;
        fn_8012C62C(object, runtime, (float*)&values.x, (float*)&values.y,
                     (float*)&values.z, 4);
        fn_8012F58C(object, runtime, 0, 0, 0, 0x40);
    } else {
        Vec4_800A3C84 values;
        values.w = lbl_8064EEC4;
        values.z = lbl_8064EEC4;
        values.y = lbl_80651A28;
        values.x = lbl_8064EEC4;
        fn_8012C62C(object, runtime, (float*)&values.x, (float*)&values.y,
                     (float*)&values.z, 4);
        fn_8012C478(object, runtime, 0);
    }
}
