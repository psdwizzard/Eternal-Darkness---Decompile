typedef struct Entry {
    int _field00;
    int count8;
    int _field08;
    int count4_a;
    int _field10;
    int count4_b;
    int _field18;
    int count4_c;
    char _pad20[0x10];
    int count4_d;
    int count12;
} Entry;

int protosize(Entry* entry)
{
    return 0x44 + entry->count8 * 8 + entry->count4_a * 4
        + entry->count4_b * 4 + entry->count4_c * 4
        + entry->count12 * 12 + entry->count4_d * 4;
}
