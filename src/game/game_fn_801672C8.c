typedef struct Value Value;

typedef struct HashNode {
    int type;
    int pad4;
    void* key;
    char padC[0x14];
    struct HashNode* next;
    int pad24;
} HashNode;

typedef struct HashTable {
    HashNode* nodes;
    int pad4;
    int size;
} HashTable;

extern Value luaO_nilobject;

Value* luaH_getstr(HashTable* table, void* key)
{
    HashNode* node = &table->nodes[*(unsigned int*)key & (table->size - 1)];

    do {
        if (node->type == 3 && node->key == key) {
            return (Value*)((char*)node + 0x10);
        }
        node = node->next;
    } while (node != 0);
    return &luaO_nilobject;
}
