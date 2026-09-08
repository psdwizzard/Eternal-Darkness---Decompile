typedef struct Iterator { unsigned int capacity, count; int* values; } Iterator;
int fn_801E8E94(Iterator* iterator)
{
    if (iterator->count != 0)
        iterator->count--;
    return iterator->values[iterator->count];
}
