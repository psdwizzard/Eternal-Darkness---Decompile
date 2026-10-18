typedef unsigned short u16;

typedef struct ResourceEntry8 {
    void* value;
    u16 id;
    u16 references;
} ResourceEntry8;

int maccmp(ResourceEntry8* left, ResourceEntry8* right)
{
    return left->id - right->id;
}
