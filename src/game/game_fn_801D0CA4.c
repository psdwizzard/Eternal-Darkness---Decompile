typedef struct Node Node;

struct Node {
    char pad[0x14];
    Node* next;
    Node* previous;
};

extern Node* lbl_8064D540;
extern Node* lbl_8064D544;

void fn_801D0CA4(Node* node)
{
    Node* tail;

    if (node == 0) {
        return;
    }

    tail = lbl_8064D540;
    if (tail != 0) {
        tail->next = node;
        node->previous = lbl_8064D540;
        lbl_8064D540 = node;
    } else {
        lbl_8064D540 = node;
        lbl_8064D544 = node;
    }
}
