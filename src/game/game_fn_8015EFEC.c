typedef struct Command {
    int type;
    int value;
    int field8;
} Command;

extern int discharge(void*, Command*);
extern void luaK_setcallreturns(void*, int);

void discharge1(void* object, Command* command)
{
    discharge(object, command);
    if (command->value == -1 && command->field8 == -1) {
        luaK_setcallreturns(object, 1);
    }
}
