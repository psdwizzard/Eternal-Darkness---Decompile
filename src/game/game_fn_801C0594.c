typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Voice Voice;

#pragma pack(4)
struct Voice {
    u8 pad_000[0x34];
    void* value_034;
    void* value_038;
    u8 pad_03C[0x10];
    int state_04C;
    u8 pad_050[4];
    void* value_054;
    u8 pad_058[8];
    void* value_060;
    u8 pad_064[4];
    u8 active_068;
    u8 pad_069[0xAB];
    u64 flags_114;
};
#pragma pack()

extern void macMakeActive(Voice*);

void macSampleEndNotify(Voice* voice)
{
    u32 changed;

    if (voice->state_04C == 1) {
        if (voice->active_068 != 0 && voice->value_054 != 0) {
            voice->value_038 = voice->value_060;
            voice->value_034 = voice->value_054;
            voice->value_054 = 0;
            macMakeActive(voice);
            changed = 1;
        } else {
            changed = 0;
        }

        if (changed == 0 && (voice->flags_114 & 0x40000) != 0) {
            macMakeActive(voice);
        }
    }
}
