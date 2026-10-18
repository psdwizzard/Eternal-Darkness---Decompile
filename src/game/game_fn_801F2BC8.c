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
extern void GXSetArray(int, void*, int);
extern void fn_801F2B44(void);
extern void GXLoadTlut(void*, int);
extern void GXLoadTexMtxImm(void*, int, int);
extern void GXLoadTexObj(void*, int);
extern void GXSetBlendMode(int, int, int, int);
extern void GXSetAlphaUpdate(int);
extern void fn_801ED118(void);
extern void fn_801ECC4C(void);
extern void GXBeginDisplayList(void*, u32);
extern void fn_801F0BF0(GameState801F2BC8*, void*, int);
extern void* GXEndDisplayList(void);
extern void GXCallDisplayList(void*, void*);

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
        GXSetArray(9, state->field_002C, 6);
        GXSetArray(10, state->field_0034, 12);
        GXSetArray(13, state->field_003C, 4);
        GXSetArray(14, state->field_003C, 4);
        fn_801F2B44();
        if (motion != 0) {
            GXLoadTlut(lbl_8063B2A0, 0);
            GXLoadTexMtxImm(lbl_8063BF68 + lbl_8064D738 * 0x60, 0x36, 0);
            GXLoadTexMtxImm(lbl_8063BF68 + lbl_8064D738 * 0x60 + 0x30, 0x39, 0);
            GXLoadTexObj(lbl_8063B260, 7);
        }
        GXSetBlendMode(1, 4, 5, 15);
        GXSetAlphaUpdate(1);
        motion = (u8*)state->field_0128[lbl_8064D738] + state->field_0134;
        fn_801ED118();
        fn_801ECC4C();
        GXBeginDisplayList(motion, 0xC360 - state->field_0134);
        fn_801F0BF0(state, saved, 1);
        sync = GXEndDisplayList();
        GXCallDisplayList(motion, sync);
        fn_801ECC4C();
        if (state->field_0130 != 0) GXCallDisplayList(state->field_0124, state->field_0130);
        fn_801ED3F4(token);
        GXSetAlphaUpdate(0);
    }
    lbl_8064C378 = old_mask;
}
