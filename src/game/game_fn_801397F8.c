typedef unsigned int u32;

typedef struct Slot {
    int id;
    unsigned char pad04[0x3C];
    void* buffer;
    void* resource;
    unsigned char pad48[8];
} Slot;

typedef struct State {
    int current;
    int arena_size;
    unsigned char pad08[0x2B0];
    Slot slots[2];
} State;

extern State lbl_805AE020;
extern volatile int lbl_8064CFE0;
extern volatile int lbl_8064CFE4;
extern volatile int lbl_8064CFE8;
extern void* lbl_8064CFD8;
extern unsigned char lbl_805E2ABC[];

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern int fn_8020D318(void*, int, int);

void* fn_801397F8(u32* out_size, int kind, int owner, int wait)
{
    int other = lbl_805AE020.current ^ 1;
    int blocked = 0;
    int enabled = OSDisableInterrupts();
    u32 size;
    void* buffer;

    if (wait != 1 && lbl_8064CFE8 != 0 && lbl_8064CFE4 != owner) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (lbl_8064CFE8 == 0) {
        lbl_8064CFE8++;
        lbl_8064CFE4 = owner;
    } else if (lbl_8064CFE4 == owner) {
        lbl_8064CFE8++;
    } else {
        lbl_8064CFE0++;
        blocked = 1;
    }
    OSRestoreInterrupts(enabled);

    if (blocked != 0) {
        fn_8020D318(lbl_805E2ABC, 0, 1);
        enabled = OSDisableInterrupts();
        lbl_8064CFE8++;
        lbl_8064CFE4 = owner;
        lbl_8064CFE0--;
        OSRestoreInterrupts(enabled);
    }

    if (kind == 2) {
        size = 0x19F0C0;
        buffer = lbl_8064CFD8;
    } else {
        size = lbl_805AE020.arena_size;
        buffer = lbl_805AE020.slots[other].buffer;
    }
    if (out_size != 0) {
        *out_size = size;
    }
    return buffer;
}
