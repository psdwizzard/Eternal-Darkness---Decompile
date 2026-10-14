typedef int BOOL;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SramControlBlock {
    u8 sram[64];
    u32 offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

extern SramControlBlock Scb_80640E40;

BOOL __OSSyncSram(void)
{
    return Scb_80640E40.sync;
}
