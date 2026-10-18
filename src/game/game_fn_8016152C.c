typedef struct Entry {
    int fields[4];
} Entry;

typedef struct Collection {
    Entry* end;
    Entry* begin;
} Collection;

extern void markobject(void*, Entry*);

void markstack(Collection* collection, void* context)
{
    Entry* entry;

    for (entry = collection->begin; entry < collection->end; entry++)
        markobject(context, entry);
}
