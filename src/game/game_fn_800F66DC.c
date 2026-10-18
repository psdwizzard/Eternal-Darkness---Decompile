extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void OSSetArenaLo(void*);
extern void* OSInitAlloc(void*, void*, int);
extern int OSCreateHeap(void*, void*);
extern void OSSetCurrentHeap(int);
extern void OSFreeToHeap(int, void*);

static int initialized;
static int unused;

static inline void InitDefaultHeap(void)
{
    void* arenaLo;
    void* arenaHi;

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);
    arenaLo = (void*)(((unsigned int)arenaLo + 0x1F) & ~0x1F);
    arenaHi = (void*)((unsigned int)arenaHi & ~0x1F);
    OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
    OSSetArenaLo(arenaHi);
    initialized = 1;
}

void __sys_free(void* p)
{
    if (!initialized) {
        InitDefaultHeap();
    }

    OSFreeToHeap(0, p);
}
