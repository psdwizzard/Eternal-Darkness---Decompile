typedef unsigned short u16;

typedef struct EntryKey {
    u16 kind;
    u16 priority;
} EntryKey;

typedef struct Entry {
    EntryKey key;
    u16 duration;
} Entry;

extern Entry lbl_805B40A0[5];
extern int lbl_8064D040;
extern const EntryKey lbl_80650460;
extern const u16 lbl_80650464;

void fn_801441C0(int kind, int priority, int duration)
{
    if (lbl_8064D040 == 0) {
        Entry sentinel;
        Entry *entry;
        Entry *lowest;
        int i;

        sentinel.key = lbl_80650460;
        sentinel.duration = lbl_80650464;
        entry = lbl_805B40A0;
        lowest = &sentinel;
        for (i = 0; i < 5; i++, entry++) {
            if (entry->duration == 0) {
                entry->key.kind = kind;
                entry->key.priority = priority;
                entry->duration = duration;
                return;
            }
            if (lowest->key.priority > entry->key.priority) {
                lowest = entry;
            } else if (lowest->key.priority == entry->key.priority &&
                       entry->key.kind < lowest->key.kind) {
                lowest = entry;
            }
        }
        if (lowest != &sentinel) {
            lowest->key.kind = kind;
            lowest->key.priority = priority;
            lowest->duration = duration;
        }
    }
}
