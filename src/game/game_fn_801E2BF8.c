typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef int s32;
typedef float f32;

typedef struct EffectState {
    u8 pad0[0x14];
    s32 field14;
    u8 pad18[4];
    s16 limit;
    u8 pad1e[4];
    s16 state;
    u16 duration;
    s16 timer;
    u8 pad28[4];
    s8 increment;
    u8 pad2d[0xF];
    f32 value;
} EffectState;

extern f32 lbl_80651240;
extern EffectState* fn_801FD6F4(void*);
extern s32 fn_801FE05C(void*);
extern void fn_801FDB10(void*);

s32 fn_801E2BF8(void* object)
{
    EffectState* state = fn_801FD6F4(object);

    if (state != 0) {
        f32 value = (f32)state->increment + state->value;

        if (state->limit < value) {
            value = state->limit;
        }
        state->value = value;
        state->value = lbl_80651240 > state->value ? lbl_80651240 : state->value;
        if (state->timer >= state->duration) {
            if (fn_801FE05C(object) != 0) {
                state->state = 2;
            }
        } else if (state->field14 == 0) {
            fn_801FDB10(object);
        }
    }
    return 1;
}
