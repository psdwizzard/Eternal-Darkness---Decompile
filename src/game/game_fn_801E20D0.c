typedef int s32;
typedef unsigned int u32;

typedef struct Current Current;
struct Current {
    unsigned char pad0[0x3C];
    s32 value;
};

typedef struct Context Context;
struct Context {
    unsigned char pad0[0x8C];
    Current* current;
};

extern u32 lbl_80651210;
extern u32 lbl_80651214;
extern u32 lbl_80651F30;

extern s32 fn_80201814(s32);
extern Context* fn_80201B8C(void);
extern void fn_8020123C(s32, s32, s32, s32);
extern void* fn_80201BC8(s32);
extern void fn_8012C62C(void*, s32, u32*, u32*, u32*, s32);

void fn_801E20D0(s32 value)
{
    s32 handle = fn_80201814(value);

    if (handle != 0) {
        s32 current = fn_80201B8C()->current->value;
        if (current != 0) {
            u32 first;
            u32 second;
            u32 third;
            void* object;

            fn_8020123C(0x39, current, current, 0);
            object = fn_80201BC8(handle);
            third = lbl_80651214;
            second = lbl_80651F30;
            first = lbl_80651210;
            fn_8012C62C(object, 0xF, &first, &second, &third, 4);
        }
    }
}
