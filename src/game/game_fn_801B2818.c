typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
};

typedef struct State {
    unsigned char pad[0xE64];
    Node* lists[3];
} State;

extern State* cseq;
extern Node* noteFree;

void seqFreeKeyOffNote(Node* node)
{
    Node* head;
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        cseq->lists[2] = node->next;
    }

    if ((head = node->next = noteFree) != 0) {
        noteFree->prev = node;
    }
    node->prev = 0;
    noteFree = node;
}
