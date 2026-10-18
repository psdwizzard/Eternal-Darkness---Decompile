typedef unsigned int u32;

typedef struct Link {
    struct Link* next;
    struct Link* prev;
    u32 key;
    u32 value;
} Link;

extern Link* vidRoot;

static inline Link* find_link(u32 key)
{
    Link* link = vidRoot;

    while (link != 0) {
        if (link->key == key) {
            return link;
        }
        if (link->key > key) {
            break;
        }
        link = link->next;
    }
    return 0;
}

u32 vidGetInternalId(u32 key)
{
    Link* link;

    if (key != 0xFFFFFFFF) {
        link = find_link(key);
        if (link != 0) {
            return link->value;
        }
    }
    return 0xFFFFFFFF;
}
