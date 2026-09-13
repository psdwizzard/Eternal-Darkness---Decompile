typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Info {
    u32 word;
    u16 half;
} Info;

typedef struct Entry {
    void* value;
    u32 unused[2];
} Entry;

extern u32 lbl_80651DB8;
extern u16 lbl_80651DBC;
extern u8 lbl_80607120[];

void fn_8018D788(int index, void* object, void** output, u16 value);
void fn_80197D20(void* object, void* entry, Info* info, u8 flags);
void fn_80198850(void* source, void* values, u8 count, void* first, void* second);
void fn_80198A2C(void* entry, void* values, u8 count);
void fn_80198420(void* values, void* entries, u8 count, void* entry, u8 value);
void* memcpy(void* dst, const void* src, unsigned long size);

void fn_80196918(u8* object, u8* config)
{
    u8 values[196];
    Entry entry;
    Info info;
    u8 second[6];
    u8 first[6];
    u8* table;
    int i;

    info.word = lbl_80651DB8;
    info.half = lbl_80651DBC;
    table = lbl_80607120;
    *(u16*)(object + 0xa6) = *(u16*)(config + 0x30);
    *(float*)(object + 0xd0) = *(float*)(config + 0x40);
    object[0xa2] = config[0x29];
    object[0xa5] = config[0x2c] & 0x1f;
    if (!(config[0x2c] & 0x80)) {
        object[0xa5] |= 0x20;
    }
    object[0xa1] = config[0x28];
    object[0xa4] = config[0x2b];
    *(u16*)(object + 0xae) = *(u16*)(object + 0xa6);
    object[0x8c] = config[0x20];
    object[0x8d] = config[0x21];
    object[0x8e] = config[0x24];
    *(u16*)(object + 0x96) = *(u16*)(config + 0x1e);
    *(u32*)(object + 0x90) = 0;
    *(s16*)(object + 0x98) = *(s16*)(config + 0x1c);
    *(u16*)(object + 0x94) = 75;
    memcpy(object + 0xd4, object + 0x10, 6);

    switch (object[0xa2]) {
    case 7: {
        for (i = 0; i < 2; i++) {
            fn_8018D788(i, object, (void**)&entry, *(u16*)(table + 2));
            fn_80197D20(object, entry.value, &info, config[0x2c]);
        }
        break;
    }
    case 8:
    case 9: {
        fn_80198850(config + 0x68, values, (u8)(object[1] >> 1), first, second);
        memcpy(object + 0x10, first, 6);
        memcpy(object + 0x16, second, 6);
        for (i = 0; i < 2; i++) {
            fn_8018D788(i, object, (void**)&entry, *(u16*)(table + 2));
            fn_80197D20(object, entry.value, &info, config[0x2c]);
            fn_80198A2C(entry.value, values, (u8)(object[1] >> 1));
            {
                u8 count = *(volatile u8*)(object + 1);
                fn_80198420(object + 0x10, *(void**)(object + 0x4c), count,
                        entry.value, object[0x8c]);
            }
        }
        break;
    }
    }
}
