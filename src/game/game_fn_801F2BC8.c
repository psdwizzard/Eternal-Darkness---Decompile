typedef signed char s8;
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GameState801F2BC8 {
    u8 pad0000[0x1C]; void* field_001C;
    u8 pad0020[0xC]; void* field_002C;
    u8 pad0030[4]; void* field_0034;
    u8 pad0038[4]; void* field_003C;
    u8 pad0040[0xE0]; void* field_0120; void* field_0124;
    void* field_0128[2]; void* field_0130; u32 field_0134;
    u8 pad0138[0x8004]; void* field_813C;
    s8 field_8140, field_8141, field_8142, field_8143;
} GameState801F2BC8;

extern int lbl_8064C378, lbl_8064D738, lbl_8064D768;
extern u8 lbl_8063B260[], lbl_8063B2A0[], lbl_8063BF68[];
extern GameState801F2BC8* fn_8015C28C(int);
extern void* fn_8015AB00(int);
extern void fn_801F1528(int);
extern void* fn_801ED3F4(void*);
extern void fn_80225F4C(int, void*, int);
extern void fn_801F2B44(void);
extern void fn_80228B98(void*, int);
extern void fn_8022B748(void*, int, int);
extern void fn_80228AFC(void*, int);
extern void fn_8022A5D8(int, int, int, int);
extern void fn_8022A71C(int);
extern void fn_801ED118(void);
extern void fn_801ECC4C(void);
extern void fn_8022B2AC(void*, u32);
extern void fn_801F0BF0(GameState801F2BC8*, void*, int);
extern void* fn_8022B374(void);
extern void fn_8022B448(void*, void*);

void fn_801F2BC8(int group)
{
    GameState801F2BC8* state = fn_8015C28C(group);
    int old_mask = lbl_8064C378;
    void* saved;
    void* token;
    void* motion;
    void* sync;
    if (lbl_8064D768 != 0) fn_801F1528(1); else fn_801F1528(0);
    if (state != 0 && state->field_8142 != 0 && state->field_8143 != 0) {
        saved = state->field_001C;
        token = fn_801ED3F4(state->field_813C);
        motion = fn_8015AB00(2);
        fn_80225F4C(9, state->field_002C, 6);
        fn_80225F4C(10, state->field_0034, 12);
        fn_80225F4C(13, state->field_003C, 4);
        fn_80225F4C(14, state->field_003C, 4);
        fn_801F2B44();
        if (motion != 0) {
            fn_80228B98(lbl_8063B2A0, 0);
            fn_8022B748(lbl_8063BF68 + lbl_8064D738 * 0x60, 0x36, 0);
            fn_8022B748(lbl_8063BF68 + lbl_8064D738 * 0x60 + 0x30, 0x39, 0);
            fn_80228AFC(lbl_8063B260, 7);
        }
        fn_8022A5D8(1, 4, 5, 15);
        fn_8022A71C(1);
        motion = (u8*)state->field_0128[lbl_8064D738] + state->field_0134;
        fn_801ED118();
        fn_801ECC4C();
        fn_8022B2AC(motion, 0xC360 - state->field_0134);
        fn_801F0BF0(state, saved, 1);
        sync = fn_8022B374();
        fn_8022B448(motion, sync);
        fn_801ECC4C();
        if (state->field_0130 != 0) fn_8022B448(state->field_0124, state->field_0130);
        fn_801ED3F4(token);
        fn_8022A71C(0);
    }
    lbl_8064C378 = old_mask;
}
