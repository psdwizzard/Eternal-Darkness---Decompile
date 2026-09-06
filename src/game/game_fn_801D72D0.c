typedef unsigned char u8;

typedef struct EntryData {
    u8 flags;
    u8 pad01[0xF];
    int owner;
} EntryData;

typedef struct Entry {
    u8 pad00[0x2C];
    EntryData* data;
} Entry;

extern void* fn_80201B9C(void);
extern int fn_80201B5C(void*);
extern Entry* fn_80201B8C(void*);
extern int fn_80201B54(void*);
extern void* fn_80201BC0(void*);
extern void fn_801D7380(int);
extern void fn_8020123C(int, int, int, int);

void fn_801D72D0(int owner)
{
    void* iterator;
    int id;

    iterator = fn_80201B9C();
    while (iterator != 0) {
        if (fn_80201B5C(iterator) == 25) {
            EntryData* data = fn_80201B8C(iterator)->data;
            if (data->owner == owner && (data->flags & 4) != 0) {
                id = fn_80201B54(iterator);
                fn_801D7380(id);
                fn_8020123C(57, id, id, 1);
            }
        }
        iterator = fn_80201BC0(iterator);
    }
}
