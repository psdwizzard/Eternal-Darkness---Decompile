typedef struct Value {
    int type;
    int pad4;
    char data[8];
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
} HashTable;

int numuse(HashTable* table)
{
    int i;
    int count = 0;
    HashNode* node = table->nodes;

    for (i = 0; i < table->size; i++, node++) {
        if (node->value.type != 1) {
            count++;
        }
    }
    return count;
}
