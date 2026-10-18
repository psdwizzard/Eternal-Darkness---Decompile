typedef struct LuaState LuaState;
typedef struct StringNode StringNode;

extern unsigned int strlen(const char*);
extern StringNode* luaS_newlstr(LuaState*, const char*, unsigned int);

StringNode* luaS_new(LuaState* state, const char* string)
{
    return luaS_newlstr(state, string, strlen(string));
}
