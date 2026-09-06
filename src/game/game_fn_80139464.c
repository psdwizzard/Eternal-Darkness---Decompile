typedef unsigned int u32;

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

extern State lbl_805AE020;
extern void* fn_801397F8(u32*, int, int, int);
extern void fn_801392A8(int, int);
extern void fn_80139940(int);
extern void fn_80139E04(void*, void*, void*, int, int);

int fn_80139464(void* object, int id)
{
    int result = 0;
    int free_slot;
    int other = lbl_805AE020.current ^ 1;

    lbl_805AE020.wanted = id;
    lbl_805AE020.request = (int)object;
    if (!fn_801397F8(0, 1, 1, 0)) {
        return 0;
    }

    if (lbl_805AE020.slots[lbl_805AE020.current].id != id && lbl_805AE020.slots[other].id != id) {
        free_slot = -1;
        if (lbl_805AE020.slots[lbl_805AE020.current].flag == 0) {
            free_slot = lbl_805AE020.current;
        } else if (lbl_805AE020.slots[other].flag == 0) {
            free_slot = other;
        }
        if (free_slot != -1 && lbl_805AE020.slots[free_slot].state != 1) {
            lbl_805AE020.slots[free_slot].id = id;
            lbl_805AE020.slots[free_slot].state = 0;
            lbl_805AE020.slots[free_slot].resource = 0;
        }
    }

    if (lbl_805AE020.slots[lbl_805AE020.current].state == 0 &&
        lbl_805AE020.slots[lbl_805AE020.current].id != -1) {
        fn_801392A8(lbl_805AE020.current, 0);
    }
    if (lbl_805AE020.slots[other].state == 0 && lbl_805AE020.slots[other].id != -1) {
        fn_801392A8(other, 1);
    }

    if (lbl_805AE020.slots[other].id == id && lbl_805AE020.slots[other].state == 2) {
        lbl_805AE020.slots[other].flag = 1;
        fn_80139E04(object, lbl_805AE020.slots[other].resource, (char*)&lbl_805AE020 + 0x10,
                     (int)lbl_805AE020.slots[other].size, 0xAA);
        if (lbl_805AE020.slots[other].resource != 0) {
            result = 1;
        }
    } else if (lbl_805AE020.slots[lbl_805AE020.current].id == id &&
               lbl_805AE020.slots[lbl_805AE020.current].state == 2) {
        lbl_805AE020.slots[lbl_805AE020.current].flag = 1;
        fn_80139E04(object, lbl_805AE020.slots[lbl_805AE020.current].resource,
                     (char*)&lbl_805AE020 + 0x10, (int)lbl_805AE020.slots[lbl_805AE020.current].size,
                     0xAA);
        if (lbl_805AE020.slots[lbl_805AE020.current].resource != 0) {
            result = 1;
        }
    }
    fn_80139940(0);
    return result;
}
