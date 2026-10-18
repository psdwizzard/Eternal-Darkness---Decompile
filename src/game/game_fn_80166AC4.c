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

void luaS_init(LuaState* state)
{
    state->strt.hash = luaM_realloc(state, 0, sizeof(void*), lbl_8024FA38, 29);
    state->udt.hash = luaM_realloc(state, 0, sizeof(void*), lbl_8024FA38, 30);
    state->nblocks += 2 * sizeof(void*);
    state->strt.size = state->udt.size = 1;
    state->strt.nuse = state->udt.nuse = 0;
    state->strt.hash[0] = state->udt.hash[0] = 0;
}
