typedef unsigned int u32;
typedef struct Table { u32 count; } Table;
u32 fn_801E88E4(Table* table)
{
    if (table != 0) return table->count;
    return 0;
}
