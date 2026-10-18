typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

#define NULL 0
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct Entry {
    u32 size;
    u32 pad4;
    u32 index;
    int object_index;
} Entry;

typedef struct EntryList {
    u8* data;
    u32 pad4;
    Entry* entries;
    u32 padC;
    int count;
} EntryList;

typedef struct MeshInfo MeshInfo;

typedef struct ObjectState {
    u16 flags;
    u8 pad2[6];
} ObjectState;

typedef struct Object {
    unsigned char pad0[0x3C];
    MeshInfo* runtime;
    unsigned char pad40[0x140];
    ObjectState object_state[4];
    unsigned char pad1A0[0xB4];
    u32 state_flags;
    unsigned char pad258[0x80];
    s8 fade_step;
    u8 fade_level;
} Object;

typedef struct Material {
    u8 pad00[0x1F];
    u8 alpha;
} Material;

extern void fn_801ECF50(int mode);
extern void fn_801ED118(void);
extern EntryList* fn_801222A0(void* runtime, int kind, int mode, int unused);
extern void fn_80122428(MeshInfo* runtime, EntryList* list, int kind, int mode, int unused);
extern void fn_801ED5F4(int, int, s16, float*, float (*)[4], float);
extern int fn_801EDA7C(s16* values, int context, int flags, void* state);
extern void fn_801ECEC8(int, int, int);
extern void GXSetBlendMode(int, int, int, int);
extern void GXSetColorUpdate(int);
extern void GXSetAlphaUpdate(int);
extern void GXCallDisplayList(void* list, u32 size);
extern Material lbl_8024EDE8[];
extern const float lbl_806500A0;

void fn_801227A0(Object* object, int kind, int inverted)
{
    MeshInfo* runtime;
    int mode = 7;
    EntryList* list;
    int i;
    Entry* entry;
    u8* data;

    runtime = object->runtime;
    if (object->state_flags & 0x00400000) {
        mode = 1;
    }
    fn_801ECF50(mode);
    fn_801ED118();
    list = fn_801222A0(runtime, kind, mode, 0);
    if (list->data == 0) {
        fn_80122428(runtime, list, kind, mode, 0);
    }

    if (!(object->state_flags & 0x00040000)) {
        return;
    }

    object->fade_level = MIN(MAX(object->fade_level + object->fade_step, 50), 150);

    lbl_8024EDE8[1].alpha = object->fade_level;
    fn_801ED5F4(0, 0, 0, NULL, NULL, lbl_806500A0);
    if (inverted) {
        lbl_8024EDE8[1].alpha = 305 - object->fade_level;
    }
    if (object->fade_level == 50 || object->fade_level == 150) {
        object->fade_step = -object->fade_step;
    }
    fn_801EDA7C((s16*)&lbl_8024EDE8[1], 0, 0x2BF, 0);

    if (inverted) {
        GXSetAlphaUpdate(1);
        GXSetColorUpdate(0);
        fn_801ECEC8(1, 3, 1);
        GXSetBlendMode(2, 4, 5, 3);
        entry = list->entries;
        data = list->data;
        for (i = 0; i < list->count; entry++, i++) {
            if (entry->size != 0 &&
                (object->object_state[entry->object_index].flags & 5) == 5) {
                GXCallDisplayList(data, entry->size);
            }
            data += entry->size;
        }
        entry = list->entries;
        for (i = 0; i < list->count; entry++, i++) {
            object->object_state[entry->object_index].flags &= ~2;
        }
        object->state_flags &= ~0x00040000u;
        GXSetBlendMode(1, 4, 5, 15);
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
    } else {
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        fn_801ECEC8(1, 3, 1);
        GXSetBlendMode(1, 4, 5, 0);
        entry = list->entries;
        data = list->data;
        for (i = 0; i < list->count; entry++, i++) {
            if (entry->size != 0 &&
                (object->object_state[entry->object_index].flags & 3) == 3) {
                GXCallDisplayList(data, entry->size);
            }
            data += entry->size;
        }
        entry = list->entries;
        for (i = 0; i < list->count; entry++, i++) {
            object->object_state[entry->object_index].flags &= ~2;
        }
        object->state_flags &= ~0x00040000u;
    }
}
