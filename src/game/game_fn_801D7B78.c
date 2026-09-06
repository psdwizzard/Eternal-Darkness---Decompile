typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Object { u8 bytes[0x1000]; } Object;

extern int fn_801CEB2C(u32);
extern int fn_800F98EC(const void*, const void*, u32);
extern void fn_801D7998(s16*, s16*, Object*);

void fn_801D7B78(int now, s16* first, s16* second, Object* object)
{
    u8* current;
    u8* base;
    int index;
    s16 count;

    base = object->bytes + 0xBC;
    count = (s16)fn_801CEB2C(*(u32*)(object->bytes + 4));
    current = base;
    index = 0;

    while (fn_800F98EC(current + 0x54, first, 6) != 0 && index < count) {
        current += 6;
        index++;
    }
    if (index < count) {
        current = base + index * 4;
        if (now - *(int*)(current + 0xC) > 60) {
            fn_801D7998(first, second, object);
            *(int*)(current + 0xC) = now;
        }
    }
}
