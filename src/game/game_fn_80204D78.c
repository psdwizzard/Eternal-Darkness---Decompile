typedef struct ListNode80204D78 ListNode80204D78;

struct ListNode80204D78 {
    ListNode80204D78 *previous;
    ListNode80204D78 *next;
};

int fn_80204D78(ListNode80204D78 *node)
{
    int count = 0;

    while (node != 0) {
        node = node->next;
        count++;
    }

    return count;
}
