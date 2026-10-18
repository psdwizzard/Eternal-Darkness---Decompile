typedef struct TableState {
    int size;
    int nuse;
    void* hash;
} TableState;

typedef struct LuaState {
    void* top;
    void* stack;
    void* stack_last;
    int stacksize;
    void* Cbase;
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

extern void* luaM_realloc(void*, void*, int, const char*, int);
extern int luaD_runprotected(LuaState*, void (*)(LuaState*, int*), int*);
extern void f_luaopen(LuaState*, int*);
extern void lua_close(LuaState*);
extern const char lbl_8024FA28[];

LuaState* lua_open(int stacksize)
{
    LuaState* state = luaM_realloc(0, 0, sizeof(LuaState), lbl_8024FA28, 68);

    if (state == 0) {
        return 0;
    }
    state->stack = 0;
    state->strt.size = state->udt.size = 0;
    state->strt.nuse = state->udt.nuse = 0;
    state->strt.hash = 0;
    state->udt.hash = 0;
    state->Mbuffer = 0;
    state->Mbuffsize = 0;
    state->rootproto = 0;
    state->rootcl = 0;
    state->roottable = 0;
    state->TMtable = 0;
    state->last_tag = -1;
    state->refArray = 0;
    state->refSize = 0;
    state->refFree = -1;
    state->nblocks = sizeof(LuaState);
    state->GCthreshold = 0x7FFFFFFD;
    state->callhook = 0;
    state->linehook = 0;
    state->allowhooks = 1;
    state->errorJmp = 0;
    if (luaD_runprotected(state, f_luaopen, &stacksize) != 0) {
        lua_close(state);
        return 0;
    }
    state->GCthreshold = 2 * state->nblocks;
    return state;
}
