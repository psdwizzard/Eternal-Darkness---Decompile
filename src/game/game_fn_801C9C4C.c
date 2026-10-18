typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VoiceChannel VoiceChannel;
typedef struct Voice Voice;
typedef struct Event Event;
typedef struct Bucket Bucket;

struct VoiceChannel {
    char pad00[0x1C];
    u8 index;
};

struct Voice {
    char pad00[0x8];
    VoiceChannel* channel;
    char pad0C[0x4];
    u32 flags;
    char pad14[0x28];
    u32 handle;
    char pad40[0x4];
    u16 sound_id;
    u8 fallback_channel;
    u8 limit;
    u16 delay_count;
    char pad4A[0x2];
    float gain;
};

struct Event {
    Event* next;
    float time;
    float value2;
    float value3;
    float value4;
    float value5;
    Voice* voice;
};

struct Bucket {
    u32 flags;
    Event* events;
    Event* pending;
    u16 count;
    u16 pad0E;
};

extern Bucket startGroup[];
extern u8 s3dUseMaxVoices;
extern u8 startGroupNum;
extern float lbl_80650FB0;
extern float lbl_80650FD4;
extern float lbl_80650FF0;
extern float lbl_80650FF4;

extern int synthFXStart(u16, int, int, u8, int);
extern void SetFXParameters(Voice*, float, float, float, float, float);

void StartContinousEmitters(void)
{
    int bucket_index;
    Event* event;
    Voice* voice;
    float one;
    float zero;
    float upper_delay;
    float lower_delay;

    bucket_index = 0;
    zero = lbl_80650FB0;
    one = lbl_80650FD4;
    upper_delay = lbl_80650FF4;
    lower_delay = lbl_80650FF0;
    for (; bucket_index < startGroupNum; bucket_index++) {
        event = startGroup[bucket_index].events;
        while (event != 0) {
            if (startGroup[bucket_index].pending != 0) {
                if (s3dUseMaxVoices != 0 &&
                    (startGroup[bucket_index].flags & 0x80000000) != 0) {
                    if (startGroup[bucket_index].count <
                        startGroup[bucket_index].events->voice->limit) {
                        goto process_event;
                    }
                }

                {
                    float elapsed = event->time -
                                    startGroup[bucket_index].pending->time;
                    if (elapsed <= lower_delay) {
                        goto next_event;
                    }
                    if (elapsed <= upper_delay) {
                        u16 delay_count;
                        Voice* delayed_voice = event->voice;
                        delay_count = delayed_voice->delay_count + 1;
                        delayed_voice->delay_count = delay_count;
                        if (delay_count < 20) {
                            goto next_event;
                        }
                    } else {
                        event->voice->delay_count = 0;
                    }
                }
            }

process_event:
            voice = event->voice;
            if (voice->channel == 0 || voice->channel->index != 0xFF) {
                u8 channel;
                if (voice->channel != 0) {
                    channel = voice->channel->index;
                } else {
                    channel = voice->fallback_channel;
                }
                if ((voice->handle = synthFXStart(voice->sound_id, 0x7F, 0x40,
                                                 channel,
                                                 (voice->flags & 0x10) != 0)) !=
                    0xFFFFFFFF) {
                    goto allocated;
                }
            }

            if ((voice->flags & 2) == 0) {
                voice->flags |= 0x40000;
                voice->flags &= ~0x20000;
            }
            goto next_event;

allocated:
            if ((voice->flags & 0x20) == 0) {
                voice->flags |= 0x100000;
                voice->gain = zero;
            } else {
                voice->gain = one;
            }
            SetFXParameters(voice, event->time, event->value2, event->value3,
                        event->value4, event->value5);
            voice->flags &= ~0x20000;
            startGroup[bucket_index].count++;
            if (startGroup[bucket_index].pending != 0) {
                startGroup[bucket_index].pending =
                    startGroup[bucket_index].pending->next;
            }
next_event:
            event = event->next;
        }
    }
}
