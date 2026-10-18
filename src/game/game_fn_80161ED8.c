extern void collectudata(void*, int);
extern void callgcTMudata(void*);
extern void collectstrings(void*, int);
extern void collecttable(void*);
extern void collectproto(void*);
extern void collectclosure(void*);

void luaC_collect(void* collection, int preserve)
{
    collectudata(collection, preserve);
    callgcTMudata(collection);
    collectstrings(collection, preserve);
    collecttable(collection);
    collectproto(collection);
    collectclosure(collection);
}
