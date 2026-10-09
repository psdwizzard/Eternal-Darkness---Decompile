typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3Words {
    unsigned int x, y, z;
} Vec3Words;

typedef struct ListNode {
    struct ListNode* next;
    struct ListNode* previous;
} ListNode;

/* The allocator owns the complete Instance definition. */
typedef struct Instance Instance;

typedef struct InstanceState {
    u8 second;
    u8 pad[3];
    unsigned int zero_c;
    unsigned int zero_10;
} InstanceState;

typedef struct InstanceData {
    ListNode node;
    InstanceState state;
    u8 pad14[0x1C];
    u16 first;
    u16 third;
    u16 fourth;
    u16 fifth;
    u16 sixth;
    u8 pad3a[2];
    Vec3Words position;
    u8 pad48[0x12E0];
    u8 seventh;
} InstanceData;

extern void fn_8014EE88(void*);
extern Instance* fn_80149D98(void*);
extern void fn_80149D64(ListNode*);

u8* fn_8014EC30(Vec3Words* position, u16 first, u8 second, u16 third,
                 u16 fourth, u16 fifth, u16 sixth, u8 seventh)
{
    InstanceState* result;
    InstanceData* object;

    result = 0;
    object = (InstanceData*)fn_80149D98(fn_8014EE88);
    if (object != 0) {
        fn_80149D64(&object->node);
        object->seventh = seventh;
        result = &object->state;
        object->position = *position;
        object->first = first;
        object->state.second = second;
        object->third = third;
        object->fourth = fourth;
        object->fifth = fifth;
        object->sixth = sixth;
        result->zero_c = 0;
        result->zero_10 = 0;
    }
    return (u8*)result;
}
