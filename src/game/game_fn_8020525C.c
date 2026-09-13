typedef struct Node8020525C {
    void *value;
    struct Node8020525C *next;
} Node8020525C;

void fn_8020525C(volatile Node8020525C *node)
{
    if (node == 0) {
        return;
    }

    if (node->value == 0) {
        node = node->next;
    }

    while (node != 0) {
        node = node->next;
    }
}
