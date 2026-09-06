typedef struct Node {
    int category;
    char pad04[4];
    int size;
    struct Node* next;
    int state;
} Node;

typedef struct Bucket {
    char pad00[0x3C];
    Node* nodes;
} Bucket;

typedef struct Collection {
    char pad00[0x38];
    int count;
    int active_count;
    Node** lists;
    char pad44[4];
    Bucket* buckets;
    char pad4C[0x14];
    int total_size;
} Collection;

extern void fn_80161B0C(Collection*, int*);

void fn_80161C30(Collection* collection, int preserve)
{
    int bucket_offset;
    int offset;
    int index;

    for (index = 0, offset = 0; index < collection->count; offset += 4, index++) {
        Node** link = (Node**)((char*)collection->lists + offset);
        Node* node;
        while ((node = *link) != 0) {
            if (node->state != 0 && preserve == 0) {
                node->state = 0;
                link = &node->next;
            } else {
                bucket_offset = (node->category << 6) + 60;
                *link = node->next;
                node->next = *(Node**)((char*)collection->buckets + bucket_offset);
                *(Node**)((char*)collection->buckets + bucket_offset) = node;
                collection->total_size -= node->size + 21;
                collection->active_count--;
            }
        }
    }
    fn_80161B0C(collection, &collection->count);
}
