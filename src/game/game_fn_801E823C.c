typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Node {
    u32 word0;
    u32 word4;
    struct Node* next;
    struct Node* prev;
} Node;

extern char lbl_80265AA0[];
extern void* lbl_8064D5B4;
extern Node* lbl_8064D5B0;
extern void* fn_801FEA8C(u32, int, const char*, int);
extern void* fn_8017CCD8(void*, u32, u32);
extern Node* fn_801E8510(void);

void fn_801E823C(u32 count)
{
    void* allocation = fn_801FEA8C((u16)count * 16, 1, lbl_80265AA0, 72);
    lbl_8064D5B4 = fn_8017CCD8(allocation, 16, count);
    lbl_8064D5B0 = fn_801E8510();
    lbl_8064D5B0->prev = 0;
    lbl_8064D5B0->next = 0;
    lbl_8064D5B0->word0 = 0;
    lbl_8064D5B0->word4 = 0;
}
