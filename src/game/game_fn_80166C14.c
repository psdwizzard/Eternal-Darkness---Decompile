typedef struct HashNode HashNode;

struct HashNode {
    unsigned int hash;
    void* value;
    void* key;
    HashNode* next;
};

typedef struct TableState {
    int size;
    int nuse;
    HashNode** hash;
} TableState;

typedef struct LuaState {
    char pad0[0x2C];
    TableState strt;
    TableState udt;
    char pad44[0x1C];
    int nblocks;
} LuaState;

extern void* luaM_realloc(LuaState*, void*, int, const char*, int);
extern const char lbl_8024FA38[];

void luaS_resize(LuaState* state, TableState* table, int newsize)
{
    HashNode** newhash;
    int i;

    newhash = luaM_realloc(state, 0, newsize * sizeof(HashNode*), lbl_8024FA38, 57);
    for (i = 0; i < newsize; i++) {
        newhash[i] = 0;
    }

    for (i = 0; i < table->size; i++) {
        HashNode* node = table->hash[i];
        if (table == &state->strt) {
            while (node != 0) {
                HashNode* next = node->next;
                unsigned int bucket = node->hash & (newsize - 1);
                node->next = newhash[bucket];
                newhash[bucket] = node;
                node = next;
            }
        } else {
            while (node != 0) {
                HashNode* next = node->next;
                unsigned int bucket = ((unsigned int)node->value >> 3) & (newsize - 1);
                node->next = newhash[bucket];
                newhash[bucket] = node;
                node = next;
            }
        }
    }

    luaM_realloc(state, table->hash, 0, lbl_8024FA38, 75);
    state->nblocks += (newsize - table->size) * sizeof(HashNode*);
    table->size = newsize;
    table->hash = newhash;
}
