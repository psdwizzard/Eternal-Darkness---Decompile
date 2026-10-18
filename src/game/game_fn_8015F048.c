typedef struct Command {
    int type;
    int value;
} Command;

typedef struct Object {
    unsigned char pad0[0x28];
    void* field28;
} Object;

extern void luaK_code1(void*, int, int);
extern void luaK_code2(void*, int, int, int);

void luaK_storevar(Object* object, Command* command)
{
    void* child = object->field28;

    switch (command->type) {
    case 1:
        luaK_code1(child, 18, command->value);
        break;
    case 0:
        luaK_code1(child, 19, command->value);
        break;
    case 2:
        luaK_code2(child, 20, 3, 3);
        break;
    }
}
