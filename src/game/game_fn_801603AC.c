typedef struct Entry {
    int type;
} Entry;

extern char* getobjname(void*, Entry*, char**);
extern void luaO_verror(void*, const char*, ...);
extern void* luaO_typenames[];
extern char lbl_8024F504[];
extern char lbl_8024F534[];

void luaG_typeerror(void* object, Entry* entry, char* text)
{
    char* value;
    char* kind = getobjname(object, entry, &value);
    void* descriptor = luaO_typenames[entry->type];

    if (kind != 0) {
        luaO_verror(object, lbl_8024F504, text, kind, value, descriptor);
    } else {
        luaO_verror(object, lbl_8024F534, text, descriptor);
    }
}
