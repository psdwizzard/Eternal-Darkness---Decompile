typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamState {
    unsigned char pad_000[0xAC];
    u32 values_AC[16];
} StreamState;

extern u32 synthGlobalVariable[];
extern u32 inpGetExCtrl(StreamState*, u32);

u32 varGet32(StreamState* state, void* indirect, u32 index)
{
    if (indirect != 0) {
        return (u16)inpGetExCtrl(state, index);
    }
    index &= 0x1F;
    if (index < 16) {
        return state->values_AC[index];
    }
    return synthGlobalVariable[index - 16];
}
