typedef struct PathNode {
    const short *position;
    struct PathNode *neighbors[8];
    struct PathNode *parent;
    float cost;
    float estimate;
    float total;
    unsigned char flags;
    unsigned char neighbor_count;
    unsigned char pad[2];
} PathNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    PathNode *entry;
    unsigned char flags;
    unsigned char pad[3];
} ListNode;

typedef struct FreeEntry {
    unsigned char pad[12];
    unsigned char flags;
    unsigned char tail[3];
} FreeEntry;
extern FreeEntry *fn_800BD5F4(void);
extern void fn_800BD628(unsigned char *entry);
extern void fn_800BD638(ListNode *node);
extern ListNode *fn_800BD6F0(void);
extern void *fn_800BD748(void);
extern ListNode *fn_800BD750(unsigned char *entry);
extern int fn_800BD7F0(unsigned char *entry);
extern int fn_800BD7FC(unsigned char *entry);
extern void fn_800BD808(unsigned char *entry);
extern void fn_800BD818(unsigned char *entry);
extern void fn_800BD828(void);
extern float fn_800BD590(const short **first, const short **second);
extern void *memset(void *dest, int value, unsigned int size);
extern PathNode *lbl_80320C60[100];
extern const float lbl_8064F0E0;

int fn_800BD3C8(PathNode *start, PathNode *goal)
{
    ListNode *list;
    ListNode *popped;
    ListNode *new_list;
    PathNode *current;
    int i;
    PathNode *path;
    PathNode *neighbor;
    PathNode *parent;
    PathNode **output;
    float cost;

    fn_800BD828();
    list = (ListNode *)fn_800BD5F4();
    start->parent = 0;
    start->cost = lbl_8064F0E0;
    start->total = fn_800BD590(&start->position, &goal->position);
    list->entry = start;
    fn_800BD638(list);
    while (fn_800BD748() != 0) {
        popped = fn_800BD6F0();
        current = popped->entry;
        fn_800BD628((unsigned char *)popped);
        if (current->position == goal->position) {
            path = current;
            memset(lbl_80320C60, 0, 0x190);
            output = lbl_80320C60;
            *output = current;
            while ((parent = path->parent) != 0) {
                *++output = parent;
                path = parent;
            }
            fn_800BD828();
            return 1;
        }
        for (i = 0; i < current->neighbor_count; i++) {
            neighbor = current->neighbors[i];
            cost = current->cost + fn_800BD590(&current->position, &neighbor->position);
            if ((fn_800BD7F0((unsigned char *)neighbor) || fn_800BD7FC((unsigned char *)neighbor)) && neighbor->cost <= cost) {
                continue;
            }
            neighbor->parent = current;
            neighbor->cost = cost;
            neighbor->estimate = fn_800BD590(&neighbor->position, &goal->position);
            neighbor->total = neighbor->cost + neighbor->estimate;
            if (fn_800BD7F0((unsigned char *)neighbor)) {
                fn_800BD808((unsigned char *)neighbor);
            }
            if (fn_800BD7FC((unsigned char *)neighbor)) {
                fn_800BD638(fn_800BD750((unsigned char *)neighbor));
            } else {
                new_list = (ListNode *)fn_800BD5F4();
                new_list->entry = neighbor;
                fn_800BD638(new_list);
            }
        }
        fn_800BD818((unsigned char *)current);
    }
    fn_800BD828();
    return 0;
}
