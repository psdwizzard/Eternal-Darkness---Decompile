typedef unsigned int u32;
typedef struct ListHead ListHead;
typedef struct ListNode ListNode;
typedef struct ListIterator { ListNode *node; } ListIterator;

extern void *fn_80201B9C(void *);
extern void *fn_80201BC8(void *);
extern float *fn_8011F130(void *);
extern int fn_80204844(void *, int);
extern int fn_8006D444(void);
extern int fn_8006D344(int, int, int);
extern ListHead *fn_80204A8C(void);
extern int fn_80204D98(void);
extern int fn_8011FB4C(void *);
extern unsigned short fn_8011F760(void *);
extern ListNode *fn_802051A4(ListNode *);
extern void *fn_80205134(void *);
extern void *fn_80201814(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201C24(void *);
extern u32 fn_80179064(int, int, int, int);
extern u32 fn_80157894(void *);
extern int fn_801E1E38(void);
extern int fn_8012FF34(void *, float *, int, int);
extern void fn_801302BC(void *, int);
extern float lbl_8064F4E4;
extern float lbl_8064F4E8;

int fn_800DC9A8(void *context)
{
    float *origin;
    void *owner;
    int result = 0;
    ListIterator item;
    int count;
    int kind;
    int i;
    int blocked;
    unsigned short height;
    float upper;

    /* NonMatching: behavior-complete reconstruction. A single-field iterator aggregate
     * tests whether scalar replacement preserves the list-head copy seen
     * in the retail code. GC/1.3 still coalesces the copy; register hints
     * also leave the instruction sequence unchanged. The u16 conversion
     * bias retains a TU-local relocation. Compiler flags remain canonical. */

    fn_80201B9C(context);
    blocked = 0;
    owner = fn_80201BC8(context);
    origin = fn_8011F130(owner);
    fn_80204844(fn_80201B9C(origin), 0x20);
    if (fn_8006D344(fn_8006D444(), 0x20200, 0))
        blocked = 1;
    if (!blocked) {
        ListHead *list = fn_80204A8C();
        count = fn_80204D98();
        kind = fn_8011FB4C(owner);
        height = fn_8011F760(owner);
        upper = lbl_8064F4E4 + height;
        for (item.node = (ListNode *)list, i = 0; i < count; i++) {
            float *position;
            void *candidate;
            void *candidate_owner;
            void *state;
            u32 flags;
            int allowed;
            u32 distance;

            item.node = fn_802051A4(item.node);
            candidate = fn_80201814(fn_80205134(item.node));
            if (*((unsigned char *)fn_80201B8C(candidate) + 0x9f) == 20)
                continue;
            candidate_owner = fn_80201BC8(candidate);
            if (fn_8011FB4C(candidate_owner) != kind)
                continue;
            state = fn_80201C24(candidate);
            position = fn_8011F130(candidate_owner);
            distance = fn_80179064((int)position[0], (int)position[1],
                                   (int)origin[0], (int)origin[1]);
            if (position[2] - origin[2] <= upper &&
                position[2] - origin[2] >= lbl_8064F4E8) {
                flags = fn_80157894(state);
                allowed = fn_801E1E38();
                if (!(flags & 8) && (!(flags & 0x10) || allowed) &&
                    distance <= 250 && fn_8012FF34(owner, position, 4, 2)) {
                    fn_801302BC(owner, 60);
                    result = 1;
                }
            }
        }
    }
    return result;
}
