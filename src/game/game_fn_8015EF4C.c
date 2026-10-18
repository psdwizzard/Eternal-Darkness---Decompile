typedef struct Command {
    int type;
    int value;
    int field8;
} Command;

extern void luaK_code1(void*, int, int);
extern void luaK_code0(void*, int);

int discharge(void* object, Command* command)
{
    switch (command->type) {
    case 1:
        luaK_code1(object, 11, command->value);
        break;
    case 0:
        luaK_code1(object, 12, command->value);
        break;
    case 2:
        luaK_code0(object, 13);
        break;
    case 3:
        return 0;
    }

    command->type = 3;
    command->field8 = -1;
    command->value = -1;
    return 1;
}
