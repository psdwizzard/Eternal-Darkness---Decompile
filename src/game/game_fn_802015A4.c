typedef struct Object802015A4 {
    unsigned char pad0[0x10];
    int unk10;
} Object802015A4;

extern void fn_8020123C(int, int, int, int);

void fn_802015A4(Object802015A4 *object)
{
    fn_8020123C(1, object->unk10, object->unk10, 0);
}
