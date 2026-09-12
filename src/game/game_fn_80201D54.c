typedef struct Object80201D54 Object80201D54;

struct Object80201D54 {
    unsigned char padding[0x34];
    void* value;
};

extern void fn_8011FB54(void* object, void* value);

void fn_80201D54(Object80201D54* object, void* value)
{
    if (object != 0 && object->value != 0) {
        fn_8011FB54(object->value, value);
    }
}
