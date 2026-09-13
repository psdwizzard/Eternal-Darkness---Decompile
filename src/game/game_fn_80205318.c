typedef struct Node80205318 {
    void *unknown0;
    struct Node80205318 *next;
    int value;
} Node80205318;

typedef struct Object80205318 {
    unsigned char unknown0[0x30];
    Node80205318 *list;
} Object80205318;

extern void *fn_80205158(Node80205318 *node);
extern int fn_80157C80(void *object);
extern void *fn_80201814(int object);
extern void fn_802020B4(void *object, void *value);

int fn_80205318(Object80205318 *object, void *value)
{
    int count = 0;
    Node80205318 *node = object->list;

    node = node != 0 ? node->next : node;

    while (node != 0) {
        if (fn_80157C80(fn_80205158(node)) & 2) {
            void *target = fn_80201814(node->value);
            if (target != 0) {
                count++;
                fn_802020B4(target, value);
            }
        }
        node = node->next;
    }

    return count;
}
