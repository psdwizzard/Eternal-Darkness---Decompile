typedef struct ListNode80204DA0 ListNode80204DA0;
typedef struct List80204DA0 List80204DA0;

struct ListNode80204DA0 {
    ListNode80204DA0 *previous;
    ListNode80204DA0 *next;
};

struct List80204DA0 {
    ListNode80204DA0 *head;
    ListNode80204DA0 *tail;
    int count;
};

extern int fn_80204D78(ListNode80204DA0 *node);

int fn_80204DA0(List80204DA0 *list, ListNode80204DA0 *node)
{
    if (list != 0 && node != 0) {
        list->count--;
        node->previous->next = node->next;
        if (node->next != 0) {
            node->next->previous = node->previous;
        }
        fn_80204D78(list->tail);
        return 1;
    }

    return 0;
}
