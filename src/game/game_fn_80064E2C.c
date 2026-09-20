typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct EventPosition {
    s32 x;
    s32 y;
    s32 z;
} EventPosition;

extern s32 lbl_8064C594;
extern s32 lbl_8064C5D8;
extern s32 lbl_8064CB24;
extern s32 lbl_8064C4E0;
extern u8 lbl_803003C8[];
extern float lbl_8064E698;
extern float lbl_8064E69C;

extern u8 *fn_80036D38(s32 context);
extern s32 fn_801A7488(s32 event);
extern void fn_801A7744(EventPosition *position, s32 event);
extern s32 fn_801A7498(s32 event);
extern int fn_80201B54();
extern int fn_80201B44();
extern u32 fn_801A74C0(s32 event);
extern void *fn_80201814();
extern s32 fn_80071D5C(void *object);
extern s32 fn_801A74F8(s32 event);
extern void fn_801A7518(s32 event, s32 value);
extern unsigned long long fn_8020123C();
extern int fn_801E79FC(void*, int);
extern void fn_801E7974(s32 object, s32 value);
extern void fn_80006954(s32 value);
extern s32 fn_800389E0(s32 context, s32 index, s16 value, s32 active);
extern s32 fn_802021AC(s32 context);
extern s32 fn_801A717C(void);
extern void fn_801A74A0(s32 event, s32 owner);
extern void fn_801A74A8(s32 event, s32 owner);
extern void fn_801A7538(s32 event, s32 value);
extern void fn_801A764C(s32 event, EventPosition *position);
extern void fn_801A7228(s32 event);
extern void *fn_80201BC8();
extern void fn_80120AD0(void *object, s32 zero, s32 amount, s32 kind,
                        float first, float second);

s32 fn_80064E2C(u32 context, s32 event, s32 index, u16 mask, s32 amount,
                 s16 first, s16 lower)
{
    u8 *state;
    s32 original_event;
    EventPosition copied_position;
    EventPosition position;
    s32 made_event;
    s32 result;
    s32 feedback;
    s32 event_value;
    s32 owner;
    s32 is_current_owner;
    s16 original_first;
    s32 update_result;
    s32 has_four;
    void *object;

    state = fn_80036D38(context);
    original_event = fn_801A7488(event);
    fn_801A7744(&position, event);
    copied_position = position;
    original_first = first;
    made_event = 0;
    result = 0;
    feedback = -1;
    event_value = fn_801A7498(event);
    owner = fn_80201B54(context);
    is_current_owner = owner == fn_80201B44();

    if (!(fn_801A74C0(event) & 0x00800000) && (s16)amount > 0) {
        s32 target = *(s32 *)(state + 0x24);
        object = fn_80201814(target);
        if (object != 0 && (!is_current_owner || fn_80071D5C(object) == 0)) {
            s32 old_amount = fn_801A74F8(event);
            u32 response;
            fn_801A7518(event, amount);
            response = (u32)fn_8020123C(0xB, owner, target, event);
            fn_801A7518(event, old_amount);
            if (!(mask & (u16)response)) {
                return 0;
            }
        }
    }

    has_four = mask & 4;
    mask = (u16)mask;
    if (has_four && lbl_8064C594 == 0) {
        return 0;
    }

    if ((mask & 1) && is_current_owner) {
        if (fn_801E79FC((void *)lbl_8064C4E0, 0x360) == 0 &&
            *(s32 *)(lbl_803003C8 + 8) == 1) {
            lbl_8064C5D8 = 1;
            fn_80006954(100);
            fn_801E7974(lbl_8064C4E0, 0x2B6);
        }
    } else if ((mask & 2) && is_current_owner) {
        if (fn_801E79FC((void *)lbl_8064C4E0, 0x2CD) == 0 &&
            *(s32 *)(lbl_803003C8 + 8) == 2) {
            lbl_8064C5D8 = 1;
            fn_80006954(100);
            fn_801E7974(lbl_8064C4E0, 0x2CC);
        }
    }

    if ((mask & 2) && is_current_owner && (s16)amount > 0) {
        feedback = 1;
        fn_8020123C(0xC9, owner, event_value, 1);
    } else if (has_four && is_current_owner && (s16)amount > 0) {
        feedback = 2;
    }

    first = (s16)(first - (s16)amount);
    first = first < lower ? first : lower;
    /* Codegen-shaping spelling: emits retail's neg/andc/srawi/and clamp. */
    first = (s16)(first & ((-first & ~first) >> 31));

    update_result = fn_800389E0(context, index, first, 1);
    result |= 1;
    if (first != 0 && original_event != -1 && index == 0) {
        u32 response = (u32)(fn_8020123C(0x35, event_value, owner, event) &
                             0xFFFFFFFFULL);
        s32 response_result = result | 0x10;
        if (response & 1) {
            response_result = result | 0x30;
        }
        result = response_result;
    } else if (first <= 0 && index == 0 && update_result != 0) {
        if (fn_802021AC(context) == 0) {
            fn_8020123C(8, event_value, owner, 0);
            result |= 2;
        } else {
            fn_800389E0(context, index, 0, 1);
        }
    } else if (first <= 0 && original_first <= 0 && index == 1 &&
               is_current_owner) {
        s32 created = fn_801A717C();
        s32 half;
        made_event = 1;
        fn_801A74A0(created, owner);
        fn_801A74A8(created, owner);
        fn_801A7538(created, 1);
        half = 1;
        if (((s16)amount >> 1) >= 1) {
            half = ((s16)amount) >> 1;
        }
        fn_801A7518(created, (s16)half);
        fn_801A764C(created, &copied_position);
        if (((u32)(fn_8020123C(0x27, event_value, owner, created) &
                    0xFFFFFFFFULL) & 1) != 0) {
            feedback = 0;
        }
        fn_801A7228(created);
    } else if (state != 0 && first <= (s16)state[0x166] && index == 0) {
        fn_8020123C(9, event_value, owner, 0);
        result |= 4;
    }

    object = context != 0 ? fn_80201BC8(context) : 0;
    if (feedback == 0) {
        if (object != 0) {
            fn_80120AD0(object, 0, 100, 0x22, lbl_8064E698,
                         lbl_8064E69C);
        }
    } else if (feedback == 1) {
        if (object != 0 && !made_event && lbl_8064CB24 == 0) {
            fn_80120AD0(object, 0, 100, 0x12, lbl_8064E698,
                         lbl_8064E69C);
        }
    } else if (feedback == 2) {
        if (object != 0 && lbl_8064C594 != 0 &&
            fn_801E79FC((void *)lbl_8064C4E0, 0x257) != 0) {
            fn_80120AD0(object, 0, 100, 0xA, lbl_8064E698,
                         lbl_8064E69C);
        }
    }
    return result;
}
