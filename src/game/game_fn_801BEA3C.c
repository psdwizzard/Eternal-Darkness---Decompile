typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamState {
    unsigned char pad_000[0xAC];
    u32 values_AC[16];
} StreamState;

extern u32 synthGlobalVariable[];
extern u32 inpGetExCtrl(StreamState*, u32);

s16 varGet(StreamState* state, void* indirect, u32 index)
{
    u32 value;

    if (indirect != 0) {
        value = (u16)inpGetExCtrl(state, index);
    } else {
        index &= 0x1F;
        if (index < 16) {
            value = state->values_AC[index];
        } else {
            value = synthGlobalVariable[index - 16];
        }
    }
    return (s16)value;
}
