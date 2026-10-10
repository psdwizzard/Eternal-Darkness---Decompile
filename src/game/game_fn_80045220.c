typedef struct GlobalBlock {
    char pad[0x1918];
    unsigned char value;
} GlobalBlock;

extern GlobalBlock lbl_803003C8;

void fn_80045220(unsigned char value) {
    lbl_803003C8.value = value;
}
