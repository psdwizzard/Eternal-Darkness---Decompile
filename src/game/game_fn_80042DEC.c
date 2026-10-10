typedef short s16;

typedef struct Msg {
    s16 type;
    s16 arg;
    int pad;
    void* next;
} Msg;

typedef struct Block {
    char head[0x20];
    s16 type;
    char pad[0x2C - 0x22];
    char queue[0x20];
} Block;

extern Block lbl_80304060;
extern int lbl_8064C7F8;
extern void fn_8020D250(void*, void*, int);

void fn_80042DEC(s16 arg) {
    Msg* m;
    m = (Msg*)&lbl_80304060.type;
    m->type = 3;
    m->arg = arg;
    m->next = &lbl_80304060;
    lbl_8064C7F8 = 1;
    fn_8020D250(lbl_80304060.queue, m, 1);
}
