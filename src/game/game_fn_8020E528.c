/* SRAM write callback invoked when the EXI bus becomes available. */

typedef int BOOL;
typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct SramControlBlock {
    u8 sram[64];
    u32 offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

extern SramControlBlock Scb_80640E40;
extern BOOL fn_8020E588(void *buffer, u32 offset, u32 size);

void fn_8020E528(s32 chan, void *context)
{
    SramControlBlock *scb = &Scb_80640E40;
    u32 *offset = &scb->offset;

    scb->sync = fn_8020E588(scb->sram + *offset, *offset, 64 - *offset);
    if (scb->sync) {
        *offset = 64;
    }
}
