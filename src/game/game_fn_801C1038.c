typedef unsigned int u32;

typedef struct Link {
    struct Link* next;
    struct Link* prev;
    u32 key;
    u32 value;
} Link;

extern Link* vidRoot;

Link* get_vidlist(u32 key)
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
