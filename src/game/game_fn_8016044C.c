typedef struct Entry {
    int type;
    char pad4[12];
} Entry;

extern void luaG_typeerror(void*, Entry*, char*);

void luaG_binerror(void* object, Entry* entry, int type, char* text)
{
    if (entry->type == type)
        entry++;
    luaG_typeerror(object, entry, text);
}
