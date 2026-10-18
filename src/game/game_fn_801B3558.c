typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    unsigned char state;
};

extern Node* seqPausedRoot;
extern Node* seqActiveRoot;

void StartPause(Node* node)
{
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        seqActiveRoot = node->next;
    }

    if (node->next != 0) {
        node->next->prev = node->prev;
    }

    if ((node->next = seqPausedRoot) != 0) {
        seqPausedRoot->prev = node;
    }
    node->prev = 0;
    seqPausedRoot = node;
    node->state = 2;
}
