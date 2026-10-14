typedef int s32;

typedef struct Item {
    char pad0[0x2D0];
    s32 value; /* 0x2D0 */
    s32 limit; /* 0x2D4 */
    char pad2D8[0x2F4 - 0x2D8];
    struct Node* list; /* 0x2F4 */
} Item;

typedef struct Node {
    Item* item;        /* 0x00 */
    char pad4[0xC];
    struct Node* next; /* 0x10 */
} Node;

s32 fn_8020F3D0(Item* self)
{
    s32 min = self->limit;
    Node* node;

    for (node = self->list; node != 0; node = node->next) {
        if (node->item != 0 && node->item->value < min) {
            min = node->item->value;
        }
    }
    return min;
}
