typedef struct ListNode80204EC8 ListNode80204EC8;
typedef struct List80204EC8 List80204EC8;
typedef struct Object80204EC8 Object80204EC8;
typedef struct Target80204EC8 Target80204EC8;

struct ListNode80204EC8 {
    ListNode80204EC8 *previous;
    ListNode80204EC8 *next;
    int value;
};

struct List80204EC8 {
    ListNode80204EC8 *head;
    ListNode80204EC8 *volatile tail;
};

struct Object80204EC8 {
    char padding[0x30];
    List80204EC8 *list;
};

struct Target80204EC8 {
    char padding[0x10];
    int value;
};

extern int fn_80204DA0(List80204EC8 *list, ListNode80204EC8 *node);
extern void fn_80205234(ListNode80204EC8 *node);

int fn_80204EC8(Object80204EC8 *object, Target80204EC8 *target)
{
    ListNode80204EC8 *node;
    unsigned int raw_node;

    if (object != 0 && target != 0) {
        List80204EC8 *list = object->list;
        if (list != 0) {
            raw_node = (unsigned int)list->tail;
        } else {
            raw_node = 0;
        }
        node = (ListNode80204EC8 *)raw_node;

        while (node != 0) {
            if (node->value == target->value) {
                fn_80204DA0(list, node);
                fn_80205234(node);
                return 1;
            }
            node = node->next;
        }
    }

    return 0;
}
