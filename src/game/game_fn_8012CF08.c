typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct Pair { u32 first, second; } Pair;

extern float lbl_806501D8;
extern void fn_80125ECC(void *);
extern void fn_8012BE78(const float*, short*);
extern void fn_8012F6E8(void*);

#pragma use_lmw_stmw on
#pragma opt_propagation off
void fn_8012CF08(u8* state, int index, Vec4 first, Vec4 second,
                 int alternate, int masked, float scale)
{
    u8* definition;
    u8* runtime;
    int bits;
    u8* entry;

    fn_80125ECC(state);
    entry = *(u8**)(*(u8***)(state + 0x240) + index);
    if (entry != 0) {
        definition = *(u8**)(entry + 4);
        fn_8012BE78((float*)&first, (short*)(entry + 0x6C));
        *(Pair*)(entry + 0x74) = *(Pair*)(entry + 0x6C);
        fn_8012BE78((float*)&second, (short*)(entry + 0x7C));
        *(float*)(entry + 0x84) = lbl_806501D8;
        *(float*)(entry + 0x88) = scale;
        *(int*)(entry + 0x8C) = masked > 0 ? masked : 0;
        fn_8012F6E8(entry + 0x24);
        if (lbl_806501D8 != *(float*)(entry + 0x88))
            *(u16*)(entry + 0x24) = 1;
        runtime = *(u8**)(state + 0x160) + *(u16*)(definition + 0xE) * 0x4C;
        *(u8**)(runtime + 0x48) = entry;
        *(u16*)(entry + 0xA) &= ~9;
        bits = alternate ? 8 : 1;
        *(u16*)(entry + 0xA) |= bits;
    }
}
#pragma opt_propagation reset
