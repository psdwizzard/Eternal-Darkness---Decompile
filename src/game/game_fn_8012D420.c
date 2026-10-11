typedef unsigned char u8;
typedef unsigned short u16;

typedef struct EntrySlot {
    u16 flags;
    u16 delay;
    u16 repeat_delay;
    u16 initial_delay;
} EntrySlot;

typedef struct Entry {
    int id;
    void* record;
    unsigned int state_flags;
    EntrySlot slots[4];
} Entry;

typedef int (*UpdateCallback)(Entry*);
typedef void (*StateCallback)(Entry*);

void fn_8012D420(Entry* entry, int index, UpdateCallback update,
                 StateCallback finish, StateCallback restart, StateCallback reset)
{
    if (entry->slots[index].delay != 0) {
        entry->slots[index].delay--;
        return;
    }
    if (entry->slots[index].flags & 0x10) {
        if (entry->slots[index].flags & 2) {
            finish(entry);
            entry->slots[index].flags &= ~1;
            return;
        }
        if (entry->slots[index].flags & 0x20) {
            entry->slots[index].flags &= ~0x10;
            reset(entry);
            update(entry);
            return;
        }
        if (entry->slots[index].flags & 0x10C) {
            restart(entry);
            entry->slots[index].flags &= ~0x10;
            if (entry->slots[index].flags & 4) {
                entry->slots[index].flags &= ~4;
                entry->slots[index].flags |= 2;
                return;
            }
            if (entry->slots[index].flags & 0x100) {
                entry->slots[index].flags &= ~0x100;
            }
        } else {
            entry->slots[index].flags &= ~1;
        }
    } else if (update(entry)) {
        entry->slots[index].flags |= 0x10;
        if (entry->slots[index].initial_delay != 0) {
            entry->slots[index].delay = entry->slots[index].initial_delay;
            entry->slots[index].initial_delay = 0;
            return;
        }
        if (entry->slots[index].repeat_delay != 0) {
            entry->slots[index].delay = entry->slots[index].repeat_delay;
        }
    } else {
        if (entry->slots[index].repeat_delay != 0) {
            entry->slots[index].delay = entry->slots[index].repeat_delay;
        }
    }
}
