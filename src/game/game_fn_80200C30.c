struct Node {
    unsigned char pad_00[0x14];
    float timer;
};

float fn_80200C30(struct Node *node)
{
    return node->timer;
}
