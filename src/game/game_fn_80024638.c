typedef unsigned char u8;
typedef unsigned int u32;

extern int DVDOpen(void*, void*);
extern int DVDReadPrio(void*, void*, u32, int, int);
extern void DVDClose(void*);

void* fn_80024638(void* object, void* destination, u32* size)
{
    u8 state[0x40];

    if (DVDOpen(object, state) != 0) {
        *size = *(u32*)&state[0x34];
        while (DVDReadPrio(state, destination, (*size + 31) & ~31, 0, 2) < 0) {
        }
        DVDClose(state);
    }
    return destination;
}
