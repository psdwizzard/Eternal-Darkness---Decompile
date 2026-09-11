typedef struct EventNode EventNode;

struct EventNode {
    int field_00;
    EventNode *next;
    int field_08;
    int field_0c;
    int kind;
};

typedef struct EventList {
    EventNode *field_00;
    EventNode *head;
} EventList;

extern EventList *fn_802014AC(int);
extern int fn_80201EB8(EventNode *);
extern void fn_8020104C(int, int, int, int, float);

void fn_80200EAC(int arg0, int arg1, int arg2, int arg3, float time)
{
    EventNode *node;

    node = fn_802014AC(arg0)->head;
    while (node != 0) {
        int value = fn_80201EB8(node);
        if (node->kind != arg1) {
            if (value == arg3 || value == -1) {
                fn_8020104C(arg0, arg1, node->kind, arg2, time);
            }
        }
        node = node->next;
    }
}
