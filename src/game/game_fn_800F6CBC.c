/* MSL alloc.c: Block_link (SubBlock_merge_prev inlined). */

typedef struct SubBlock {
    unsigned long size_;
    struct Block* bp_;
    struct SubBlock* prev_;
    struct SubBlock* next_;
} SubBlock;

typedef struct Block {
    struct Block* prev_;
    struct Block* next_;
    unsigned long max_size_;
    unsigned long size_;
} Block;

extern void fn_800F6C00(SubBlock* ths, SubBlock** start); /* SubBlock_merge_next */

#define SubBlock_size(ths) ((ths)->size_ & ~7)
#define Block_size(ths) ((ths)->size_ & ~7)
#define Block_start(ths) (*(SubBlock**)((char*)(ths) + Block_size((ths)) - sizeof(unsigned long)))

#define SubBlock_set_free(ths)                                                   \
    {                                                                            \
        unsigned long this_size = SubBlock_size((ths));                          \
        (ths)->size_ &= ~0x02;                                                   \
        *(unsigned long*)((char*)(ths) + this_size) &= ~0x04;                    \
        *(unsigned long*)((char*)(ths) + this_size - sizeof(unsigned long)) = this_size; \
    }

static inline SubBlock* SubBlock_merge_prev(SubBlock* ths, SubBlock** start)
{
    unsigned long prevsz;
    SubBlock* p;

    if (!(ths->size_ & 0x04)) {
        prevsz = *(unsigned long*)((char*)ths - sizeof(unsigned long));
        if (prevsz & 0x02) {
            return ths;
        }
        p = (SubBlock*)((char*)ths - prevsz);
        p->size_ &= 0x07UL;
        p->size_ |= (prevsz + SubBlock_size(ths)) & ~7;
        if (!(p->size_ & 0x02)) {
            unsigned long sz = prevsz + SubBlock_size(ths);
            *(unsigned long*)((char*)p + sz - sizeof(unsigned long)) = sz;
        }
        if (*start == ths) {
            *start = (*start)->next_;
        }
        ths->next_->prev_ = ths->prev_;
        ths->next_->prev_->next_ = ths->next_;
        return p;
    }
    return ths;
}

void fn_800F6CBC(Block* ths, SubBlock* sb)
{
    SubBlock** st;

    SubBlock_set_free(sb);
    st = &Block_start(ths);
    if (*st != 0) {
        sb->prev_ = (*st)->prev_;
        sb->prev_->next_ = sb;
        sb->next_ = *st;
        (*st)->prev_ = sb;
        *st = sb;
        *st = SubBlock_merge_prev(*st, st);
        fn_800F6C00(*st, st);
    } else {
        *st = sb;
        sb->prev_ = sb;
        sb->next_ = sb;
    }
    if (ths->max_size_ < SubBlock_size(*st)) {
        ths->max_size_ = SubBlock_size(*st);
    }
}
