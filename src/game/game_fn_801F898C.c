typedef struct Object {
    unsigned char pad0[0x44];
    int value;
} Object;

void fn_801F898C(Object* object, int value)
{
    object->value = value;
}
