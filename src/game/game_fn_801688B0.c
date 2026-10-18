#pragma use_lmw_stmw on

extern int LoadHeader(void*, void*);
extern void* LoadFunction(void*, void*, int);

void* LoadChunk(void* object, void* input)
{
    return LoadFunction(object, input, LoadHeader(object, input));
}
