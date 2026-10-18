/* MSL alloc.c: SubBlock_merge_next. */

typedef struct SubBlock {
    unsigned long size_;
    struct Block* bp_;
    struct SubBlock* prev_;
    struct SubBlock* next_;
} SubBlock;

void SubBlock_merge_next(SubBlock* ths, SubBlock** start)
{
    unsigned long size = ths->size_ & ~7;
    SubBlock* next = (SubBlock*)((char*)ths + size);
    unsigned long new_size;

    if (next->size_ & 2) {
        return;
    }
    new_size = size + (next->size_ & ~7);
    ths->size_ &= 7UL;
    ths->size_ |= new_size & ~7;
    if (!(ths->size_ & 2)) {
        *(unsigned long*)((char*)ths + new_size - sizeof(unsigned long)) = new_size;
    }
    if (!(ths->size_ & 2)) {
        *(unsigned long*)((char*)ths + new_size) &= ~4;
    } else {
        *(unsigned long*)((char*)ths + new_size) |= 4;
    }
    if (*start == next) {
        *start = (*start)->next_;
    }
    if (*start == next) {
        *start = 0;
    }
    next->next_->prev_ = next->prev_;
    next->prev_->next_ = next->next_;
}
