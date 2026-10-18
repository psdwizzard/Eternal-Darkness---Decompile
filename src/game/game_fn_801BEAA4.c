typedef signed short s16;
typedef unsigned int u32;

typedef struct StreamState {
    unsigned char pad_000[0xAC];
    u32 values_AC[16];
} StreamState;

extern u32 synthGlobalVariable[];
extern void inpSetExCtrl(StreamState*, u32, s16);

void varSet32(StreamState* state, void* indirect, u32 index, u32 value)
{
    if (indirect != 0) {
        inpSetExCtrl(state, index, (s16)value);
    } else {
        index &= 0x1F;
        if (index < 16) {
            state->values_AC[index] = value;
        } else {
            synthGlobalVariable[index - 16] = value;
        }
    }
}
