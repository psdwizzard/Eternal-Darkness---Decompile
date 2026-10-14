/* GXInitLightAttn: set angular and distance attenuation coefficients. */
typedef struct {
    unsigned char pad[0x10];
    float a[3];
    float k[3];
} GXLightObjInt;

void fn_80227874(GXLightObjInt *lt_obj, float a0, float a1, float a2,
                 float k0, float k1, float k2)
{
    lt_obj->a[0] = a0;
    lt_obj->a[1] = a1;
    lt_obj->a[2] = a2;
    lt_obj->k[0] = k0;
    lt_obj->k[1] = k1;
    lt_obj->k[2] = k2;
}
