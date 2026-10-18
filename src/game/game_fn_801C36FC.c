typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct StreamRequest {
    u8 state, pad01, type, handle;
    u32 position, remaining, last;
    union {
        u32 transfer[5];
        struct { u8 pad10[2]; u16 generation; } request;
    } work;
} StreamRequest;
typedef struct SoundState {
    union {
        u8 records[0x908];
        struct { u8 pad00[4]; u32 stream_size; } stream;
    } data;
    u8 map[64];
    u32 pad948;
    u32 (*callback)(int, u32*);
} SoundState;
extern SoundState lbl_80627D60;
extern u16* synthVoice;
extern u32 hwGetVirtualSampleState(u32);
extern u32 fn_801CD094(u32);
extern u32 hwGetVirtualSampleID(u8);
extern u32 hwVoiceInStartup(u8);
extern void hwBreak(u8);
extern void vsUpdateBuffer(StreamRequest*, u32);

void vsSampleUpdates(void)
{
    SoundState* sound;
    u8* cursor;
    u32 i;
    u32 count = sizeof(lbl_80627D60.map);
    if (lbl_80627D60.callback == 0) return;
    sound = &lbl_80627D60;
    cursor = (u8*)sound;
    for (i = 0; i < count; i++, cursor++) {
        u32 pos;
        StreamRequest* req;
        u32 target;
        if (cursor[0x908] == 0xFF || !hwGetVirtualSampleState(i)) continue;
        req = (StreamRequest*)(sound->data.records + cursor[0x908] * 0x24 + 8);
        pos = fn_801CD094(i);
        if (req->type == 5)
            target = (pos / 14) * 14;
        else
            target = pos;
        switch (req->state) {
        case 1:
            vsUpdateBuffer(req, target);
            break;
        case 2:
            if ((((u32)req->work.request.generation << 8) | req->handle) == hwGetVirtualSampleID(req->handle)) {
                vsUpdateBuffer(req, target);
                if (pos >= req->last) req->remaining -= pos - req->last;
                else req->remaining -= sound->data.stream.stream_size - (req->last - pos);
                req->last = pos;
                if (((int)(synthVoice[req->handle * 0x202 + 0x103] * 0xA0 + 0xFFF) / 4096) > (int)req->remaining) {
                    if (!hwVoiceInStartup(req->handle)) hwBreak(req->handle);
                    req->state = 0;
                    sound->map[req->handle] = 0xFF;
                }
            } else {
                req->state = 0;
                sound->map[req->handle] = 0xFF;
            }
            break;
        }
    }
}
