typedef unsigned int u32;

typedef struct Pair {
    u32 first;
    u32 second;
} Pair;

extern Pair salHooks;

void sndSetHooks(Pair* value)
{
    salHooks = *value;
}
