typedef struct ListLink {
    void *previous;
    void *next;
} ListLink;

typedef struct IntrusiveList {
    unsigned int linkOffset;
    void *first;
    void *last;
} IntrusiveList;

/* Insert an entry before the given object; null appends to the list. */
void fn_8022C8BC(IntrusiveList *list, void *before, void *entry)
{
    void *first = list->first;
    unsigned int offset = list->linkOffset;
    ListLink *link = (ListLink *)((unsigned char *)entry + offset);
    ListLink *following;
    ListLink *previous;

    if (first != 0) {
        if (before == 0) {
            ((ListLink *)((unsigned char *)list->last + offset))->next = entry;
            link->previous = list->last;
            link->next = 0;
            list->last = entry;
            return;
        }
        following = (ListLink *)((unsigned char *)before + offset);
        if (before == first) {
            list->first = entry;
            link->next = before;
            following->previous = entry;
            return;
        }
        previous = (ListLink *)((unsigned char *)following->previous + offset);
        link->next = before;
        link->previous = following->previous;
        following->previous = entry;
        previous->next = entry;
        return;
    }
    list->last = entry;
    list->first = entry;
    link->previous = 0;
    link->next = 0;
}
