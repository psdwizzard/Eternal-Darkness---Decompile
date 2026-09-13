typedef struct Node802053B0 {
    void *unknown0;
    struct Node802053B0 *next;
    int value;
} Node802053B0;

typedef struct Object802053B0 {
    unsigned char unknown0[0x30];
    Node802053B0 *list;
} Object802053B0;

extern void *fn_80205158(Node802053B0 *node);
extern int fn_80158234(void *object);
extern unsigned int fn_80157BF4(void *object);
extern void *fn_80201814(int object);

void *fn_802053B0(Object802053B0 *object, void *value)
{
    int result = 0;
    Node802053B0 *node = object->list;

    node = node != 0 ? node->next : node;

    while (node != 0 && result == 0) {
        void *current = fn_80205158(node);

        if (((unsigned short)fn_80158234(current) &
             (unsigned short)fn_80158234(value)) != 0 &&
            current != value && fn_80157BF4(current) == 4) {
            result = node->value;
        }
        node = node->next;
    }

    if (result != 0) {
        return fn_80201814(result);
    }
    return 0;
}
