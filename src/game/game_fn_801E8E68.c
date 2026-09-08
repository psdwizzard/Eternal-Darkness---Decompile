typedef struct Iterator { unsigned int capacity, count; int* values; } Iterator;
void fn_801E8E68(Iterator* iterator, int value)
{
    if (iterator->count != iterator->capacity) {
        iterator->values[iterator->count] = value;
        iterator->count++;
    }
}
