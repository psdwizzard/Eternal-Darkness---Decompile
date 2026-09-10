typedef struct Node {
    unsigned char pad[0x10];
    struct Node* next;
} Node;

extern Node lbl_8063F020;

void fn_801FF9A0(void)
{
    Node* node;

    asm {
        li r0, 0x20
        mtctr r0
    delay:
        bdnz delay
    }

    node = &lbl_8063F020;
    while (node != 0) {
        node = node->next;
    }

    node = (Node*)((unsigned char*)&lbl_8063F020 + 0x14);
    while (node != 0) {
        node = node->next;
    }
}
