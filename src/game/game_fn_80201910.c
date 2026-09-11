typedef struct Object80201910 {
    unsigned char unk0[0x18];
    int id;
} Object80201910;

typedef struct Entry80201910 {
    unsigned char unk0[0x24];
    Object80201910 *object;
} Entry80201910;

extern Entry80201910 *fn_80201814(int);

int fn_80201910(int id)
{
    Entry80201910 *entry = fn_80201814(id);

    if (entry != 0) {
        return entry->object->id;
    }

    return 0;
}
