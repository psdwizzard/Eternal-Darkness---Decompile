typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EntryKey {
    u16 kind;
    u16 priority;
} EntryKey;

typedef struct Entry {
    EntryKey key;
    u16 duration;
} Entry;

extern Entry lbl_805B40A0[5];
extern u32 lbl_8064D044;
extern void fn_8021959C(int, int);

void fn_8014426C(void)
{
    Entry sentinel = {{0, 0}, 0};
    Entry *entry;
    Entry *highest;
    int i;

    entry = lbl_805B40A0;
    highest = &sentinel;
    for (i = 0; i < 5; i++, entry++) {
        if (entry->duration != 0) {
            if (entry->key.kind > highest->key.kind) {
                highest = entry;
            }
            entry->duration--;
        }
    }
    lbl_8064D044++;
    if (highest != &sentinel) {
        if (lbl_8064D044 % (highest->key.kind + highest->key.priority) < highest->key.kind) {
            fn_8021959C(0, 1);
        } else {
            fn_8021959C(0, 0);
        }
    } else {
        fn_8021959C(0, 0);
    }
}
