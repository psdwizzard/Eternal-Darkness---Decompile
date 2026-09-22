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

typedef struct EntryPair {
    EntryA* first;
    void* second;
} EntryPair;

typedef struct ResourceTable {
    void* base;
    u32 count;
    EntryPair* entries;
} ResourceTable;

extern EntryPair* fn_8015DB74(ResourceTable*, u32);
extern void fn_80228474(void*, void*, u16, u16, u32, u32, u32, int);
extern void fn_80228730(void*, u32, u32, float, float, float, int, u8, int);

void fn_8015DB84(ResourceTable* table, void* context, u32 index)
{
    EntryPair* pair = fn_8015DB74(table, index);
    EntryA* entry = pair->first;
    long long different;

    if (entry->field21 == ((volatile EntryA*)entry)->field22) {
        different = 0;
    } else {
        different = 1;
    }
    fn_80228474(context, entry->data, entry->field2, entry->field0,
                entry->field4, entry->fieldC, entry->field10, different);
    entry = pair->first;
    fn_80228730(context, entry->field14, entry->field18,
                (float)entry->field21, (float)entry->field22, entry->field1C,
                0, entry->field20, 0);
}
