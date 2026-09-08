typedef struct Iterator { unsigned int capacity, count; int* values; } Iterator;
int fn_801E8EEC(Iterator* iterator)
{
    return iterator->count == 0;
}
