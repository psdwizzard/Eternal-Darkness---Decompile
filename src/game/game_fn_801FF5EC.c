typedef struct Node {
    void* object;
    unsigned int id;
    unsigned int value;
    int state;
    struct Node* next;
} Node;

typedef struct Context {
    unsigned char pad[0x10];
    Node* head;
} Context;

extern void fn_801FF554(Context* context);

void fn_801FF5EC(Context* left, Context* right)
{
    Node* left_node;
    Node* right_node;

    if (left != 0) {
        fn_801FF554(left);
        left_node = left->head;
    }
    if (right != 0) {
        fn_801FF554(right);
        right_node = right->head;
    }
    if (left != 0) {
        left->head = 0;
    }

    while (left_node != 0) {
        Node* scan = left_node;
        Node* remainder;

        if (right_node != 0) {
            while (right_node->next != 0 &&
                   right_node->next->state < left_node->state) {
                right_node = right_node->next;
            }
            if (right_node->next != 0) {
                while (scan->next != 0 &&
                       scan->next->state < right_node->next->state) {
                    scan = scan->next;
                }
                remainder = scan->next;
                scan->next = right_node->next;
                right_node->next = left_node;
                left_node = remainder;
                right_node = scan;
                continue;
            }
        }

        right->head = left_node;
        right_node = right->head;
        left_node = left_node->next;
        right_node->next = 0;
    }
}
