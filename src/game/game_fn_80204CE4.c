typedef struct ListNode80204CE4 ListNode80204CE4;

struct ListNode80204CE4 {
    ListNode80204CE4 *previous;
    ListNode80204CE4 *next;
    unsigned int value;
};

extern ListNode80204CE4 *fn_80205210(void *object);
extern unsigned int fn_80201B54(void *object);

int fn_80204CE4(void *object, ListNode80204CE4 *node)
{
    ListNode80204CE4 *new_node;

    if (object != 0 && node != 0) {
        new_node = fn_80205210(object);
        new_node->previous = node;
        new_node->next = node->next;
        node->next = new_node;
        if (new_node->next != 0) {
            new_node->next->previous = new_node;
        }
        new_node->value = fn_80201B54(object);
        node->value++;
        return 1;
    }

    return 0;
}
