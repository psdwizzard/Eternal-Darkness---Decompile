typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct PatchEntry {
    u8 unknown[6];
    u16 value[3];
} PatchEntry;

typedef struct PatchState {
    u32 unknown;
    PatchEntry* data;
} PatchState;

extern void DCInvalidateRange(void*, u32);
extern void DCFlushRange(void*, u32);

void fn_801EB5C8(PatchState* state, u8* stream, int index)
{
    u16 count = 0;
    u8* out = stream;
    u32 size;
    int i;

    while (count == 0) {
        count = ((u16)out[1] << 8) | out[2];
        out += 3;
    }

    size = count << 3;
    stream = out;
    DCInvalidateRange(out, size);
    out += 6;

    for (i = 0; i < count; i++) {
        u16 value = state->data[i].value[index];
        out[0] = value >> 8;
        out[1] = value;
        out += 8;
    }

    DCFlushRange(stream, size);
}
