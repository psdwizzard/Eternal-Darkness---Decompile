typedef unsigned int u32;
typedef struct Node Node;
struct Node { Node* next; unsigned char pad[8]; u32 key; };

extern Node* seqPausedRoot;
extern Node* seqActiveRoot;
extern void seqStop(u32);

void seqKillAllInstances(void)
{
    Node* node = seqActiveRoot;
    while (node != 0) {
        seqStop(node->key);
        node = node->next;
    }
    node = seqPausedRoot;
    while (node != 0) {
        seqStop(node->key);
        node = node->next;
    }
}
