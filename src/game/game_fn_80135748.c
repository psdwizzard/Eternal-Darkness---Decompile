typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Slot { void* owner; u32 capacity; void* data; u32 x; u32 y; unsigned short tag; u8 state; } Slot;

extern Slot* lbl_8064CF88;
extern char* lbl_8064CF80;
extern int lbl_8064CFAC;
extern u32 lbl_8064CFB0;
extern u8 lbl_8064CFA4;

/* Resets the pool and returns its aligned data start. */
u32 fn_80135748(u32* end_out)
{
    int i;
    Slot* slot;
    char* aligned;
    u32 end;
    int count;

    lbl_8064CFA4 = 1;
    count = lbl_8064CFAC;
    aligned = (char*)(((u32)lbl_8064CF88->data + 31) & ~31);
    end = (u32)(lbl_8064CF80 + lbl_8064CFB0) - (u32)aligned;
    if (end_out != 0) *end_out = end;
    for (i = 0; i < count; i++) {
        slot = &lbl_8064CF88[i];
        slot->state = 0;
        slot->owner = 0;
    }
    return (u32)aligned;
}
