typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

extern int fn_8015C71C(void);
extern void* fn_8011FB4C(u8*);
extern void fn_80125ECC(void *);
extern void fn_8012F6E8(void*);
extern void fn_8012CAC4(u8*, int, void*);
extern int lbl_8064CF38;

typedef struct Slot {
    u8 pad0[0x48];
    void* entry;
} Slot;

void* fn_8012C62C(u8* state, int index, void* a, s8* b, void* c, int flags)
{
    u8* definition;
    u8* entry;

    if (*(int*)(state + 0x244) == 0x30) {
        lbl_8064CF38++;
        if (lbl_8064CF38 > 2) {
            /* Debugger breakpoint retained from the original limit guard. */
            asm { nop }
        }
    }
    fn_8011FB4C(state);
    if (fn_8015C71C() == -1)
        return 0;
    fn_80125ECC(state);
    entry = *(u8**)(*(u8***)(state + 0x240) + index);
    if (entry) {
        definition = *(u8**)(entry + 4);
        *(unsigned int*)(entry + 0x30) = *(unsigned int*)a;
        *(unsigned int*)(entry + 0x2C) = *(unsigned int*)a;
        *(unsigned int*)(entry + 0x38) = *(unsigned int*)c;
        *(unsigned int*)(entry + 0x34) = *(unsigned int*)b;
        fn_8012F6E8(entry + 0xC);
        if (b[0] != 0 || b[1] != 0 || b[2] != 0 || b[3] != 0)
            *(u16*)(entry + 0xC) = 1;
        if (*(Slot**)(state + 0x160))
            (*(Slot**)(state + 0x160))[*(u16*)(definition + 0xE)].entry = entry;
        *(u16*)(entry + 8) &= ~0x16;
        *(u16*)(entry + 8) |= flags;
        fn_8012CAC4(state, index, entry);
    }
    return entry;
}
