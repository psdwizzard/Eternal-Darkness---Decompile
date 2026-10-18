typedef struct Entry {
    int type;
    char pad4[12];
} Entry;

extern char* const luaO_typenames[6];
extern char lbl_8024F554[];
extern char lbl_8024F578[];
extern void luaO_verror(void*, const char*, ...);

void luaG_ordererror(void* object, Entry* entry)
{
    int current_type = entry[-1].type;
    int previous_type = entry[-2].type;
    char* previous_descriptor = luaO_typenames[previous_type];
    char* current_descriptor = luaO_typenames[current_type];

    if ((signed char)previous_descriptor[2] == (signed char)current_descriptor[2])
        luaO_verror(object, lbl_8024F554, previous_descriptor, current_descriptor);
    else
        luaO_verror(object, lbl_8024F578, previous_descriptor, current_descriptor);
}
