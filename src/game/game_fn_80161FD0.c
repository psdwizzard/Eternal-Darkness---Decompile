typedef unsigned int u32;

typedef struct Entry {
    char pad00[0x10];
    u32 index;
} Entry;

extern void* token2string[];
extern Entry* luaS_new(void*, void*);

void luaX_init(void* owner)
{
    int i;

    for (i = 0; i < 18; i++) {
        Entry* entry = luaS_new(owner, token2string[i]);
        entry->index = (unsigned char)(i + 3);
    }
}
