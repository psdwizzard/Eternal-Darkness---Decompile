typedef unsigned char u8;
typedef short s16;

typedef struct Runtime800A57D4 {
    u8 pad0[0x9F];
    u8 state;
} Runtime800A57D4;

extern void* fn_8015C910(void);
extern int fn_800460EC(void);
extern int fn_8006D4DC(int);
extern void* fn_80201ADC(void);
extern int fn_80038308(void*, int, s16*);
extern int fn_800389E0(void*, int, s16, int);
extern void fn_80036C40(void*, int, s16);
extern unsigned long long fn_8020123C();
extern int lbl_8064C544;

#pragma opt_propagation off
int fn_800A57D4(int* timer, Runtime800A57D4* runtime)
{
    int result = 0;
    int zero_mask;
    int old_timer;
    void* object;
    s16 value;

    if (fn_8015C910() == 0 && fn_800460EC() == 0 && fn_8006D4DC(0x17) == 0) {
        object = fn_80201ADC();
        old_timer = *timer;
        zero_mask = -old_timer;
        zero_mask = old_timer | ~zero_mask;
        zero_mask >>= 31;
        *timer = (old_timer - 1) & ~zero_mask;
        if (*timer <= 0) {
            switch (runtime->state) {
            case 3:
                *timer = 200;
                break;
            case 4:
                *timer = 140;
                break;
            case 6:
                *timer = 160;
                break;
            }
            fn_80038308(object, 1, &value);
            value--;
            fn_800389E0(object, 1, value, 1);
            fn_80038308(object, 1, &value);
            if (value <= 0) {
                fn_8020123C(0x87, lbl_8064C544, lbl_8064C544, 0);
                result = 1;
            }
        } else {
            fn_80038308(object, 1, &value);
            fn_80036C40(object, 1, value);
        }
    }
    return result;
}
#pragma opt_propagation reset
