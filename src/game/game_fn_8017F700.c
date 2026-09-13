typedef unsigned char u8;

void fn_8017F700(u8* source, u8* destination, u8 index)
{
    u8* row;
    int count;
    u8* entry;
    int i;
    u8 value;

    count = destination[1];
    row = &(*(u8**)(source + 0x4C))[(u8)index * 0x38];
    value = row[0x21];
    entry = *(u8**)(destination + 0x4C);
    for (i = 0; i < count; i++) {
        entry[0x21] = value;
        entry += 0x38;
    }
}
