typedef unsigned int u32;

typedef struct EventNode EventNode;

struct EventNode {
    int kind;
    int field_04;
    void *object;
    int field_0c;
    int field_10;
    float time;
    int field_18;
    int field_1c;
    EventNode *prev;
    EventNode *next;
    u32 flags;
};

typedef struct EventList {
    char pad[0x24];
    EventNode *head;
} EventList;

extern EventList *lbl_8064D86C;
extern float lbl_80651580;

extern void *fn_80201814(void *);
extern unsigned char fn_80202160(void *);

void fn_80200E1C(void)
{
    EventNode *node;
    void *found;
    float step;

    node = lbl_8064D86C->head;
    step = lbl_80651580;
    while (node != 0) {
        if (!(node->flags & 1)) {
            found = fn_80201814(node->object);
            if (found != 0) {
                if (fn_80202160(found) || node->kind == 0x4b) {
                    node->time += step;
                }
            }
        }
        node = node->next;
    }
}
