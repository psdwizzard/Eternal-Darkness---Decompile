typedef unsigned int u32;

typedef struct Node {
    void* object;
    u32 id;
    u32 value;
    u32 state;
    struct Node* next;
} Node;

typedef struct Context {
    unsigned char pad[0x10];
    Node* head;
} Context;

Node* fn_801FF2F8(Context* context, u32 id)
{
    Node* node = context->head;
    Node* found = 0;

    while (node != 0) {
        if (node->object != 0 && node->id == id) {
            node->state = 0;
            found = node;
        }
        node = node->next;
    }
    return found;
}
