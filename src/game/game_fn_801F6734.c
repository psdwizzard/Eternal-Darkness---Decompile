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

int fn_801F6734(void* source, Entry* entry)
{
    u16 values[4];

    memcpy(values, source, sizeof(values));
    entry->type = values[0];
    entry->animation[0] = values[1];
    entry->field_2 = values[2];
    entry->field_4 = values[3];
    return sizeof(values);
}
