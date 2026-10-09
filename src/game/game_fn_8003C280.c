typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

typedef struct ObjectInfo {
    u8 pad0[0x94];
    s32 state;
} ObjectInfo;

extern ObjectInfo *fn_80201B8C(void *object);
extern s32 fn_80038308(void *object, s32 index, s16 *value);
extern s32 fn_80038464(void *object, s32 index, s16 *value);
extern s32 lbl_8064D18C;

s32 fn_8003C280(void *object)
{
    s16 x;
    s16 y;
    ObjectInfo *info;
    s32 matches;
    s32 result;

    info = fn_80201B8C(object);
    fn_80038308(object, 0, &x);
    fn_80038464(object, 0, &y);
    if (lbl_8064D18C == 0x60) {
        return 2;
    }
    matches = 0;
    if (x == y || info->state == 4) {
        matches = 1;
    }
    result = 2;
    if (matches != 0) {
        result = 3;
    }
    return result;
}
