typedef struct ObjectNode ObjectNode;

struct ObjectNode {
    char unknown[0x20];
    ObjectNode *previous;
    ObjectNode *next;
    int value;
};

extern ObjectNode *fn_8017CDB4(void *);
extern void fn_802007DC(void);
extern void fn_800073D8(void *);
extern ObjectNode *lbl_8064D86C;
extern int lbl_8064D868;
extern void *lbl_8064D87C;
extern void *lbl_8064D18C;

ObjectNode *fn_8020080C(void)
{
    ObjectNode *node = fn_8017CDB4(lbl_8064D87C);

    if (node != 0) {
        ObjectNode *next = lbl_8064D86C->next;
        node->previous = lbl_8064D86C;
        node->next = next;
        lbl_8064D86C->next = node;
        if (next != 0) {
            next->previous = node;
        }
        node->value = 0;
        lbl_8064D868++;
        return node;
    }

    fn_802007DC();
    fn_800073D8(lbl_8064D18C);
    fn_800073D8(lbl_8064D18C);
    return 0;
}
