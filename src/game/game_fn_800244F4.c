typedef unsigned char u8;
typedef unsigned int u32;

extern int DVDOpen(void*, void*);
extern int DVDReadPrio(void*, u32, u32, int, int);
extern void DVDClose(void*);

void fn_800244F4(void* object, u32* result, u32 value, u32 unused)
{
    u8 state[0x40];

    if (DVDOpen(object, state) != 0) {
        *result = *(u32*)&state[0x34];
        while (DVDReadPrio(state, value, (*result + 31) & ~31, 0, 2) < 0) {
        }
        DVDClose(state);
    }
}
