typedef struct LuaState LuaState;
typedef struct HashTable HashTable;

struct LuaState {
    char pad0[0x28];
    HashTable* tables;
    char pad2C[0x34];
    int nblocks;
};

struct HashTable {
    void* nodes;
    int marked;
    int size;
    void* firstfree;
    HashTable* next;
    HashTable* self;
};

extern void* luaM_realloc(LuaState*, void*, unsigned int, const char*, int);
extern int luaO_power2(int);
extern void setnodevector(LuaState*, HashTable*, int);
extern const char lbl_8024FA84[];

HashTable* luaH_new(LuaState* state, int requested)
{
    HashTable* table = luaM_realloc(state, 0, 24, lbl_8024FA84, 178);

    table->marked = 4;
    table->next = state->tables;
    state->tables = table;
    table->self = table;
    table->size = 0;
    state->nblocks += 24;
    table->nodes = 0;
    setnodevector(state, table, luaO_power2(requested));
    return table;
}
