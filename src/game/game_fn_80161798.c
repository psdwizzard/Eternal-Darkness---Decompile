typedef struct Entry {
    int kind;
    char pad04[0xC];
} Entry;

typedef struct Record {
    Entry entries[2];
    char pad20[8];
} Record;

typedef struct Item {
    Record* entries;
    int unused;
    int count;
    char pad0C[8];
    struct Item* next;
} Item;

typedef struct Node {
    void* unused0;
    char pad04[4];
    struct Node* next;
    char pad0C[2];
    short count;
    Entry entries[1];
} Node;

typedef struct List {
    Item* items;
    Node* nodes;
} List;

typedef struct Collection {
    char pad00[0x44];
    Item* first;
} Collection;

extern void marktagmethods(Collection*, List*);
extern void markstack(Collection*, List*);
extern void marklock(Collection*, List*);
extern void markobject(List*, Entry*);
extern void luaH_remove(Item*, Entry*);

void markall(Collection* collection)
{
    List list;
    Entry* entry;
    Node* node;
    Item* item;
    int i;
    int j;
    int offset;
    Record* record;

    list.nodes = 0;
    list.items = collection->first;
    list.items->next = 0;
    marktagmethods(collection, &list);
    markstack(collection, &list);
    marklock(collection, &list);

    for (;;) {
        for (;;) {
            node = list.nodes;
            if (node == 0) {
                break;
            }
            list.nodes = node->next;
            entry = (Entry*)node;
            i = 0;
            while (i < node->count) {
                markobject(&list, entry + 1);
                entry++;
                i++;
            }
        }

        if (list.items == 0) {
            break;
        }
        item = list.items;
        list.items = item->next;
        j = 0;
        offset = 0;
        while (j < item->count) {
            record = (Record*)((char*)item->entries + offset);
            if (record->entries[0].kind != 1) {
                if (record->entries[1].kind == 1)
                    luaH_remove(item, (Entry*)record);
                markobject(&list, &record->entries[0]);
                markobject(&list, &record->entries[1]);
            }
            offset += sizeof(Record);
            j++;
        }
    }
}
