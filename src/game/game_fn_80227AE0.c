/* GXInitLightPos: store the light position. */

typedef unsigned char u8;
typedef float f32;

typedef struct {
    u8 pad[0x28];
    f32 lpos[3];
    f32 ldir[3];
} GXLightObjInt;

void fn_80227AE0(GXLightObjInt *lt_obj, f32 x, f32 y, f32 z)
{
    lt_obj->lpos[0] = x;
    lt_obj->lpos[1] = y;
    lt_obj->lpos[2] = z;
}
