typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u16 type;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    u16* animation;
} Entry;

extern void* memcpy(void*, const void*, u32);

int fn_801F663C(void* destination, Entry* entry)
{
    u16 values[4];

    values[0] = entry->type;
    values[1] = entry->animation[0];
    values[2] = entry->field_2;
    values[3] = entry->field_4;
    memcpy(destination, values, sizeof(values));
    return sizeof(values);
}
