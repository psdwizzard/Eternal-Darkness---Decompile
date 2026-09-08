typedef unsigned short u16;
typedef int s32;

typedef struct Entry {
    void (*callback)(void*, void*);
    void* argument0;
    void* argument1;
    short delay;
    u16 flags;
} Entry;

extern Entry lbl_80637C10;
extern void fn_801E8534(Entry*);

void fn_801E83A8(void)
{
    register Entry* entry;
    s32 i;

    entry = &lbl_80637C10;
    for (i = 0; i < 350; i++, entry++) {
        if (entry->flags & 1) {
            if (entry->delay <= 1) {
                entry->callback(entry->argument0, entry->argument1);
                fn_801E8534(entry);
            } else {
                entry->delay--;
            }
        }
    }
}
