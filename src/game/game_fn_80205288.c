typedef struct Node80205288 {
    void *unknown0;
    struct Node80205288 *next;
    int value;
} Node80205288;

typedef struct Object80205288 {
    unsigned char unknown0[0x30];
    Node80205288 *list;
} Object80205288;

extern void *fn_80205158(Node80205288 *node);
extern int fn_80157C80(void *object);
extern void *fn_80201814(int object);

void *fn_80205288(Object80205288 *object)
{
    int result = 0;
    Node80205288 *node = object->list;

    node = node != 0 ? node->next : node;

    while (node != 0 && result == 0) {
        if (fn_80157C80(fn_80205158(node)) & 2) {
            result = node->value;
        }
        node = node->next;
    }

    if (result != 0) {
        return fn_80201814(result);
    }
    return 0;
}
