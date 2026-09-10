typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Record {
    Vec3 position;
    u8 color[4];
    u32 value;
} Record;

void fn_801FD6AC(Record* record, const Vec3* position, const u8* color, u32 value)
{
    if (record != 0) {
        record->position.x = position->x;
        record->position.y = position->y;
        record->position.z = position->z;
        record->color[0] = color[0];
        record->color[1] = color[1];
        record->color[2] = color[2];
        record->color[3] = color[3];
        record->value = value;
    }
}
