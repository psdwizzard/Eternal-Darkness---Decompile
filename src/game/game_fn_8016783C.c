typedef struct LuaState {
    char pad0[0x60];
    int nblocks;
} LuaState;

typedef struct HashTable {
    void* nodes;
    int pad4;
    int size;
} HashTable;

extern void* luaM_realloc(LuaState*, void*, unsigned int, const char*, int);
extern const char lbl_8024FA84[];

void luaH_free(LuaState* state, HashTable* table)
{
    state->nblocks -= table->size * 40 + 24;
    luaM_realloc(state, table->nodes, 0, lbl_8024FA84, 193);
    luaM_realloc(state, table, 0, lbl_8024FA84, 194);
}
