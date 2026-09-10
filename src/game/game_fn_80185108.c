typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

extern void* memcpy(void*, const void*, u32);
extern void fn_801806D4(void*, void*, int);

void fn_80185108(u8* self)
{
    u8 value[4];
    u8* saved_self;
    int count;
    s16 current;
    int index;
    u8* entry;
    u8* position;

    saved_self = self;
    position = saved_self + 0x8C;
    entry = *(u8**)(saved_self + 0x4C);
    memcpy(value, position, 4);
    current = value[3];
    index = 0;
    count = saved_self[1];
    while (index < count) {
        fn_801806D4(entry + 0x20, value, 0);
        fn_801806D4(entry + 0x20, value, 1);
        value[3] = current;
        current -= position[4];
        if (current < 0) {
            current = 0;
        }
        entry += 0x38;
        index++;
    }
}
