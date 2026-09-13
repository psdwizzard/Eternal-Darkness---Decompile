typedef struct DebugEntry {
    void* object;
    void* owner;
    signed char active;
    unsigned char pad9;
    unsigned short timer;
} DebugEntry;

extern DebugEntry lbl_805B1268[6];

int fn_80140CD8(void* object, void* owner)
{
    unsigned char index;
    DebugEntry* entry;
    int i = 0;
    while ((unsigned char)i < 6) {
        index = i;
        entry = &lbl_805B1268[index];
        if (entry->active == 1 && entry->object == object && entry->owner == owner)
            return index;
        i++;
    }
    return -1;
}
