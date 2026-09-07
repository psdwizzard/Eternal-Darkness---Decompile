typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Slot {
    void* owner;
    u32 capacity;
    void* data;
    u32 field_C;
    u32 field_10;
    u16 field_14;
    u8 state;
} Slot;

typedef struct Pair { u16 count; u16 pad; void* data; } Pair;
typedef struct Entry { u32 count; void* array; } Entry;
typedef struct Object {
    void* records;
    u16 record_count;
    char pad_6[0xA];
    Entry entries[32];
    char pad_110[4];
    void* base;
    char pad_118[4];
    u32 source;
    u32 size;
    Slot* slot;
} Object;

typedef struct Manager { char pad_0[0x244]; u32 tag; } Manager;

extern Slot* fn_80134F7C(Object*);
extern char* fn_8013523C(Manager*, Object*);

Slot* fn_8013507C(Manager* manager, Object* object)
{
    Slot* slot = fn_80134F7C(object);
    char* image;
    char* section;
    int i;
    slot->state = 4;
    object->slot = slot;
    slot->field_14 = manager->tag;
    slot->owner = object;
    slot->field_C = object->source;
    slot->field_10 = object->size;
    image = fn_8013523C(manager, object);
    object->base = image + *(u32*)image;
    section = image + *(u32*)(image + 12);
    object->records = image + *(u32*)(image + 8);
    for (i = 0; i < object->record_count; i++) {
        Pair* p = (Pair*)((char*)object->records + i * 16);
        Pair* q = (Pair*)((char*)p + 8);
        if (p->count == 0) {
            p->data = 0;
        } else {
            p->data = image + (u32)p->data;
        }
        if (q->count == 0) {
            q->data = 0;
        } else {
            q->data = image + (u32)q->data;
        }
    }
    for (i = 0; i < 32; i++) {
        if (object->entries[i].count != 0) {
            object->entries[i].array = section;
            section += object->entries[i].count * 8;
        } else {
            object->entries[i].array = 0;
        }
    }
    return slot;
}
