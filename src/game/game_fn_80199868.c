typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

extern void fn_8018E230(void*, void*, int, u8, u8, u8);
extern void fn_8018E260(void*, u8, u8);
extern void* fn_80201814(u32);
extern void* fn_80201BC8(void);
extern void fn_8011F6A4(void*, void*, void*, int, void*, int);
extern void fn_80180518(void*, u8, int);
extern u8 fn_8018E26C(void*, void*);
extern int fn_80180430(void*, u8);
extern int fn_80180454(void*);
extern void fn_8017DCA8(void*, s16, void*);

int fn_80199868(u8* object)
{
    u8* config = object + 0x8c;
    struct {
        u32 unused[2];
        float x;
        float y;
        float z;
        u32 padding[5];
    } result;

    {
    int index;
    int first;
    u8* entry;
    if (*(u16*)(object + 0xa) % config[0] == 0) {
        first = (*(u16*)(object + 0xa) / config[0]) * config[1];
        entry = *(u8**)(object + 0x4c) + first * 0x38;
        for (index = first; index < first + config[1]; index++) {
            fn_8018E230(entry, entry + 0x2b, 2, config[3], object[4], config[4]);
            fn_8018E260(entry, config[3], config[4]);
            entry += 0x38;
        }
    }
    }

    {
    u8* entry;
    u8* sequence;
    void* actor;
    int first;
    int index;
    if (*(u16*)(object + 0xa) >= config[2] &&
        (*(u16*)(object + 0xa) - config[2]) % config[0] == 0 &&
        *(u16*)(object + 0xa) <= *(u16*)(object + 0xc) &&
        fn_80201814(*(u32*)(config + 0x1c)) != 0) {
        actor = fn_80201BC8();
        sequence = config;
        first = (*(u16*)(object + 0xa) - config[2]) / config[0];
        first *= config[1];
        entry = *(u8**)(object + 0x4c) + first * 0x38;
        for (index = first; index < first + config[1]; index++) {
            fn_8011F6A4(actor, *(void**)(sequence + 0x20),
                        *(void**)(sequence + 0x28), -1, &result, 1);
            *(s16*)(entry + 0xa) = (s16)result.x;
            *(s16*)(entry + 0xc) = (s16)result.y;
            *(s16*)(entry + 0xe) = (s16)result.z;
            fn_80180518(object + 0x24, (u8)index, 1);
            entry += 0x38;
            sequence += 4;
        }
    }
    }

    {
    u8* entry;
    int index;
    int count;
    entry = *(u8**)(object + 0x4c);
    index = 0;
    count = object[1];
    for (; index < count; index++) {
        if (entry[0] != 0) {
            if (!fn_8018E26C(entry, entry + 0x2b)) {
                fn_80180518(object + 0x24, (u8)index, 0);
            }
        }
        if (fn_80180430(object + 0x24, (u8)index)) {
            fn_8017DCA8(entry + 0xa, *(s16*)(entry + 0x1c), entry + 0x10);
        }
        entry += 0x38;
    }
    }

    (*(u16*)(object + 0xa))++;
    if (*(u16*)(object + 0xa) > *(u16*)(object + 0xc) &&
        fn_80180454(object + 0x24)) {
        *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
