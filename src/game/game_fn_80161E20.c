typedef struct Argument {
    int type;
    char pad04[4];
    void* value;
    char pad0C[4];
} Argument;

typedef struct Node {
    char pad00[0x0C];
    struct Node* next;
} Node;

typedef struct Bucket {
    char pad00[0x3C];
    Node* nodes;
} Bucket;

typedef struct Collection {
    char pad00[0x48];
    Bucket* buckets;
    int bucket_index;
    char pad50[0x0C];
    int threshold;
    int total_size;
} Collection;

extern char lbl_8064BA88;
extern void fn_80161D58(Collection*, Argument*);
extern void* fn_8016B5CC(Collection*, Node*, unsigned int, char*, int);

#pragma opt_loop_invariants off
void fn_80161E20(Collection* collection)
{
    Argument argument;
    int index;

    argument.type = 0;
    collection->threshold = collection->total_size << 1;

    index = collection->bucket_index;
    while (index >= 0) {
        Node* node;
        while ((node = collection->buckets[index].nodes) != 0) {
            collection->buckets[index].nodes = node->next;
            argument.value = node;
            fn_80161D58(collection, &argument);
            fn_8016B5CC(collection, node, 0, &lbl_8064BA88, 323);
        }
        index--;
    }
}
#pragma opt_loop_invariants reset
