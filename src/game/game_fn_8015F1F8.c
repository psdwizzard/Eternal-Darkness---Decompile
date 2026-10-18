typedef struct Object {
    char pad0[0x14];
    int value;
    int result;
} Object;

extern void luaK_concat(Object*, int*, int);
extern void luaK_patchlistaux(Object*, int, int, int, int);

void luaK_patchlist(Object* object, int index, int value)
{
    if (value == object->value) {
        luaK_concat(object, &object->result, index);
    } else {
        luaK_patchlistaux(object, index, value, 0, 0);
    }
}
