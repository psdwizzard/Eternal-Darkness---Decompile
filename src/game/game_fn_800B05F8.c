typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct SaveState {
    s32 key;
    s32 previous;
    s32 room;
} SaveState;

typedef struct SaveHeader {
    SaveState state;
    s32 cameraMode;
    s32 cameraParam;
    u32 reserved;
    u64 playTime;
    u16 firstSize;
    u16 secondSize;
    u32 firstChecksum;
    u32 secondChecksum;
    u8 padding[0x14];
} SaveHeader;

typedef struct ObjectInfo {
    u8 padding[0x98];
    short cameraParam;
} ObjectInfo;

typedef struct Object Object;
typedef struct Camera Camera;

extern SaveState lbl_803003C8;
extern Object *fn_80201B3C(void);
extern Camera *fn_80201BC8(void *object);
extern void *fn_80201B8C(u8 *object);
extern s32 fn_8011EB04(Camera *camera);
extern u64 fn_801E8E2C(void);
extern u16 fn_800087E8(u8 *destination);
extern u16 fn_800BA284(u8 *destination);
extern u32 fn_801E7454(const u8 *data, u32 size);
extern void *memcpy(void *destination, const void *source, u32 size);

s32 fn_800B05F8(u8 *data)
{
    SaveHeader header;
    Object *object;
    Camera *camera;
    ObjectInfo *info;
    u8 *secondBlock;
    u32 total;

    object = fn_80201B3C();
    if (object != 0) {
        camera = fn_80201BC8(object);
    } else {
        camera = 0;
    }
    info = fn_80201B8C((u8 *)object);
    header.state = lbl_803003C8;
    header.cameraMode = fn_8011EB04(camera);
    header.cameraParam = info->cameraParam;
    header.playTime = fn_801E8E2C();
    header.firstSize = fn_800087E8(data + 0x40);
    header.firstChecksum = fn_801E7454(data + 0x40, header.firstSize);
    total = header.firstSize + 0x40;
    secondBlock = data + (u16)total;
    header.secondSize = fn_800BA284(secondBlock);
    header.secondChecksum = fn_801E7454(secondBlock, header.secondSize);
    total += header.secondSize;
    memcpy(data, &header, 0x40);
    return total;
}
