/* GXLoadLightObjImm: GXLoadLightObjImm (Dolphin SDK GXLight.c).
 * Writes a light object's color, attenuation, position and direction
 * into the XF light registers for the given light id. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct GXData {
    u8 pad0[2];
    u16 bpSentNot;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
    f32 f32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

typedef struct GXLightObjInt {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
} GXLightObjInt;

void GXLoadLightObjImm(GXLightObjInt *obj, int light)
{
    u32 idx;
    u32 addr;

    switch (light) {
    case 0x01: idx = 0; break;
    case 0x02: idx = 1; break;
    case 0x04: idx = 2; break;
    case 0x08: idx = 3; break;
    case 0x10: idx = 4; break;
    case 0x20: idx = 5; break;
    case 0x40: idx = 6; break;
    case 0x80: idx = 7; break;
    default:   idx = 0; break;
    }

    addr = idx * 16 + 0x600;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = addr | (0xF << 16);
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = 0;
    GXWGFifo.u32 = obj->Color;
    GXWGFifo.f32 = obj->a[0];
    GXWGFifo.f32 = obj->a[1];
    GXWGFifo.f32 = obj->a[2];
    GXWGFifo.f32 = obj->k[0];
    GXWGFifo.f32 = obj->k[1];
    GXWGFifo.f32 = obj->k[2];
    GXWGFifo.f32 = obj->lpos[0];
    GXWGFifo.f32 = obj->lpos[1];
    GXWGFifo.f32 = obj->lpos[2];
    GXWGFifo.f32 = obj->ldir[0];
    GXWGFifo.f32 = obj->ldir[1];
    GXWGFifo.f32 = obj->ldir[2];
    gx->bpSentNot = 1;
}
