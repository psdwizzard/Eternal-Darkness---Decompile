typedef unsigned char u8;
typedef unsigned int u32;

extern void fn_801DD0A8(u32, void*, int);

int fn_801DD188(void* object, int operation, u8 kind)
{
    int result = 0;

    if (operation == 4) {
        result = 0x818;
        switch (kind) {
        case 2:
            result |= 0x10000;
            break;
        case 3:
            result |= 0x20000;
            break;
        case 4:
            result |= 0x40000;
            break;
        }
        fn_801DD0A8(result, object, 0);
        result = 1;
    }
    return result;
}
