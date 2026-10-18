typedef unsigned int u32;

typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    u32 value;
};

typedef struct List {
    unsigned char pad00[0x1C];
    Node* head;
} List;

void InsertGlobalEvent(List* list, Node* node)
{
    Node* current = list->head;
    Node* previous = 0;

    while (current != 0) {
        if (current->value > node->value) {
            node->next = current;
            node->prev = previous;
            if (previous != 0)
                previous->next = node;
            else
                list->head = node;
            current->prev = node;
            return;
        }
        previous = current;
        current = current->next;
    }

    node->prev = previous;
    if (previous != 0)
        previous->next = node;
    else
        list->head = node;
    node->next = 0;
}
