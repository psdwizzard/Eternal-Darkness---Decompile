typedef void (*ResourceDestructor)(void *);

typedef struct ResourceEntry {
    struct ResourceEntry *previous;
    struct ResourceEntry *next;
    ResourceDestructor destroy;
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

extern int AllocCacheNode(ResourceEntry **entry, const char *text);
extern void Strcpy(char *destination, const char *source);
extern void DSInsertListObject(ResourceList *list, ResourceEntry *before,
                      ResourceEntry *entry);

ResourceEntry *DSAddCacheNode(ResourceCache *cache, const char *path,
                         void *resource, ResourceDestructor destroy)
{
    ResourceEntry *entry = 0;

    if ((unsigned char)AllocCacheNode(&entry, path) == 0) {
        return 0;
    }
    Strcpy(entry->text, path);
    entry->resource = resource;
    entry->destroy = destroy;
    entry->references = 0;
    DSInsertListObject(&cache->entries, 0, entry);
    return entry;
}
