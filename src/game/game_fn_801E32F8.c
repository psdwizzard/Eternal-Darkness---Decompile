typedef unsigned char u8;

typedef struct Object {
    u8 pad0[0x10];
    u8* field10;
} Object;

void fn_801E32F8(Object* object)
{
    u8* field = object->field10;

    if (field != 0) {
        *field &= ~1;
    }
}
