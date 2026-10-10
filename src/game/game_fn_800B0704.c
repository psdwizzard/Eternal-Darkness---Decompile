typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct SaveHeader {
    s32 key;
    s32 previous;
    s32 room;
    s32 cameraMode;
    s32 cameraParam;
    u8 pad[0x2C];
} SaveHeader;

typedef struct SaveState {
    s32 key;
    s32 previous;
    s32 room;
} SaveState;

typedef struct EntryName {
    char text[11];
} EntryName;

typedef struct CameraName {
    char text[9];
} CameraName;

extern void *memcpy(void *dst, const void *src, u32 size);
extern s32 fn_80008888(void *data, s32 key);
extern void fn_80024B74(s32 room);
extern void fn_80042678(u16 room, const char *name, s32 arg, s32 handle);
extern void fn_80042818(s32 room);
extern void fn_80042CAC(s32 a, s32 b);
extern void fn_80042DA8(void);
extern void fn_80042DEC(s32 a);
extern void fn_80042F7C(s32 room, s32 b);
extern void fn_80043034(s32 a);
extern void fn_800477F8(s32 a, s32 b);
extern void fn_800B0414(s32 a, s32 b, s32 c, s32 mode, s32 param);
extern s32 fn_800BB270(void *data);
extern void fn_801597BC(s32 room, u32 entry, u32 camera, s32 a, s32 b);
extern u8 *fn_8017BA24(void);
extern u32 fn_801E741C(const char *name);
extern s32 fn_80228250(s32 a, s32 b, s32 c, s32 d, s32 e);

extern const EntryName lbl_802397B0;
extern const CameraName lbl_802397BC;
extern SaveState lbl_803003C8;
extern char lbl_8064B6B8[5];
extern s32 lbl_8064D18C;
extern s32 lbl_8064D68C;

s32 fn_800B0704(u8 *data, s32 isNew) {
    SaveHeader header;
    EntryName entry;
    CameraName camera;
    s32 total;
    u16 size;

    size = isNew ? 0x1900 : 0x4000;
    memcpy(&header, data, sizeof(SaveHeader));
    if (isNew) {
        lbl_803003C8.previous = lbl_803003C8.key;
    } else {
        lbl_803003C8.previous = header.previous;
    }
    lbl_803003C8.key = header.key;
    lbl_803003C8.room = header.room;
    total = fn_80008888(data + 0x40, header.key) + 0x40;
    fn_80042F7C(lbl_803003C8.room, 1);
    fn_80043034(3);
    fn_80042818(lbl_803003C8.room);
    switch (header.cameraMode) {
    case 0x77:
        fn_80042DEC(2);
        fn_80042DA8();
        break;
    case 0x78:
        fn_80042CAC(2, 1);
        fn_80042DEC(3);
        fn_80042DA8();
        break;
    case 0x79:
        fn_80042CAC(3, 1);
        fn_80042DEC(4);
        fn_80042DA8();
        break;
    case 0x7A:
        fn_80042CAC(4, 1);
        break;
    }
    fn_800B0414(3, 0, 0, header.cameraMode, header.cameraParam);
    fn_80024B74(lbl_803003C8.room);
    memcpy(fn_8017BA24(), data, size);
    fn_80042678(lbl_803003C8.room, lbl_8064B6B8, lbl_8064D68C, fn_80228250(0x100, 0x100, 1, 0, 0));
    total += fn_800BB270(fn_8017BA24() + (u16)total);
    memcpy(data, fn_8017BA24(), size);
    fn_800477F8(1, 0);
    if (isNew) {
        entry = lbl_802397B0;
        camera = lbl_802397BC;
        lbl_8064D18C = 0x47;
        fn_801597BC(lbl_8064D18C, fn_801E741C(entry.text), fn_801E741C(camera.text), 0, 0);
    }
    return total;
}
