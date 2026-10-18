typedef struct Object {
    char* current;
    char* allocation;
    char* end;
    int count;
} Object;

void restore_stack_limit(Object* object)
{
    if ((object->current - object->allocation) / 16 < object->count - 1)
        object->end = object->allocation + ((object->count - 1) << 4);
}
