typedef struct Iterator { unsigned int capacity, count; int* values; } Iterator;
int fn_801E8EBC(Iterator* iterator)
{
    if (iterator != 0) {
        int index = iterator->count - 1;
        if (index < 0)
            index = 0;
        return iterator->values[index];
    }
    return 0;
}
