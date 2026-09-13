typedef struct Node80205158 {
    void *value;
    void *next;
    int id;
} Node80205158;

typedef struct Object80205158 {
    unsigned char padding[0x2C];
    void *value;
} Object80205158;

extern Object80205158 *fn_80201814(int id);

void *fn_80205158(Node80205158 *node)
{
    Object80205158 *object;

    if (node != 0 && node->value != 0) {
        object = fn_80201814(node->id);
        if (object != 0) {
            return object->value;
        }
    }

    return 0;
}
