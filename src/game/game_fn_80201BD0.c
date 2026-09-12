typedef struct Node80201BD0 Node80201BD0;

struct Node80201BD0 {
    Node80201BD0 *next;
    Node80201BD0 *link;
    unsigned char padding[0x2C];
    void *object;
};

extern Node80201BD0 *fn_802014AC(void);

Node80201BD0 *fn_80201BD0(void *object)
{
    Node80201BD0 *node = fn_802014AC()->link;

    while (node != 0) {
        if (node->object == object) {
            return node;
        }
        node = node->link;
    }

    return 0;
}
