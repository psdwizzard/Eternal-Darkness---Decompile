
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct Entry
{
    s16 id;
    u16 value2;
    u16 value4;
    u16 value6;
} Entry;
extern Entry lbl_805FAA60[10];
extern u8 lbl_80300368[];
extern int lbl_8064D18C;
extern void *fn_80201B3C();
extern int fn_80201EB8();
extern void fn_8016AFB0(s16);
extern void fn_8016ADF0(s16, s16, s16);
extern void *memcpy(void *, const void *, unsigned long);
extern void fn_8011E98C(void *);
extern void fn_8011E800(int);
#pragma use_lmw_stmw on
void fn_800CFA3C(void *state, Entry *entries, void *stream)
{
    Entry *global;
    int i;
    Entry *entry;
    int special = 0;
    void *object;
    object = fn_80201B3C(state);
    if ((object != 0) && (fn_80201EB8(object) != lbl_8064D18C)) {
        special = 1;
    }
    global = lbl_805FAA60;
    entry = global;
    i = 0;
    while (i < 10) {
        if ((entry->value6 == 0) && ((entry->value4 == 0) || (special != 0))) {
            fn_8016AFB0(entry->id);
        }
        i++;
        entry++;
    }

    i = 0;
    entry = entries;
    while (i < 10) {
        int j;
        Entry *g = global;
        int found = 0;
        for (j = 0; j < 10; j++, g++) {
            if (g->id == entry->id) {
                found = 1;
                break;
            }
        }

        if (!found) {
            fn_8016ADF0(entry->id, (s16) entry->value2, (s16) entry->value4);
        }
        i++;
        entry++;
    }

    memcpy(lbl_80300368, state, 0x44);
    fn_8011E98C(stream);
    fn_8011E800(0);
}
