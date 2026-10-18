typedef unsigned char u8;

typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    unsigned char pad[4];
    int value;
    u8 type;
    u8 list;
};

typedef struct TypeInfo {
    u8 list;
    unsigned char pad[0x37];
} TypeInfo;

typedef struct State {
    unsigned char pad[0xE64];
    Node* lists[3];
    unsigned char pad2[0x6A8];
    TypeInfo types[1];
} State;

extern State* cseq;
extern Node* noteFree;

Node* AllocateNote(int value, u8 type)
{
    Node* node;
    Node* current;
    Node* previous;

    if ((node = noteFree) != 0) {
        if ((noteFree = node->next) != 0) {
            noteFree->prev = 0;
        }

        node->value = value;
        node->type = type;
        node->list = cseq->types[type].list;

        previous = 0;
        current = cseq->lists[node->list];
        while (current != 0) {
            if (current->value > node->value) {
                node->next = current;
                node->prev = previous;
                if (previous != 0) {
                    previous->next = node;
                } else {
                    cseq->lists[node->list] = node;
                }
                current->prev = node;
                return node;
            }
            previous = current;
            current = current->next;
        }

        node->prev = previous;
        if (previous != 0) {
            previous->next = node;
        } else {
            cseq->lists[node->list] = node;
        }
        node->next = 0;
    }

    return node;
}
