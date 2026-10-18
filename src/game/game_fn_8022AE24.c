typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern void GXSetVtxDesc(int attribute, int type);
extern void GXSetVtxDescv(void *descriptors);
extern void GXGetVtxDesc(int attribute, int *type);
extern void GXGetVtxDescv(void *descriptors);
extern void GXClearVtxDesc(void);
extern void GXSetVtxAttrFmt(int format, int attribute, int count, int type, u8 fraction);
extern void GXSetVtxAttrFmtv(int format, void *attributes);
extern void GXGetVtxAttrFmtv(int format, void *attributes);
extern void GXBegin(int primitive, int format, u16 vertices);
typedef struct VertexDescriptor {
    int attribute;
    int type;
} VertexDescriptor;
typedef struct VertexFormat {
    int attribute;
    int count;
    int type;
    u8 fraction;
} VertexFormat;
/* The SDK pools these two save areas into one 0x288-byte BSS block. */
static VertexDescriptor vcd[27];
static VertexFormat lbl_806424F0[27];
extern f32 lbl_80651754;
extern f32 lbl_80651768;

typedef union WriteGatherPipe {
    u8 byte;
    u16 halfword;
    unsigned int word;
    f32 real;
} WriteGatherPipe;
extern volatile WriteGatherPipe GXWGFifo : 0xCC008000;
#define FIFO GXWGFifo.real

/* Draw a sphere as latitude strips, preserving the caller's vertex format. */
void GXDrawSphere(u8 latitudeCount, u8 longitudeCount)
{
    int textureType;
    f32 latitudeStep = lbl_80651754 / (f32)latitudeCount;
    f32 longitudeStep = lbl_80651768 / (f32)longitudeCount;
    int latitude, longitude;
    f32 radius;

    GXGetVtxDesc(13, &textureType);
    GXGetVtxDescv(vcd);
    GXGetVtxAttrFmtv(3, lbl_806424F0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(10, 1);
    GXSetVtxAttrFmt(3, 9, 1, 4, 0);
    GXSetVtxAttrFmt(3, 10, 0, 4, 0);
    if (textureType != 0) {
        GXSetVtxDesc(13, 1);
        GXSetVtxAttrFmt(3, 13, 1, 4, 0);
    }

    radius = 1.0f;
    for (latitude = 0; latitude < latitudeCount; latitude++) {
        f32 angle = (f32)latitude * latitudeStep;
        f32 nextAngle = angle + latitudeStep;
        f32 ringRadius = radius * sinf(angle);
        f32 nextRingRadius = radius * sinf(nextAngle);
        f32 height = radius * cosf(angle);
        f32 nextHeight = radius * cosf(nextAngle);
        GXBegin(0x98, 3, (u16)((longitudeCount + 1) * 2));
        for (longitude = 0; longitude <= longitudeCount; longitude++) {
            f32 longitudeAngle = (f32)longitude * longitudeStep;
            f32 cosine = cosf(longitudeAngle);
            f32 sine = sinf(longitudeAngle);
            f32 x = cosine * nextRingRadius;
            f32 y = sine * nextRingRadius;
            FIFO = x;
            FIFO = y;
            FIFO = nextHeight;
            FIFO = x / radius;
            FIFO = y / radius;
            FIFO = nextHeight / radius;
            if (textureType != 0) {
                FIFO = (f32)longitude / (f32)longitudeCount;
                FIFO = (f32)(latitude + 1) / (f32)latitudeCount;
            }
            x = cosine * ringRadius;
            y = sine * ringRadius;
            FIFO = x;
            FIFO = y;
            FIFO = height;
            FIFO = x / radius;
            FIFO = y / radius;
            FIFO = height / radius;
            if (textureType != 0) {
                FIFO = (f32)longitude / (f32)longitudeCount;
                FIFO = (f32)latitude / (f32)latitudeCount;
            }
        }
    }
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(3, lbl_806424F0);
}
