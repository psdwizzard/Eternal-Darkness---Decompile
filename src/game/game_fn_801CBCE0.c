typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct CacheEntry {
    u8 bytes[0x20];
    u16 value;
    u8 tail[2];
} CacheEntry;

extern u32 lbl_80253370[];
extern u32 inpGlobalMIDIDirtyFlags[][16];
extern CacheEntry inpAuxA[][4];
extern u16 _GetInputValue(u8*, u8*, u8, u8);

u16 inpGetAuxA(u8 voice, u8 channel, u8 entry, u8 row)
{
    u32 pending;
    u32 mask = lbl_80253370[(u8)channel];
    pending = !!(mask & inpGlobalMIDIDirtyFlags[(u8)row][(u8)entry]);

    if (pending) {
        inpGlobalMIDIDirtyFlags[(u8)row][(u8)entry] &= ~mask;
    }
    if (!pending) {
        return inpAuxA[(u8)voice][(u8)channel].value;
    }
    return _GetInputValue(0, (u8*)&inpAuxA[(u8)voice][(u8)channel], entry,
                       row);
}
