typedef struct Node80205134 {
    void *value;
    void *next;
    int id;
} Node80205134;

int fn_80205134(Node80205134 *node)
{
    if (node != 0 && node->value != 0) {
        return node->id;
    }

    return -1;
}
