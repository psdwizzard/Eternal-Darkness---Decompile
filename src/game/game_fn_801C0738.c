typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Voice Voice;

#pragma pack(4)
struct Voice {
    u8 pad_000[0x34];
    void* value_034;
    void* value_038;
    u8 pad_03C[0x14];
    void* value_050;
    u8 pad_054[8];
    void* value_05C;
    u8 pad_060[8];
    u8 active_068;
    u8 pad_069[0xAB];
    u64 flags_114;
};
#pragma pack()

extern void macMakeActive(Voice*);

void macSetPedalState(Voice* voice, u32 enabled)
{
    u32 changed;

    if (enabled != 0) {
        voice->flags_114 |= 0x10000000000ULL;
    } else {
        if (voice->value_034 != 0 &&
            (voice->flags_114 & 0x40000000000ULL) != 0) {
            if (voice->active_068 != 0 && voice->value_050 != 0) {
                voice->value_038 = voice->value_05C;
                voice->value_034 = voice->value_050;
                voice->value_050 = 0;
                macMakeActive(voice);
                changed = 1;
            } else {
                changed = 0;
            }

            if (changed == 0 && (voice->flags_114 & 4) != 0) {
                macMakeActive(voice);
            }
        }
        voice->flags_114 &= ~0x50000000000ULL;
    }
}
