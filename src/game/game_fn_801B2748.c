typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    void* object;
};

typedef struct State {
    unsigned char pad[0xE64];
    Node* lists[3];
} State;

extern State* cseq;
extern void synthSendKeyOff(void*);

void KeyOffNotes(void)
{
    Node* node;
    Node* next;
    unsigned int i;

    for (i = 0; i < 2; i++) {
        node = cseq->lists[i];
        while (node != 0) {
            next = node->next;
            synthSendKeyOff(node->object);
            if ((cseq->lists[i] = node->next) != 0) {
                cseq->lists[i]->prev = 0;
            }
            if ((node->next = cseq->lists[2]) != 0) {
                cseq->lists[2]->prev = node;
            }
            cseq->lists[2] = node;
            node = next;
        }
    }
}
