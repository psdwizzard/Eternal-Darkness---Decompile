typedef signed short s16;
typedef unsigned char u8;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_8016A7D8(void*);
extern void fn_8016A830(void*, double);
extern void fn_80163BB4(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201C24();
extern s16 fn_801578E8(void*);
extern s16 fn_801578F4(void*);
extern unsigned int fn_80157BC4(void*);
extern unsigned int fn_80157BDC(void*);
extern unsigned int fn_80157BD0(void*);
extern unsigned int fn_80157900(void*);
extern u8 fn_80157AB8(void*);
extern u8 fn_80157918(void*);
extern const char lbl_8024FF00[];

int fn_80175BB8(void* state)
{
    const char* strings = lbl_8024FF00;
    int kind;
    int object_id;
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, strings, 2, fn_8016A598(state));
        return 0;
    }
    object_id = fn_8016A694(state, 1);
    kind = fn_8016A694(state, 2);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        fn_8016A694(state, 3);
        switch (kind) {
        case 0: fn_8016A830(state, fn_801578E8(object)); break;
        case 1: fn_8016A830(state, fn_801578F4(object)); break;
        case 2: fn_8016A830(state, fn_80157BC4(object)); break;
        case 3: fn_8016A830(state, fn_80157BDC(object)); break;
        case 4: fn_8016A830(state, fn_80157BD0(object)); break;
        case 5: fn_8016A830(state, fn_80157900(object)); break;
        case 6: fn_8016A830(state, fn_80157AB8(object)); break;
        case 7: fn_8016A830(state, fn_80157918(object)); break;
        default:
            fn_8016A7D8(state);
            fn_80163BB4(state, strings + 0x5A8, kind);
            break;
        }
    } else {
        fn_8016A7D8(state);
        fn_80163BB4(state, strings + 0x5CC, object_id);
    }
    return 1;
}
