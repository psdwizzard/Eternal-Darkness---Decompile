typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

extern void* fn_80201814(u32);
extern int fn_80201AE4(void);
extern void* fn_80201B8C(void*);
extern int fn_80038308(void*, int, s16*);
extern int fn_80038464(void*, int, s16*);
extern void fn_800389E0(void*, int, int, int);
extern const double lbl_80651100;
extern const double lbl_80651108;

void fn_801D88D4(int flags, int subject)
{
    void* object = fn_80201814(subject);
    int local_player;
    int value;
    int value0;
    int value1;
    s16 case1_second;
    s16 case1_third;
    s16 case1_first;
    s16 case2_first;
    s16 case4_second;
    s16 case4_first;
    s16 case8_fourth;
    s16 case8_third;
    s16 case8_second;
    s16 case8_initial;
    s16 case8_first;

    if (object == 0) {
        return;
    }
    value = 0;
    if (subject == fn_80201AE4()) {
        local_player = 1;
    } else {
        flags = (flags & ~0xF) | 1;
        local_player = 0;
    }
    if (*(u8*)((u8*)fn_80201B8C(object) + 0x9F) == 13) {
        return;
    }

    switch (flags & 0xF) {
    case 1:
        if (fn_80038464(object, 3, &case1_first)) {
            fn_800389E0(object, 3, case1_first, 0);
        }
        fn_80038308(object, 0, &case1_second);
        fn_80038464(object, 0, &case1_third);
        switch (flags & 0x70000) {
        case 0x10000:
            value = (int)(lbl_80651100 * case1_third + case1_second);
            break;
        case 0x20000:
            value = (int)(lbl_80651108 * case1_third + case1_second);
            break;
        case 0x40000:
            value = case1_third;
            break;
        }
        fn_800389E0(object, 0, value, local_player);
        break;
    case 2:
        fn_80038308(object, 2, &case2_first);
        switch (flags & 0x70000) {
        case 0x10000:
            value = case2_first + 30;
            break;
        case 0x20000:
            value = case2_first + 40;
            break;
        case 0x40000:
            value = case2_first + 50;
            break;
        }
        fn_800389E0(object, 2, value, local_player);
        break;
    case 4:
        fn_80038308(object, 1, &case4_second);
        fn_80038464(object, 1, &case4_first);
        switch (flags & 0x70000) {
        case 0x10000:
            value = (int)(lbl_80651100 * case4_first + case4_second);
            break;
        case 0x20000:
            value = (int)(lbl_80651108 * case4_first + case4_second);
            break;
        case 0x40000:
            value = case4_first;
            break;
        }
        fn_800389E0(object, 1, value, local_player);
        break;
    case 8:
        value0 = 0;
        value1 = 0;
        if (fn_80038464(object, 3, &case8_initial)) {
            fn_800389E0(object, 3, case8_initial, 0);
        }
        fn_80038308(object, 0, &case8_fourth);
        fn_80038308(object, 1, &case8_third);
        fn_80038464(object, 0, &case8_second);
        fn_80038464(object, 1, &case8_first);
        switch (flags & 0x70000) {
            case 0x10000:
                value0 = (int)(lbl_80651100 * case8_second + case8_fourth);
                value1 = (int)(lbl_80651100 * case8_first + case8_third);
                break;
            case 0x20000:
                value0 = (int)(lbl_80651108 * case8_second + case8_fourth);
                value1 = (int)(lbl_80651108 * case8_first + case8_third);
                break;
            case 0x40000:
                value0 = case8_second;
                value1 = case8_first;
                break;
        }
        fn_800389E0(object, 0, value0, local_player);
        fn_800389E0(object, 1, value1, local_player);
        break;
    }
}
