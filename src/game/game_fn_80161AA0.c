typedef struct Node {
    char pad00[0x10];
    struct Node* next;
    struct Node* owner;
} Node;

typedef struct Collection {
    char pad00[0x28];
    Node* nodes;
} Collection;

extern void luaH_free(Collection*, Node*);

void collecttable(Collection* collection)
{
    Node** link = &collection->nodes;

    while (*link != 0) {
        Node* node = *link;
        if (node->owner != node) {
            node->owner = node;
            link = &node->next;
        } else {
            *link = node->next;
            luaH_free(collection, node);
        }
    }
}
