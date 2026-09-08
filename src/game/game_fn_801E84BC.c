typedef unsigned short u16;

typedef struct Node {
    void* word0;
    void* word4;
    struct Node* next;
    u16 field_C;
    u16 flags;
} Node;

extern Node lbl_80637C10[];

Node* fn_801E84BC(void)
{
    int i;
    Node* node = lbl_80637C10;

    for (i = 0; i < 350; node++, i++) {
        if (!(node->flags & 1)) {
            node = &lbl_80637C10[i];
            node->flags |= 1;
            return node;
        }
    }
    return 0;
}
