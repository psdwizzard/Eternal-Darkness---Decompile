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
extern char lbl_8063D378[];
extern char lbl_8063D400[];
extern char lbl_8024EDA0[];
extern int lbl_8064B9C0;
extern short lbl_8064B9C4;
extern void* lbl_8064CE88;
extern void* lbl_8064CE8C;
extern int (*lbl_8064CE90)(void);
extern void* lbl_8064CE98;
extern unsigned int lbl_80650060;
extern unsigned int lbl_80650064;

extern void* memset(void*, int, unsigned long);
extern int fn_801F743C(void*);
extern int fn_801A5CE0(void);
extern int fn_801A5D04(void);
extern void fn_8011DD8C(int, int);
extern void fn_8011DF6C(void);
extern void fn_8011DFA8(void);
extern void* fn_801E5D08(void*);
extern int fn_801A8B40(const unsigned char*, const unsigned char*, unsigned char*, short*);
extern void fn_801E6228(void*, const char*, ...);

void fn_8011E534(void)
{
    int allowed;
    Entry* entry;
    int i;
    int found;
    unsigned char* value;
    unsigned int upper;
    unsigned int lower;

    allowed = 0;
    if (fn_801F743C(lbl_8063D378) != 0 && fn_801F743C(lbl_8063D400) != 0) {
        allowed = 1;
    }

    entry = lbl_80332428;
    memset(&lbl_803324D0, 0, sizeof(Entry));
    lbl_803324D0.resource = -1;

    if ((lbl_8064CE90 == 0 || lbl_8064CE90() != 0) && lbl_8064CE88 == 0) {
        i = 0;
        found = 0;
        for (; i < 6 && found == 0; i++, entry++) {
            switch (i) {
            case 1:
            case 3:
            case 5:
                if (fn_801A5CE0() == 0 && fn_801A5D04() == 0) {
                    continue;
                }
                break;
            }
            if (!(entry->flags & 1) || allowed != 0) {
                if (entry->state == 0 && entry->resource != -1) {
                    found = 1;
                    lbl_803324D0 = *entry;
                }
            }
        }
    } else {
        if (!(entry->flags & 1) || allowed != 0) {
            if (entry->state == 0 && entry->resource != -1) {
                lbl_803324D0 = *entry;
            }
        }
    }

    fn_8011DD8C(0, 0);
    fn_8011DD8C(1, 0);
    fn_8011DD8C(3, 0);
    fn_8011DD8C(5, 0);

    if (lbl_8064CE8C != 0) {
        lbl_803324D0.resource = -1;
    }
    if (lbl_803324D0.resource != lbl_8064B9C0) {
        fn_8011DF6C();
        lbl_8064B9C0 = lbl_803324D0.resource;
        fn_8011DFA8();
    }

    if (lbl_8064CE98 != 0 && (lbl_803324D0.flags & 2)) {
        value = fn_801E5D08(lbl_8064CE98);
        lower = lbl_80650064;
        upper = lbl_80650060;
        fn_801A8B40((unsigned char*)&upper, (unsigned char*)&lower, value, &lbl_8064B9C4);
        fn_801E6228(lbl_8064CE98, lbl_8024EDA0, 0xF0, 0xF0, 0x122 - value[1], 0xFF);
    }
}
