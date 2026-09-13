typedef struct Object80204C94 Object80204C94;

struct Object80204C94 {
    unsigned char pad_00[0x30];
    void *node;
};

extern int fn_80205110(Object80204C94 *object);
extern void fn_80205234(void *node);

void fn_80204C94(Object80204C94 *object)
{
    if (object->node != 0 && fn_80205110(object) == 0) {
        fn_80205234(object->node);
        object->node = 0;
    }
}
