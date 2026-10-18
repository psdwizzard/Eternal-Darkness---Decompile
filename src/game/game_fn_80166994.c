typedef struct TObject {
    int tag;
    char value[12];
} TObject;

typedef struct TableState {
    int size;
    int nuse;
    void* hash;
} TableState;

typedef struct LuaState {
    TObject* top;
    TObject* stack;
    TObject* stack_last;
    int stacksize;
    TObject* Cbase;
    void* errorJmp;
    void* Mbuffer;
    int Mbuffsize;
    void* rootproto;
    void* rootcl;
    void* roottable;
    TableState strt;
    TableState udt;
    void* gt;
    void* TMtable;
    int last_tag;
    void* refArray;
    int refSize;
    int refFree;
    int GCthreshold;
    int nblocks;
    void* callhook;
    void* linehook;
    int allowhooks;
} LuaState;

extern void luaC_collect(LuaState*, int);
extern void luaS_freeall(LuaState*);
extern void* luaM_realloc(LuaState*, void*, int, const char*, int);
extern const char lbl_8024FA28[];

void lua_close(LuaState* state)
{
    luaC_collect(state, 1);
    luaS_freeall(state);
    if (state->stack) {
        state->nblocks -= (state->stack_last - state->stack + 1) * sizeof(TObject);
    }
    luaM_realloc(state, state->stack, 0, lbl_8024FA28, 110);
    state->nblocks -= (state->last_tag + 1) * 64;
    luaM_realloc(state, state->TMtable, 0, lbl_8024FA28, 112);
    state->nblocks -= state->refSize * 24;
    luaM_realloc(state, state->refArray, 0, lbl_8024FA28, 114);
    state->nblocks -= state->Mbuffsize;
    luaM_realloc(state, state->Mbuffer, 0, lbl_8024FA28, 116);
    luaM_realloc(state, state, 0, lbl_8024FA28, 118);
}
