typedef struct ListNode80204E0C ListNode80204E0C;
typedef struct List80204E0C List80204E0C;

struct ListNode80204E0C {
    ListNode80204E0C *previous;
    ListNode80204E0C *next;
    int count;
};

struct List80204E0C {
    ListNode80204E0C *head;
    ListNode80204E0C *tail;
    int count;
};

extern List80204E0C *fn_80204B10(void *object, int *index);
extern ListNode80204E0C *fn_80204A94(ListNode80204E0C *node, void *object);
extern int fn_80204DA0(List80204E0C *list, ListNode80204E0C *node);

int fn_80204E0C(void *object, ListNode80204E0C *target)
{
    int result = 0;

    if (object != 0 && target != 0) {
        List80204E0C *list = fn_80204B10(object, 0);
        ListNode80204E0C *node = fn_80204A94((ListNode80204E0C *)list, object);

        if (list != 0 && node != 0) {
            fn_80204DA0(list, node);
            node->previous = target;
            node->next = target->next;
            target->next = node;
            if (node->next != 0) {
                node->next->previous = node;
            }
            target->count++;
            result = 1;
        }
    }

    return result;
}
