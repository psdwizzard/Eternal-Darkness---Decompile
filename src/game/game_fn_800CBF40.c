typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Owner { void *effect; } Owner;
typedef struct Entry Entry;
typedef struct Node Node;
typedef struct Object Object;
typedef struct Actor Actor;

extern u8 *fn_80047D6C(void);
extern void *fn_80047D84(void);
extern void fn_80047FFC(int enabled);
extern void fn_8007C13C(Owner *owner);
extern void fn_8007C17C(Owner *owner);
extern void fn_8007C1D8(Owner *owner);
extern int fn_8011EB04(Actor *actor);
extern int fn_8011EB1C(Actor *actor);
extern void *fn_8011FE3C(void *object, void *value);
extern Node *fn_80155DB4(u32 id);
extern void fn_801568B8(Node *node, void *value);
extern void fn_801568C0(Node *node, void *value);
extern void fn_801568FC(Node *node, void *value);
extern void fn_80156904(Node *node, void *value);
extern void fn_801570F8(Node *first, Node *second);
extern u32 fn_80157924(Object *object);
extern u8 fn_80157AB8(Object *object);
extern u32 fn_80157C80(Object *object);
extern u32 fn_80157C88(Object *object, u32 flags);
extern int fn_8015878C(int *value);
extern void fn_8017FE14(void *object, void *value);
extern void fn_8017FE1C(void *object, void *value);
extern int fn_8018E8E4(u8 *object);
extern void *fn_801D1C2C(void);
extern void fn_801E79A0(u8 *bits, u32 index);
extern u64 fn_8020123C(int kind, int first, int second, int arg3);
extern Entry *fn_80201814(int id);
extern void *fn_80201BC8(void *entry);
extern void *fn_80201C24(Entry *entry);
extern void fn_802020B4(Entry *entry, int enabled);
extern u8 *lbl_8064C4E0;

void fn_800CBF40(int *source, int id)
{
    int active;
    Entry *entry = fn_80201814(id);
    Node *node = fn_80155DB4((u32)entry);
    Object *object = fn_80201C24(entry);
    Actor *actor = fn_80201BC8(entry);
    int sourceId = fn_8015878C(source);
    Node *sourceNode = fn_80155DB4((u32)fn_80201814(sourceId));

    fn_802020B4(entry, 0);
    active = 0;
    if (id != (int)fn_801D1C2C() && fn_80157AB8(object) != 0) {
        active = 1;
    }

    if (fn_8011EB04(actor) == 0x63 && fn_8011EB1C(actor) == 4) {
        Owner *owner = (Owner *)fn_80047D6C();
        fn_80047FFC(0);
        fn_8007C13C(owner);
        fn_801E79A0(lbl_8064C4E0, 0x29A);
    } else if (fn_8011EB04(actor) == 0xF1 && fn_8011EB1C(actor) == 4) {
        fn_8007C1D8(fn_80047D84());
        fn_801E79A0(lbl_8064C4E0, 0x48);
    } else if (active) {
        Owner *owner = (Owner *)fn_80047D6C();
        fn_801E79A0(lbl_8064C4E0, 0x299);
        fn_8007C17C(owner);
    }

    if (active) {
        void *effect = (void *)fn_80157924(object);
        if (effect != 0) {
            fn_8017FE1C(effect, 0);
            fn_8017FE14(effect, (void *)fn_8018E8E4);
        }
    }

    {
        u32 flags = fn_80157C80(object);
        fn_80157C88(object, flags & ~2U);
    }
    fn_801568C0(node, 0);
    fn_801568B8(node, 0);
    fn_80156904(node, 0);
    fn_801568FC(node, 0);
    fn_801570F8(node, sourceNode);
    fn_8011FE3C(actor, 0);
    fn_8020123C(0x3C, id, sourceId, 0);
}
