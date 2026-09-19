typedef signed short s16;
typedef unsigned char u8;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201C24();
extern void fn_80157B48(void*, s16);
extern void fn_80157B54(void*, s16);
extern void fn_80157B94(void*, u8);
extern void fn_80157BAC(void*, u8);
extern void fn_80157BB8(void*, u8);
extern void fn_80157BA0(void*, s16);
extern void fn_80157B60(void*, u8);
extern void fn_80157B3C(void*, u8);
extern const char lbl_8024FF00[];

int fn_80175A08(void* state)
{
    struct { const char* strings; } diagnostic;
    int kind;
    int object_id;
    void* object;
    int value;
    diagnostic.strings = lbl_8024FF00;
    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, diagnostic.strings, 3, fn_8016A598(state));
        return 0;
    }

    object_id = fn_8016A694(state, 1);
    kind = fn_8016A694(state, 2);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        value = fn_8016A694(state, 3);
        switch (kind) {
        case 0:
            fn_80157B48(object, value);
            break;
        case 1:
            fn_80157B54(object, value);
            break;
        case 2:
            fn_80157B94(object, value);
            break;
        case 3:
            fn_80157BAC(object, value);
            break;
        case 4:
            fn_80157BB8(object, value);
            break;
        case 5:
            fn_80157BA0(object, value);
            break;
        case 6:
            fn_80157B60(object, value);
            break;
        case 7:
            fn_80157B3C(object, value);
            break;
        default:
            fn_80163BB4(state, diagnostic.strings + 0x5A8, kind);
            break;
        }
    } else {
        fn_80163BB4(state, diagnostic.strings + 0x5CC, object_id);
    }
    return 0;
}
