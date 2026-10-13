/* fn_80227A10: GXInitLightDistAttn - computes the distance attenuation
 * coefficients k0..k2 of a light object from a reference distance and
 * brightness. */

typedef unsigned char u8;
typedef float f32;

typedef enum {
    GX_DA_OFF,
    GX_DA_GENTLE,
    GX_DA_MEDIUM,
    GX_DA_STEEP
} GXDistAttnFn;

typedef struct {
    u8 pad[0x1C];
    f32 k[3];
} GXLightObjInt;

void fn_80227A10(GXLightObjInt *lt_obj, f32 ref_dist, f32 ref_br, GXDistAttnFn dist_func) {
    f32 k0, k1, k2;

    if (ref_dist < 0.0f) {
        dist_func = GX_DA_OFF;
    }
    if (ref_br <= 0.0f || ref_br >= 1.0f) {
        dist_func = GX_DA_OFF;
    }

    switch (dist_func) {
    case GX_DA_GENTLE:
        k0 = 1.0f;
        k1 = (1.0f - ref_br) / (ref_br * ref_dist);
        k2 = 0.0f;
        break;
    case GX_DA_MEDIUM:
        k0 = 1.0f;
        k1 = 0.5f * (1.0f - ref_br) / (ref_br * ref_dist);
        k2 = 0.5f * (1.0f - ref_br) / (ref_dist * (ref_br * ref_dist));
        break;
    case GX_DA_STEEP:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = (1.0f - ref_br) / (ref_dist * (ref_br * ref_dist));
        break;
    case GX_DA_OFF:
    default:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = 0.0f;
        break;
    }

    lt_obj->k[0] = k0;
    lt_obj->k[1] = k1;
    lt_obj->k[2] = k2;
}
