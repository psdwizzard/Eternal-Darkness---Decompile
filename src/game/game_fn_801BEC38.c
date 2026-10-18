typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamState {
    u8 pad_000[0xAC];
    u32 values_AC[16];
    u8 pad_EC[0x0C];
    void* object_F8;
} StreamState;

typedef struct StreamCommand {
    u32 value;
    u32 flags;
} StreamCommand;

typedef struct Voice {
    u8 pad_000[0x34];
    void* active_034;
    void* prior_038;
    u8 pad_03C[0x1C];
    void* pending_058;
    u8 pad_05C[8];
    void* pending_prior_064;
    u8 active_068;
    u8 pad_069[0x8F];
    void* object_F8;
    u8 pad_0FC[6];
    u16 id_102;
    u8 pad_104[0x2E8];
    u8 queue_count_3EC;
    u8 pad_3ED;
    u8 queue_pos_3EE;
    u8 pad_3EF;
    void* queue_3F0[4];
    u8 pad_400[4];
} Voice;

extern u32 synthGlobalVariable[];
extern u8 synthInfo[];
extern Voice* synthVoice;
extern void (*synthMessageCallback)(u32, u32);
extern u32 vidGetInternalId(u32);
extern void macMakeActive(Voice*);

static inline u32 handleMessageTrap(Voice* voice)
{
    if (voice->active_068 != 0 && voice->pending_058 != 0) {
        voice->prior_038 = voice->pending_prior_064;
        voice->active_034 = voice->pending_058;
        voice->pending_058 = 0;
        macMakeActive(voice);
        return 1;
    }
    return 0;
}

static inline void sendMessage(u32 handle, u32 selected)
{
    u32 result;
    Voice* voice;
    result = vidGetInternalId(handle);
    if (result != (u32)-1) {
        voice = &synthVoice[(u8)result];
        if (voice->queue_count_3EC < 4) {
            voice->queue_count_3EC++;
            voice->queue_3F0[voice->queue_pos_3EE] = (void*)selected;
            voice->queue_pos_3EE = (voice->queue_pos_3EE + 1) & 3;
            handleMessageTrap(voice);
        }
    }
}

static inline u32 getVariable(StreamState* state, u32 index)
{
    u32 value;

    index &= 0x1F;
    if (index < 16) {
        value = state->values_AC[index];
    } else {
        value = synthGlobalVariable[index - 16];
    }
    return value;
}

void mcmdSendMessage(StreamState* state, StreamCommand* command)
{
    u32 selected;
    u32 id;
    u8 i;
    Voice* voice;

    selected = getVariable(state, command->flags >> 8);

    if (((command->value >> 8) & 0xFF) == 0) {
        id = command->value >> 16;
        if (id != 0xFFFF) {
            i = 0;
            while (i < synthInfo[0x210]) {
                voice = &synthVoice[i];
                if (voice->active_034 != 0 && id == voice->id_102) {
                    sendMessage(*(u32*)((u8*)voice->object_F8 + 8), selected);
                }
                i++;
            }
        } else if (synthMessageCallback != 0) {
            synthMessageCallback(*(u32*)((u8*)state->object_F8 + 8), selected);
        }
    } else {
        sendMessage(getVariable(state, command->flags), selected);
    }
}
