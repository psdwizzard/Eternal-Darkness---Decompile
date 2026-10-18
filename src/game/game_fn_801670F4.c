typedef struct LuaState LuaState;

typedef struct StringNode {
    int hash;
    int marked;
    int length;
    void* next;
    int type;
} StringNode;

extern StringNode* luaS_new(LuaState*, const char*);

StringNode* luaS_newfixed(LuaState* state, const char* string)
{
    StringNode* node = luaS_new(state, string);

    if (node->type == 0) {
        node->type = 2;
    }
    return node;
}
