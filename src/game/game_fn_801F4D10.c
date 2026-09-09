typedef unsigned int u32;

typedef struct StateBlock {
    u32 words[13];
} StateBlock;

extern float lbl_80651348;

extern void* fn_801EB080(void);
extern float fn_801F4914(void);
extern void fn_801F44DC(void);
extern void fn_80226EA0(int, int, int, int);
extern void fn_80226FA4(int, int, int, int);
extern void fn_802276AC(void*, int);
extern void fn_802266B0(void);
extern void fn_801F4A18(float);
extern void fn_801F683C(StateBlock*);
extern void fn_801F03F0(StateBlock*, int);

void fn_801F4D10(void)
{
    void* context;
    float value;
    StateBlock copy;
    StateBlock source;

    context = fn_801EB080();
    value = fn_801F4914();
    if (lbl_80651348 != value) {
        fn_801F44DC();
        fn_80226EA0(0, 0, 0x280, 0x1E0);
        fn_80226FA4(0x280, 0x1E0, 4, 0);
        fn_802276AC(context, 0);
        fn_802266B0();
        fn_801F4A18(value);
        fn_801F683C(&source);
        copy = source;
        fn_801F03F0(&copy, 0);
    }
}
