typedef short s16;

typedef struct Msg {
    s16 type;
    s16 arg;
    int pad;
    void* next;
} Msg;

typedef struct Block {
    char pad0[0x2C];
    char queue[0x20];
    s16 type;
    char pad2[0x58 - 0x4E];
    char tail[4];
} Block;

extern Block lbl_80304060;
extern int lbl_8064C7D0;
extern void fn_8020D250(void*, void*, int);

void fn_80042E3C(void) {
    Msg* m = (Msg*)&lbl_80304060.type;
    lbl_80304060.type = 7;
    m->arg = 0;
    m->next = lbl_80304060.tail;
    lbl_8064C7D0 = lbl_8064C7D0 + 1;
    fn_8020D250(lbl_80304060.queue, m, 1);
}
