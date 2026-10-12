typedef struct ItemEntry {
    void *model;
    char pad04[0x18];
    unsigned int flags;
} ItemEntry;

extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *node);
extern int fn_80201EB8(void *node);
extern void *fn_80201B94(void *node);
extern int fn_80201B4C(void *node);
/* The original caller supplies a value which this routine ignores. */
extern int fn_80201C58();
extern void *fn_80201BC8(void *node);
extern void *fn_8011F950(void *object);
extern int fn_8011EB04(void *object);
extern ItemEntry *fn_8002A444(int kind, int value);
extern void fn_8012B9C8(void *owner, void *value);
extern void fn_80126880(void *object);
extern void *fn_8011F938(void *object, void *value);
extern void fn_80139DD4(void *object);
extern void fn_8011FC38(void *object, int value, int flag);
extern void fn_8011F7E0(void *object, int value);

void fn_80046B68(void) {
    void *node;
    void *data;
    void *object;
    int mode;
    void *owner;
    ItemEntry *entry;

    for (node = fn_80201B9C(); node != 0; node = fn_80201BC0(node)) {
        fn_80201EB8(node);
        data = fn_80201B94(node);
        mode = fn_80201B4C(node);
        if ((mode == 2 || mode == 1) && (unsigned int)fn_80201C58(data) != 0) {
            object = fn_80201BC8(node);
            owner = fn_8011F950(object);
            if (owner != 0) {
                entry = fn_8002A444(fn_8011EB04(object), mode);
                if (entry != 0 && (entry->flags & 1)) {
                    entry->flags &= ~1U;
                    fn_8012B9C8(owner, (void *)1);
                }
                fn_80126880(object);
            }
            fn_8011F938(object, 0);
            fn_80139DD4(object);
            fn_8011FC38(object, -1, 0);
            fn_8011F7E0(object, 0);
        }
    }
}
