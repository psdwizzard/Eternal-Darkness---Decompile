typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

typedef struct Runtime Runtime;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;

extern s32 fn_80201B54(s32 *object);
extern void *fn_80201BC8(void *object);
extern void *fn_80036D5C(void *object);
extern void fn_80036DA4(void *object, void *value);
extern void fn_8003C6B8(void *object, void *resource, s32 id);
extern u8 *fn_801294DC(void *owner, s32 kind, s32 flags, s32 mode);
extern void fn_80128C28(Runtime *runtime, u32 callback, u32 argument);
extern s32 fn_8003CB6C(void *unused, s32 id);
extern void fn_80201138(s32 kind, void *context, s32 value, s32 id,
                       s32 argument, f32 delay);
extern void fn_80201D2C(Object80201D2C *object, s32 value);
extern void fn_80201D14(Object80201D14 *object, u8 value);
extern s32 lbl_8064D18C;
extern const f32 lbl_8064E288;
extern const f32 lbl_8064E28C;

void fn_8003C758(void *object)
{
    void *resource;
    s32 id;
    u32 flags;
    u8 *animation;
    double delay;

    id = fn_80201B54(object);
    fn_80036D5C(object);
    resource = fn_80201BC8(object);
    flags = (u32)fn_80036D5C(object);
    if (flags & 0x80) {
        fn_8003C6B8(object, resource, id);
    } else if (!(flags & 2)) {
        animation = fn_801294DC(resource, 0x18, 0x20, 10);
        if (animation != 0) {
            fn_80128C28((Runtime *)animation, (u32)fn_8003CB6C, id);
            if (lbl_8064D18C == 0xFB) {
                delay = lbl_8064E288;
            } else {
                delay = lbl_8064E28C;
            }
            fn_80201138(0x18, object, 9, -1, 0, delay);
            fn_80036DA4(object, (void *)(flags | 2));
            fn_80201D2C(object, 9);
            fn_80201D14(object, 1);
        }
    }
}
