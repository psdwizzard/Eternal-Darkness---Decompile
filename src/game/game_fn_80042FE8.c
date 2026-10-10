typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Msg {
    u16 kind;
    u16 value;
    u32 pad;
    u32 extra;
} Msg;

extern char lbl_8030408C[];
extern Msg lbl_80304110;
extern void fn_8020D250(void *, void *, int);

void fn_80042FE8(u32 a, u32 b) {
    Msg *m = &lbl_80304110;
    m->kind = 9;
    m->value = a | (b << 15);
    m->extra = 0;
    fn_8020D250(lbl_8030408C, m, 1);
}
