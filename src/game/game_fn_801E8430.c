typedef unsigned int u32;

typedef struct Node {
    u32 word0;
    u32 word4;
    struct Node* next;
    struct Node* prev;
} Node;

extern Node* lbl_8064D5B0;
extern void* lbl_8064D5B4;
extern void* memset(void*, int, unsigned int);
extern void fn_8017CE74(void*, Node*);

void fn_801E8430(Node* node)
{
    lbl_8064D5B0->next = node->next;
    if (node->next != 0) {
        node->next->prev = lbl_8064D5B0;
    }
    memset(node, 0, 16);
    fn_8017CE74(lbl_8064D5B4, node);
}
