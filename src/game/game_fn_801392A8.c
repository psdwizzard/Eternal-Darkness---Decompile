typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Entry {
    void* data;
    u32 size;
} Entry;

typedef struct Slot {
    int id;
    unsigned char handle[0x3C];
    void* buffer;
    void* resource;
    u32 size;
    signed char state;
    signed char flag;
    unsigned char pad[2];
} Slot;

typedef struct State {
    int current;
    int arena_size;
    int request;
    int wanted;
    unsigned char pad10[0x2A8];
    Slot slots[2];
} State;

typedef struct Selection {
    int file;
    short pad;
    short id;
} Selection;

extern State lbl_805AE020;
extern Selection lbl_805AE780;
extern void* lbl_8064A65C;
extern int lbl_8064B9E0;
extern short lbl_8064B9E4;
extern char fn_801390D4[];

extern Entry* fn_80138950(void*, u16);
extern void fn_80138FE4(int, u32);
extern void fn_8013915C(void);
extern void* fn_801397F8(u32*, int, int, int);
extern void fn_80139940(int);
extern void fn_8015E9EC(u32, void*, u32);
extern int fn_80213320(int, void*);
extern int fn_802137F4(void*, void*, u32, u32, int);
extern int fn_80213704(void*, void*, u32, u32, void*, int);
extern void fn_8021345C(void*);

void fn_801392A8(int index, int async)
{
    Slot* slot = &lbl_805AE020.slots[index];
    Entry* entry = fn_80138950(lbl_8064A65C, (u16)slot->id);
    u32 amount;
    void* data;

    if (entry == 0) {
        return;
    }
    amount = (entry->size + 31) & ~31;
    data = slot->buffer;
    slot->state = 1;
    slot->flag = 1;

    if (async == 0 && slot->id == lbl_8064B9E0 && lbl_8064B9E4 == lbl_805AE780.id) {
        fn_801397F8(0, 1, 1, 2);
        fn_8015E9EC(0xEA5E40, data, amount);
        fn_80138FE4(index, (u32)data + amount);
        fn_8013915C();
        fn_80139940(0);
    } else if (lbl_805AE780.file != -1 && fn_80213320(lbl_805AE780.file, slot->handle)) {
        fn_801397F8(0, 1, 1, 2);
        if (async == 0) {
            do {
            } while (fn_802137F4(slot->handle, data, amount, entry->size, 2) == -1);
            fn_80138FE4(index, (u32)data + amount);
            fn_8013915C();
            fn_8021345C(slot->handle);
            fn_80139940(0);
        } else {
            do {
            } while (fn_80213704(slot->handle, data, amount, entry->size,
                                  fn_801390D4, 2) == 0);
        }
    }
}
