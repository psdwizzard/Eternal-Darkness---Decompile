typedef struct Buffer {
    char pad0[0x120];
    int owner;
    char pad124[4];
    void* aux_a;
    void* aux_b;
    char pad130[0x8010];
    short state;
} Buffer;

typedef struct Saved {
    Buffer* buffer;
    void* aux_a;
    void* aux_b;
} Saved;

typedef struct BufferSet {
    int bank;
    int active;
    short state;
    short pad_a;
    Buffer* volatile buffers[7];
} BufferSet;

typedef struct Slot {
    short state;
    short pad2;
    int pad4;
    int pad8;
    int kind;
    int offset;
    int size;
} Slot;

extern BufferSet lbl_805B6FE0;
extern Slot lbl_805B6F80[4];
extern int lbl_8064D168;
extern int lbl_8064D17C;
extern int lbl_8064D178;
extern int lbl_8064D144;
extern char lbl_8024F038[];

extern int fn_800460FC(void);
extern int fn_800460F4(void);
extern void* fn_801FEA8C(int, int, char*, int);
extern void* memset(void*, int, unsigned int);

void fn_801599BC(int fresh, int clear)
{
    Saved saved[2];
    int count = fn_800460FC();
    int i;

    if (fresh == 1) {
        for (i = 0; i < count; i++) {
            saved[i].buffer = lbl_805B6FE0.buffers[i];
            saved[i].aux_a = lbl_805B6FE0.buffers[i]->aux_a;
            saved[i].aux_b = lbl_805B6FE0.buffers[i]->aux_b;
        }
    }
    if (clear == 1) {
        memset(&lbl_805B6FE0, 0, 0x1C);
    }
    if (count == 1) {
        lbl_805B6FE0.active = -1;
    } else {
        lbl_805B6FE0.active = lbl_805B6FE0.bank ^ 1;
    }
    lbl_805B6FE0.state = -1;

    for (i = 0; i < count; i++) {
        if (fresh == 0) {
            lbl_805B6FE0.buffers[i] = fn_801FEA8C(0x8148, 1, lbl_8024F038, 0x761);
            memset(lbl_805B6FE0.buffers[i], 0, 0x8148);
            lbl_805B6FE0.buffers[i]->aux_a = fn_801FEA8C(0xC360, 1, lbl_8024F038, 0x763);
            lbl_805B6FE0.buffers[i]->aux_b = fn_801FEA8C(0xC360, 1, lbl_8024F038, 0x764);
        } else {
            lbl_805B6FE0.buffers[i] = saved[i].buffer;
            if (clear == 1) {
                memset(lbl_805B6FE0.buffers[i], 0, 0x8148);
            }
            lbl_805B6FE0.buffers[i]->aux_a = saved[i].aux_a;
            lbl_805B6FE0.buffers[i]->aux_b = saved[i].aux_b;
        }
        if (clear == 1) {
            lbl_805B6FE0.buffers[i]->state = -1;
            lbl_805B6FE0.buffers[i]->owner = (&lbl_8064D168)[i];
        }
    }

    if (clear != 0) {
        int slot;
        int offset = 0x600000;
        Slot* entry;
        lbl_8064D17C = fn_800460F4();
        memset(lbl_805B6F80, 0, 0x60);
        entry = lbl_805B6F80;
        for (i = 0; i < 4; i++) {
            entry->state = -1;
            entry->kind = 5;
            entry->offset = offset;
            entry->size = 0x1A9A00;
            offset += 0x1A9A00;
            entry++;
        }
        slot = lbl_8064D17C;
        lbl_8064D178 = slot;
        if (slot < 4) {
            lbl_805B6F80[slot].kind = -1;
            lbl_805B6F80[slot].size = 0xDBCAA0 - lbl_805B6F80[slot].offset;
        }
    }
    lbl_8064D144 = 0;
}
