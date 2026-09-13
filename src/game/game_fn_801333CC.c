typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1C;
    u32 field_20;
    u32 field_24;
} Entry;

typedef struct Manager {
    char pad_0[5];
    u8 count;
    char pad_6[10];
    Entry* entries;
} Manager;

typedef struct Triple {
    u32 x;
    u32 y;
    u32 z;
} Triple;

extern Manager* fn_8015E4A4(void);
extern void *fn_80201B9C();
extern int fn_8013864C(int, int);
extern int fn_80053E50(float, int, int, int, int, int, int, int, int,
                      Triple, int);
extern const float lbl_80650258;

void fn_801333CC(void)
{
    Manager* manager = fn_8015E4A4();

    if (manager != 0) {
        int offset;
        int i;

        i = 0;
        offset = 0;

        while (i < manager->count) {
            Entry entry = *(Entry*)((char*)manager->entries + offset);
            int resource;

            fn_80201B9C();
            resource = fn_8013864C(entry.field_4, 0x24);
            if (resource > -1) {
                float volume = lbl_80650258;
                Triple position = *(Triple*)((char*)manager->entries + offset + 0x14);
                fn_80053E50(volume, 0x1D, resource, -1, -1, -1, -1,
                            0, 0, position, -1);
                *(u32*)((char*)manager->entries + offset) = 0;
                *(u32*)((char*)manager->entries + offset + 0xC) = 0;
            }
            offset += 0x28;
            i++;
        }
    }
}
