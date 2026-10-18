typedef unsigned short u16;

typedef struct IdEntry {
    u16 unused0;
    u16 unused2;
    u16 id;
} IdEntry;

int curvecmp(IdEntry* left, IdEntry* right)
{
    return left->id - right->id;
}
