typedef struct Object80201EB8 Object80201EB8;

struct Object80201EB8 {
    unsigned char padding[0x34];
    void* value;
};

extern int fn_8011FB4C(void* value);

int fn_80201EB8(Object80201EB8* object)
{
    if (object != 0 && object->value != 0) {
        return fn_8011FB4C(object->value);
    }
    return -1;
}
