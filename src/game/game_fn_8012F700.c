typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Item {
    int id;
    u8 pad[4];
    u16 flags;
    u8 rest[0x86];
} Item;

typedef struct Object {
    u8 pad[0x23C];
    Item* items;
} Object;

int fn_8012F700(Object* object)
{
    int count = 0;
    int i;

    if (object->items != 0) {
        for (i = 0; i < 12; i++) {
            Item* item = &object->items[i];
            if (item != 0 && item->id != -1) {
                u16 flags = item->flags;
                if (!(flags & 1) || (flags & 2) || (flags & 4)) {
                    count++;
                }
            }
        }
    }
    return count;
}
