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
extern int lbl_8064D868;
extern void *lbl_8064D87C;
extern int lbl_8064D18C;
extern float lbl_80651580;

extern unsigned int fn_8015C910(void);
extern void *fn_80201814(void *);
extern unsigned char fn_80202160(void *);
extern void *fn_80201ADC(void);
extern int fn_80201BC8(void *);
extern int fn_80047178(void);
extern int fn_8012FA54(int, int);
extern int fn_80201EB8(void *);
extern float fn_80200BDC(void);
extern void fn_8020088C(EventNode *);
extern void fn_8017CE74(void *, EventNode *);

void fn_80200C74(void)
{
    int state;
    int value;
    void *found;
    EventNode *node;
    void *object;
    EventNode *next;

    node = lbl_8064D86C->head;
    while (node != 0) {
        if (!(node->flags & 1)) {
            if (fn_8015C910()) {
                found = fn_80201814(node->object);
                if (found != 0) {
                    if (fn_80202160(found) || node->kind == 0x4b) {
                        node->time += lbl_80651580;
                    }
                }
            } else if (node->kind == 0x4b) {
                value = 0;
                object = fn_80201ADC();
                if (object != 0) {
                    value = fn_80201BC8(object);
                }
                state = fn_80047178();
                value = fn_8012FA54(value, 0xf);
                {
                    int result = fn_80201EB8(object);
                    if (!state || !value || result != lbl_8064D18C) {
                        node->time += lbl_80651580;
                    }
                }
            }
            if (node->time <= fn_80200BDC()) {
                fn_8020088C(node);
                node->flags |= 1;
            }
        }
        node = node->next;
    }

    node = lbl_8064D86C->head;
    value = 0;
    while (node != 0) {
        next = node->next;
        if (node->flags & 1) {
            node->prev->next = node->next;
            if (node->next != 0) {
                node->next->prev = node->prev;
            }
            node->next = 0;
            node->prev = 0;
            --lbl_8064D868;
            fn_8017CE74(lbl_8064D87C, node);
        }
        node = next;
    }
}
