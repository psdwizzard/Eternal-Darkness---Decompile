typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 size;
    u32 pad4;
    u32 index;
    int object_index;
} Entry;

typedef struct EntryList {
    u32 total_size;
    u32 pad4;
    Entry* entries;
    u32 padC;
    int count;
} EntryList;

typedef struct Runtime {
    unsigned char pad[0x60];
    unsigned char* objects;
} Runtime;

typedef struct Object {
    unsigned char pad0[0x3C];
    Runtime* runtime;
    unsigned char pad40[0x140];
    u16 object_state[16];
    unsigned char pad1A0[0xB4];
    u32 state_flags;
} Object;

extern void fn_801ECF50(int mode);
extern EntryList* fn_801222A0(Runtime* runtime, int kind, int mode, int unused);
extern void fn_80122428(Runtime* runtime, EntryList* list, int kind, int mode, int unused);
extern int fn_80122538(Object* object, void* item, int object_index);
extern int fn_80122C00(Object* object, void* item, u32 object_index, int arg,
                       int force, int extra, float first, float second);
extern void fn_8022B448(u32 offset, u32 size);

void fn_80122638(Object* object, int kind, int arg, int wanted, int force,
                 int extra, float first, float second)
{
    int i;
    Runtime* runtime = object->runtime;
    int mode = 7;
    EntryList* list;
    Entry* entry;
    u32 offset;
    int object_index;

    if (object->state_flags & 0x00400000) {
        mode = 1;
    }
    fn_801ECF50(mode);
    list = fn_801222A0(runtime, kind, mode, 0);
    if (list->total_size == 0) {
        fn_80122428(runtime, list, kind, mode, 0);
    }

    entry = list->entries;
    offset = list->total_size;
    for (i = 0; i < list->count; entry++, i++) {
        if (entry->size != 0) {
            u16* state_flags;
            object_index = entry->object_index;
            state_flags = &object->object_state[object_index * 4];
            if ((*state_flags & 5) == 5) {
                void* item = runtime->objects + entry->index * 0x20;
                int item_kind = fn_80122538(object, item, object_index);
                if (item_kind != wanted) {
                    if (force == 0) {
                        goto next_entry;
                    }
                }
                if (fn_80122C00(object, item, entry->object_index, arg, force,
                                extra, first, second)) {
                    fn_8022B448(offset, entry->size);
                }
            }
        }
    next_entry:
        offset += entry->size;
    }
}
