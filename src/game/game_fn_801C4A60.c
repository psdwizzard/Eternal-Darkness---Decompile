typedef unsigned int u32;

typedef struct SortEntry {
    unsigned char pad00[0x1C];
    u32 key;
} SortEntry;

void SortVoices(SortEntry** entries, int first, int last)
{
    int partition;
    int scan;
    SortEntry* temp;

    if (first < last) {
        temp = entries[first];
        entries[first] = entries[(first + last) / 2];
        entries[(first + last) / 2] = temp;

        partition = first;
        for (scan = first + 1; scan <= last; scan++) {
            if (entries[scan]->key < entries[first]->key) {
                partition++;
                temp = entries[partition];
                entries[partition] = entries[scan];
                entries[scan] = temp;
            }
        }

        temp = entries[first];
        entries[first] = entries[partition];
        entries[partition] = temp;

        SortVoices(entries, first, partition - 1);
        SortVoices(entries, partition + 1, last);
    }
}
