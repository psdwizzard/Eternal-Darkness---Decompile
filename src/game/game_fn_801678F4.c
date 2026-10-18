typedef struct LuaState {
    char pad0[0x60];
    int nblocks;
} LuaState;

typedef struct Value {
    int type;
    int pad4;
    double data;
} Value;

typedef struct HashNode {
    Value key;
    Value value;
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

extern int numuse(HashTable*);
extern void setnodevector(LuaState*, HashTable*, int);
extern Value* luaH_set(LuaState*, HashTable*, Value*);
extern void* luaM_realloc(LuaState*, void*, unsigned int, const char*, int);
extern const char lbl_8024FA84[];

void rehash(LuaState* state, HashTable* table)
{
    HashNode* node;
    int oldsize = table->size;
    HashNode* oldnodes = table->nodes;
    int i;
    int count = numuse(table);
    int quarter = oldsize / 4;

    if (count >= oldsize - quarter) {
        setnodevector(state, table, oldsize * 4);
    } else if (count <= quarter && oldsize > 4) {
        setnodevector(state, table, oldsize / 2);
    } else {
        setnodevector(state, table, oldsize);
    }

    node = oldnodes;
    for (i = 0; i < oldsize; node++, i++) {
        if (node->value.type != 1) {
            *luaH_set(state, table, &node->key) = node->value;
        }
    }

    luaM_realloc(state, oldnodes, 0, lbl_8024FA84, 229);
}
