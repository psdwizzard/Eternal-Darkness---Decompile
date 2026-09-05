typedef struct Slot {
    char pad_0[0x50];
    int handle;
    char pad_54[0x24];
} Slot;

extern Slot lbl_8030F540;
extern void* fn_801FD6F4(int);
extern void fn_801FD534(void*);

void fn_80132C24(void)
{
    int zero = 0;
    Slot* slot;
    int i = 0;
    do {
        void* resource;
        slot = &lbl_8030F540 + i;
        resource = fn_801FD6F4(slot->handle);
        if (resource != 0) {
            fn_801FD534(*(void**)resource);
            slot->handle = zero;
        }
        i++;
    } while (i < 3);
}
