typedef struct List80205110 {
    void *head;
    void *tail;
    int count;
} List80205110;

typedef struct Object80205110 {
    unsigned char padding[0x30];
    List80205110 *list;
} Object80205110;

int fn_80205110(Object80205110 *object)
{
    if (object != 0 && object->list != 0) {
        return object->list->count;
    }

    return -1;
}
