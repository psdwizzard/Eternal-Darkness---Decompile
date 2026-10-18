typedef unsigned int u32;

typedef struct Allocator {
    void* (*alloc)(u32);
    void (*free)(void*);
} Allocator;

extern Allocator salHooks;

void* salMalloc(u32 size)
{
    return salHooks.alloc(size);
}
