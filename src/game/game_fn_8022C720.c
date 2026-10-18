typedef struct StringEntry {
    unsigned char unknown[8];
    void (*destroy)(void *);
    char *text;
    unsigned char data[8];
} StringEntry;

extern int __OSCurrHeap;
extern void *OSAllocFromHeap(int heap, unsigned long size);
extern void FreeCacheNode(StringEntry **entry);
extern unsigned long Strlen(const char *text);

/* Allocate an entry and enough space for its null-terminated text. */
int AllocCacheNode(StringEntry **entry, const char *text) {
    if (*entry != 0) {
        FreeCacheNode(entry);
    }

    *entry = OSAllocFromHeap(__OSCurrHeap, sizeof(StringEntry));
    if (*entry == 0) {
        return 0;
    }

    (*entry)->text = OSAllocFromHeap(__OSCurrHeap, Strlen(text) + 1);
    if ((*entry)->text == 0) {
        return 0;
    }
    return 1;
}
