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

extern int fn_80167D2C(Entry*);
extern void fn_801603AC(Object*, Entry*, void*);
extern void fn_80160748(Object*, Entry*);
extern void fn_8016088C(Object*, void*, Callback, void*);
extern Entry* fn_801608D0(Object*, Closure*, void*);
extern Entry* fn_801697AC(Object*, Closure*, void*);
extern void fn_8016057C(Object*, int);
extern void fn_80161FA0(Object*);

void fn_80160B18(Object* object, Entry* entry, int amount)
{
    Callback callback_source;
    Entry* first_result;
    Holder holder;
    Closure* closure;

    if (entry->fields.type != 5) {
        Closure* tag_method = object->table[fn_80167D2C(entry)].saved;
        if (tag_method == 0) {
            fn_801603AC(object, entry, &lbl_8064BA68);
        }
        fn_80160748(object, entry);
        entry->fields.value = tag_method;
        entry->fields.type = 5;
    }

    closure = entry->fields.value;
    holder.value = closure;
    entry->fields.value = &holder;
    entry->fields.type = 6;
    callback_source = object->source;
    if (callback_source != 0) {
        fn_8016088C(object, entry, callback_source, &lbl_8064BA68);
    }

    first_result = closure->count != 0 ? fn_801608D0(object, closure, entry + 1)
                                       : fn_801697AC(object, closure, entry + 1);

    if (callback_source != 0) {
        fn_8016088C(object, entry, callback_source, &lbl_8064BA70);
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
                fn_8016057C(object, 1);
            }
            object->current++;
            amount--;
        }
    }
    fn_80161FA0(object);
}
