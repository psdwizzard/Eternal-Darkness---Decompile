typedef struct StringEntry {
    unsigned char unknown[8];
    void (*destroy)(void *);
    char *text;
    unsigned char data[8];
} StringEntry;

extern int __OSCurrHeap;
extern void OSFreeToHeap(int heap, void *ptr);

/* Destroy the entry's payload and release its text and storage. */
void FreeCacheNode(StringEntry **entry)
{
    if (*entry != 0) {
        if ((*entry)->destroy != 0) {
            (*entry)->destroy((*entry)->data);
        }
        OSFreeToHeap(__OSCurrHeap, (*entry)->text);
        OSFreeToHeap(__OSCurrHeap, *entry);
        *entry = 0;
    }
}
