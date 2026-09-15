typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void*, void*);

typedef struct Entry {
    u8 pad00[0xA8];
    Callback callback;
    void* callback_arg;
    u8 padB0[8];
    int* current_value;
    u8 padBC[0x3E];
    u16 kind;
    u16 flags;
} Entry;

int fn_80129C2C(void* owner, Entry* entry, int value, int flags, int kind)
{
    int reject;
    unsigned short old_kind;
    int result = 0;
    if ((entry->flags & 4) != 0) {
        int same = *entry->current_value == value;
        old_kind = entry->kind;
        reject = (unsigned short)kind > old_kind ||
            (same && (flags & 0x10) != 0) ||
            ((unsigned short)kind == old_kind && !same && (flags & 0x20) != 0);
        if (reject) {
            Callback callback = entry->callback;
            if (callback != 0) {
                entry->callback = 0;
                callback(owner, entry->callback_arg);
            }
            result = 1;
        }
    } else {
        result = 1;
    }
    return result;
}
