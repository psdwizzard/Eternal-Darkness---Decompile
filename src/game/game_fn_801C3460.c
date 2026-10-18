typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SoundEntry {
    u8 pad00[0x1A];
    u16 sequence;
    u8 pad1C[8];
} SoundEntry;

typedef struct SoundState {
    u8 bytes[0x950];
} SoundState;

extern SoundState lbl_80627D60;

void vsSampleEndNotify(u32 handle)
{
    u8* state = (u8*)&lbl_80627D60;
    u32 offset = handle;
    volatile u8* map;
    u8 slot;
    register u16 sequence;

    if (offset != (u32)-1) {
        map = state + (offset = 0x908);
        slot = map[(u8)handle];
        if (slot != 0xFF) {
            offset = slot * 0x24;
            sequence = ((SoundEntry*)&lbl_80627D60)[slot].sequence;
            if (sequence == ((handle >> 8) & 0xFFFF)) {
                if (*(void (**)(int, u16*))(state + 0x94C) != 0) {
                    (*(void (**)(int, u16*))(state + 0x94C))(2, (u16*)(state + offset + 0x18));
                }
                state[offset + 8] = 0;
                map[state[offset + 0xB]] = 0xFF;
            }
        }
    }
}
