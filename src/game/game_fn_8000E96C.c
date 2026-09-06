typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Entry {
    char pad0[0x2C];
    s16 x;
    s16 y;
    s16 z;
    char pad32[0x16];
    u32 flags;
} Entry;

typedef struct EntryList {
    char pad0[0x34];
    u16 count;
    char pad36[2];
    Entry* entries;
} EntryList;

extern const char lbl_8023BEF8[];
extern const double lbl_8064DCE8;
extern const float lbl_8064DCF0;
extern const float lbl_8064DD00;
extern const float lbl_8064DD04;
extern void* fn_8015C390(s32);
extern void* fn_8015C2FC(s32);
extern int fn_8016A598(void*);
extern void fn_80163BB4(void*, const char*, ...);
extern int fn_80201B44(void);
extern void* fn_80201814(s32);
extern void* fn_80201BC8(void*);
extern void fn_8013F3C0(float (*)[4], const Vec3*, const Vec3*,
                       float);
extern void* fn_8013FBE4(void*, const void*, void*, void*, u32);

s32 fn_8000E96C(void* script)
{
    EntryList* list;
    void* manager;
    s32 object_id;
    s32 i;
    Entry* entry;
    float matrix[4][4];
    Vec3 rotation;
    Vec3 position;
    char result[0x18];

    list = fn_8015C390(2);
    manager = fn_8015C2FC(2);
    object_id = fn_80201B44();

    if (fn_8016A598(script) != 0) {
        fn_80163BB4(script, lbl_8023BEF8, 0, fn_8016A598(script));
        return 0;
    }

    fn_80201BC8(fn_80201814(object_id));

    if (list != 0 && list->count != 0) {
        entry = list->entries;
        for (i = 0; i < list->count; i++, entry++) {
            if (entry->flags & 0x40) {
                rotation.x = entry->x;
                rotation.y = entry->y;
                rotation.z = lbl_8064DD00 + entry->z;
                position = rotation;
                position.z -= lbl_8064DD04;
                fn_8013F3C0(matrix, &rotation, &position, lbl_8064DCF0);
                fn_8013FBE4(manager, matrix, result, 0, 0);
            }
        }
    }
    return 0;
}
