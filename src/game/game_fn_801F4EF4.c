typedef unsigned int u32;

typedef struct StateBlock {
    u32 words[13];
} StateBlock;

extern int lbl_8064D75C;

extern void* fn_801EB080(void);
extern void fn_801F44DC(void);
extern void fn_801F4570(int, int);
extern void fn_801F683C(StateBlock*);
extern void fn_801F03F0(StateBlock*, int);

void fn_801F4EF4(void)
{
    StateBlock copy;
    StateBlock source;

    fn_801EB080();
    fn_801F44DC();
    fn_801F4570(0, 1);
    fn_801F683C(&source);
    copy = source;
    fn_801F03F0(&copy, 0);
    lbl_8064D75C = 1;
}
