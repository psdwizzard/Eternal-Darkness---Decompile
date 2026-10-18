typedef struct TPLPalette TPLPalette;
typedef struct ResourceCache ResourceCache;
typedef struct ResourceEntry ResourceEntry;
typedef void (*ResourceDestructor)(void *);

extern unsigned char DOCacheInitialized;
extern ResourceCache DODisplayCache;
extern void TexFreeFunc(void *resource);
extern void LoadTexPalette(TPLPalette **palette, const char *path);
extern ResourceEntry *DSAddCacheNode(ResourceCache *cache, const char *path,
                               void *resource, ResourceDestructor destroy);
extern void *DSGetCacheObj(ResourceCache *cache, const char *path);

static inline void loadPalette(TPLPalette **palette, const char *path,
                               ResourceDestructor destroy)
{
    if (DOCacheInitialized) {
        *palette = DSGetCacheObj(&DODisplayCache, path);
    }
    if (*palette == 0) {
        LoadTexPalette(palette, path);
        if (DOCacheInitialized) {
            ResourceCache *cache = &DODisplayCache;
            DSAddCacheNode(cache, path, *palette, destroy);
            DSGetCacheObj(cache, path);
        }
    }
}

void TEXGetPalette(TPLPalette **palette, const char *path)
{
    ResourceDestructor destroy = TexFreeFunc;
    loadPalette(palette, path, destroy);
}
