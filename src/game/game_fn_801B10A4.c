typedef unsigned int u32;

typedef void (*Callback)(u32);

typedef struct CallbackEntry {
    u32 pad000[3];
    u32 mask;
    u32 pad010;
    Callback callback;
} CallbackEntry;

void __DTKCheckUserCallback(CallbackEntry* entry, u32 mask)
{
    u32 active;

    if (entry != 0 && entry->callback != 0) {
        active = entry->mask & mask;
        if (active != 0) {
            entry->callback(active);
        }
    }
}
