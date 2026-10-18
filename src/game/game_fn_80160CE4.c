typedef struct Args {
    void* entry;
    int amount;
} Args;

extern void luaD_call(void*, void*, int);

void f_call(void* object, Args* args)
{
    luaD_call(object, args->entry, args->amount);
}
