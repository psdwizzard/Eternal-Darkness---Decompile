typedef struct Object80201948 {
    unsigned char unk0[0x18];
    int id;
} Object80201948;

typedef struct Entry80201948 {
    unsigned char unk0[0x24];
    Object80201948 *object;
} Entry80201948;

typedef struct Node80201948 {
    unsigned int unk0;
    struct Node80201948 *next;
    int id;
} Node80201948;

extern Entry80201948 *fn_80201814(int);

int fn_80201948(int id, Node80201948 *node)
{
    Entry80201948 *entry;
    Node80201948 *current;
    int is_header = 0;

    if (node != 0 && node->unk0 == 0) {
        is_header = 1;
    }

    if (is_header) {
        current = node->next;
    } else {
        current = node;
    }

    for (; current != 0; current = current->next) {
        entry = fn_80201814(current->id);
        if (entry != 0 && entry->object != 0 && entry->object->id == id) {
            return current->id;
        }
    }

    return -1;
}
