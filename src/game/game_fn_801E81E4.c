typedef unsigned int u32;

typedef struct Node {
    u32 word0;
    u32 word4;
    struct Node* next;
    struct Node* prev;
} Node;

extern unsigned char lbl_80637C10[];
extern Node* lbl_8064D5B0;
extern void* memset(void*, int, u32);
extern Node* fn_801E8510(void);

void fn_801E81E4(void)
{
    memset(lbl_80637C10, 0, 0x15E0);
    lbl_8064D5B0 = fn_801E8510();
    lbl_8064D5B0->prev = 0;
    lbl_8064D5B0->next = 0;
    lbl_8064D5B0->word0 = 0;
    lbl_8064D5B0->word4 = 0;
}
