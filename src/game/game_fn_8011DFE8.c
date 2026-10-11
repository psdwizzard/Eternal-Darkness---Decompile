typedef signed short s16;

typedef struct ResourceSet {
    char pad_0[0x3A];
    s16 ids[4];
    char pad_42[0x2A];
    s16 mode;
} ResourceSet;

typedef struct Entry {
    int value;
    void* object;
    int resource;
    void* callback;
    int state;
    int index;
    unsigned short flags;
    unsigned short pad;
} Entry;

extern Entry lbl_80332428[];
extern Entry lbl_803324D0;
extern int (*lbl_8064CE9C)(void*, int);
extern void fn_8016AFB0(s16);
extern void fn_8011DD8C(int, int);
extern void fn_8011E26C(int);

void fn_8011DFE8(ResourceSet* set)
{
    s16 first = 0;
    s16 second = 0;
    s16 third = 0;
    int id;

    switch (set->mode) {
    case 2:
        break;
    case 0:
        first = set->ids[0];
        second = set->ids[1];
        third = set->ids[2];
        break;
    case 1:
        first = set->ids[1];
        second = set->ids[2];
        third = set->ids[3];
        break;
    }

    fn_8016AFB0(first);
    fn_8016AFB0(third);
    fn_8016AFB0(second);
    id = lbl_8064CE9C(lbl_80332428[2].callback, 2);
    if (id != 0 && (id == first || id == third || id == second)) {
        fn_8011DD8C(2, 1);
        fn_8011DD8C(4, 1);
        if (lbl_803324D0.index == 2 || lbl_803324D0.index == 4) {
            fn_8011E26C(1);
        }
    } else {
        id = lbl_8064CE9C(lbl_80332428[4].callback, 4);
        if (id != 0 && (id == first || id == third || id == second)) {
            fn_8011DD8C(4, 1);
            if (lbl_803324D0.index == 4) {
                fn_8011E26C(1);
            }
        }
    }
}
