typedef struct Collection {
    char pad00[0x18];
    void* allocation;
    unsigned int capacity;
    char pad20[0x40];
    int total_size;
} Collection;

extern char lbl_8064BA88;
extern void* luaM_realloc(Collection*, void*, unsigned int, char*, int);

void checkMbuffer(Collection* collection)
{
    unsigned int capacity = collection->capacity;

    if (capacity > 512) {
        unsigned int new_capacity = capacity >> 1;
        collection->total_size += new_capacity - capacity;
        collection->capacity = new_capacity;
        collection->allocation = luaM_realloc(collection, collection->allocation,
                                             new_capacity, &lbl_8064BA88, 291);
    }
}
