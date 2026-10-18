typedef struct Counts {
    int capacity;
    unsigned int used;
} Counts;

extern void luaS_resize(void*, Counts*, int);

void checktab(void* collection, Counts* counts)
{
    int capacity = counts->capacity;
    if (counts->used < capacity / 4 && capacity > 10)
        luaS_resize(collection, counts, capacity / 2);
}
