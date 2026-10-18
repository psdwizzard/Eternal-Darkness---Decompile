typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Node Node;
struct Node {
    Node* next;
    unsigned char pad[5];
    unsigned char index;
    u16 key;
    u32 value;
};

extern Node* seqPausedRoot;
extern Node* seqActiveRoot;
extern void seqStop(u32);

void seqKillInstancesByGroupID(u32 key)
{
    Node* node;

    node = seqActiveRoot;
    while (node != 0) {
        if (node->key == (u16)key) {
            seqStop(node->value);
        }
        node = node->next;
    }

    node = seqPausedRoot;
    while (node != 0) {
        if (node->key == (u16)key) {
            seqStop(node->value);
        }
        node = node->next;
    }
}
