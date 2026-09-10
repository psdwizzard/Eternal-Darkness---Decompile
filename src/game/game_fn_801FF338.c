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

extern Node lbl_8063F048[256];
extern int lbl_8064D7DC;

Node* fn_801FF338(Context* context)
{
    int attempts = 0;
    Node* node = 0;

    while (node == 0) {
        node = &lbl_8063F048[lbl_8064D7DC];
        lbl_8064D7DC++;
        if (lbl_8064D7DC >= 256) {
            lbl_8064D7DC = 0;
        }

        attempts++;
        if (attempts > 256) {
            int i;

            if (context->head == node) {
                context->head = node->next;
            } else {
                for (i = 0; i < 256; i++) {
                    if (lbl_8063F048[i].next == node) {
                        lbl_8063F048[i].next = node->next;
                    }
                }
            }
            node->next = 0;
            return node;
        }

        if (node->object != 0) {
            node = 0;
        }
    }
    return node;
}
