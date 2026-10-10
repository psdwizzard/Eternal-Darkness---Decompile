typedef unsigned short u16;

typedef struct Entry Entry;

extern int fn_8011EB04(void *);
extern void *fn_801E86A0(void *, int);
extern Entry *fn_80138950(void *, u16);
extern void *lbl_8064C530;

Entry *fn_80042748(void *object, u16 id)
{
    int key = fn_8011EB04(object);
    void *table = fn_801E86A0(lbl_8064C530, key);

    if (table != 0) {
        return fn_80138950(table, id);
    }
    return 0;
}
