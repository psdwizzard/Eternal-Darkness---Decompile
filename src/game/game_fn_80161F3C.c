typedef struct Collection {
    char pad00[0x5C];
    int threshold;
    int total_size;
} Collection;

extern const volatile unsigned int luaO_nilobject[4];
extern void markall(Collection*);
extern void invalidaterefs(Collection*);
extern void luaC_collect(Collection*, int);
extern void checkMbuffer(Collection*);
extern void callgcTM(Collection*, char*);

void luaC_collectgarbage(Collection* collection)
{
    markall(collection);
    invalidaterefs(collection);
    luaC_collect(collection, 0);
    checkMbuffer(collection);
    collection->threshold = collection->total_size << 1;
    callgcTM(collection, (char*)luaO_nilobject);
}
