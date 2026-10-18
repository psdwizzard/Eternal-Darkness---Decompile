typedef struct Value Value;

typedef struct HashNode {
    int type;
    int pad4;
    double number;
    Value* result;
    char pad14[0xC];
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode* nodes;
    int pad4;
    int size;
} HashTable;

extern Value luaO_nilobject;

Value* luaH_getnum(HashTable* table, double number)
{
    HashNode* node = &table->nodes[((int)number) & (table->size - 1)];

    do {
        if (node->type == 2 && node->number == number) {
            return (Value*)((char*)node + 0x10);
        }
        node = node->next;
    } while (node != 0);
    return &luaO_nilobject;
}
