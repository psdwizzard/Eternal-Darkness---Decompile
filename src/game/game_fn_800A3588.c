typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec800A3588 {
    float x, y, z;
} Vec800A3588;

typedef struct Object800A3588 {
    u8 pad0[0x160];
    void* active;
    u8 pad164[0xFA];
    u8 enabled;
} Object800A3588;

extern int fn_80201B54();
extern int fn_800A1B90(void*, void*, void*);
extern void fn_80201E78(Vec800A3588*, void*);
extern void* fn_801A717C(void);
extern void fn_801A74D8(void*, int);
extern void fn_801A74A0(void*, void*);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void fn_801A7588(void*, int);
extern void fn_801A764C(void*, Vec800A3588*);
extern u8 fn_80204508(void*, void*);
extern void fn_801A7470(void*, int);
extern unsigned long long fn_8020123C();
extern void fn_801A7228(void*);

int fn_800A3588(Object800A3588* object, void* arg1, void* arg2, void* arg3,
                int create)
{
    Vec800A3588 position;
    Vec800A3588 source;
    int result = 0;
    void* effect;
    void* converted;
    void* target;
    int found;

    if (object->active != 0) {
        converted = (void*)fn_80201B54(arg1);
        found = fn_800A1B90(arg2, converted, arg3);
        if (create != 0 && found == 0 && object->enabled != 0) {
            fn_80201E78(&source, arg3);
            position = source;
            effect = fn_801A717C();
            target = (void*)fn_80201B54(arg3);
            fn_801A74D8(effect, 0x100);
            fn_801A74A0(effect, converted);
            fn_801A7538(effect, 5);
            fn_801A7518(effect, 3);
            fn_801A7588(effect, 0x8000);
            fn_801A764C(effect, &position);
            if (fn_80204508(arg3, arg1)) {
                fn_801A7470(effect, 12);
            } else {
                fn_801A7470(effect, 11);
            }
            fn_8020123C(0x27, converted, target, effect);
            fn_801A7228(effect);
            result = 1;
        }
        object->enabled = found;
    }
    return result;
}
