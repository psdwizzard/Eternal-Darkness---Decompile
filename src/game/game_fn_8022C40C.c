typedef struct TPLPalette TPLPalette;
typedef struct ResourceCache ResourceCache;
typedef struct ResourceEntry ResourceEntry;
typedef void (*ResourceDestructor)(void *);

extern unsigned char lbl_8064DBD0;
extern ResourceCache lbl_80642BC0;
extern void fn_8022C668(void *resource);
extern void fn_8022C4C0(TPLPalette **palette, const char *path);
extern ResourceEntry *fn_8022C690(ResourceCache *cache, const char *path,
                               void *resource, ResourceDestructor destroy);
extern void *fn_8022C7C8(ResourceCache *cache, const char *path);

static inline void loadPalette(TPLPalette **palette, const char *path,
                               ResourceDestructor destroy)
{
    if (lbl_8064DBD0) {
        *palette = fn_8022C7C8(&lbl_80642BC0, path);
    }
    if (*palette == 0) {
        fn_8022C4C0(palette, path);
        if (lbl_8064DBD0) {
            ResourceCache *cache = &lbl_80642BC0;
            fn_8022C690(cache, path, *palette, destroy);
            fn_8022C7C8(cache, path);
        }
    }
}

void fn_8022C40C(TPLPalette **palette, const char *path)
{
    ResourceDestructor destroy = fn_8022C668;
    loadPalette(palette, path, destroy);
}
