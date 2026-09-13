typedef struct Node802051BC {
    void *value;
    struct Node802051BC *next;
    int id;
} Node802051BC;

Node802051BC *fn_802051BC(Node802051BC *node)
{
    if (node->next != 0) {
        while (node->next != 0) {
            node = node->next;
        }

        return node;
    }

    return 0;
}
