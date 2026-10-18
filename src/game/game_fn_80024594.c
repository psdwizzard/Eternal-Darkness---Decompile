typedef unsigned char u8;
typedef unsigned int u32;

extern char lbl_8023DD88[];

extern int DVDOpen(void*, void*);
extern int DVDReadPrio(void*, void*, u32, int, int);
extern void DVDClose(void*);
extern void* fn_801FEA8C(u32, int, const char*, int);

void* fn_80024594(void* object, u32* size)
{
    u8 state[0x40];
    void* result = 0;

    if (DVDOpen(object, state) != 0) {
        *size = *(u32*)&state[0x34];
        result = fn_801FEA8C((*size + 31) & ~31, 1, lbl_8023DD88, 139);
        while (DVDReadPrio(state, result, (*size + 31) & ~31, 0, 2) < 0) {
        }
        DVDClose(state);
    }
    return result;
}
