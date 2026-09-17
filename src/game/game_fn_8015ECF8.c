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
extern void* fn_8016393C(void*, void*, int, unsigned int, int, void*, unsigned int);

int fn_8015ECF8(Object* object, double value)
{
    DoubleTable* table = object->table;
    int last_index = table->last_index;
    int index = last_index;
    int offset = last_index * 8;
    int first = (last_index - 20) & ~-(last_index < 20);

    for (; index >= first; index--, offset -= 8) {
        if (*(double*)((unsigned char*)table->values + offset) == value)
            return index;
    }

    table->values = fn_8016393C(object->allocator, table->values,
                                table->last_index, 1, 8,
                                lbl_8024F280, 0x3FFFFFF);
    index = table->last_index++;
    table->values[index] = value;
    return index;
}
