typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vertex {
    s16 x;
    s16 y;
    s16 z;
} Vertex;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Setup {
    u16 pad00;
    u16 offset;
    u8 pad04[6];
    u16 vertexSize;
    u16 colorSize;
    u16 indexSize;
} Setup;

typedef struct Buffers {
    u8* vertices;
    u8* indices;
    u8* colors;
} Buffers;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Entry {
    u8 pad00[0xA];
    s16 x;
    s16 z;
    u8 pad0E[0x12];
    u8 count;
    u8 pad21[0xA];
    u8 alpha;
    u8 pad2C[0xC];
} Entry;

typedef struct Object {
    u8 pad00;
    u8 count;
    u8 pad02[0xC];
    s16 id;
    u8 pad10[0x3C];
    Entry* entries;
    u8 pad50[0xC];
    u32 source;
    u8 pad60[0x64];
    Vec3 position;
    Vec3 corners[3];
} Object;

extern Setup lbl_80607120;
extern int lbl_8064D738;
extern void fn_8018D788(int, Object*, Buffers*, u16);
extern void DCFlushRange(void*, u32);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(Object*, u32*, int);
extern void fn_801889D8(void*, void*, void*);

void fn_8019C7A8(Object* object)
{
    Setup setup;
    Buffers buffers;
    Vec3 position;
    Vec3 points[3];
    s16 anchorX;
    s16 offsetX;
    int half;
    s16 offsetY;
    s16 midpointX;
    int saved;
    s16 anchorY;
    int midpointZ;
    Vec3* pointBase;
    Vec3* point;
    s16 x;
    int midpointY;
    Entry* entry;
    Color* color;
    Vertex* vertex;
    s16 z;
    int inner;
    int outer;
    u8 count;
    float dx;
    float dz;

    setup = lbl_80607120;
    count = object->count;
    fn_8018D788(lbl_8064D738, object, &buffers, setup.offset);
    pointBase = points;
    entry = object->entries;
    color = (Color*)buffers.colors;

    for (outer = 0; outer < count; outer++) {
        z = entry->z;
        x = entry->x;
        vertex = (Vertex*)(buffers.vertices + outer * 4 * sizeof(Vertex));
        dx = (float)x - object->position.x;
        dz = (float)z - object->position.y;
        position = object->position;
        points[0] = object->corners[0];
        points[0].x += dx;
        points[0].y += dz;
        points[1] = object->corners[1];
        points[1].x += dx;
        points[1].y += dz;
        points[2] = object->corners[2];
        points[2].x += dx;
        points[2].y += dz;
        position.x = (float)x;
        position.y = (float)z;

        half = (s16)(points[2].x - points[0].x) >> 1;
        midpointX = (s16)(points[0].x + (float)half);
        half = (s16)(points[2].y - points[0].y) >> 1;
        midpointY = (s16)(points[0].y + (float)half);
        half = (s16)(points[2].z - points[0].z) >> 1;
        midpointZ = (s16)(points[0].z + (float)half);

        anchorX = (s16)(midpointX + (s16)((s16)((float)midpointX - position.x) * 2));
        anchorY = (s16)(midpointY + (s16)((s16)((float)midpointY - position.y) * 2));
        offsetX = (s16)((midpointX - anchorX) >> 1);
        offsetY = (s16)((midpointY - anchorY) >> 1);

        points[0].x += offsetX;
        points[0].y += offsetY;
        points[1].x += offsetX;
        points[1].y += offsetY;
        points[2].x += offsetX;
        points[2].y += offsetY;

        anchorX += offsetX;
        anchorY += offsetY;
        point = pointBase;
        for (inner = 0; inner < entry->count - 1; inner++) {
            vertex->x = (s16)point->x;
            vertex->y = (s16)point->y;
            vertex->z = (s16)point->z;
            point++;
            vertex++;
            color->a = entry->alpha;
            color++;
        }
        vertex->x = anchorX;
        vertex->y = anchorY;
        vertex->z = midpointZ;
        color->a = entry->alpha;
        color++;
        entry++;
    }

    DCFlushRange(buffers.vertices, setup.vertexSize);
    DCFlushRange(buffers.indices, setup.indexSize);
    DCFlushRange(buffers.colors, setup.colorSize);
    saved = fn_801ED57C(0);
    fn_8018D0D0(object, &object->source, object->id);
    fn_801889D8(buffers.vertices, buffers.indices, buffers.colors);
    fn_801ED57C(saved);
}
