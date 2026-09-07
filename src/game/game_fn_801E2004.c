typedef int s32;
typedef unsigned int u32;

typedef struct Current Current;
struct Current {
    unsigned char pad0[0x3C];
    s32 value;
};

typedef struct Inner Inner;
struct Inner {
    unsigned char pad0[4];
    s32 value;
};

typedef struct Context Context;
struct Context {
    unsigned char pad0[0x34];
    Inner* inner;
    unsigned char pad38[0x54];
    Current* current;
};

extern u32 fn_80201814(s32);
extern Context* fn_80201B8C(void);
extern void* fn_801D38E8(s32);

void* fn_801E2004(s32 value)
{
    void* result = 0;

    if (fn_80201814(value)) {
        if (fn_80201814(fn_80201B8C()->current->value)) {
            result = fn_801D38E8(fn_80201B8C()->inner->value);
        }
    }
    return result;
}
