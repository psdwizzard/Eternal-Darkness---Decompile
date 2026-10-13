/* MSL alloc.c: deallocate_from_fixed_pools (with deallocate_from_var_pools inlined). */

typedef struct SubBlock {
    unsigned long size_;
    struct Block* bp_;
} SubBlock;

typedef struct Block {
    struct Block* prev_;
    struct Block* next_;
    unsigned long max_size_;
    unsigned long size_;
    SubBlock start_;
} Block;

typedef struct FixSubBlock {
    struct FixBlock* block_;
    struct FixSubBlock* next_;
} FixSubBlock;

typedef struct FixBlock {
    struct FixBlock* prev_;
    struct FixBlock* next_;
    unsigned long client_size_;
    FixSubBlock* start_;
    unsigned long n_allocated_;
} FixBlock;

typedef struct FixStart {
    FixBlock* tail_;
    FixBlock* head_;
} FixStart;

typedef struct __mem_pool_obj {
    Block* start_;
    FixStart fix_start[6];
} __mem_pool_obj;

/* fix_pool_sizes */
extern const volatile unsigned int lbl_80239CE8[6];

extern void fn_800F6CBC(Block* bp, SubBlock* sb); /* Block_link */
extern void fn_800F66DC(void* p);                 /* __sys_free */

static inline int Block_empty(Block* bp)
{
    unsigned long sbsize = bp->start_.size_;
    return (sbsize & 2) == 0 && (sbsize & ~7) == (bp->size_ & ~7) - 0x18;
}

static inline Block* unlink(__mem_pool_obj* pool_obj, Block* bp)
{
    Block* result = bp->next_;
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

static inline void deallocate_from_var_pools(__mem_pool_obj* pool_obj, void* ptr)
{
    SubBlock* sb = (SubBlock*)((char*)ptr - sizeof(SubBlock));
    Block* bp = (Block*)((unsigned long)sb->bp_ & ~1);

    fn_800F6CBC(bp, sb);
    if (Block_empty(bp)) {
        unlink(pool_obj, bp);
        fn_800F66DC(bp);
    }
}

void fn_800F6A04(__mem_pool_obj* pool_obj, void* ptr, unsigned long size)
{
    unsigned long i = 0;
    FixSubBlock* p;
    FixBlock* b;
    FixStart* fs;

    while (size > lbl_80239CE8[i]) {
        ++i;
    }
    p = (FixSubBlock*)((char*)ptr - sizeof(FixBlock*));
    b = p->block_;
    fs = &pool_obj->fix_start[i];
    if (b->start_ == 0 && fs->head_ != b) {
        if (fs->tail_ == b) {
            fs->head_ = fs->head_->prev_;
            fs->tail_ = fs->tail_->prev_;
        } else {
            b->prev_->next_ = b->next_;
            b->next_->prev_ = b->prev_;
            b->next_ = fs->head_;
            b->prev_ = b->next_->prev_;
            b->prev_->next_ = b;
            b->next_->prev_ = b;
            fs->head_ = b;
        }
    }
    p->next_ = b->start_;
    b->start_ = p;
    if (--b->n_allocated_ == 0) {
        if (fs->head_ == b) {
            fs->head_ = b->next_;
        }
        if (fs->tail_ == b) {
            fs->tail_ = b->prev_;
        }
        b->prev_->next_ = b->next_;
        b->next_->prev_ = b->prev_;
        if (fs->head_ == b) {
            fs->head_ = 0;
        }
        if (fs->tail_ == b) {
            fs->tail_ = 0;
        }
        deallocate_from_var_pools(pool_obj, b);
    }
}
