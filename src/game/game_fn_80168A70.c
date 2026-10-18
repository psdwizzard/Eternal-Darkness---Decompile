typedef struct Value {
    int type;
    int unused;
    union {
        double number;
        char* string;
    } data;
} Value;

extern char lbl_8064BBE0;
extern int sprintf(char*, const char*, ...);
extern char* luaS_new(void*, const char*);

int luaV_tostring(void* state, Value* value)
{
    char buffer[24];

    if (value->type != 2)
        return 1;
    sprintf(buffer, &lbl_8064BBE0, value->data.number);
    value->data.string = luaS_new(state, buffer);
    value->type = 3;
    return 0;
}
