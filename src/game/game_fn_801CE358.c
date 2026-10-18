typedef unsigned int u32;

typedef struct Allocator {
    void* (*alloc)(u32);
    void (*free)(void*);
} Allocator;

extern Allocator salHooks;

void salFree(void* allocation)
{
    salHooks.free(allocation);
}
