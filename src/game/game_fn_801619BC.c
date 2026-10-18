typedef struct Node {
    char pad00[0x26];
    short active;
    struct Node* next;
} Node;

typedef struct Collection {
    char pad00[0x20];
    Node* nodes;
} Collection;

extern void luaF_freeproto(Collection*, Node*);

void collectproto(Collection* collection)
{
    int zero = 0;
    Node** link = &collection->nodes;

    while (*link != 0) {
        Node* node = *link;
        if (node->active != 0) {
            node->active = zero;
            link = &node->next;
        } else {
            *link = node->next;
            luaF_freeproto(collection, node);
        }
    }
}
