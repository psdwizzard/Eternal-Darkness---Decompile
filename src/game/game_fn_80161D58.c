typedef struct Argument {
    double value[2];
} Argument;

typedef struct Entry {
    int type;
    char pad04[4];
    void* value;
    char pad0C[4];
    Argument argument;
} Entry;

typedef struct Bucket {
    char pad00[0x34];
    void* saved;
    char pad38[8];
} Bucket;

typedef struct Collection {
    Entry* current;
    char pad04[0x44];
    Bucket* buckets;
    char pad4C[0x20];
    void* source;
} Collection;

extern int luaT_tag(Argument*);
extern void luaD_checkstack(Collection*, int);
extern void luaD_call(Collection*, Entry*, int);

void callgcTM(Collection* collection, Argument* argument)
{
    void* saved = collection->buckets[luaT_tag(argument)].saved;

    if (saved != 0) {
        void* source = collection->source;
        collection->source = 0;
        luaD_checkstack(collection, 2);
        collection->current->value = saved;
        collection->current->type = 5;
        collection->current->argument = *argument;
        collection->current++;
        luaD_call(collection, collection->current - 1, 0);
        collection->source = source;
    }
}
