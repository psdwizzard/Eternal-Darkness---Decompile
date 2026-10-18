typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Voice Voice;

#pragma pack(4)
struct Voice {
    u8 pad_000[0x34];
    void* value_034;
    void* value_038;
    Voice* next_03C;
    u32 next_040;
    Voice* scheduled_next_044;
    u8 pad_048[0x0C];
    void* value_054;
    u8 pad_058[8];
    void* value_060;
    u8 pad_064[4];
    u8 active_068;
    u8 pad_069[0x2F];
    u32 time_hi_098;
    u32 time_lo_09C;
    u32 saved_hi_0A0;
    u32 saved_lo_0A4;
    u8 pad_0A8[0x4C];
    u32 id_F4;
    u8 pad_0F8[0x1C];
    u64 flags_114;
};
#pragma pack()

extern Voice* macActiveMacroRoot;
extern Voice* macTimeQueueRoot;
extern u64 macRealTime;
extern void macMakeActive(Voice*);
extern u32 hwIsActive(u8);
extern void macHandleActive(Voice*);

void macHandle(u32 elapsed)
{
    u64 scheduled;
    Voice* voice;
    Voice* next;
    u32 active;
    volatile u32 stack_align;
    volatile u32 stack_align_2;

    voice = macTimeQueueRoot;
    while (voice != 0 &&
           (scheduled = *(u64*)&voice->time_hi_098) <= macRealTime) {
        next = voice->scheduled_next_044;
        macMakeActive(voice);
        *(u64*)&voice->saved_hi_0A0 = scheduled;
        voice = next;
    }

    voice = macActiveMacroRoot;
    while (voice != 0) {
        if (voice->active_068 != 0) {
            active = voice->value_054 != 0;
        } else {
            active = 0;
        }
        if (active != 0 &&
            (voice->flags_114 & 0x20) == 0 &&
            hwIsActive((u8)voice->id_F4) == 0 &&
            voice->active_068 != 0 && voice->value_054 != 0) {
            voice->value_038 = voice->value_060;
            voice->value_034 = voice->value_054;
            voice->value_054 = 0;
            macMakeActive(voice);
        }
        macHandleActive(voice);
        voice = voice->next_03C;
    }

    macRealTime += elapsed;
}
