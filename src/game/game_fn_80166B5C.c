typedef struct TableState {
    int size;
    int nuse;
    void** hash;
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

void luaS_freeall(LuaState* state)
{
    state->nblocks -= (state->strt.size + state->udt.size) * sizeof(void*);
    luaM_realloc(state, state->strt.hash, 0, lbl_8024FA38, 41);
    luaM_realloc(state, state->udt.hash, 0, lbl_8024FA38, 43);
}
