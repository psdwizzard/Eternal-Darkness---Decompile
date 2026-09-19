typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

#pragma use_lmw_stmw on

typedef struct HandlerState {
    unsigned char pad00[0x14];
    s32 object_id;
    s32 context_id;
} HandlerState;

extern f32 lbl_8064E63C;
extern f32 lbl_8064E640;
extern int fn_80200C38();
extern s32 fn_801A74F8(void);
extern u16 fn_801A7530(s32 value);
extern int fn_80038308(void *, int, short *);
extern s32 fn_80038464(s32 context, s32 index, s16 *value);
extern HandlerState *fn_80036D38(s32 context);
extern int fn_80201B44();
extern int fn_800389E0(s32 context, s32 index, s32 value, s32 active);
extern s32 fn_80200C20(s32 value);
extern unsigned long long fn_8020123C();
extern void fn_8011F778(s32 object, f32 value);
extern void fn_80048708(s32 object);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a, b, c, d, e) fn_8020104C((a), (void *)(b), (void *)(c), (int)(d), (e))
extern void fn_80201D34(void *, s32);
extern void fn_80201D1C(void *, s32);

void fn_80063124(s32 context, s32 object, s32 event, s32 current_object,
                  s32 unused, s32 *out_result)
{
    s32 event_data;
    u32 channels;
    s32 step;
    s32 signed_step;
    s32 special;
    s32 index;
    s32 result;

    result = 0;
    event_data = fn_80200C38(event);
    step = fn_801A74F8();
    fn_801A7530(event_data);
    channels = (u16)fn_801A7530(event_data);
    signed_step = (s16)step;
    special = channels & 2;

    for (index = 0; index < 4; index++) {
        if ((channels & (1 << index)) != 0) {
            s16 remaining;
            s16 limit;
            HandlerState *state;
            s32 is_current;

            if (fn_80038308((void *)context, index, &remaining) == 0) {
                continue;
            }
            if (fn_80038464(context, index, &limit) == 0) {
                continue;
            }

            state = fn_80036D38(context);
            is_current = fn_80201B44() == current_object;
            remaining -= signed_step;
            remaining = remaining < limit ? remaining : limit;
            remaining = remaining > 0 ? remaining : 0;
            fn_800389E0(context, index, remaining, 1);

            if (special != 0 && is_current != 0 && (s16)step > 0) {
                fn_8020123C(0xC9, current_object, fn_80200C20(event), 1);
            }

            result |= 1;
            if (remaining <= 0 && index == 0) {
                fn_8011F778(object, lbl_8064E63C);
                fn_80048708(object);
                fn_8020123C(0x24, current_object, state->object_id, 0);
                fn_8020104C(8, state->object_id, current_object, 0,
                            lbl_8064E640);
                fn_80201D34((void *)context, state->context_id);
                fn_80201D1C((void *)context, 1);
                state->object_id = 0;
                state->context_id = 0;
                result |= 2;
            }
        }
    }

    if (out_result != 0) {
        *out_result = result;
    }
}
