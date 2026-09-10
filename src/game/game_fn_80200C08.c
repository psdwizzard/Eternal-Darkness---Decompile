struct Node {
    unsigned char pad_00[0x14];
    float timer;
};

void fn_80200C08(struct Node *node, float timer)
{
    node->timer = timer;
}
