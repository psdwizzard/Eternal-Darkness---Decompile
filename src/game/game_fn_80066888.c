typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct EventVectors {
    Vec3 origin;
    Vec3 direction;
} EventVectors;

extern f32 lbl_8064E698;
extern f32 lbl_8064E6C0;
extern f32 lbl_8064E6E8;
extern f32 lbl_8064E6EC;

extern u32 fn_801A7590(s32 event);
extern void fn_801A76F4(EventVectors *vectors, s32 event);
extern f32 fn_80211B08(Vec3 *position);
extern s32 fn_80066D80(s32 context, s32 index);
extern s32 fn_801A74F8(s32 event);
extern void fn_8012EDB0(s32 context, s32 index, Vec3 *position, f32 first,
                        f32 second);
extern s32 fn_8013057C(s32 context, s32 index);
extern void fn_801301B0(s32 context, s32 clear, s32 set);

#pragma opt_common_subs off
void fn_80066888(s32 context, s32 event, f32 first, f32 second)
{
    EventVectors vectors;
    Vec3 copied_position;
    u32 mask;
    s32 index;
    s32 any_active;

    mask = fn_801A7590(event);
    any_active = 0;
    fn_801A76F4(&vectors, event);

    if (fn_80211B08(&vectors.direction) > lbl_8064E6C0) {
        copied_position = vectors.direction;
        for (index = 0; index < 15; index++) {
            if ((mask & (1U << index)) && fn_80066D80(context, index)) {
                f32 scale = (f32)(s16)fn_801A74F8(event) / lbl_8064E6E8;
                f32 bounded = lbl_8064E6EC;
                f32 upper = lbl_8064E698;

                if (scale > bounded) {
                    bounded = scale;
                }
                if (upper < bounded) {
                    bounded = lbl_8064E698;
                } else if (scale > lbl_8064E6EC) {
                    bounded = scale;
                }

                fn_8012EDB0(context, index, &copied_position,
                            first * bounded, second * bounded);
                if (!any_active && fn_8013057C(context, index)) {
                    any_active = 1;
                }
            }
        }

        if (any_active) {
            fn_801301B0(context, 0, 0x40);
        }
    }
}
#pragma opt_common_subs reset
