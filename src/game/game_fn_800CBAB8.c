/* Set up the selected actor, its effects, and the interaction with its source. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry Entry;
typedef struct Node Node;
typedef struct Object Object;
typedef struct Actor Actor;
typedef struct Owner Owner;

extern Owner *fn_80047D6C(void);
extern void fn_80047DF8(Actor *, void *, int);
extern void fn_80047F5C(Actor *, void *, int);
extern void fn_8007C17C(Owner *);
extern u8 fn_800CC2D8(Actor *, int);
extern void fn_800DC3A0(void *, int, int, u8, int, u16);
extern int fn_8011EB04(Actor *);
extern int fn_8011EB1C(Actor *);
extern int fn_8011F130(Actor *);
extern void fn_8011F7E0(Actor *, int);
extern void fn_8011FA8C(Actor *, int, int);
extern int fn_8011FB4C(Actor *);
extern void fn_8011FB54(Actor *, int);
extern void fn_8011FE3C(Actor *, Actor *);
extern void fn_801261F4(Actor *);
extern void fn_8012C478(Actor *, int, int);
extern void fn_8012C62C(Actor *, int, u32 *, u32 *, u32 *, int);
extern void fn_8012F58C(Actor *, int, int, int, int, int);
extern Node *fn_80155DB4(u32);
extern void fn_801568D8(Node *);
extern void fn_801568E4(Node *);
extern void fn_801568F0(Node *);
extern void fn_80156904(Node *, void *);
extern void fn_80156F80(Node *, Node *);
extern int fn_80157918(Object *);
extern void *fn_80157924(Object *);
extern u8 fn_80157AB8(Object *);
extern u32 fn_80157C80(Object *);
extern void fn_80157C88(Object *, u32);
extern int fn_8015878C(int *);
extern void fn_8017FE14(void *, void *);
extern void fn_8017FE1C(void *, void *);
extern u16 fn_8017FEA4(void *);
extern u16 fn_8017FEFC(void *);
extern int fn_8017FF14(void *, u16);
extern int fn_80199120(void *);
extern int fn_801E1ED4(int);
extern void *fn_801E2004(int);
extern void fn_801E7974(void *, int);
extern int fn_801E79FC(void *, int);
extern void fn_801E8328(int, void *);
extern int fn_801E855C(int, void *, int);
extern void fn_8020123C(int, int, int, int);
extern Entry *fn_80201814(int);
extern int fn_80201B44(void);
extern void fn_80201B8C(Entry *);
extern Actor *fn_80201BC8(Entry *);
extern Object *fn_80201C24(Entry *);
extern void fn_802020B4(Entry *, int);
extern void fn_80205680(Entry *, int, int);
extern void fn_8002A754(void);
extern void fn_8018ABD4(void);
extern void fn_80199B84(void);
extern u32 lbl_80303CA0[];
extern u32 lbl_80303D18[];
extern void *lbl_8064C4E0;
extern Node *lbl_8064C554;
extern u32 lbl_8064F2E8;
extern u32 lbl_8064F2EC;
extern u32 lbl_8064F2F0;
extern u32 lbl_8064F2F4;
extern u32 lbl_80651A88;
extern u32 lbl_80651A8C;

void fn_800CBAB8(int *source, int id)
{
    u32 firstC, firstB, firstA;
    u32 secondC, secondB, secondA;
    int active;
    Node *node;
    Object *object;
    Entry *entry;
    Actor *actor;
    Node *sourceNode;
    Actor *sourceActor;
    int sourceId;
    Entry *sourceEntry;
    u32 flags;
    int effectValue;
    u16 delta;
    void *effect;
    u16 endValue;

    entry = fn_80201814(id);
    node = fn_80155DB4((u32)entry);
    object = fn_80201C24(entry);
    actor = fn_80201BC8(entry);
    sourceId = fn_8015878C(source);
    sourceEntry = fn_80201814(sourceId);
    sourceNode = fn_80155DB4((u32)sourceEntry);
    sourceActor = fn_80201BC8(sourceEntry);
    fn_802020B4(entry, 1);
    if (node == 0) {
        node = lbl_8064C554;
    }
    fn_8011FA8C(actor, 0x10000, 0);
    fn_8011F7E0(actor, 0);
    fn_8011FB54(actor, fn_8011FB4C(sourceActor));
    fn_801261F4(actor);
    fn_8012C478(actor, 15, 1);
    if (fn_801E1ED4(fn_80201B44()) != 0 && (int)fn_801E2004(fn_80201B44()) == 4) {
        firstA = lbl_8064F2F0;
        firstB = lbl_8064F2EC;
        firstC = lbl_8064F2E8;
        fn_8012C62C(actor, 15, &firstC, &firstB, &firstA, 6);
        fn_8012F58C(actor, 15, 0, 1, 30, 8);
    } else {
        secondA = lbl_80651A8C;
        secondB = lbl_80651A88;
        secondC = lbl_8064F2F4;
        fn_8012C62C(actor, 15, &secondC, &secondB, &secondA, 0);
    }
    fn_80201B8C(entry);
    if (fn_800CC2D8(actor, 0)) {
        fn_8012C478(actor, 16, 0);
    }
    if (fn_800CC2D8(actor, 1)) {
        fn_8012C478(actor, 17, 0);
    }
    flags = fn_80157C80(object);
    if (fn_8011EB04(actor) != 0xF1) {
        fn_80157C88(object, flags | 2);
    }
    fn_801568F0(node);
    fn_801568E4(node);
    fn_801568D8(node);
    fn_80156904(node, (void *)fn_8002A754);
    fn_80156F80(node, sourceNode);
    fn_8011FE3C(actor, sourceActor);
    active = fn_80157AB8(object);
    if (fn_8011EB04(actor) == 0x63 && fn_8011EB1C(actor) == 4) {
        if (fn_801E79FC(lbl_8064C4E0, 0x29B)) {
            fn_801E7974(lbl_8064C4E0, 0x29A);
        } else {
            fn_80047DF8(actor, lbl_80303D18, 0);
        }
    } else if (fn_8011EB04(actor) == 0xF1 && fn_8011EB1C(actor) == 4) {
        if (fn_801E79FC(lbl_8064C4E0, 0x29B)) {
            fn_801E7974(lbl_8064C4E0, 0x48);
        } else {
            fn_80047F5C(actor, lbl_80303CA0, 0);
        }
    } else if (active) {
        effectValue = fn_8011F130(actor);
        effect = fn_80157924(object);
        if (effect != 0 && lbl_80303D18[0] != 0) {
            fn_8007C17C(fn_80047D6C());
        }
        if (effect != 0 && lbl_80303D18[0] == 0) {
            if (fn_80199120(effect)) {
                delta = 0;
            } else {
                endValue = fn_8017FEFC(effect);
                delta = endValue - fn_8017FEA4(effect);
            }
            if (delta == 0) {
                fn_8017FF14(effect, delta);
            }
            fn_800DC3A0(lbl_80303D18, id, effectValue, active, fn_80157918(object), delta);
            if (fn_801E79FC(lbl_8064C4E0, 0x29B)) {
                fn_801E7974(lbl_8064C4E0, 0x299);
            } else if (fn_801E855C(20, lbl_80303D18, 0) == 0) {
                fn_801E8328(20, lbl_80303D18);
            }
        }
    }
    if (active) {
        effect = fn_80157924(object);
        if (effect != 0) {
            fn_8017FE1C(effect, (void *)fn_8018ABD4);
            fn_8017FE14(effect, (void *)fn_80199B84);
        }
    }
    fn_80205680(entry, sourceId, 0x5B);
    fn_8020123C(0x3C, id, sourceId, 0);
}
