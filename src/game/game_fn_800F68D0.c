/* MSL alloc.c: free (__pool_free with deallocate_from_var_pools inlined). */

/* This file's view of the allocator records. The callees' own definitions of
 * struct Block / struct SubBlock / struct __mem_pool_obj differ from each other,
 * so they are only named here as incomplete types (compatible with any
 * completion) and this file uses its own local layouts. */
struct Block;
struct SubBlock;
struct __mem_pool_obj;

typedef struct MemSubBlock {
    unsigned long size_;
    struct MemBlock* bp_;
} MemSubBlock;

typedef struct MemBlock {
    struct MemBlock* prev_;
    struct MemBlock* next_;
    unsigned long max_size_;
    unsigned long size_;
    MemSubBlock start_;
} MemBlock;

typedef struct MemFixBlock {
    struct MemFixBlock* prev_;
    struct MemFixBlock* next_;
    unsigned long client_size_;
} MemFixBlock;

typedef struct MemFixStart {
    MemFixBlock* tail_;
    MemFixBlock* head_;
} MemFixStart;

typedef struct MemPool {
    MemBlock* start_;
    MemFixStart fix_start[6];
} MemPool;

extern MemPool lbl_8032C8B8;      /* protopool */
extern unsigned char lbl_8064CC48; /* initialized */

extern void* memset(void* dst, int value, unsigned long size);
extern void deallocate_from_fixed_pools(struct __mem_pool_obj* pool_obj, void* ptr, unsigned long size); /* deallocate_from_fixed_pools */
extern void Block_link(struct Block* bp, struct SubBlock* sb);                         /* Block_link */
extern void __sys_free(void* p);                                                       /* __sys_free */

static inline MemPool* get_malloc_pool(void)
{
    if (!lbl_8064CC48) {
        memset(&lbl_8032C8B8, 0, sizeof(MemPool));
        lbl_8064CC48 = 1;
    }
    return &lbl_8032C8B8;
}

static inline unsigned long __msize_inline(void* ptr)
{
    /* The header word just before ptr is either the owning fixed block or the
     * variable block with its low bit set; the word before that is the
     * variable sub-block size. */
    unsigned long header = ((unsigned long*)ptr)[-1];

    return !(header & 1) ? ((MemFixBlock*)header)->client_size_
                         : (((unsigned long*)ptr)[-2] & ~7) - sizeof(MemSubBlock);
}

static inline int Block_empty(MemBlock* bp)
{
    unsigned long sbsize = bp->start_.size_;
    return (sbsize & 2) == 0 && (sbsize & ~7) == (bp->size_ & ~7) - 0x18;
}

static inline MemBlock* unlink(MemPool* pool_obj, MemBlock* bp)
{
    MemBlock* result = bp->next_;
    if (result == bp) {
        result = 0;
    }
    if (pool_obj->start_ == bp) {
        pool_obj->start_ = result;
    }
    if (result != 0) {
        result->prev_ = bp->prev_;
        result->prev_->next_ = result;
    }
    bp->next_ = 0;
    bp->prev_ = 0;
    return result;
}

static inline void deallocate_from_var_pools(MemPool* pool_obj, void* ptr)
{
    MemSubBlock* sb = (MemSubBlock*)((char*)ptr - sizeof(MemSubBlock));
    MemBlock* bp = (MemBlock*)((unsigned long)sb->bp_ & ~1);

    Block_link((struct Block*)bp, (struct SubBlock*)sb);
    if (Block_empty(bp)) {
        unlink(pool_obj, bp);
        __sys_free(bp);
    }
}

void free(void* ptr)
{
    MemPool* pool_obj = get_malloc_pool();
    unsigned long size;

    if (ptr == 0) {
        return;
    }
    size = __msize_inline(ptr);
    if (size <= 0x44) {
        deallocate_from_fixed_pools((struct __mem_pool_obj*)pool_obj, ptr, size);
    } else {
        deallocate_from_var_pools(pool_obj, ptr);
    }
}
