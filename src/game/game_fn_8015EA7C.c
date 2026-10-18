typedef struct Object {
    unsigned char pad0[8];
    void* value;
} Object;

extern void luaX_error(void*, void*, void*);

void luaK_error(Object* object, void* value)
{
    luaX_error(object, value, object->value);
}
