typedef unsigned char u8;
typedef unsigned short u16;

typedef struct List {
    u8 pad[6];
    u16 count;
    u16* values;
} List;

typedef struct Entry {
    u8 pad[4];
    List* list;
} Entry;

typedef struct Flag {
    u16 bits;
    u8 pad[6];
} Flag;

typedef struct Object {
    u8 pad[0x180];
    Flag flags[24];
    Entry** entries;
} Object;

extern void fn_80125ECC(void *);

/* NonMatching: retail keeps offset/value in r3/r4 and forms object + scaled
 * value before the 0x180 displacement; GC/1.3 uses r4/r3 and indexed access. */
void fn_8012FB50(Object* object, int index)
{
    Entry* entry;
    int offset;
    int i;
    u16 value;

    fn_80125ECC(object);
    entry = object->entries[index];
    if (entry != 0) {
        List* list = entry->list;
        for (i = 0, offset = 0; i < list->count; i++, offset += 2) {
            value = *(u16*)((u8*)list->values + offset);
            if (!(value & 0x8000)) {
                object->flags[value].bits |= 2;
            }
        }
    } else if (index == -1) {
        return;
    }
}
