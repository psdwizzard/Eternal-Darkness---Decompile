typedef struct Object {
    unsigned char pad0[0x14];
    int current;
    int value;
} Object;

extern int luaK_code1(Object*, int, int);
extern void luaK_concat(Object*, int*, int);

int luaK_jump(Object* object)
{
    int result = luaK_code1(object, 42, -1);

    if (result == object->current) {
        luaK_concat(object, &result, object->value);
        object->value = -1;
    }
    return result;
}
