typedef unsigned int u32;

typedef struct StreamState {
    unsigned char pad[0x34];
    u32 capacity;
} StreamState;

extern StreamState* DTKGetCurrentTrackFileInfo(void);
extern void fn_801AD8E8(void);

u32 fn_801AD7C0(u32 size, int discriminator)
{
    StreamState* state;

    if (size != 0) {
        state = DTKGetCurrentTrackFileInfo();
        if (state != 0) {
            if (size > state->capacity) {
                fn_801AD8E8();
            } else if ((size & 0x7FFF) != 0) {
                fn_801AD8E8();
            } else if (size > state->capacity - 0x8000) {
                fn_801AD8E8();
            } else {
                return size;
            }
        } else {
            fn_801AD8E8();
        }
    }
    return 0;
}
