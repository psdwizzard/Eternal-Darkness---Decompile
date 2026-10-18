typedef struct Node Node;
struct Node {
    Node* next;
    unsigned char pad[5];
    unsigned char type;
    unsigned char pad2[2];
    unsigned int value;
};

extern Node* seqPausedRoot;
extern Node* seqActiveRoot;

int seqGetPrivateId(unsigned int value)
{
    unsigned int key = __rlwinm(value, 0, 1, 31);
    Node* first = seqActiveRoot;
    Node* second;

    while (first != 0) {
        if (first->value == key) {
            key = first->type;
            return key | (value & 0x80000000U);
        }
        first = first->next;
    }

    second = seqPausedRoot;
    while (second != 0) {
        if (second->value == key) {
            key = second->type;
            return key | (value & 0x80000000U);
        }
        second = second->next;
    }

    return -1;
}
