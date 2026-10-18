typedef struct Item {
    void* first;
    char pad04[0xC];
    int active;
    void* next;
} Item;

typedef struct Entry {
    int kind;
    int unused;
    Item* item;
} Entry;

typedef struct List {
    Item* head;
} List;

extern void markclosure(List*, Item*);

void markobject(List* list, Entry* entry)
{
    Item* item;

    switch (entry->kind) {
    case 0:
    case 3:
        item = entry->item;
        if (item->active == 0)
            item->active = 1;
        break;
    case 6:
        markclosure(list, entry->item->first);
        break;
    case 5:
        markclosure(list, entry->item);
        break;
    case 4:
        item = entry->item;
        if (item->next == item) {
            item->next = list->head;
            list->head = entry->item;
        }
        break;
    }
}
