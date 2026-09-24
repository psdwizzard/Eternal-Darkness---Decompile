typedef unsigned char u8;
typedef unsigned int u32;

typedef struct EventPayload {
    u32 second;
    u8 pad[0x1C];
    u32 first;
} EventPayload;

extern u32 fn_801DE5C4(void *);
extern u32 fn_801DE5CC(void *);
extern unsigned long long fn_8020123C(u8, u32, u32, void *);

int fn_800CA554(void *object, u32 packed)
{
    register u8 *savedObject = (u8 *)object;
    register u32 group;
    register u32 savedPacked;
    EventPayload payload;

    group = packed >> 8;
    savedPacked = packed;
    payload.first = fn_801DE5C4(savedObject);
    payload.second = fn_801DE5CC(savedObject);
    fn_8020123C((u8)savedPacked, group, group, &payload);
    return 1;
}
