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

extern void fn_8016166C(Collection*, List*);
extern void fn_8016152C(Collection*, List*);
extern void fn_8016158C(Collection*, List*);
extern void fn_801616EC(List*, Entry*);
extern void fn_80167454(Item*, Entry*);

void fn_80161798(Collection* collection)
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
    fn_8016166C(collection, &list);
    fn_8016152C(collection, &list);
    fn_8016158C(collection, &list);

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
                fn_801616EC(&list, entry + 1);
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
                    fn_80167454(item, (Entry*)record);
                fn_801616EC(&list, &record->entries[0]);
                fn_801616EC(&list, &record->entries[1]);
            }
            offset += sizeof(Record);
            j++;
        }
    }
}
