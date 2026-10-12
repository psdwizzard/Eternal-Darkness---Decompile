typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;

extern f32 fn_80048C2C(f32 angle);
extern f32 fn_80048C50(f32 angle);
extern void fn_80224A60(int attribute, int type);
extern void fn_80224DC0(void *descriptors);
extern void fn_802252AC(int attribute, int *type);
extern void fn_80225460(void *descriptors);
extern void fn_802254D0(void);
extern void fn_8022551C(int format, int attribute, int count, int type, u8 fraction);
extern void fn_80225878(int format, void *attributes);
extern void fn_80225ED8(int format, void *attributes);
extern void fn_80226AB4(int primitive, int format, u16 vertices);
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
static VertexDescriptor lbl_80642418[27];
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
void fn_8022AE24(u8 latitudeCount, u8 longitudeCount)
{
    int textureType;
    f32 latitudeStep = lbl_80651754 / (f32)latitudeCount;
    f32 longitudeStep = lbl_80651768 / (f32)longitudeCount;
    int latitude, longitude;
    f32 radius;

    fn_802252AC(13, &textureType);
    fn_80225460(lbl_80642418);
    fn_80225ED8(3, lbl_806424F0);
    fn_802254D0();
    fn_80224A60(9, 1);
    fn_80224A60(10, 1);
    fn_8022551C(3, 9, 1, 4, 0);
    fn_8022551C(3, 10, 0, 4, 0);
    if (textureType != 0) {
        fn_80224A60(13, 1);
        fn_8022551C(3, 13, 1, 4, 0);
    }

    radius = 1.0f;
    for (latitude = 0; latitude < latitudeCount; latitude++) {
        f32 angle = (f32)latitude * latitudeStep;
        f32 nextAngle = angle + latitudeStep;
        f32 ringRadius = radius * fn_80048C2C(angle);
        f32 nextRingRadius = radius * fn_80048C2C(nextAngle);
        f32 height = radius * fn_80048C50(angle);
        f32 nextHeight = radius * fn_80048C50(nextAngle);
        fn_80226AB4(0x98, 3, (u16)((longitudeCount + 1) * 2));
        for (longitude = 0; longitude <= longitudeCount; longitude++) {
            f32 longitudeAngle = (f32)longitude * longitudeStep;
            f32 cosine = fn_80048C50(longitudeAngle);
            f32 sine = fn_80048C2C(longitudeAngle);
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
    fn_80224DC0(lbl_80642418);
    fn_80225878(3, lbl_806424F0);
}
