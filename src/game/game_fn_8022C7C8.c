typedef struct ResourceEntry {
    struct ResourceEntry *previous;
    struct ResourceEntry *next;
    void (*destroy)(void *);
    char *text;
    void *resource;
    unsigned short references;
} ResourceEntry;

typedef struct ResourceList {
    unsigned long linkOffset;
    ResourceEntry *head;
    ResourceEntry *tail;
} ResourceList;

typedef struct ResourceCache {
    unsigned long unknown;
    ResourceList entries;
} ResourceCache;

extern signed char Strcmp(const char *left, const char *right);

static inline ResourceEntry *findResource(ResourceCache *cache, const char *path)
{
    ResourceEntry *entry = cache->entries.head;

    if (path != 0) {
        while (entry != 0) {
            if (Strcmp(path, entry->text) == 0) {
                return entry;
            }
            entry = entry->next;
        }
    }
    return 0;
}

/* Acquire a cached resource and count the new reference. */
void *DSGetCacheObj(ResourceCache *cache, const char *path)
{
    ResourceEntry *entry = findResource(cache, path);

    if (entry != 0) {
        ++entry->references;
        return entry->resource;
    }
    return 0;
}
