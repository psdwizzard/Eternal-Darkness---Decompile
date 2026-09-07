typedef void (*Callback)(void);

extern unsigned int fn_801A7468(void *);
extern void fn_801287C4(void *, Callback, void *, int);
extern void fn_801296E8(void *, int);
extern void fn_801A7560(void *, int);
extern void fn_800D3D3C(void);
extern void fn_800A3468(void);
extern void fn_800A1A24(void);
extern void fn_800A1A04(void);

void fn_800D64A8(void *actor, void *unused, void *context, void *state)
{
    int code;

    fn_801A7468(state);
    for (code = 0x29; code < 0x32; code += 2) {
        fn_801287C4(context, fn_800D3D3C, state, code);
    }
    fn_801296E8(context, 0x20000);
    fn_801287C4(context, fn_800A3468, state, 0x30);
    fn_801287C4(context, fn_800A1A24, actor, 0x0f);
    fn_801287C4(context, fn_800A1A04, (void *)0x8000, 0x22);
    fn_801287C4(context, fn_800A1A04, (void *)0x10000, 0x23);
    fn_801A7560(state, 0x2000);
}
