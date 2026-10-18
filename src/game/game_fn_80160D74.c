typedef struct Args {
    void* value;
    int flag;
} Args;

extern void* luaU_undump(void*, void*);
extern void* luaY_parser(void*, void*);
extern void luaV_Lclosure(void*, void*, int);

void f_parser(void* object, Args* args)
{
    void* value;

    if (args->flag != 0) {
        value = luaU_undump(object, args->value);
    } else {
        value = luaY_parser(object, args->value);
    }
    luaV_Lclosure(object, value, 0);
}
