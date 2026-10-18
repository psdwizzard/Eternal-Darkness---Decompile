typedef struct Node {
    void* object;
    int unused;
    struct Node* next;
    short count;
} Node;

typedef struct List {
    int unused;
    Node* head;
} List;

extern void protomark(void*);

void markclosure(List* list, Node* node)
{
    if (node->next == node) {
        if (node->count == 0)
            protomark(node->object);
        node->next = list->head;
        list->head = node;
    }
}
