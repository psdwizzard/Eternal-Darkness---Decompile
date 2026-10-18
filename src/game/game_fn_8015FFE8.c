typedef struct Root { char pad0[0x18]; int* values; } Root;
typedef struct Chain { Root* root; } Chain;
typedef struct Inner { Chain* chain; int** current; } Inner;
typedef struct Object { char pad0[8]; Inner* inner; } Object;

int currentpc(Object* object)
{
    Inner* inner = object->inner;
    if (inner->current != 0)
        return *inner->current - inner->chain->root->values - 1;
    return -1;
}
