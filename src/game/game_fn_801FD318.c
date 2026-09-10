typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TailState {
    float x;
    float y;
    float z;
} TailState;

typedef struct State {
    void* pointers[12];
    u8 entries[12][124];
    TailState tail;
} State;

extern State lbl_8063EA00;
extern u32 lbl_8064D7C8;
extern u32 lbl_8064D7CC;
extern void* lbl_8064D7D0;
extern const float lbl_80651540;
extern const float lbl_80651544;
extern void* memset(void*, int, unsigned int);

void fn_801FD318(void)
{
    State* state = &lbl_8063EA00;

    memset(state->entries, 0, sizeof(state->entries));
    state->pointers[0] = state->entries[0];
    state->pointers[1] = state->entries[1];
    state->pointers[2] = state->entries[2];
    state->pointers[3] = state->entries[3];
    state->pointers[4] = state->entries[4];
    state->pointers[5] = state->entries[5];
    state->pointers[6] = state->entries[6];
    state->pointers[7] = state->entries[7];
    state->pointers[8] = state->entries[8];
    state->pointers[9] = state->entries[9];
    state->pointers[10] = state->entries[10];
    state->pointers[11] = state->entries[11];
    lbl_8064D7D0 = state->entries;
    lbl_8064D7CC = 0;
    lbl_8064D7C8 = 0x10000;
    state->tail.x = lbl_80651540;
    state->tail.y = lbl_80651540;
    state->tail.z = lbl_80651544;
}
