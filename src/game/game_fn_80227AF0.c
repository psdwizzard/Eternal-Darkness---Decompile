/* GXInitLightDir: store the negated light direction. */

typedef unsigned char u8;
typedef float f32;

typedef struct {
    u8 pad[0x28];
    f32 lpos[3];
    f32 ldir[3];
} GXLightObjInt;

void GXInitLightDir(GXLightObjInt *lt_obj, f32 nx, f32 ny, f32 nz)
{
    lt_obj->ldir[0] = -nx;
    lt_obj->ldir[1] = -ny;
    lt_obj->ldir[2] = -nz;
}
