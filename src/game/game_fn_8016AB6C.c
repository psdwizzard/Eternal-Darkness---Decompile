typedef struct Value {
    double first;
    double second;
} Value;

typedef struct Entry {
    Value value;
    int next;
    int pad14;
} Entry;

typedef struct Context {
    Value* current;
    char pad04[0x4C];
    Entry* entries;
    int count;
    int free;
    char pad5C[4];
    int allocated_size;
} Context;

extern char lbl_8024FE8C[];
extern void* luaM_growaux(void*, void*, unsigned int, unsigned int,
                         unsigned int, char*, unsigned int);

int lua_ref(Context* context, int special)
{
    int index;

    if (((int*)&context->current[-1])[0] == 1) {
        index = -1;
    } else {
        if (context->free != -1) {
            index = context->free;
            context->free = context->entries[index].next;
        } else {
            context->entries = luaM_growaux(context, context->entries,
                                            context->count, 1, sizeof(Entry),
                                            lbl_8024FE8C, 0x7FFFFFFD);
            context->allocated_size += sizeof(Entry);
            index = context->count++;
        }
        context->entries[index].value = context->current[-1];
        context->entries[index].next = special ? -4 : -2;
    }
    context->current--;
    return index;
}
