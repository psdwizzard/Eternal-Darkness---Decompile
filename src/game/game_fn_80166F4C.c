typedef struct HashNode HashNode;

struct HashNode {
    int tag;
    void* key;
    unsigned int size;
    HashNode* next;
    int type;
    int unused;
    unsigned char data[1];
};

typedef struct TableState {
    int size;
    int nuse;
    HashNode** hash;
} TableState;

typedef struct LuaState {
    char pad0[0x38];
    TableState udt;
    char pad44[0x1C];
    int nblocks;
} LuaState;

extern void* luaM_realloc(LuaState*, void*, int, const char*, int);
extern void newentry(LuaState*, TableState*, HashNode*, unsigned int);
extern const char lbl_8024FA38[];

HashNode* luaS_newudata(LuaState* state, unsigned int size, void* key)
{
    HashNode* node = luaM_realloc(state, 0, size + 24, lbl_8024FA38, 117);

    node->type = 0;
    node->next = 0;
    node->size = size;
    node->tag = 0;
    node->key = size != 0 ? node->data : key;
    state->nblocks += size + 21;
    newentry(state, &state->udt, node, ((unsigned int)node->key >> 3) & (state->udt.size - 1));
    return node;
}
