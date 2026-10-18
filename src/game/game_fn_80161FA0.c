typedef struct Collection {
    char pad00[0x5C];
    unsigned int threshold;
    unsigned int total_size;
} Collection;

extern void luaC_collectgarbage(Collection*);

void luaC_checkGC(Collection* collection)
{
    if (collection->total_size >= collection->threshold)
        luaC_collectgarbage(collection);
}
