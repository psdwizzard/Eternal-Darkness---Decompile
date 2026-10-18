typedef struct Root {
    char pad0[0x2C];
    int* values;
    int count;
} Root;

typedef struct Counter {
    char pad0[0x38];
    int count;
} Counter;

typedef struct Object {
    Root* root;
    char pad4[4];
    Counter* counter;
    int allocator;
    int value;
    char pad14[0x10];
    int previous_count;
} Object;

extern char lbl_8024F2C0[];
extern int* luaM_growaux(int, int*, int, int, int, void*, unsigned int);

void codelineinfo(Object* object)
{
    Root* root = object->root;
    Counter* counter = object->counter;

    if (counter->count > object->previous_count) {
        root->values = luaM_growaux(object->allocator, root->values,
                                  root->count, 2, 4, lbl_8024F2C0,
                                  0x7FFFFFFD);
        if (counter->count > object->previous_count + 1) {
            root->values[root->count++] =
                -(counter->count - (object->previous_count + 1));
        }
        root->values[root->count++] = object->value;
        object->previous_count = counter->count;
    }
}
