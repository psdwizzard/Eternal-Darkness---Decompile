/* GXInitLightColor: pack an RGBA color into a light object. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef float f32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct GXLightObjInt {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
} GXLightObjInt;

void fn_80227BE0(GXLightObjInt *obj, GXColor color)
{
    obj->Color = ((u32)color.r << 24) | ((u32)color.g << 16) |
                 ((u32)color.b << 8) | color.a;
}
