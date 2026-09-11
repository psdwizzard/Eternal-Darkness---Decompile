typedef struct Node {
    unsigned char pad_00[0x24];
    struct Node *next;
} Node;

extern Node *lbl_8064D86C;

Node *fn_80200C40(void)
{
    return lbl_8064D86C->next;
}
