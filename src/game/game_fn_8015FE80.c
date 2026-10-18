typedef struct Node2 { char pad0[0xC]; short value; } Node2;
typedef struct Node1 { Node2* node; } Node1;
typedef struct Object { int type; char pad4[4]; Node1* child; } Object;

int isLmark(Object* object)
{
    int result = 0;
    if (object != 0 && object->type == 6 && object->child->node->value == 0)
        result = 1;
    return result;
}
