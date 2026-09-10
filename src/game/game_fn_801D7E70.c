typedef unsigned char u8;

typedef struct Object { u8 bytes[0x100]; } Object;

extern void* fn_80201814(int);
extern Object* fn_80201B8C(void);
extern int fn_80201AE4(void);
extern void fn_801D7380(int);
extern void fn_8020123C(int, int, int, int);

void fn_801D7E70(int value, int flag)
{
    Object* state;
    int object;

    if (fn_80201814(value) != 0) {
        state = fn_80201B8C();
        if (value == fn_80201AE4()) {
            object = *(int*)(*(u8**)(state->bytes + 0x8C) + 0x2C);
            if (object != 0) {
                if (flag == 0) {
                    fn_801D7380(object);
                }
                fn_8020123C(0x39, object, object, !flag);
            }
        }
    }
}
