typedef int s32;
typedef unsigned int u32;

typedef struct Inner Inner;
struct Inner {
    unsigned char pad0[0x3C];
    s32 value;
};

typedef struct Context Context;
struct Context {
    unsigned char pad0[0x8C];
    Inner* inner;
};

extern u32 fn_80201814(s32);
extern Context* fn_80201B8C(void);

s32 fn_801E1ED4(s32 value)
{
    s32 result = 0;

    if (fn_80201814(value)) {
        result = fn_80201B8C()->inner->value;
    }
    return result;
}
