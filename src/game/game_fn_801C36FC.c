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
extern u16* lbl_8064D3D0;
extern u32 fn_801CCAE4(u32);
extern u32 fn_801CD094(u32);
extern u32 fn_801CD424(u8);
extern u32 fn_801CD44C(u8);
extern void fn_801CC8C4(u8);
extern void fn_801C350C(StreamRequest*, u32);

void fn_801C36FC(void)
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
        if (cursor[0x908] == 0xFF || !fn_801CCAE4(i)) continue;
        req = (StreamRequest*)(sound->data.records + cursor[0x908] * 0x24 + 8);
        pos = fn_801CD094(i);
        if (req->type == 5)
            target = (pos / 14) * 14;
        else
            target = pos;
        switch (req->state) {
        case 1:
            fn_801C350C(req, target);
            break;
        case 2:
            if ((((u32)req->work.request.generation << 8) | req->handle) == fn_801CD424(req->handle)) {
                fn_801C350C(req, target);
                if (pos >= req->last) req->remaining -= pos - req->last;
                else req->remaining -= sound->data.stream.stream_size - (req->last - pos);
                req->last = pos;
                if (((int)(lbl_8064D3D0[req->handle * 0x202 + 0x103] * 0xA0 + 0xFFF) / 4096) > (int)req->remaining) {
                    if (!fn_801CD44C(req->handle)) fn_801CC8C4(req->handle);
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
