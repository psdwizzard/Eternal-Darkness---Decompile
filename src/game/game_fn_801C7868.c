typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*Callback)(int, void**, void*);

typedef struct ArenaEntry {
    void* small;
    u8 pad04[0x2C];
    void* first[3];
    void* second[3];
    u8 pad48[8];
    u8 flag;
    u8 pad51[3];
    int value54;
    u8 pad58[0x54];
    Callback first_callback;
    Callback second_callback;
    void* first_arg;
    void* second_arg;
} ArenaEntry;

extern ArenaEntry dspStudio[];
extern u8 salMaxStudioNum;
extern u8 salAuxFrame;
extern void DCFlushRangeNoSync(void*, u32);

void salHandleAuxProcessing(void)
{
    u8 i;
    ArenaEntry* entry;
    void* buffer;
    void* ranges[3];

    entry = dspStudio;
    for (i = 0; i < salMaxStudioNum; i++, entry++) {
        if (entry->flag == 1) {
            if (entry->first_callback != 0) {
                buffer = entry->first[(salAuxFrame + 2) % 3];
                ranges[0] = buffer;
                ranges[1] = (u8*)buffer + 0x280;
                ranges[2] = (u8*)buffer + 0x500;
                entry->first_callback(0, ranges, entry->first_arg);
                DCFlushRangeNoSync(buffer, 0x780);
            }
            if (entry->value54 == 0 && entry->second_callback != 0) {
                buffer = entry->second[(salAuxFrame + 2) % 3];
                ranges[0] = buffer;
                ranges[1] = (u8*)buffer + 0x280;
                ranges[2] = (u8*)buffer + 0x500;
                entry->second_callback(0, ranges, entry->second_arg);
                DCFlushRangeNoSync(buffer, 0x780);
            }
        }
    }
}
