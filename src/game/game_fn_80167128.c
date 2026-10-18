typedef struct Value {
    int type;
    int pad;
    union {
        double number;
        void* pointer;
        unsigned int word;
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

HashNode* luaH_mainposition(HashTable* table, Value* value)
{
    unsigned int key;

    switch (value->type) {
    case 2:
        key = (int)value->data.number;
        break;
    case 3:
        key = *(unsigned int*)value->data.pointer;
        break;
    case 0:
        key = value->data.word >> 3;
        break;
    case 4:
        key = value->data.word >> 3;
        break;
    case 5:
        key = value->data.word >> 3;
        break;
    default:
        return 0;
    }

    return &table->nodes[key & (table->size - 1)];
}
