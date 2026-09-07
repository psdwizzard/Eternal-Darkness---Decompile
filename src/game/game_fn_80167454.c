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

extern HashNode* fn_80167128(HashTable*, Value*);
extern Value* fn_80167264(HashTable*, double);
extern Value lbl_8023A868;

void fn_80167454(HashTable* table, Value* value)
{
    HashNode* node;
    int index;

    if (value->type == 2 ||
        (value->type == 3 && *(unsigned int*)((char*)value->data.pointer + 8) <= 30)) {
        return;
    }

    node = fn_80167128(table, value);
    index = ((char*)node - (char*)table->nodes) / 40;

    while (fn_80167264(table, (double)index) != &lbl_8023A868) {
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
