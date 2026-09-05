typedef struct StringNode StringNode;

struct StringNode {
    unsigned int hash;
    unsigned int marked;
    int length;
    StringNode* next;
    void* value;
    char chars[1];
};

typedef struct TableState {
    int size;
    int nuse;
    StringNode** hash;
} TableState;

typedef struct LuaState {
    char pad0[0x2C];
    TableState strt;
    char pad38[0x28];
    int nblocks;
} LuaState;

extern unsigned int fn_80166BD4(const char*, int);
extern int fn_800F98EC(const void*, const void*, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);
extern void* fn_8016B5CC(LuaState*, void*, int, const char*, int);
extern void fn_80166DD4(LuaState*, TableState*, StringNode*, unsigned int);
extern const char lbl_8024FA38[];

#pragma opt_propagation off
#pragma opt_lifetimes off
StringNode* fn_80166E3C(LuaState* state, const char* string, unsigned int length)
{
    int allocsize;
    StringNode* node;
    unsigned int bucket;
    unsigned int hash = fn_80166BD4(string, length);
    unsigned int len = length;
    bucket = hash & (state->strt.size - 1);
    node = state->strt.hash[bucket];

    while (node != 0) {
        if (node->length == len && fn_800F98EC(string, node->chars, len) == 0) {
            return node;
        }
        node = node->next;
    }

    {
    allocsize = len + 21;
    node = fn_8016B5CC(state, 0, allocsize, lbl_8024FA38, 101);
    node->value = 0;
    node->next = 0;
    node->length = len;
    node->hash = hash;
    node->marked = 0;
    memcpy(node->chars, string, len);
    node->chars[len] = 0;
    state->nblocks += allocsize;
    }
    fn_80166DD4(state, &state->strt, node, bucket);
    return node;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
