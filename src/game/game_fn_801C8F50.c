typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Voice Voice;
typedef struct Owner Owner;

struct Voice {
    char pad00[8];
    Owner* owner;
    char pad0C[4];
    u32 flags;
    Vec3 position;
    Vec3 velocity;
    char pad2C[4];
    float amount;
    float amount_limit;
    char pad38[4];
    u32 handle;
};

struct Owner {
    char pad00[0x1C];
    u8 channel;
};

extern u8 sndActive;
extern float lbl_80650FD0;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern u32 vidGetInternalId(u32);
extern void hwChangeStudio(u8, u8);
extern void synthSendKeyOff(u32);

int sndUpdateEmitter(Voice* voice, Vec3* position, Vec3* velocity, u8 amount,
                Owner* owner)
{
    if (sndActive != 0) {
        hwDisableIrq();
        voice->position = *position;
        voice->velocity = *velocity;
        voice->amount = (float)amount / lbl_80650FD0;
        if (voice->amount_limit > voice->amount) {
            voice->amount_limit = voice->amount;
        }
        if (voice->owner != owner) {
            if (voice->handle != 0xFFFFFFFF) {
                if (owner->channel != 0xFF) {
                    u32 channel = vidGetInternalId(voice->handle);
                    if (channel != 0xFFFFFFFF) {
                        hwChangeStudio((u8)channel, owner->channel);
                    }
                } else {
                    synthSendKeyOff(voice->handle);
                    voice->flags |= 0x00080000;
                    voice->handle = 0xFFFFFFFF;
                }
            }
            voice->owner = owner;
        }
        hwEnableIrq();
        return 1;
    }
    return 0;
}
