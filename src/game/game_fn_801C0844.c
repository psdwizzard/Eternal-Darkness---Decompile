typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct Voice Voice;

#pragma pack(4)
struct Voice {
    u8 pad_000[0x44];
    Voice* scheduled_next_044;
    Voice* scheduled_prev_048;
    u8 pad_04C[0x4C];
    u64 scheduled_time_098;
};
#pragma pack()

extern Voice* macTimeQueueRoot;

void TimeQueueAdd(Voice* voice)
{
    Voice* current = macTimeQueueRoot;
    Voice* previous = 0;

    while (current != 0 && current->scheduled_time_098 < voice->scheduled_time_098) {
        previous = current;
        current = current->scheduled_next_044;
    }

    if (current == 0) {
        if (previous == 0) {
            macTimeQueueRoot = voice;
            voice->scheduled_next_044 = 0;
            voice->scheduled_prev_048 = 0;
        } else {
            previous->scheduled_next_044 = voice;
            voice->scheduled_prev_048 = previous;
            voice->scheduled_next_044 = 0;
        }
    } else {
        voice->scheduled_next_044 = current;
        if ((voice->scheduled_prev_048 = current->scheduled_prev_048) != 0) {
            current->scheduled_prev_048->scheduled_next_044 = voice;
        } else {
            macTimeQueueRoot = voice;
        }
        current->scheduled_prev_048 = voice;
    }
}
