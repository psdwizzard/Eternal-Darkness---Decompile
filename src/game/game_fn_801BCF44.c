typedef unsigned short u16;

typedef struct IdEntry {
    u16 id;
} IdEntry;

int smpcmp(IdEntry* left, IdEntry* right)
{
    return left->id - right->id;
}
