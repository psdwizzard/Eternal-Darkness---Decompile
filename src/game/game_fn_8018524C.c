typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void* memcpy(void*, const void*, u32);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern u8 fn_8018E26C(void*, void*);

typedef struct Entry {
    u8 active;
    u8 pad_01[9];
    u8 position[6];
    u8 pad_10[0x1B];
    u8 field_2B;
    u8 pad_2C[0x0C];
} Entry;

typedef struct Object {
    u8 pad_00;
    u8 count;
    u8 pad_02[2];
    u8 field_04;
    u8 pad_05[5];
    u16 counter;
    u16 limit;
    u8 pad_0E[0x14];
    u16 state;
    u8 pad_24[0x28];
    Entry* entries;
    u8 pad_50[0x44];
    int field_94;
    u8 position[12];
    u16 flags;
} Object;

typedef struct Header8018524C {
    u8 pad00[0xC];
    u16 flags;
} Header8018524C;

u32 fn_8018524C(Object* self)
{
    int count;
    int old_counter;
    u8* position;
    Entry* entry;
    int index;
    Entry* entry1;
    Entry* current;
    Entry* destination0;
    Entry* source0;
    Entry* destination1;
    Entry* source1;
    Header8018524C* header;

    position = (u8*)self + 0x98;
    header = (Header8018524C*)position;
    old_counter = self->counter;
    entry = self->entries;
    count = self->count;
    entry1 = self->entries + 1;
    self->counter = old_counter + 1;

    destination0 = entry + (count - 2);
    destination1 = entry1 + (count - 2);
    source0 = destination0 - 2;
    source1 = destination1 - 2;

    if (self->flags & 1) {
        index = (count >> 1) - 1;
        while (index > 0) {
            memcpy(destination0->position, source0->position, 6);
            destination0 -= 2;
            source0 -= 2;
            memcpy(destination1->position, source1->position, 6);
            destination1 -= 2;
            source1 -= 2;
            index--;
        }
        memcpy(entry[0].position, position, 6);
        memcpy(entry1->position, position + 6, 6);
        header->flags &= ~1;
    }

    if (header->flags & 0x10) {
        current = entry;
        for (index = 0; index < count; current++, index++) {
            if (current->active)
                fn_8018E26C(current, &current->field_2B);
        }
    }

    if (header->flags & 8) {
        header->flags |= 0x10;
        header->flags &= ~8;
        for (index = 0; index < count; entry++, index++) {
            fn_8018E230(entry, &entry->field_2B, 1, entry->field_2B,
                        self->field_04, 0);
        }
    }

    if (self->field_94 == 0 &&
        ((header->flags & 2) != 0 || old_counter > self->limit)) {
        self->state = 8;
    }
    return 0;
}
