typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Sample Sample;
typedef struct Target Target;
typedef struct Voice Voice;

struct Sample {
    Sample* next;
    u32 pad04;
    Target* target;
    u32 pad0C;
    float x;
    float y;
    float z;
};

struct Target {
    Target* next;
    u32 pad04;
    u32 owner;
    float x;
    float y;
    float z;
    float mean_square_distance;
    u8 channel;
    u8 pad1D[3];
    void (*on_start)(u8, void*);
    void (*on_stolen)(u8);
    void* callback_arg;
    u32 fade;
};

struct Voice {
    Voice* next;
    u32 pad04;
    Target* target;
    u32 pad0C;
    u32 flags;
    u8 pad14[0x28];
    int handle;
};

extern Voice* lbl_8064D4BC;
extern Sample* lbl_8064D4C0;
extern Target* lbl_8064D4C4;
extern u32 lbl_8064D4CC;
extern u8 lbl_8064D4D0;
extern u8 lbl_8064D4D1;
extern float lbl_80650FB0;
extern double lbl_80650FB8;
extern float lbl_80650FC0;
extern float lbl_80650FC4;
extern double lbl_80650FC8;

extern void fn_801C8160(void);
extern void fn_801B80D8(int);
extern void fn_801B9170(int, int, int);
extern void fn_801B9220(u8);

void fn_801C8224(void)
{
    Target* candidate;
    Target* target;
    Target* stolen;
    Sample* sample;
    Voice* voice;
    u32 count;
    u32 channel_count;
    u32 channel_mask;
    u8 found;
    u32 channel;
    float distance;
    float best_distance;
    float delta[3];

    fn_801C8160();

    count = 0;
    sample = lbl_8064D4C0;
    while (sample != 0) {
        sample = sample->next;
        count++;
    }

    if (count != 0) {
        target = lbl_8064D4C4;
        while (target != 0) {
            if (target->channel == 0xFF) {
                sample = lbl_8064D4C0;
                distance = lbl_80650FB0;
                {
                    Sample* cursor = sample;
                    while (cursor != 0) {
                        delta[0] = target->x - cursor->x;
                        delta[1] = target->y - cursor->y;
                        delta[2] = target->z - cursor->z;
                        cursor = cursor->next;
                        distance += delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
                    }
                }
                distance /= count;

                found = 0;
                while (sample != 0) {
                    if (sample->target == target) {
                        found = 1;
                        break;
                    }
                    sample = sample->next;
                }

                channel_count = lbl_8064D4D1;
                channel_mask = ~(-1 << channel_count);
                if ((channel_mask & lbl_8064D4CC) != channel_mask) {
                    for (channel = 0; channel < channel_count; channel++) {
                        if ((lbl_8064D4CC & (1 << channel)) == 0) {
                            break;
                        }
                    }
                    lbl_8064D4CC |= 1 << channel;
                    target->channel = channel + lbl_8064D4D0;
                } else {
                    best_distance = lbl_80650FC0;
                    stolen = lbl_8064D4C4;
                    while (stolen != 0) {
                        if (stolen->channel != 0xFF && best_distance < stolen->mean_square_distance) {
                            best_distance = stolen->mean_square_distance;
                            candidate = stolen;
                        }
                        stolen = stolen->next;
                    }
                    stolen = candidate;

                    if (found || best_distance > distance) {
                        voice = lbl_8064D4BC;
                        while (voice != 0) {
                            if (voice->target == stolen) {
                                fn_801B80D8(voice->handle);
                                voice->flags |= 0x00080000;
                                voice->handle = -1;
                            }
                            voice = voice->next;
                        }
                        if (stolen->on_stolen != 0) {
                            stolen->on_stolen(stolen->channel);
                        }
                        fn_801B9220(stolen->channel);
                        target->channel = stolen->channel;
                        stolen->channel = 0xFF;
                        stolen->owner = 0;
                    } else {
                        goto next_target;
                    }
                }

                target->mean_square_distance = distance;
                target->fade = found ? 0x007F0000 : 0;
                if (target->fade * 1.2014794e-07f >= 0.5) {
                    fn_801B9170(target->channel, 1, 0);
                } else {
                    fn_801B9170(target->channel, 0, 0);
                }
                if (target->on_start != 0) {
                    target->on_start(target->channel, target->callback_arg);
                }
            } else {
                if ((target->owner & 0x80000000) != 0) {
                    target->fade += 0x00040000;
                    if (target->fade >= 0x007F0000) {
                        target->fade = 0x007F0000;
                        target->owner &= 0x7FFFFFFF;
                    }
                    if (target->fade * 1.2014794e-07f >= 0.5) {
                        fn_801B9170(target->channel, 1, 0);
                    } else {
                        fn_801B9170(target->channel, 0, 0);
                    }
                }
                if ((target->owner & 0x40000000) != 0) {
                    target->fade -= 0x00040000;
                    if ((int)target->fade >= 0) {
                        target->fade = 0;
                        target->owner &= 0xBFFFFFFF;
                    }
                    if (target->fade * 1.2014794e-07f >= 0.5) {
                        fn_801B9170(target->channel, 1, 0);
                    } else {
                        fn_801B9170(target->channel, 0, 0);
                    }
                }
            }
next_target:
            target = target->next;
        }
    }
}
