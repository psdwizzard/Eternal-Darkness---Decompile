typedef struct LuaState {
    char pad0[0x60];
    int nblocks;
} LuaState;

typedef struct Value {
    int type;
    int pad4;
    char data[8];
} Value;

typedef struct HashNode {
    Value value;
    Value key;
    struct HashNode* next;
    char pad24[4];
} HashNode;

typedef struct HashTable {
    HashNode* nodes;
    int pad4;
    int size;
    HashNode* firstfree;
} HashTable;

#pragma use_lmw_stmw on

extern void* luaM_realloc(LuaState*, void*, unsigned int, const char*, int);
extern void lua_error(LuaState*, const char*);
extern const char lbl_8024FA74[];
extern const char lbl_8024FA84[];

void setnodevector(LuaState* state, HashTable* table, int size)
{
    int i;

    if ((unsigned int)size > 0x7FFFFFFD) {
        lua_error(state, lbl_8024FA74);
    }

    table->nodes = luaM_realloc(state, 0, size * sizeof(HashNode),
                               lbl_8024FA84, 166);
    for (i = 0; i < size; i++) {
        table->nodes[i].key.type = 1;
        table->nodes[i].value.type = 1;
        table->nodes[i].next = 0;
    }

    state->nblocks += (size - table->size) * sizeof(HashNode);
    table->size = size;
    table->firstfree = &table->nodes[size - 1];
}
