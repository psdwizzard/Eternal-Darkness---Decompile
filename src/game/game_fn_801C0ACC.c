typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Voice Voice;

#pragma pack(4)
struct Voice {
    u8 pad_000[0x3C];
    Voice* active_prev_03C;
    Voice* active_next_040;
    Voice* scheduled_next_044;
    Voice* scheduled_prev_048;
    int active_04C;
    u8 pad_050[0x48];
    u64 scheduled_time_098;
    u64 current_time_0A0;
    u8 pad_0A8[0x6C];
    u64 flags_114;
};
#pragma pack()

extern Voice* macActiveMacroRoot;
extern Voice* macTimeQueueRoot;
extern u64 macRealTime;

void macMakeInactive(Voice* voice, int active)
{
    if (voice->active_04C == active) {
        return;
    }

    if (voice->active_04C == 0) {
        if (voice->active_next_040 == 0) {
            macActiveMacroRoot = voice->active_prev_03C;
        } else {
            voice->active_next_040->active_prev_03C = voice->active_prev_03C;
        }
        if (voice->active_prev_03C != 0) {
            voice->active_prev_03C->active_next_040 = voice->active_next_040;
        }
    }

    if (active == 2 && voice->scheduled_time_098 != 0) {
        if (voice->scheduled_time_098 != ~0ULL) {
            if (voice->scheduled_prev_048 == 0) {
                macTimeQueueRoot = voice->scheduled_next_044;
            } else {
                voice->scheduled_prev_048->scheduled_next_044 = voice->scheduled_next_044;
            }
            if (voice->scheduled_next_044 != 0) {
                voice->scheduled_next_044->scheduled_prev_048 = voice->scheduled_prev_048;
            }
        }
        voice->scheduled_time_098 = 0;
        voice->current_time_0A0 = macRealTime;
        voice->flags_114 &= ~0x40004ULL;
    }

    voice->active_04C = active;
}
