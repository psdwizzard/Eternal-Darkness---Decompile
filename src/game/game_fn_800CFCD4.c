typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Callbacks {
    void (*slots[19])(void);
} Callbacks;

typedef struct Context {
    Callbacks *callbacks;
    u8 pad004[0x25C];
    u16 field260;
    u8 pad262[2];
    void *field264;
    u8 pad268[4];
    u16 field26C;
    u16 field26E;
    u16 field270;
    u16 field272;
    u8 pad274[0x10];
    u16 field284;
} Context;

extern u8 lbl_80248A60[];
extern void fn_800CFDF4(void);
extern void fn_800CFF04(void);
extern void fn_800D00C0(void);
extern void fn_800D00C8(void);
extern void fn_800D0B74(void);
extern void fn_800D30A4(void);
extern void fn_800D322C(void);
extern void fn_800D3374(void);
extern void fn_800D0454(void);
extern void fn_800D0510(void);
extern void fn_800D0584(void);
extern void fn_800D05FC(void);
extern void fn_800D06DC(void);

#pragma use_lmw_stmw on
void fn_800CFCD4(Context *ctx)
{
    ctx->field264 = lbl_80248A60;
    ctx->field26C = 0x3E;
    ctx->field26E = 0x960;
    ctx->field270 = 0x1964;
    ctx->field272 = 3;
    ctx->field284 = 0;
    ctx->field260 = 0x168;
    ctx->callbacks->slots[0] = fn_800CFDF4;
    ctx->callbacks->slots[1] = fn_800CFF04;
    ctx->callbacks->slots[2] = fn_800D00C0;
    ctx->callbacks->slots[3] = fn_800D0B74;
    ctx->callbacks->slots[4] = fn_800D30A4;
    ctx->callbacks->slots[10] = fn_800D322C;
    ctx->callbacks->slots[11] = fn_800D00C8;
    ctx->callbacks->slots[13] = fn_800D0454;
    ctx->callbacks->slots[14] = fn_800D0510;
    ctx->callbacks->slots[15] = fn_800D0584;
    ctx->callbacks->slots[16] = fn_800D05FC;
    ctx->callbacks->slots[17] = fn_800D06DC;
    ctx->callbacks->slots[18] = fn_800D3374;
}
#pragma use_lmw_stmw reset
