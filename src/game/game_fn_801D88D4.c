typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

extern void* fn_80201814(u32);
extern int fn_80201AE4(void);
extern void* fn_80201B8C(void*);
extern int fn_80038308(void*, int, s16*);
extern int fn_80038464(void*, int, s16*);
extern void fn_800389E0(void*, int, s16, int);
extern const double lbl_80651100;
extern const double lbl_80651108;

void fn_801D88D4(u32 flags, u32 subject)
{
    void* object = fn_80201814(subject);
    int local_player;
    int value = 0;
    int value0;
    int value1;
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;

    if (object == 0) {
        return;
    }
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
        if (fn_80038464(object, 3, &first)) {
            fn_800389E0(object, 3, first, 0);
        }
        fn_80038308(object, 0, &second);
        fn_80038464(object, 0, &third);
        switch (flags & 0x70000) {
        case 0x10000:
            value = (int)(lbl_80651100 * third + second);
            break;
        case 0x20000:
            value = (int)(lbl_80651108 * third + second);
            break;
        case 0x40000:
            value = third;
            break;
        }
        fn_800389E0(object, 0, value, local_player);
        break;
    case 2:
        fn_80038308(object, 2, &first);
        switch (flags & 0x70000) {
        case 0x10000:
            value = first + 30;
            break;
        case 0x20000:
            value = first + 40;
            break;
        case 0x40000:
            value = first + 50;
            break;
        }
        fn_800389E0(object, 2, value, local_player);
        break;
    case 4:
        fn_80038308(object, 1, &second);
        fn_80038464(object, 1, &first);
        switch (flags & 0x70000) {
        case 0x10000:
            value = (int)(lbl_80651100 * first + second);
            break;
        case 0x20000:
            value = (int)(lbl_80651108 * first + second);
            break;
        case 0x40000:
            value = first;
            break;
        }
        fn_800389E0(object, 1, value, local_player);
        break;
    case 8:
        value0 = 0;
        value1 = 0;
        if (fn_80038464(object, 3, &first)) {
            fn_800389E0(object, 3, first, 0);
        }
        fn_80038308(object, 0, &fourth);
        fn_80038308(object, 1, &third);
        fn_80038464(object, 0, &second);
        fn_80038464(object, 1, &first);
        switch (flags & 0x70000) {
            case 0x10000:
                value0 = (int)(lbl_80651100 * second + fourth);
                value1 = (int)(lbl_80651100 * first + third);
                break;
            case 0x20000:
                value0 = (int)(lbl_80651108 * second + fourth);
                value1 = (int)(lbl_80651108 * first + third);
                break;
            case 0x40000:
                value0 = second;
                value1 = first;
                break;
        }
        fn_800389E0(object, 0, value0, local_player);
        fn_800389E0(object, 1, value1, local_player);
        break;
    }
}
