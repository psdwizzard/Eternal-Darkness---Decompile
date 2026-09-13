typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    char pad_00[0x2C];
    u32 value;
    char pad_30[0x44];
} Entry;

typedef struct Manager {
    char pad_00[0xB0];
    u16 count;
    char pad_B2[2];
    Entry *entries;
} Manager;

extern Manager *fn_8015C28C(int);
extern void *fn_80201814(void *);
extern void *fn_80201BC8(void *);
extern int fn_8013B8C0(void *, Entry *);

int fn_802066E0(void *arg, u32 value)
{
    int i;
    Manager *manager = fn_8015C28C(2);
    void *entry = fn_80201814(arg);
    u16 count = manager->count;
    Entry *candidate = manager->entries;
    void *object = fn_80201BC8(entry);

    if (object != 0) {
        for (i = 0; i < count; i++, candidate++) {
            if (candidate->value == value &&
                fn_8013B8C0(object, candidate) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
