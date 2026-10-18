typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EntryA {
    u16 field0;
    u16 field2;
    u32 field4;
    void* data;
    u32 fieldC;
    u32 field10;
    u32 field14;
    u32 field18;
    float field1C;
    u8 field20;
    u8 field21;
    u8 field22;
    u8 fixed;
} EntryA;

typedef struct EntryB {
    u16 field0;
    u16 pad2;
    u32 field4;
    void* field8;
} EntryB;

typedef struct EntryPair {
    EntryA* first;
    EntryB* second;
} EntryPair;

typedef struct ResourceTable {
    void* base;
    u32 count;
    EntryPair* entries;
} ResourceTable;

extern EntryPair* fn_8015DB74(ResourceTable*, u32);
extern void GXInitTlutObj(void*, void*, u32, u16);
extern void GXInitTexObjCI(void*, void*, u16, u16, u32, u32, u32, int, u32);
extern void GXInitTexObjLOD(void*, u32, u32, float, float, float, int, u8, int);

void fn_8015DC54(ResourceTable* table, register void* first_context,
                 register void* second_context, register u32 final_argument,
                 u32 index)
{
    EntryPair* pair;
    enum { SAME, DIFFERENT } different;
    EntryA* entry;

    pair = fn_8015DB74(table, index);
    if (pair->first->field21 == pair->first->field22) {
        different = 0;
    } else {
        different = 1;
    }

    GXInitTlutObj(second_context, pair->second->field8,
                pair->second->field4, pair->second->field0);
    entry = pair->first;
    GXInitTexObjCI(first_context, entry->data, entry->field2, entry->field0,
                entry->field4, entry->fieldC, entry->field10, different,
                final_argument);

    GXInitTexObjLOD(first_context, pair->first->field14, pair->first->field18,
                (float)pair->first->field21, (float)pair->first->field22,
                pair->first->field1C, 0, pair->first->field20, 0);
}
