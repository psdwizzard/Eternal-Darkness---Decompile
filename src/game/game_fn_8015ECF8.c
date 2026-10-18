typedef struct DoubleTable {
    double* values;
    int last_index;
} DoubleTable;

typedef struct Object {
    DoubleTable* table;
    unsigned char pad4[8];
    void* allocator;
} Object;

extern char lbl_8024F280[];
extern void* luaM_growaux(void*, void*, int, unsigned int, int, void*, unsigned int);

int number_constant(Object* object, double value)
{
    DoubleTable* table = object->table;
    int last_index = table->last_index;
    int first = last_index < 20 ? 0 : last_index - 20;
    int offset = last_index * 8;
    int index = last_index;

    while (--index, offset -= 8, index >= first) {
        if (*(double*)((unsigned char*)table->values + offset) == value)
            return index;
    }

    table->values = luaM_growaux(object->allocator, table->values,
                                table->last_index, 1, 8,
                                lbl_8024F280, 0x3FFFFFF);
    index = table->last_index++;
    table->values[index] = value;
    return index;
}
