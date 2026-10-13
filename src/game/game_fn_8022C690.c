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

extern int fn_8022C720(ResourceEntry **entry, const char *text);
extern void fn_8022C950(char *destination, const char *source);
extern void fn_8022C8BC(ResourceList *list, ResourceEntry *before,
                      ResourceEntry *entry);

ResourceEntry *fn_8022C690(ResourceCache *cache, const char *path,
                         void *resource, ResourceDestructor destroy)
{
    ResourceEntry *entry = 0;

    if ((unsigned char)fn_8022C720(&entry, path) == 0) {
        return 0;
    }
    fn_8022C950(entry->text, path);
    entry->resource = resource;
    entry->destroy = destroy;
    entry->references = 0;
    fn_8022C8BC(&cache->entries, 0, entry);
    return entry;
}
