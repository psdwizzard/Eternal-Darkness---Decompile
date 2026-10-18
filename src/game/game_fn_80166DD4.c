typedef struct HashNode HashNode;

struct HashNode {
    unsigned int hash;
    void* value;
    void* key;
    HashNode* next;
};

typedef struct TableState {
    int size;
    int nuse;
    HashNode** hash;
} TableState;

typedef struct LuaState LuaState;

extern void luaS_resize(LuaState*, TableState*, int);

void newentry(LuaState* state, TableState* table, HashNode* node, unsigned int bucket)
{
    node->next = table->hash[bucket];
    table->hash[bucket] = node;
    table->nuse++;
    if ((unsigned int)table->nuse > (unsigned int)table->size && table->size < 0x3FFFFFFE) {
        luaS_resize(state, table, table->size * 2);
    }
}
