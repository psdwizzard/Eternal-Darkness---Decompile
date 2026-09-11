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

int fn_80200F3C(int arg0, int arg1)
{
    EventNode *node;
    int count;

    node = fn_802014AC(arg0)->head;
    count = 0;
    while (node != 0) {
        if (node->kind != arg0) {
            if (arg1 == fn_80201EB8(node)) {
                count++;
            }
        }
        node = node->next;
    }
    return count;
}
