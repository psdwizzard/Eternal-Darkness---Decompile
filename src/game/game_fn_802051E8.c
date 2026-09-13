typedef struct Node802051E8 {
    struct Node802051E8 *value;
} Node802051E8;

Node802051E8 *fn_802051E8(Node802051E8 *node)
{
    if (node != 0) {
        node = node->value;
        if (node != 0 && node->value != 0) {
            return node;
        }
    }

    return 0;
}
