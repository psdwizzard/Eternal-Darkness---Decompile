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
    u32 i;

    memset(state->entries, 0, sizeof(state->entries));
    for (i = 0; i < 12; i++) {
        state->pointers[i] = state->entries[i];
    }
    lbl_8064D7D0 = state->entries;
    lbl_8064D7CC = 0;
    lbl_8064D7C8 = 0x10000;
    state->tail.x = lbl_80651540;
    state->tail.y = lbl_80651540;
    state->tail.z = lbl_80651544;
}
