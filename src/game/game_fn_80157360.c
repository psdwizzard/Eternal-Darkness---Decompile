typedef struct Object {
    struct Object* previous;
    struct Object* next;
    struct Object* child_previous;
    struct Object* child_next;
    char pad10[0x34];
    unsigned int flags;
} Object;

extern Object* fn_80155EF4(void);

unsigned int fn_80157360(unsigned int (*callback)(void*, Object*), Object* object,
                         void* context, unsigned int flags)
{
    Object* current;
    unsigned int result;
    unsigned int include_removed;
    unsigned int ignore_result;
    unsigned int descend;

    object = object != 0 ? object : fn_80155EF4();

    include_removed = flags & 2;
    ignore_result = flags & 4;
    descend = flags & 1;
    result = 0;

    if ((object->flags & 1) != 0) {
        if (descend != 0) {
            current = object->child_previous;
        } else {
            current = object->previous;
        }
    } else {
        current = object;
    }

    while (current != 0 && result == 0) {
        if ((current->flags & 2) == 0 || include_removed != 0) {
            result = callback(context, current);
            if (ignore_result != 0) {
                result = 0;
            }
        }
        if (descend != 0) {
            current = current->child_previous;
        } else {
            current = current->previous;
        }
    }
    return result;
}
