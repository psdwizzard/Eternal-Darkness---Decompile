extern void *fn_801294DC(void *, int, int, int);
extern void* fn_80072354(void*);
extern void* fn_801A717C(void*);
extern void fn_801A7460(void*, void*);
extern void fn_801A74A0(void*, void*);
extern void fn_801A74A8(void*, int);
extern void fn_801A74C8(void*, int);
extern void fn_801A7560(void*, int);
extern void fn_800CF6AC(void*, void*, void*, void*, int, int);
extern void fn_801A7550(void*, int);
extern void fn_801A7558(void*, int);
extern void fn_801A764C(void*, int);
extern void fn_801287C4(void*, void*, void*, int);
extern void fn_80128C28();
extern void fn_80128C44(void*, void*, void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8003B8A0(void);
extern void fn_8008D5D4(void);
extern void fn_800DEA88(void);
extern void fn_8008DD24(void);
extern void fn_80204230(void);

typedef struct Data8008D31C {
    unsigned char pad0[0x50];
    void* value50;
    unsigned char pad54[0x3c];
    void* value90;
} Data8008D31C;

typedef struct Value8008D31C {
    unsigned char pad0[0x1c];
    short timer;
} Value8008D31C;

int fn_8008D31C(void* object, void* target, int value, Data8008D31C* data,
                void* resource, void* argument, int parameter)
{
    int result = 0;
    void* created;
    int callback;
    void* nested;
    void* effect;

    created = fn_801294DC(resource, (int)argument, 0, 6);
    if (created != 0) {
        nested = fn_80072354(data->value90);
        effect = fn_801A717C(nested);
        fn_801A7460(effect, argument);
        fn_801A74A0(effect, target);
        fn_801A74A8(effect, value);
        fn_801A74C8(effect, 1);
        fn_801A7560(effect, 132);
        fn_800CF6AC(object, nested, data, effect, 0, 4);
        fn_801A7550(effect, 12);
        fn_801A7558(effect, 7);
        fn_801A764C(effect, parameter);
        fn_801287C4(created, fn_8003B8A0, effect, 18);
        callback = 19;
        do {
            fn_801287C4(created, fn_8008D5D4, effect, callback);
            callback++;
        } while (callback < 28);
        fn_801287C4(created, fn_800DEA88, effect, 13);
        fn_80128C28(created, fn_8008DD24, effect);
        fn_80128C44(created, fn_80204230, effect);
        ((Value8008D31C*)data->value50)->timer = 300;
        fn_80201D2C(object, 6);
        fn_80201D14(object, 1);
        result = 1;
    }
    return result;
}
