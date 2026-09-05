typedef unsigned int u32;

typedef struct Allocator {
    void* (*alloc)(u32);
    void (*free)(void*);
} Allocator;

extern Allocator lbl_8064D4DC;

void* fn_801CE330(u32 size)
{
    return lbl_8064D4DC.alloc(size);
}
