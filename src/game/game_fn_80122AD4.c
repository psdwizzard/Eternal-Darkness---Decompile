typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Item {
    u8 pad0[0xA];
    s16 index;
    u8 padC[0x13];
    u8 kind;
} Item;

typedef struct Runtime {
    u8 pad0[0x1E];
    u16 kind;
    u8 pad20[0x40];
    Item* items;
} Runtime;

typedef struct ObjectSlot {
    void* child;
    u16 flags;
    u16 pad6;
} ObjectSlot;

typedef struct Object {
    u8 pad0[0x3C];
    Runtime* runtime;
    u8 pad40[0x13C];
    ObjectSlot slots[25];
} Object;

typedef struct Entry {
    u32 size;
    u32 pad4;
    u32 index;
    int object_index;
} Entry;

typedef struct DisplayList {
    u32* data;
    u32 object;
    Entry* entries;
    int size;
    int count;
    u32 kind;
    int mode;
    u32 value;
} DisplayList;

extern int fn_80130998(int value, float scale);
extern void fn_80226D28(int enabled);
extern DisplayList* fn_801222A0(void* object, int kind, int mode, int value);
extern void fn_80122428(Runtime* runtime, DisplayList* list, int kind, int mode, int value);
extern void fn_801ECF50(int mode);
extern int fn_80122538(Object* object, Item* item, int object_index);
extern void fn_8022B448(u32 offset, u32 size);

void fn_80122AD4(Object* object, int mode, int filter, float scale)
{
    int i;
    Runtime* runtime;
    int kind;
    DisplayList* list;
    Entry* entry;
    u32 offset;
    int result;

    runtime = object->runtime;
    kind = fn_80130998(runtime->kind, scale);
    fn_80226D28(0);
    list = fn_801222A0(runtime, kind, mode, 0);
    if (list->data == 0) {
        fn_80122428(runtime, list, kind, mode, 0);
    }
    fn_801ECF50(mode);
    entry = list->entries;
    offset = (u32)list->data;
    for (i = 0; i < list->count; i++) {
        if (entry->size & 0x1F) {
            /* Invalidate the cached mode without advancing past this entry. */
            list->mode = -1;
        } else {
            if (entry->size != 0 &&
                (object->slots[entry->object_index].flags & 5) == 5) {
                result = fn_80122538(object, &runtime->items[entry->index], entry->object_index);
                if (result == filter) {
                    fn_8022B448(offset, entry->size);
                }
            }
            offset += entry->size;
            entry++;
        }
    }
    fn_80226D28(1);
}
