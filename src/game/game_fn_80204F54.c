typedef struct ListNode80204F54 ListNode80204F54;
typedef struct List80204F54 List80204F54;
typedef struct Object80204F54 Object80204F54;

struct ListNode80204F54 {
    ListNode80204F54 *previous;
    ListNode80204F54 *next;
    int value;
};

struct List80204F54 {
    ListNode80204F54 *head;
    ListNode80204F54 *tail;
};

struct Object80204F54 {
    char padding[0x10];
    int value;
};

extern List80204F54 *fn_80204A8C(void);
extern int fn_80204DA0(List80204F54 *list, ListNode80204F54 *node);
extern void fn_80205234(ListNode80204F54 *node);

int fn_80204F54(Object80204F54 *object)
{
    ListNode80204F54 *node;
    List80204F54 *list = fn_80204A8C();

    if (list != 0) {
        node = list->tail;
    } else {
        node = 0;
    }

    while (node != 0) {
        if (node->value == object->value) {
            fn_80204DA0(fn_80204A8C(), node);
            fn_80205234(node);
            return 1;
        }
        node = node->next;
    }

    return 0;
}
