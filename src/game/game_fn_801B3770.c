typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Link Link;
struct Link { Link* next; Link* prev; void* object; };

typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    u8 state;
    u8 type;
    u8 pad0A[2];
    u32 key;
};

typedef struct Entry Entry;
struct Entry { u8 data[0x1868]; };

extern Entry lbl_8060C020[];
extern Node* volatile lbl_8064D394;
extern Node* volatile lbl_8064D398;
extern Node* volatile lbl_8064D39C;
extern void fn_801B244C(void*);
extern void fn_801C21E8(void*);

void fn_801B3770(u32 handle)
{
    Entry* entries = lbl_8060C020;
    u32 key = handle & 0x7FFFFFFF;
    u32 id;
    Node* search = lbl_8064D39C;
    Node* node;
    Link* link;
    u32 i;
    while (search != 0) {
        if (search->key == key) {
            id = search->type;
            id |= handle & 0x80000000U;
            goto resolved;
        }
        search = search->next;
    }
    search = lbl_8064D398;
    while (search != 0) {
        if (search->key == key) {
            id = search->type;
            id |= handle & 0x80000000U;
            goto resolved;
        }
        search = search->next;
    }
    id = -1;
resolved:
    if (id == 0xFFFFFFFFU) return;
    if ((id & 0x80000000U) == 0) {
        u32 offset = id * sizeof(Entry);
        u8* entry = (u8*)entries + offset;
        u8 state = entry[0x1408];
        node = (Node*)(entry + 0x1400);
        switch (state) {
        case 1:
            if (node->prev) node->prev->next = node->next;
            else lbl_8064D39C = node->next;
            for (i = 0; i < 2; i++) {
                link = *(Link**)((u8*)node + 0xE64 + i * 4);
                while (link) { fn_801C21E8(link->object); link = link->next; }
            }
            link = *(Link**)((u8*)entries + offset + 0x226C);
            while (link) { fn_801C21E8(link->object); link = link->next; }
            fn_801B244C(node);
            break;
        case 2:
            if (node->prev) node->prev->next = node->next;
            else lbl_8064D398 = node->next;
            break;
        }
        if (node->next) node->next->prev = node->prev;
        node->state = 0;
        node->next = lbl_8064D394;
        node->prev = 0;
        if (lbl_8064D394) lbl_8064D394->prev = node;
        lbl_8064D394 = node;
    } else {
        {
            u8* entry = (u8*)entries + (id & 0x7FFFFFFF) * sizeof(Entry);
            u8 state = entry[0x1408];
            node = (Node*)(entry + 0x1400);
            if (state != 0) *(u32*)((u8*)node + 0xEDC) = 0;
        }
    }
}
