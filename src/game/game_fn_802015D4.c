typedef struct Object802015D4 {
    unsigned char pad0[0x10];
    int unk10;
} Object802015D4;

extern void fn_8020123C(int, int, int, int);

void fn_802015D4(Object802015D4 *object)
{
    fn_8020123C(3, object->unk10, object->unk10, 0);
    fn_8020123C(4, object->unk10, object->unk10, 0);
}
