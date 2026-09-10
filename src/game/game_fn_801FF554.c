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

extern void* memset(void* dest, int value, unsigned int size);
extern void fn_801FF4A0(Context* context, Node* inserted);

void fn_801FF554(Context* context)
{
    Context sorted;
    Node* node = context->head;

    memset(&sorted, 0, sizeof(Context));
    while (node != 0) {
        Node* current = node;
        node = node->next;
        current->next = 0;
        fn_801FF4A0(&sorted, current);
    }
    *context = sorted;
}
