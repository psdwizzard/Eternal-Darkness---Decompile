typedef unsigned char u8;

extern int fn_80180430(void*, u8);
extern void fn_8018E230(void*, void*, int, int, int, int);

#pragma opt_propagation off
void fn_801A5860(u8* object)
{
    u8* entry = *(u8**)(object + 0x4c);
    int count = object[1];
    unsigned int i = 0;
    for (; i < count; i++) {
        if (fn_80180430(object + 0x24, (u8)i) != 0 && entry[0] == 0) {
            fn_8018E230(entry, entry + 0x2b, 1, entry[0x2b], object[4], 0);
        }
        entry += 0x38;
    }
}
#pragma opt_propagation reset
