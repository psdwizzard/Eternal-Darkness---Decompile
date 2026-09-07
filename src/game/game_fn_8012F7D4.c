typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Pair {
    u32 first;
    u32 second;
} Pair;

typedef struct Item {
    int id;
    u8 pad4[4];
    u16 flags;
    u8 padA[2];
    Pair pair;
    u8 pad14[0x18];
    u32 value2C;
    u32 value30;
    u32 value34;
    u32 value38;
    u8 rest[0x54];
} Item;

typedef struct Object {
    u8 pad[0x23C];
    Item* items;
} Object;

#pragma pack(1)
typedef struct SerializedItem {
    int index;
    u16 flags;
    Pair pair;
    u32 value2C;
    u32 value30;
    u32 value34;
    u32 value38;
    u8 pad[2];
} SerializedItem;
#pragma pack()

#pragma use_lmw_stmw on

extern int fn_8012F700(Object*);
extern void* memcpy(void*, const void*, unsigned long);

int fn_8012F7D4(u8* output, Object* object)
{
    u8 count = fn_8012F700(object);
    int outputOffset;
    int i;

    memcpy(output, &count, 1);
    for (i = 0, outputOffset = 1; i < 12; i++) {
        Item* item;
        if (object->items == 0) {
            continue;
        }
        item = (Item*)((u8*)object->items + (u32)i * 0x90);
        if (item != 0 && item->id != -1) {
            u16 flags = item->flags;
            if (!(flags & 1) || (flags & 2) || (flags & 4)) {
                SerializedItem serialized;
                serialized.index = i;
                serialized.flags = item->flags;
                serialized.pair = item->pair;
                serialized.value2C = item->value2C;
                serialized.value30 = item->value30;
                serialized.value34 = item->value34;
                serialized.value38 = item->value38;
                memcpy(output + outputOffset, &serialized, 0x20);
                outputOffset += 0x20;
            }
        }
    }
    return (outputOffset + 0x1F) & ~0x1F;
}
