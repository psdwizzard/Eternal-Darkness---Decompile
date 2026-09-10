extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void OSSetArenaLo(void*);
extern void* fn_8020AF08(void*, void*, int);
extern int fn_8020AF78(void*, void*);
extern void fn_8020AEF8(int);
extern void fn_8020AE7C(int, void*);

static int lbl_8064CC30;
static int unused;

static inline void InitDefaultHeap(void)
{
    void* arenaLo;
    void* arenaHi;

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    arenaLo = fn_8020AF08(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);
    arenaLo = (void*)(((unsigned int)arenaLo + 0x1F) & ~0x1F);
    arenaHi = (void*)((unsigned int)arenaHi & ~0x1F);
    fn_8020AEF8(fn_8020AF78(arenaLo, arenaHi));
    OSSetArenaLo(arenaHi);
    lbl_8064CC30 = 1;
}

void fn_800F66DC(void* p)
{
    if (!lbl_8064CC30) {
        InitDefaultHeap();
    }

    fn_8020AE7C(0, p);
}
