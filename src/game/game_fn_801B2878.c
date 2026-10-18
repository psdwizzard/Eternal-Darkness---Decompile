typedef struct Node Node;
struct Node {
    Node* next;
    unsigned char pad[8];
    unsigned int value;
};

typedef struct Entry {
    unsigned char pad[12];
    unsigned int value;
    unsigned char rest[0x1858];
} Entry;

extern Node* seqPausedRoot;
extern Node* seqActiveRoot;
extern volatile unsigned int seq_next_id;
extern Entry lbl_8060D420[];

unsigned int GetPublicId(int index)
{
    Node* first;
    Node* second;
    unsigned int value;
    Node* node;

    first = seqActiveRoot;
    second = seqPausedRoot;

    do {
        value = seq_next_id++;
        seq_next_id = __rlwinm(seq_next_id, 0, 1, 31);

        node = first;
        while (node != 0) {
            if (node->value == value) {
                value = -1;
                break;
            }
            node = node->next;
        }

        node = second;
        while (node != 0) {
            if (node->value == value) {
                value = -1;
                break;
            }
            node = node->next;
        }
    } while (value == (unsigned int)-1);

    return lbl_8060D420[index].value = value;
}
