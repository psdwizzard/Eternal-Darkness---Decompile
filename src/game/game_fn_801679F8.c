typedef struct LuaState LuaState;

typedef struct Value {
    int type;
    int pad4;
    double data;
} Value;

typedef struct HashNode {
    Value key;
    Value value;
    struct HashNode* next;
    int pad24;
} HashNode;

typedef struct HashTable {
    HashNode* nodes;
    int pad4;
    int size;
    HashNode* firstfree;
} HashTable;

#pragma use_lmw_stmw on

extern HashNode* luaH_mainposition(HashTable*, Value*);
extern int luaO_equalObj(Value*, HashNode*);
extern void lua_error(LuaState*, const char*);
extern void rehash(LuaState*, HashTable*);
extern const char lbl_8024FA48[];

Value* luaH_set(LuaState* state, HashTable* table, Value* key)
{
    HashNode* mainnode = luaH_mainposition(table, key);
    HashNode* node = mainnode;

    if (mainnode == 0) {
        lua_error(state, lbl_8024FA48);
    }

    do {
        if (luaO_equalObj(key, node)) {
            return &node->value;
        }
        node = node->next;
    } while (node != 0);

    if (mainnode->key.type != 1) {
        node = table->firstfree;
        if (mainnode > node) {
            HashNode* other = luaH_mainposition(table, &mainnode->key);
            if (other != mainnode) {
                while (other->next != mainnode) {
                    other = other->next;
                }
                other->next = node;
                *node = *mainnode;
                mainnode->next = 0;
                goto set_key;
            }
        }
        node->next = mainnode->next;
        mainnode->next = node;
        mainnode = node;
    }

set_key:
    mainnode->key = *key;

    for (;;) {
        if (table->firstfree->key.type == 1) {
            return &mainnode->value;
        }
        if (table->firstfree != table->nodes) {
            table->firstfree--;
        } else {
            rehash(state, table);
            return luaH_set(state, table, key);
        }
    }
}
