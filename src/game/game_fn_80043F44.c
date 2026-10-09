typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SpawnRequest {
    u8 position[0x10];
    u32 kind;
    u32 subtype;
    u32 param18;
    u32 param1C;
    u32 param20;
    u32 param24;
    u32 count;
    u32 owner;
    u32 enabled;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

extern void* memset(void*, int, unsigned int);
extern u32 lbl_8064D18C;

void fn_80043F44(SpawnRequest* request)
{
    memset(request, 0, sizeof(SpawnRequest));
    request->kind = -1;
    request->subtype = -1;
    request->param18 = -1;
    request->param1C = -1;
    request->param20 = -1;
    request->count = 0;
    request->owner = lbl_8064D18C;
    request->enabled = 1;
    request->active = 1;
    request->flags = 0;
}
