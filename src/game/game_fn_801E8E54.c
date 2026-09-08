typedef struct Iterator { unsigned int capacity, count; int* values; } Iterator;
void fn_801E8E54(Iterator* iterator, unsigned int capacity, int* values)
{
    iterator->capacity = capacity;
    iterator->count = 0;
    iterator->values = values;
}
