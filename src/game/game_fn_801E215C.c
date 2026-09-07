typedef signed short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct LookupRow LookupRow;
struct LookupRow {
    s16 values[5];
};

typedef struct Object Object;
struct Object {
    u32 pad0;
    u32 flags;
};

typedef struct Current Current;
struct Current {
    unsigned char pad0[0x3C];
    s32 value;
};

typedef struct Context Context;
struct Context {
    unsigned char pad0[0x34];
    Object* object;
    unsigned char pad38[0x54];
    Current* current;
};

extern LookupRow lbl_8023BA30[];
extern u32 lbl_8064C4E0;
extern u32* lbl_8064C5A8;
extern s32 lbl_8064D18C;
extern u32 lbl_80651218;
extern u32 lbl_8065121C;
extern u32 lbl_80651F34;

extern u32 fn_80201ADC(void);
extern Context* fn_80201B8C(void);
extern u32 fn_80201814(s32);
extern s32 fn_801E79FC(u32, s32);
extern void fn_801E79A0(u32, s32);
extern s32 fn_801D38E8(u32);
extern s32 fn_802019EC(s32, s32);
extern void* fn_80201BC8(s32);
extern void fn_8012C478(void*, s32, s32);
extern void fn_8012C62C(void*, s32, u32*, u32*, u32*, s32);

void fn_801E215C(s32 type)
{
    s32 effect = 0;
    s32 removed;
    Object* object;
    s32 allowed;
    s32 handle;
    void* result;

    if (type == 0x5A) {
        effect = 0x1C7;
    } else if (type == 0xCA) {
        effect = 0x34A;
    }

    if (effect == 0) {
        return;
    }
    removed = 0;

    if (fn_80201ADC() != 0 &&
        fn_80201814(fn_80201B8C()->current->value) != 0) {
        object = fn_80201B8C()->object;
        if (fn_801E79FC(lbl_8064C4E0, effect) != 0) {
            allowed = lbl_8023BA30[fn_801D38E8(object->flags)].values[*lbl_8064C5A8] == 1;
            if (lbl_8064D18C == 0xCA) {
                allowed = allowed && ((object->flags & 0x70000) == 0x20000);
            } else if (lbl_8064D18C == 0x5A) {
                allowed = allowed && ((object->flags & 0x70000) == 0x40000);
            }
            if (allowed) {
                fn_801E79A0(lbl_8064C4E0, effect);
                removed = 1;
            }
        }
    }

    handle = fn_80201814(fn_802019EC(effect, type));
    if (handle == 0) {
        return;
    }
    result = fn_80201BC8(handle);
    if (result != 0) {
        if (fn_801E79FC(lbl_8064C4E0, effect) != 0) {
            fn_8012C478(result, 0xF, 0);
        } else {
            u32 first = lbl_80651218;
            u32 second = lbl_8065121C;
            u32 third = lbl_80651F34;
            u32 arg1;
            u32 arg2;
            u32 arg3;
            if (removed) {
                ((u8*)&first)[3] = 0;
                ((u8*)&third)[3] = 5;
            }
            fn_8012C478(result, 0xF, 1);
            arg1 = first;
            arg2 = third;
            arg3 = second;
            fn_8012C62C(result, 0xF, &arg1, &arg2, &arg3, 4);
        }
    }
}
