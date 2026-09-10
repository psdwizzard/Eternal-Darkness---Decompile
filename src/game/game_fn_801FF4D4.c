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

extern Node* fn_801FF338(Context* context);
extern void fn_801FF4A0(Context* context, Node* inserted);

int fn_801FF4D4(Context* context, void* object, unsigned int value,
                unsigned int id)
{
    Node* node = fn_801FF338(context);

    node->state = 0;
    node->value = value;
    node->id = id;
    node->object = object;
    if (node == 0) {
        return 0;
    }
    fn_801FF4A0(context, node);
    return 1;
}
