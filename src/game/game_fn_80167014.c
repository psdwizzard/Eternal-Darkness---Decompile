typedef struct HashNode HashNode;

struct HashNode {
    int tag;
    void* key;
    unsigned int size;
    HashNode* next;
};

typedef struct TableState {
    int size;
    int nuse;
    HashNode** hash;
} TableState;

typedef struct LuaState {
    char pad0[0x38];
    TableState udt;
} LuaState;

extern HashNode* luaS_newudata(LuaState*, unsigned int, void*);

HashNode* luaS_createudata(LuaState* state, void* key, int tag)
{
    HashNode* node = state->udt.hash[((unsigned int)key >> 3) & (state->udt.size - 1)];

    while (node != 0) {
        if (key == node->key && (tag == node->tag || tag == -1)) {
            return node;
        }
        node = node->next;
    }

    node = luaS_newudata(state, 0, key);
    if (tag != -1) {
        node->tag = tag;
    }
    return node;
}
