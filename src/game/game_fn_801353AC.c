typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Range {
    u32 unused;
    u32 size;
    u32 start;
} Range;

typedef struct Object {
    char pad_0[0x3C];
    void* descriptor;
    char pad_40[0x120];
    struct EntryTable* entries;
} Object;

typedef struct Descriptor { char pad_0[8]; u16 count; } Descriptor;
typedef struct Entry { char pad_0[0x14]; u32 a; u32 b; char pad_1C[0x30]; } Entry;
typedef struct EntryTable { u32 unused; Entry entries[1]; } EntryTable;
typedef struct Runtime2 { void* value; } Runtime2;
typedef struct Runtime1 { char pad_0[4]; Runtime2* next; } Runtime1;
typedef struct Runtime { char pad_0[0xB8]; Runtime1* next; } Runtime;

#define FN_80128E30_RETURN Runtime*
#define FN_80128E30_PARAMETERS Object*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern u32 lbl_8064CFB4;

/* NonMatching: behavior- and size-exact range-overlap test at 98.983604%.
 * GC/1.3 rotates the entry address, endpoint values, and two boolean results
 * through r3/r4/r7/r8; retail uses r7/r4/r7 and r3/r4 without r8. */
int fn_801353AC(Object* object, Range* range, int unused)
{
    int i;

    if (object != 0 && range != 0 && fn_80128E30(object)->next->next->value != 0) {
        for (i = 0; i < ((Descriptor*)object->descriptor)->count; i++) {
            Entry* entry = &object->entries->entries[i];
            u32 a = entry->a;
            u32 b = entry->b;
            int b_inside = b >= range->start && b < range->start + range->size;
            int a_inside = a >= range->start && a < range->start + range->size;
            if (a_inside | b_inside) {
                lbl_8064CFB4 = 1;
                return 1;
            }
        }
        lbl_8064CFB4 = 0;
    }
    return 0;
}
