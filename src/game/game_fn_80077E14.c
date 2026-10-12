typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct OwnerInfo {
    char pad[0x24];
    s32 objectId;
} OwnerInfo;

typedef struct ObjectInfo {
    char pad[0x8C];
    OwnerInfo *owner;
} ObjectInfo;

typedef struct Work {
    char pad[0x48];
    s32 resource;
} Work;

typedef struct {
    unsigned char pad[0x7C];
    u32 value;
} ResourceFlags;

typedef struct {
    unsigned char pad[0xB4];
    s16 value;
} ResourceAmount;

typedef struct {
    unsigned char pad[0xB6];
    u16 value;
} ResourceChannels;

typedef struct Entry80201814 Entry80201814;

extern void *fn_80200C38(void **event);
extern void fn_80077F90(void *object);
extern void *fn_80201B8C(unsigned char *object);
extern Entry80201814 *fn_80201814(s32 objectId);
extern void fn_801A74D8(ResourceFlags *resource, u32 flags);
extern void fn_801A74E8(ResourceFlags *resource, u32 flags);
extern s16 fn_801A74F8(ResourceAmount *resource);
extern u16 fn_801A7530(ResourceChannels *resource);
extern u64 fn_8020123C(s32 kind, s32 source, s32 target, s32 value);
extern s32 fn_80038308(void *object, s32 channel, s16 *value);
extern s32 fn_800389E0(void *object, s32 channel, s16 value, s32 notify);

void fn_80077E14(unsigned char *object, void *model, void **event,
                 s32 source, Work *work)
{
    s32 remaining;
    ObjectInfo *info;
    void *resource;
    s16 value;
    u16 channels;
    s32 channel;
    void *ownerObject = 0;
    s16 decrement;
    s32 target = 0;
    s16 amount;

    value = 0;
    resource = fn_80200C38(event);
    fn_80077F90(model);
    info = fn_80201B8C(object);
    if (info != 0) {
        if (info->owner != 0) {
            target = info->owner->objectId;
            ownerObject = fn_80201814(target);
        }
    }
    if (ownerObject != 0) {
        fn_801A74D8(resource, 0x400000);
        amount = (s16)fn_8020123C(0xB, source, target, (s32)resource);
        fn_801A74E8(resource, 0x400000);
    } else {
        amount = fn_801A74F8(resource);
    }
    channels = fn_801A7530(resource);
    decrement = amount;
    channel = 0;
    do {
        if (channels & (1 << channel)) {
            fn_80038308(object, channel, &value);
            remaining = value - decrement;
            value = remaining > 0 ? remaining : 0;
            fn_800389E0(object, channel, value, 1);
            if (value == 0) {
                fn_8020123C(0x73, source, work->resource, 0);
                fn_8020123C(8, source, source, 0);
                work->resource = 0;
            }
        }
        ++channel;
    } while (channel < 4);
}
