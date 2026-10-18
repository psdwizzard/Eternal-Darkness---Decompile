typedef union Entry {
    struct {
        int type;
        char padding04[4];
        void* value;
        short count;
        char padding0E[2];
    } fields;
    double copy[2];
} Entry;

typedef struct Holder {
    void* value;
    char padding04[28];
} Holder;

typedef struct Closure {
    char padding00[12];
    short count;
} Closure;

typedef void (*Callback)(struct Object*, Entry*, void*);

typedef struct TableEntry {
    char padding00[56];
    Closure* saved;
    char padding3C[4];
} TableEntry;

typedef struct Object {
    Entry* current;
    char padding04[4];
    Entry* end;
    char padding0C[60];
    TableEntry* table;
    char padding4C[24];
    Callback source;
} Object;

extern char lbl_8064BA68;
extern char lbl_8064BA70;

extern int luaT_tag(Entry*);
extern void luaG_typeerror(Object*, Entry*, void*);
extern void luaD_openstack(Object*, Entry*);
extern void luaD_callHook(Object*, void*, Callback, void*);
extern Entry* callCclosure(Object*, Closure*, void*);
extern Entry* luaV_execute(Object*, Closure*, void*);
extern void luaD_checkstack(Object*, int);
extern void luaC_checkGC(Object*);

void luaD_call(Object* object, Entry* entry, int amount)
{
    Callback callback_source;
    Entry* first_result;
    Holder holder;
    Closure* closure;

    if (entry->fields.type != 5) {
        Closure* tag_method = object->table[luaT_tag(entry)].saved;
        if (tag_method == 0) {
            luaG_typeerror(object, entry, &lbl_8064BA68);
        }
        luaD_openstack(object, entry);
        entry->fields.value = tag_method;
        entry->fields.type = 5;
    }

    closure = entry->fields.value;
    holder.value = closure;
    entry->fields.value = &holder;
    entry->fields.type = 6;
    callback_source = object->source;
    if (callback_source != 0) {
        luaD_callHook(object, entry, callback_source, &lbl_8064BA68);
    }

    first_result = closure->count != 0 ? callCclosure(object, closure, entry + 1)
                                       : luaV_execute(object, closure, entry + 1);

    if (callback_source != 0) {
        luaD_callHook(object, entry, callback_source, &lbl_8064BA70);
    }

    if (amount == -1) {
        while (first_result < object->current) {
            *entry++ = *first_result++;
        }
        object->current = entry;
    } else {
        while (amount > 0 && first_result < object->current) {
            *entry++ = *first_result++;
            amount--;
        }
        object->current = entry;
        while (amount > 0) {
            object->current->fields.type = 1;
            if (object->current == object->end) {
                luaD_checkstack(object, 1);
            }
            object->current++;
            amount--;
        }
    }
    luaC_checkGC(object);
}
