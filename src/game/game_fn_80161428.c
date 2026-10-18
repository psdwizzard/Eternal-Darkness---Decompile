typedef struct Item {
    char _pad00[0x10];
    int active;
} Item;

typedef struct Entry {
    Item* item;
    int minimum;
    int maximum;
} Entry;

typedef struct Object {
    char _pad00[0x8];
    Item** items;
    int item_count;
    struct Object** children;
    int child_count;
    char _pad18[0xE];
    short active;
    char _pad28[0xC];
    int entry_count;
    Entry* entries;
    char _pad3C[4];
    Item* primary;
} Object;

void protomark(Object* object)
{
    int i;

    if (object->active == 0) {
        object->active = 1;
        if (object->primary->active == 0)
            object->primary->active = 1;

        for (i = 0; i < object->item_count; i++) {
            if (object->items[i]->active == 0)
                object->items[i]->active = 1;
        }

        for (i = 0; i < object->child_count; i++)
            protomark(object->children[i]);

        for (i = 0; i < object->entry_count; i++) {
            if (object->entries[i].item->active == 0)
                object->entries[i].item->active = 1;
        }
    }
}
