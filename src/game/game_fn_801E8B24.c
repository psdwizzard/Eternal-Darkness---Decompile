typedef struct Object {
    int words[8];
    void (*callback)(struct Object*);
} Object;
void fn_801E8B24(Object* object, int value, int other)
{
    int old = object->words[3];
    object->words[3] = value;
    object->words[4] = other;
    if (object->callback != 0 && old != object->words[3]) object->callback(object);
}
