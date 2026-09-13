typedef struct Node802051A4 {
    void *value;
    struct Node802051A4 *next;
    int id;
} Node802051A4;

Node802051A4 *fn_802051A4(Node802051A4 *node)
{
    if (node != 0) {
        return node->next;
    }

    return 0;
}
