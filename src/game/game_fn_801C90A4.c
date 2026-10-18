typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Owner {
    char pad00[0x1C];
    u8 channel;
} Owner;

typedef struct Voice {
    struct Voice* previous;
    struct Voice* next;
    Owner* owner;
    void* commands;
    u32 flags;
    Vec3 position;
    Vec3 velocity;
    float gain;
    float pan;
    float surround;
    float pitch;
    u32 handle;
    void* user_data;
    u16 sound_id;
    u8 input_channel;
    u8 output_channel;
    u16 state;
} Voice;

extern Voice lbl_80629390;
extern Voice* s3dEmitterRoot;
extern double lbl_80650FB8;
extern float lbl_80650FEC;
extern float lbl_80650FB0;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void CalcEmitter(Voice*, float*, float*, float*, float*, float*);
extern u32 synthFXStart(u16, u32, u32, u8, u32);
extern u8 synthFXGetMaxVoices(u16);
extern void SetFXParameters(Voice*, float, float, float, float, float);

int AddEmitter(float gain, float pitch, Voice* voice, Vec3* position,
                Vec3* velocity, u32 flags,
                u16 sound_id, void* user_data, u8 input_channel,
                u8 output_channel, Owner* owner, void* commands, u8 extra)
{
    Voice* result;
    float pitch_scale;
    float surround;
    float pan;
    float calculated_gain;
    float unused;
    float input_scale;

    hwDisableIrq();
    result = voice == 0 ? &lbl_80629390 : voice;
    result->flags = flags;
    result->position = *position;
    result->velocity = *velocity;
    result->gain = gain;
    result->sound_id = sound_id;
    input_scale = lbl_80650FEC;
    result->pan = input_scale * (float)input_channel;
    result->surround = input_scale * (float)output_channel;
    result->pitch = pitch;
    result->user_data = user_data;
    result->owner = owner;
    result->input_channel = extra;

    if (voice == 0) {
        if (result->owner != 0 && result->owner->channel == 0xFF) {
            hwEnableIrq();
            return -1;
        }
        CalcEmitter(result, &calculated_gain, &unused, &pitch_scale, &surround,
                    &pan);
        if (lbl_80650FB0 == calculated_gain) {
            hwEnableIrq();
            return -1;
        }
        result->handle = synthFXStart(result->sound_id, 0x7F, 0x40,
                                     result->owner != 0
                                         ? result->owner->channel
                                         : result->input_channel,
                                     (result->flags & 0x10) != 0);
        if (result->handle == 0xFFFFFFFF) {
            hwEnableIrq();
            return -1;
        }
        SetFXParameters(result, calculated_gain, pitch_scale, surround, pan,
                    unused);
        hwEnableIrq();
        return result->handle;
    }

    if ((result->previous = s3dEmitterRoot) != 0) {
        s3dEmitterRoot->next = result;
    }
    result->next = 0;
    s3dEmitterRoot = result;
    result->commands = commands;
    result->handle = 0xFFFFFFFF;
    result->state = 0;
    result->flags |= 0x30000;
    result->output_channel = synthFXGetMaxVoices(result->sound_id);
    hwEnableIrq();
    return -1;
}
