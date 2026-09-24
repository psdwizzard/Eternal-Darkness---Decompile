typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

extern s32 lbl_8064D18C;
extern int fn_80200C38();
extern int fn_80201EB8();
extern s32 fn_801A74F8(s32 value);
extern u16 fn_801A7530(s32 value);
extern void fn_801A7488(s32 value);
extern void* fn_801A7498(s32 value);
extern int fn_80201B54();
extern void fn_80201F80(s32 context, s32 zero, s32 flags);
extern int fn_80201B44();
extern void *fn_80201B9C();
extern void *fn_80204844(void *object, s32 value);
extern void *fn_8006D444(void);
extern s32 fn_8006D344(void *object, s32 flags, s32 zero);
extern unsigned long long fn_8020123C();
extern int fn_80038308(void *, int, short *);
extern s32 fn_80038464(s32 context, s32 index, s16 *value);
extern s32 fn_80064E2C(s32 context, s32 value, s32 index, u16 mask,
                      s32 amount, s32 first, s32 second);
extern s32 fn_801A7500(s32 value);
extern s32 fn_801A7508(s32 value);
extern s32 fn_801A7510(s32 value);

void fn_80064B38(s32 context, void *event, s32 *result)
{
    s32 event_value;
    s32 output = 0;
    s32 owner;
    s32 amount;
    u16 mask;
    s32 current;
    s32 index;
    s16 first;
    s16 second;
    s32 extra1;
    s32 extra2;
    s32 extra3;
    volatile s32 bit;

    event_value = fn_80200C38(event);
    current = fn_80201EB8((void *)context);
    if (lbl_8064D18C == current || current == -1) {
        amount = fn_801A74F8(event_value);
        mask = fn_801A7530(event_value);
        fn_801A7488(event_value);
        fn_801A7498(event_value);
        owner = fn_80201B54(context);

        if ((s16)amount == 0x7FFF) {
            fn_80201F80(context, 0, 0x800);
        }

        current = owner == fn_80201B44();
        mask = (u16)mask;
        if ((mask & 1) && current) {
            void *object = fn_80201B9C();
            object = fn_80204844(object, 0x20);
            object = fn_8006D444();
            if (fn_8006D344(object, 0x10000, 0)) {
                fn_8020123C(8, owner, owner, 0);
                return;
            }
        }

        for (index = 0; index < 4; index++) {
            bit = 1 << index;
            if ((mask & bit) && fn_80038308((void *)context, index, &first) &&
                fn_80038464(context, index, &second)) {
                output |= fn_80064E2C(context, event_value, index, bit,
                                      amount, first, second);
            }
        }

        extra1 = fn_801A7500(event_value);
        extra2 = fn_801A7508(event_value);
        extra3 = fn_801A7510(event_value);

        bit = 1;
        if ((s16)extra1 && fn_80038308((void *)context, 1, &first) &&
            fn_80038464(context, 1, &second)) {
            output |= fn_80064E2C(context, event_value, 1, 1 << bit,
                                  extra1, first, second);
        }
        bit = 2;
        if ((s16)extra2 && fn_80038308((void *)context, 2, &first) &&
            fn_80038464(context, 2, &second)) {
            output |= fn_80064E2C(context, event_value, 2, 1 << bit,
                                  extra2, first, second);
        }
        bit = 3;
        if ((s16)extra3 && fn_80038308((void *)context, 3, &first) &&
            fn_80038464(context, 3, &second)) {
            output |= fn_80064E2C(context, event_value, 3, 1 << bit,
                                  extra3, first, second);
        }
    }

    if (result != 0) {
        *result = output;
    }
}
