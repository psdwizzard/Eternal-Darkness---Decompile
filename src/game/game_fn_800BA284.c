typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct SaveState {
    s32 key;
    s32 previous;
    s32 room;
} SaveState;

typedef struct SaveBlockHeader {
    s16 room;
    s16 objectCount;
    u32 flags;
    s16 specialCount;
    u16 selectedCount;
    u8 unused[8];
} SaveBlockHeader;

typedef struct ObjectInfo {
    u8 pad0[0x3c];
    void *state;
    u8 pad40[0x7c - 0x40];
    void *direction;
} ObjectInfo;

typedef struct ObjectState {
    u8 pad0[0x10];
    s32 value;
    u8 pad14[4];
    s32 identifier;
} ObjectState;

typedef struct Direction {
    u8 pad0[0x1c];
    s32 identifier;
} Direction;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct SpecialPacket {
    s8 type;
    u8 pad;
    s16 identifier;
    s16 angles[4];
} SpecialPacket;

typedef struct CameraPacket {
    s32 value;
    s32 unused;
    float time;
} CameraPacket;

extern SaveState lbl_803003C8;
extern u8 lbl_80332158[];
extern char lbl_8064B6B8;
extern s32 lbl_8064D68C;
extern float lbl_8064F010;

extern void *memcpy(void *, const void *, u32);
extern s32 fn_8003BF5C(void *);
extern void fn_80042678(u16, const char *, s32, s32);
extern s32 fn_80043FB0(void *, s32 *, s32 *);
extern s32 fn_800B9578(u8 *, void *, s32 *, s32);
/* Defined as returning unsigned short (already zero-extended in r3); the
 * original caller saw it through an int-returning declaration. */
extern s32 fn_800BA068(u8 *, s32, void *, s32 *);
extern s32 fn_800BA124(void *, u32, s32);
extern s32 fn_80117E58(void);
extern s32 fn_8011EB04(void *);
extern void *fn_8011FB4C(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern void fn_80179E60(s16 *, float *);
extern void fn_801EB9F0(void *);
extern void fn_801EBA58(void *);
extern void fn_801EBDDC(void *);
extern void fn_801ECBBC(void *);
extern void fn_801EF3E0(float, float);
extern float fn_80200534(s32, s32, s32);
extern s32 fn_80200614(s32, s32, s32);
extern float fn_80200BDC(void);
extern s32 fn_80201B54(void *);
extern s32 fn_80201B5C(void *);
extern ObjectInfo *fn_80201B8C(void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80204844(void *, s32);
extern void *fn_80204A8C(void);
extern s32 fn_80204D98(void *);
extern s32 fn_80228250(u16, u16, u32, u8, u8);
extern void DCInvalidateRange(void *, u32);

u16 fn_800BA284(u8 *destination)
{
    SaveBlockHeader header;
    s32 count;
    s32 kind;
    s32 value;
    s32 other;
    s32 field;
    s16 selectedId;
    CameraPacket cameraPacket;
    SpecialPacket special;
    u8 transform[12];
    s32 color;
    s32 result;
    void *node;
    void *selected;
    void *camera;
    ObjectInfo *info;
    u32 selectedKey;
    s32 wantedId;
    s32 size;
    s32 id;
    float oldTime;
    ObjectState *cameraState;

    count = 0;
    fn_80201B9C();
    wantedId = 0;
    selected = fn_80204A8C();
    header.room = fn_80204D98(selected);
    header.objectCount = 0;
    header.flags = 0;
    header.specialCount = 0;
    header.selectedCount = 0;
    fn_80042678((u16)lbl_803003C8.room, &lbl_8064B6B8, lbl_8064D68C,
                 fn_80228250(0x100, 0x100, 1, 0, 0));
    size = fn_800BA068(destination + 0x14, -1, selected, &count) + 0x14;
    selectedKey = (u32)fn_80204844(fn_80201B9C(), 0x22);
    if (selectedKey != 0) {
        info = fn_80201B8C((void *)selectedKey);
        if (info != 0 && info->state != 0) {
            wantedId = ((ObjectState *)info->state)->identifier;
        }
    }

    node = fn_80201B9C();
    while (node != 0) {
        if (fn_800BA124(node, selectedKey, wantedId) != 0 &&
            fn_8003BF5C(node) != 0 &&
            fn_80043FB0(node, &kind, &value) == 0 && kind == 1) {
            camera = fn_80201BC8(node);
            fn_8011EB04(camera);
            fn_8011FB4C(camera);
            fn_8011F114((Vec3 *)transform, (Vec3 *)camera);
            selectedId = value;
            memcpy(destination + (u16)size, &selectedId, 2);
            size += 2;
            header.selectedCount++;
        }
        node = fn_80201BC0(node);
    }

    node = fn_80201B9C();
    while (node != 0) {
        s32 include = fn_800BA124(node, selectedKey, wantedId);
        if (fn_8003BF5C(node) != 0 &&
            fn_80043FB0(node, &other, &field) == 0 && other == 1) {
            include = 0;
        }
        if (include != 0) {
            size += fn_800B9578(destination + (u16)size, node, &count, 0);
            header.objectCount++;
        }
        node = fn_80201BC0(node);
    }

    node = fn_80201B9C();
    while (node != 0) {
        id = fn_80201B54(node);
        if (fn_80201B5C(node) == 0x22) {
            cameraState = (ObjectState *)fn_80201B8C(node)->state;
            header.flags |= 2;
            if (fn_80200614(id, -1, 0x39) != 0) {
                cameraPacket.time = lbl_8064F010;
            } else {
                cameraPacket.time = fn_80200534(id, -1, 0x5f);
                oldTime = (float)fn_80117E58();
                cameraPacket.time += fn_80200BDC() - oldTime;
            }
            cameraPacket.value = cameraState->value;
        }
        node = fn_80201BC0(node);
    }
    if (header.flags != 0) {
        memcpy(destination + (u16)size, &cameraPacket, 12);
        size += 12;
    }

    node = fn_80201B9C();
    while (node != 0) {
        s32 type = fn_80201B5C(node);
        if (type == 0x4e) {
            info = fn_80201B8C(node);
            special.type = type;
            special.identifier = ((Direction *)info->direction)->identifier;
            fn_80179E60(special.angles, (float *)info->direction);
            memcpy(destination + (u16)size, &special, 12);
            size += 12;
            header.specialCount++;
        }
        node = fn_80201BC0(node);
    }
    memcpy(destination, &header, 0x14);

    result = (size + 0x1f) & 0xffe0;
    if (*(s32 *)(lbl_80332158 + 0x24) != 0) {
        fn_801EB9F0(lbl_80332158 + 0x28);
        fn_801EF3E0(*(float *)(lbl_80332158 + 0x144),
                     *(float *)(lbl_80332158 + 0x148));
        color = *(s32 *)(lbl_80332158 + 0x14c);
        fn_801ECBBC(&color);
        DCInvalidateRange((void *)lbl_8064D68C,
                          fn_80228250(0x100, 0x100, 1, 0, 0));
        fn_801EBDDC(lbl_80332158 + 0x28);
    }
    fn_801EBA58((void *)lbl_8064D68C);
    return result;
}
