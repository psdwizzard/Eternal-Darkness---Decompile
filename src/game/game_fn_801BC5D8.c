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
extern void hwRemoveSample(void*, u32);

int dataRemoveSampleReference(u16 id)
{
    int registry_index;
    GroupEntry* entry;

    for (registry_index = 0; (unsigned)registry_index < dataSmpSDirNum; registry_index++) {
        entry = lbl_8061C748[registry_index].entries;
        while (entry->id != 0xFFFF) {
            if (entry->id == id && entry->state != 0xFFFF) {
                entry->state--;
                if (entry->state == 0) {
                    hwRemoveSample(&entry->link, entry->resolved);
                }
                return 1;
            }
            entry++;
        }
    }
    return 0;
}
