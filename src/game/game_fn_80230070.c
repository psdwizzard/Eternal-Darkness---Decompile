#include "src/game/types.h"

extern void *memset(void *, int, unsigned long);

typedef struct AllocationChain {
    void *allocation;
    struct AllocationChain *next;
} AllocationChain;

typedef struct BlockStorage {
    u8 pad00[0x40];
    s32 total;
    u8 pad44[8];
    AllocationChain *chain;
} BlockStorage;

void _vorbis_block_ripcord(BlockStorage *block)
{
    AllocationChain *node = block->chain;

    while (node != 0) {
        AllocationChain *next = node->next;
        memset(node, 0, sizeof(*node));
        node = next;
    }
    block->total = 0;
    block->chain = 0;
}
