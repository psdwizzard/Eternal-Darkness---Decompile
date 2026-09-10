typedef struct Object {
    unsigned char pad00[0x34];
    void* value;
} Object;

void* fn_801F99B8(Object* object)
{
    return object->value;
}
