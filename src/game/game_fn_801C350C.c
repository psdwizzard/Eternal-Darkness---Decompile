typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamRequest {
    u8 state;
    u8 pad01;
    u8 type;
    u8 handle;
    u32 position;
    u32 remaining;
    u32 last;
    union {
        u32 transfer[5];
        struct {
            u8 pad10[2];
            unsigned short generation;
        } request;
    } work;
} StreamRequest;

typedef struct SoundState {
    union {
        u8 records[0x908];
        struct {
            u8 pad00[4];
            u32 stream_size;
        } stream;
    } data;
    u8 map[64];
    u32 pad948;
    u32 (*callback)(int, u32*);
} SoundState;

extern SoundState vs;

void vsUpdateBuffer(StreamRequest* request, u32 target)
{
    SoundState* state = &vs;
    StreamRequest* req = request;
    u32* stream_size;
    u32 result;
    u32 unused[3];

    if (req->position == target)
        return;

    if (req->position < target) {
        switch (req->type) {
        case 5:
            break;
        default:
            return;
        }
        req->work.transfer[1] = ((req->position / 7) * 4) & ~7;
        req->work.transfer[2] = target - req->position;
        req->work.transfer[3] = 0;
        req->work.transfer[4] = 0;
        result = state->callback(1, req->work.transfer);
        if (result != 0)
            req->position = (req->position + result) % state->data.stream.stream_size;
        return;
    }

    if (target == 0) {
        switch (req->type) {
        case 5:
            break;
        default:
            return;
        }
        req->work.transfer[1] = ((req->position / 7) * 4) & ~7;
        stream_size = &state->data.stream.stream_size;
        req->work.transfer[2] = *stream_size - req->position;
        req->work.transfer[3] = 0;
        req->work.transfer[4] = 0;
        result = state->callback(1, req->work.transfer);
        if (result != 0)
            req->position = (req->position + result) % *stream_size;
        return;
    }

    switch (req->type) {
    case 5:
        break;
    default:
        return;
    }
    req->work.transfer[1] = ((req->position / 7) * 4) & ~7;
    stream_size = &state->data.stream.stream_size;
    req->work.transfer[2] = *stream_size - req->position;
    req->work.transfer[3] = 0;
    req->work.transfer[4] = target;
    result = state->callback(1, req->work.transfer);
    if (result != 0)
        req->position = (req->position + result) % *stream_size;
}
