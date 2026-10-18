typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GroupEntry {
    u16 id;
    u16 state;
    u32 base;
    u32 resolved;
    unsigned char link[0x14];
} GroupEntry;

typedef struct RegistryEntry {
    GroupEntry* entries;
    u32 value;
    u16 count;
    u16 padding;
} RegistryEntry;

extern RegistryEntry lbl_8061C748[];
extern u16 dataSmpSDirNum;
extern void hwSaveSample(void*, void*);

int dataAddSampleReference(u16 id)
{
    int registry_index = 0;
    GroupEntry* found = 0;
    GroupEntry* entry;

    while ((unsigned)registry_index < dataSmpSDirNum) {
        entry = lbl_8061C748[registry_index].entries;
        while (entry->id != 0xFFFF) {
            if (entry->id == id && entry->state != 0xFFFF) {
                found = entry;
                goto found_entry;
            }
            entry++;
        }
        registry_index++;
    }

found_entry:
    if (found->state == 0) {
        void* link;
        found->resolved = found->base + lbl_8061C748[registry_index].value;
        link = (unsigned char*)found + 0xC;
        hwSaveSample(&link, &found->resolved);
    }
    found->state++;
    return 1;
}
