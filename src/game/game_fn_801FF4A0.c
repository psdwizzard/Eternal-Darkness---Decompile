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

void fn_801FF4A0(Context* context, Node* inserted)
{
    Node* node = context->head;

    while (node != 0 && node->state < inserted->state) {
        context = (Context*)node;
        node = node->next;
    }
    context->head = inserted;
    inserted->next = node;
}
