typedef struct ListNode80204C2C ListNode80204C2C;
typedef struct Object80204C2C Object80204C2C;

struct ListNode80204C2C {
    void *previous;
    void *next;
    unsigned int value;
};

struct Object80204C2C {
    unsigned char pad_00[0x30];
    ListNode80204C2C *node;
};

extern ListNode80204C2C *fn_80205210(void);

ListNode80204C2C *fn_80204C2C(Object80204C2C *object)
{
    if (object != 0 && object->node == 0) {
        object->node = fn_80205210();
        object->node->next = 0;
        object->node->previous = 0;
        object->node->value = 0;
        return object->node;
    }

    return 0;
}
