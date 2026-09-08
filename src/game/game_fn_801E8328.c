typedef unsigned int u32;

typedef struct Node {
    u32 word0;
    u32 word4;
    struct Node* next;
    struct Node* prev;
} Node;

extern Node* lbl_8064D5B0;
extern Node* fn_801E8510(void);

int fn_801E8328(u32 word0, u32 word4)
{
    Node* node = fn_801E8510();

    if (node != 0) {
        node->word0 = word0;
        node->word4 = word4;
        node->prev = lbl_8064D5B0;
        node->next = lbl_8064D5B0->next;
        if (node->next != 0) {
            node->next->prev = node;
        }
        lbl_8064D5B0->next = node;
        return 1;
    }
    return 0;
}
