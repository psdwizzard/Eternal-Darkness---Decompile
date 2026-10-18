typedef struct Value {
    int type;
    int pad4;
    union {
        double number;
        void* pointer;
    } data;
} Value;

typedef struct HashNode {
    char pad0[0x28];
} HashNode;

typedef struct HashTable {
    HashNode* nodes;
    int pad4;
    int size;
} HashTable;

#pragma use_lmw_stmw on
#pragma opt_propagation off

extern HashNode* luaH_mainposition(HashTable*, Value*);
extern Value* luaH_getnum(HashTable*, double);
extern Value luaO_nilobject;

void luaH_remove(HashTable* table, Value* value)
{
    HashNode* node;
    int index;

    if (value->type == 2 ||
        (value->type == 3 && *(unsigned int*)((char*)value->data.pointer + 8) <= 30)) {
        return;
    }

    node = luaH_mainposition(table, value);
    index = ((char*)node - (char*)table->nodes) / 40;

    while (luaH_getnum(table, (double)index) != &luaO_nilobject) {
        if (index >= 0x7FFFFFFD - table->size) {
            return;
        }
        index += table->size;
    }

    value->type = 2;
    value->data.number = (double)index;
}

#pragma opt_propagation reset
#pragma use_lmw_stmw off
