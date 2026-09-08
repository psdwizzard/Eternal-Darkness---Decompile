typedef signed char s8;
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct State801F2DB0 {
    u8 pad000[0x1C]; void* saved;
    u8 pad020[0xC]; void* vertices;
    u8 pad030[4]; void* texcoords;
    u8 pad038[4]; void* colors;
    u8 pad040[0xE0]; void* base;
    void* image; void* buffers[2]; void* output; u32 size;
    u8 scratch[0x8000];
    void* work; void* resource; s8 pad8140[2]; s8 enabled_a; s8 enabled_b;
} State801F2DB0;

extern void* lbl_8064C378;
extern int lbl_8064D738, lbl_8064D748, lbl_8064D768;
extern int lbl_8064D6E4, lbl_8064D728;
extern u8 lbl_8064D5F8;
extern u8 lbl_8063B2A0[], lbl_8063B2AC[], lbl_8063B2B8[];
extern u8 lbl_8063B2C4[], lbl_8063B2D0[], lbl_8063B260[], lbl_8063BF68[];

extern State801F2DB0* fn_8015C28C(int);
extern void* fn_8015AB00(int);
extern void fn_80228B98(void*, int), fn_80228AFC(void*, int);
extern void fn_8022B748(void*, int, int), fn_80225F4C(int, void*, int);
extern void* fn_801ED3F4(void*);
extern void fn_801F2B44(void), fn_801F1528(int), fn_801ED118(void), fn_801ECC4C(void);
extern void fn_8022B448(void*, void*), fn_8022B2AC(void*, u32);
extern void fn_801F0BF0(State801F2DB0*, void*, int);
extern void* fn_8022B374(void);
extern void fn_802263D4(void), fn_801EB948(State801F2DB0*), fn_801EB9E4(void);
extern void fn_801F0B24(State801F2DB0*), fn_801EB7A8(State801F2DB0*, u8);
extern void* memset(void*, int, u32);

void fn_801F2DB0(int group)
{
    State801F2DB0* state = fn_8015C28C(group);
    void* old_mask = lbl_8064C378;
    void* saved;
    void* token;
    void* active = fn_8015AB00(2);
    void* sync;
    u8* scratch;

    lbl_8064D748 = (int)fn_8015C28C(2)->resource;
    fn_80228B98(lbl_8063B2AC, 2);
    fn_80228B98(lbl_8063B2B8, 3);
    fn_80228B98(lbl_8063B2C4, 4);
    fn_80228B98(lbl_8063B2D0, 5);
    if (active != 0) {
        fn_80228B98(lbl_8063B2A0, 0);
        fn_8022B748(lbl_8063BF68 + lbl_8064D738 * 0x60, 0x36, 0);
        fn_8022B748(lbl_8063BF68 + lbl_8064D738 * 0x60 + 0x30, 0x39, 0);
        fn_80228AFC(lbl_8063B260, 7);
    }
    if (state != 0 && state->enabled_a != 0 && state->enabled_b != 0) {
        saved = state->saved;
        token = fn_801ED3F4(state->resource);
        fn_80225F4C(9, state->vertices, 6);
        fn_80225F4C(10, state->texcoords, 12);
        fn_80225F4C(13, state->colors, 4);
        fn_80225F4C(14, state->colors, 4);
        fn_801F2B44();
        if (state->work != 0) {
            if (lbl_8064D768 != 0) fn_801F1528(1); else fn_801F1528(0);
            fn_8022B448(state->base, state->work);
            fn_801ED118();
            fn_801ECC4C();
            lbl_8064D728 = 0;
            fn_8022B2AC(state->buffers[lbl_8064D6E4], 0xC360);
            fn_801F0BF0(state, saved, 0);
            sync = fn_8022B374();
            fn_8022B448(state->buffers[lbl_8064D6E4], sync);
            state->size = (u32)sync;
        } else {
            lbl_8064D768 = 0;
            scratch = state->scratch;
            fn_8022B2AC(state->base, 0x55740);
            fn_802263D4();
            fn_801EB948(state);
            memset(scratch, 0, 0x8000);
            fn_801F0B24(state);
            if (lbl_8064D768 != 0) fn_801F1528(1); else fn_801F1528(0);
            fn_801F0BF0(state, saved, 0);
            state->work = fn_8022B374();
            fn_801ED118();
            fn_801ECC4C();
            state->image = (u8*)state->base + (u32)state->work;
            fn_8022B2AC(state->image, 0x55740 - (u32)state->work);
            fn_802263D4();
            fn_801F0BF0(state, saved, 1);
            state->output = fn_8022B374();
            fn_801EB9E4();
            fn_8022B448(state->base, state->work);
            memset(scratch, 0, 0x8000);
            fn_801F0B24(state);
            if (lbl_8064D768 != 0) fn_801F1528(1); else fn_801F1528(0);
            fn_801ED118();
            fn_801ECC4C();
            fn_8022B2AC(state->buffers[lbl_8064D6E4], 0xC360);
            fn_801F0BF0(state, saved, 0);
            sync = fn_8022B374();
            fn_8022B448(state->buffers[lbl_8064D6E4], sync);
            state->size = (u32)sync;
        }
        lbl_8064C378 = old_mask;
        fn_801EB7A8(state, lbl_8064D5F8);
        fn_801ED3F4(token);
    }
}
