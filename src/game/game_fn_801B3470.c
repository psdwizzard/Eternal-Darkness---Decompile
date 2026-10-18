typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Command {
    u32 key;
    u32 value;
} Command;

typedef struct Channel {
    void* active;
    Command* cursor;
    u32 position;
    u8 pad0C[0x24];
    u8 limit_index;
    u8 pad31[7];
} Channel;

typedef struct State {
    u8 pad000[0x118];
    void* flags_object;
    u8 pad11C[0x13CC];
    Channel channels[256];
} State;

extern State* cseq;
extern u32 curSeqId;
extern void synthSetBpm(u32, u8, u8);

void HandleMasterTrack(u8 index)
{
    Channel* channel;
    Command* command;
    u32 value;

    channel = &cseq->channels[index];
    if (channel->active != 0) {
        while ((command = channel->cursor)->key != 0xFFFFFFFF) {
            if (command->key > *(u32*)((u8*)channel + 0x24 + channel->limit_index * 8)) {
                break;
            }

            if (*(u32*)((u8*)cseq->flags_object + 0x10) & 0x40000000) {
                value = command->value;
                channel->position = value;
                synthSetBpm(value >> 10, curSeqId, index);
            } else {
                synthSetBpm(command->value, curSeqId, index);
                channel->position = channel->cursor->value << 10;
            }
            channel->cursor++;
        }
    }
}
