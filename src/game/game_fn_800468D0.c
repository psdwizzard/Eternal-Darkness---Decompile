typedef struct ItemEntry {
    void *model;
    char pad04[0x18];
    unsigned int flags;
} ItemEntry;

extern int fn_80201B4C(void *);
extern void *fn_80201B94(void *);
extern unsigned int fn_80201C58(void);
extern void *fn_80201BC8(void *);
extern int fn_8011FB4C(void *);
extern int fn_8011EB04(void *);
extern void *fn_80155DB4(void *);
extern void fn_801568C0(void *, int);
extern void fn_801568B8(void *, int);
extern void fn_8011F938(void *, void *);
extern void fn_80139DD4(void *);
extern void fn_8011F7E0(void *, int);
extern void fn_8011FC38(void *, int, int);
extern unsigned int fn_8011F950(void *);
extern ItemEntry *fn_8002A444(int, int);
extern void fn_8012B954(void *);
extern unsigned int fn_8011FB6C(void *);
extern void fn_8011FBC4(void *, int);
extern void fn_80139D88(void *, ItemEntry *);
extern int fn_8011FCEC(void *);
extern void fn_801261F4(void *);
extern int fn_8015E4E8(void);
extern void fn_8011EBFC(void *);
extern int fn_8012A100(void *, int);
extern void fn_8011EAB4(void *, int);
extern void *fn_801294DC(void *, int, int, int);

void fn_800468D0(void *actor, char *state) {
    int mode;
    short slot;
    void *obj;
    int cur;
    int id;
    ItemEntry *entry;
    void *sub;

    if (actor == 0) {
        return;
    }
    mode = fn_80201B4C(actor);
    if (fn_80201B94(actor) == 0) {
        return;
    }
    if (mode != 2) {
        if (mode != 1) {
            return;
        }
        if (fn_80201C58() == 0) {
            return;
        }
    }

    slot = *(short *)(state + 0x8140);
    obj = fn_80201BC8(actor);
    cur = fn_8011FB4C(obj);
    id = fn_8011EB04(obj);
    if (cur != slot) {
        if (id == -1) {
            sub = fn_80155DB4(actor);
            fn_801568C0(sub, 0);
            fn_801568B8(sub, 0);
            fn_8011F938(obj, 0);
            fn_80139DD4(obj);
            fn_8011F7E0(obj, 0);
            fn_8011FC38(obj, -1, 1);
        }
        return;
    }

    if (fn_8011F950(obj) != 0) {
        return;
    }
    entry = fn_8002A444(id, mode);
    if (entry == 0) {
        return;
    }
    sub = entry->model;
    if (!(entry->flags & 1)) {
        entry->flags |= 1;
        fn_8012B954(sub);
    }
    fn_8011F938(obj, sub);
    if (fn_8011FB6C(obj) == 0) {
        fn_8011FBC4(obj, *(int *)(state + 0x11C));
    }
    fn_80139D88(obj, entry);
    fn_8011FC38(obj, 0, 1);
    fn_8011F7E0(obj, 0);
    if (fn_8011FCEC(obj) != -1) {
        fn_801261F4(obj);
        if (fn_8015E4E8() == 0) {
            fn_8011EBFC(obj);
        }
    } else if (fn_8012A100(obj, 0xF) != 0) {
        fn_8011EAB4(obj, 0xF);
        if (fn_8015E4E8() == 0) {
            fn_801294DC(obj, 0xF, 0x21, 1);
        }
    } else if (fn_8012A100(obj, 0x1B) != 0) {
        fn_8011EAB4(obj, 0x1B);
        if (fn_8015E4E8() == 0) {
            fn_801294DC(obj, 0x1B, 0x21, 1);
        }
    }
}
