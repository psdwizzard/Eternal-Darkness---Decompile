typedef unsigned int u32;

typedef struct Node {
    unsigned char pad[8];
    int size;
    unsigned char pad_C[4];
    struct Node* next;
} Node;

typedef struct Context {
    unsigned char pad[0x10];
    Node* head;
} Context;

extern void fn_801FF7D4(Node* node, u32* cursor);
extern void fn_801FF704(Node* node);

void fn_801FF838(Context* context, u32 cursor)
{
    Node* node = context->head;
    Node* previous = 0;
    int finished = 0;
    int total = 0;
    int count = 0;

    while (!finished && node != 0) {
        Node* next = node->next;

        total += node->size;
        if (total < 0x7A120 && count < 0x100) {
            fn_801FF7D4(node, &cursor);
            previous = node;
            node = next;
            count++;
        } else {
            Node* scan;

            fn_801FF704(previous);
            scan = context->head;
            while (scan != 0) {
                scan = scan->next;
            }
            finished = 1;
        }
    }
}
