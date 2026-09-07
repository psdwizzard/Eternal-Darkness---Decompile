typedef unsigned int u32;

extern u32 fn_801E88E4(void*);
extern u32 fn_801E88FC(void*, u32);
extern u32* fn_801E880C(void*, u32, u32);

void fn_801E6EB0(void* resource, u32 mask, int header)
{
    u32 groups;
    u32 group;
    u32 entries;
    u32 keep;
    u32 entry;
    u32* object;

    if (resource == 0) {
        return;
    }
    groups = fn_801E88E4(resource);
    keep = ~mask;
    for (group = 0; group < groups; group++) {
        entries = fn_801E88FC(resource, group);
        for (entry = 0; entry < entries; entry++) {
            object = fn_801E880C(resource, group, entry);
            if (object != 0) {
                if (header) {
                    object[0] &= keep;
                } else {
                    object[4] &= keep;
                }
            }
        }
    }
}
