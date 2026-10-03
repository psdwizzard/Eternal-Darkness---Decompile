typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamState {
    short handle;
    u8 read_state;
    u8 state;
    u8 pad04[0xC];
    u32 ring_start;
    u32 ring_end;
    u32 unknown18;
    u32 cursor;
    u32 request;
    u32 produced;
    u32 limit;
    u32 unknown2C;
    u32 previous;
    u32 staging;
    u32 source;
    u32 active;
    int requested_id;
    u32 result;
    u32 bank;
    void* manager;
} StreamState;

extern volatile StreamState lbl_805BB1E0;
__declspec(section ".sdata") extern u32 lbl_8064D160[];
extern char lbl_8024F1D8[];
extern char lbl_8024F200[];
extern u8 lbl_805FA240[];
extern u8 lbl_805E28FC[];
extern void fn_80155BB0(const char*, const char*, ...);
extern u32 fn_801332F0(void*, int);
extern void fn_8015E0A0(u32);
extern void fn_8015B274(u32, u32, u32, u32, void*, u32, void*, u32);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void fn_80158E84(int);
extern int fn_8015E548(int);
extern void fn_8015C020(int);

u32 fn_8015E1A8(int id)
{
    volatile StreamState* state = &lbl_805BB1E0;
    u32 return_value = 0;
    u32 old_staging;
    u32 buffer;
    int interrupts;
    u32 size;
    u32 previous_active;

    if (state->requested_id > id) {
        fn_80155BB0(lbl_8024F1D8, lbl_8024F200, id,
                    state->requested_id);
        goto done;
    }
    if (state->requested_id == id) {
        return_value = state->result;
        goto done;
    }

    (void)state->requested_id;
    state->bank = state->bank ^ 1;
    size = fn_801332F0(state->manager, id);
    old_staging = state->staging;
    buffer = lbl_8064D160[state->bank];
    fn_8015E0A0(size);
    fn_8015B274(size, old_staging, buffer, 0x4B904, lbl_805FA240,
                0x400, lbl_805E28FC, 1);

    interrupts = OSDisableInterrupts();
    state->requested_id = id;
    state->result = buffer;
    return_value = state->result;
    previous_active = state->active;
    state->active = state->staging;
    state->staging += size;
    state->source += size;
    state->cursor = (state->cursor + 31) & ~31;
    state->staging = (state->staging + 31) & ~31;
    if (state->staging >= state->ring_end) {
        u32 overflow = state->staging - state->ring_end;
        state->staging = state->ring_start + overflow;
        state->previous += state->ring_end - state->ring_start;
    }
    state->staging = (state->staging + 31) & ~31;
    state->source = (state->source + 31) & ~31;
    fn_80158E84(1);
    if (lbl_805BB1E0.produced - lbl_805BB1E0.cursor > 0x5B160) {
        state->read_state = 3;
        state->state = 3;
    } else if (lbl_805BB1E0.produced != lbl_805BB1E0.cursor) {
        state->read_state = 2;
        state->state = 3;
    } else if (state->state != 5) {
        state->read_state = 1;
        state->state = 4;
    }
    if (previous_active != 0 && state->produced < state->limit) {
        if (state->request > previous_active) {
            state->produced += (state->ring_end - state->request) +
                               (previous_active - state->ring_start);
            state->request = previous_active;
        } else {
            state->produced += previous_active - state->request;
            state->request = previous_active;
        }
        if (state->produced > state->limit) {
            u32 excess = state->produced - state->limit;
            state->produced -= excess;
            state->request -= excess;
            if (state->request < state->ring_start)
                state->request += state->ring_end - state->ring_start;
        }
    }
    OSRestoreInterrupts(interrupts);
    if (fn_8015E548(state->read_state))
        fn_8015C020(0);
done:
    return return_value;
}
