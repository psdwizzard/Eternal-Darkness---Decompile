typedef unsigned int u32;

typedef struct Allocator {
    void* (*alloc)(u32);
    void (*free)(void*);
} Allocator;

extern Allocator lbl_8064D4DC;

void fn_801CE358(void* allocation)
{
    lbl_8064D4DC.free(allocation);
}
