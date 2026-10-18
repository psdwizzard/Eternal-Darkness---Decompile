typedef struct Item {
    char pad00[8];
    struct Item* link8;
    char pad0C[4];
    int active;
    struct Item* link14;
} Item;

typedef struct Entry {
    int kind;
    int unused;
    Item* item;
} Entry;

int hasmark(Entry* entry)
{
    switch (entry->kind) {
    case 0:
    case 3:
        return entry->item->active;
    case 4:
        return entry->item->link14 != entry->item;
    case 5:
        return entry->item->link8 != entry->item;
    default:
        return 1;
    }
}
