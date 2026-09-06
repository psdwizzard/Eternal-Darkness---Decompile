typedef unsigned char u8;
typedef struct Object { u8 bytes[0x100]; } Object;

extern Object* fn_80201B8C(void);
extern void* fn_80201ADC(void);
extern void fn_8020123C(int, int, int, int);

void fn_801D7E08(void* value)
{
    Object* state;
    int object;

    if (value != 0) {
        state = fn_80201B8C();
        if (value == fn_80201ADC()) {
            object = *(int*)(*(u8**)(state->bytes + 0x8C) + 0x2C);
            if (object != 0) {
                fn_8020123C(0x39, object, object, 0);
            }
        }
    }
}
