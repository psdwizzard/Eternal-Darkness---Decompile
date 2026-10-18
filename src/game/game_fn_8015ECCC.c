typedef struct Object {
    unsigned char pad0[0x28];
    void* value;
} Object;

extern int luaK_code1(void*, int, int);

int luaK_kstr(Object* object, int value)
{
    return luaK_code1(object->value, 7, value);
}
