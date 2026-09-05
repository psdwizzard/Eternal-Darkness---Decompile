typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Work8009E2E8 {
    u8 pad00[0x20];
    u32 flags;
} Work8009E2E8;

typedef struct State8009E2E8 {
    u8 pad00[0xC4];
    Work8009E2E8* work;
} State8009E2E8;

/*
 * Honest behavior-complete reconstruction. The remaining mismatch is MWCC
 * lifetime coalescing: generated code reuses two callee-saved registers and
 * emits a 0x10-byte frame, while retail retains r29-r31 and a 0x20-byte frame.
 */

extern int fn_8006D2C8(State8009E2E8*, int);
extern void fn_800A1580(int);
extern int fn_80070CD8(void);
extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern int fn_80201B54();
extern unsigned long long fn_8020123C();

int fn_8009E2E8(register State8009E2E8* state)
{
    int result = 0;

    if (state != 0 && fn_8006D2C8(state, 0xD) != 0 &&
        (state->work->flags & 4) != 0) {
        void* value;
        result = 1;
        fn_800A1580(0xD);
        if (fn_80070CD8() == 0) {
            value = fn_80204844(fn_80201B9C(), 0x20);
            result = 0;
            fn_8020123C(0x52, (void*)fn_80201B54(value),
                        (void*)fn_80201B54(value), 0);
        }
    }
    return result;
}
