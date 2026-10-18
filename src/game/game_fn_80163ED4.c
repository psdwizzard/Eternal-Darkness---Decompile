extern void luaK_error(void*, char*);

void check_condition(void* lexer, int condition, char* message)
{
    if (condition == 0) {
        luaK_error(lexer, message);
    }
}
