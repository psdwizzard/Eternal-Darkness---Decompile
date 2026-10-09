typedef signed int s32;
typedef unsigned char u8;
typedef float f32;

typedef struct ObjectInfo {
    u8 pad0[0x94];
    s32 state;
} ObjectInfo;

extern ObjectInfo *fn_80201B8C(void *object);
extern s32 fn_80066D04(void *object, s32 index);
extern f32 lbl_8064E27C;
extern f32 lbl_8064E280;

f32 fn_8003C210(void *object)
{
    ObjectInfo *info;

    info = fn_80201B8C(object);
    if (info->state == 4 ||
        (fn_80066D04(object, 0) == 0 && info->state == 1)) {
        return lbl_8064E27C;
    }
    return lbl_8064E280;
}
