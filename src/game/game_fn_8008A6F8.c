typedef unsigned char u8;
typedef signed int s32;

extern void* lbl_8064D18C;
extern u8 lbl_803003C8[];
extern float lbl_8064EBC0;
extern float lbl_8064EBC4;

extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern int fn_80201B54();
extern int fn_80201EB8();
extern int fn_801E8328();
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80128C28();
extern void fn_8008A8D8(void);
extern int fn_800389E0(void*, s32, s32, s32);
extern void fn_80201138(s32, void*, s32, s32, float, s32);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

/* Object-spawn callback. Keep the identity lookup as a separate full
 * expression to preserve the canonical compiler's comparison operand order. */
void fn_8008A6F8(void* object)
{
    void* resource;
    s32 object_id;
    void* created;
    s32 zero;
    s32 actual;
    float scale;

    fn_80201B8C(object);
    resource = fn_80201BC8(object);
    object_id = ((s32)fn_80201B54(object));
    actual = fn_80201EB8(object);
    if (actual != (s32)lbl_8064D18C) {
        fn_801E8328(2, object);
        return;
    }

    created = fn_801294DC(resource, 0x18, 0x20, 0xA);
    if (created == 0)
        return;
    fn_80128C28(created, fn_8008A8D8, object_id);
    fn_800389E0(object, 0, 0, 1);
    if (*(s32*)(lbl_803003C8 + 8) == 5)
        scale = lbl_8064EBC0;
    else
        scale = lbl_8064EBC4;
    zero = 0;
    fn_80201138(0x11, object, 8, -1, scale, zero);
    fn_80201D2C(object, 8);
    fn_80201D14(object, 1);
}
