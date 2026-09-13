typedef struct Node80204A94 Node80204A94;

struct Node80204A94 {
    void *value;
    Node80204A94 *next;
    int key;
};

extern int fn_80201B54(void *object);

Node80204A94 *fn_80204A94(Node80204A94 *node, void *object)
{
    int key;

    if (object != 0) {
        key = fn_80201B54(object);
    } else {
        key = -1;
    }

    while (node != 0 && key != -1) {
        if (node->key == key && node->value != 0) {
            return node;
        }
        node = node->next;
    }

    return 0;
}
