typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Link {
    struct Link* next;
    struct Link* prev;
    u8 pad_008[8];
} Link;

extern Link lbl_80626DA0[];
extern Link* vidCurrentId;
extern Link* vidRoot;
extern Link* vidFree;

void vidInit(void)
{
    u32 i;
    Link* link;
    Link* previous;

    link = lbl_80626DA0;
    vidFree = link;
    i = 0;
    vidCurrentId = 0;
    previous = 0;
    vidRoot = 0;

    for (; i < 128; i++) {
        link->prev = previous;
        if (previous != 0) {
            previous->next = link;
        }
        previous = link;
        link++;
    }
    previous->next = 0;
}
