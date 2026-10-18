typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct Effect {
    u8 pad0[0x74];
    int handle;
    u8 pad78[0x17];
    s8 active;
    u8 pad90[2];
    s8 detailed;
    u8 pad93[5];
} Effect;

extern Effect lbl_806080E0[80];
extern void fn_801AB0C4(Effect*, s8, int);
extern void VIWaitForRetrace(void);
extern void fn_801A99B4(void);

void fn_801AC350(s8 value, int detailed, int drain)
{
    int passes;
    Effect* effect;
    int i;
    int limit;
    int active;

    effect = lbl_806080E0;
    passes = 0;
    for (i = 0; i < 80; i++, effect++) {
        if (effect->detailed == 0 || detailed == 0) {
            fn_801AB0C4(effect, value, 4);
        } else if (effect->handle != -1) {
            fn_801AB0C4(effect, value + 10 < 127 ? value + 10 : 127, 6);
        } else {
            fn_801AB0C4(effect, 0, 4);
        }
    }

    if (drain != 0) {
        limit = value + 10;
        do {
            active = 0;
            effect = lbl_806080E0;
            for (i = 0; i < 80; i++, effect++) {
                if (effect->active != 0) {
                    active++;
                }
            }
            if (active != 0) {
                VIWaitForRetrace();
                fn_801A99B4();
                passes++;
            }
            if (passes > limit) {
                passes = 0;
                effect = lbl_806080E0;
                for (i = 0; i < 80; i++, effect++) {
                    if (effect->active != 0) {
                        fn_801AB0C4(effect, 0, 4);
                    }
                }
            }
        } while (active != 0);
    }
}
