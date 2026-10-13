/* fn_80227890: GXInitLightSpot - computes the spotlight angle attenuation
 * coefficients a0..a2 of a light object from a cutoff angle in degrees. */

typedef unsigned char u8;
typedef float f32;

extern f32 fn_80048C50(f32 angle); /* cosf */

typedef enum {
    GX_SP_OFF,
    GX_SP_FLAT,
    GX_SP_COS,
    GX_SP_COS2,
    GX_SP_SHARP,
    GX_SP_RING1,
    GX_SP_RING2
} GXSpotFn;

typedef struct {
    u8 pad[0x10];
    f32 a[3];
} GXLightObjInt;

void fn_80227890(GXLightObjInt *lt_obj, f32 cutoff, GXSpotFn spot_func) {
    f32 a0, a1, a2, r, d, cr;

    if (cutoff <= 0.0f || cutoff > 90.0f) {
        spot_func = GX_SP_OFF;
    }

    r = 3.1415927f * cutoff / 180.0f;
    cr = fn_80048C50(r);

    switch (spot_func) {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        a0 = -cr / (1.0f - cr);
        a1 = 1.0f / (1.0f - cr);
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        a0 = 0.0f;
        a1 = -cr / (1.0f - cr);
        a2 = 1.0f / (1.0f - cr);
        break;
    case GX_SP_SHARP:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = cr * (cr - 2.0f) / d;
        a1 = 2.0f / d;
        a2 = -1.0f / d;
        break;
    case GX_SP_RING1:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = -4.0f * cr / d;
        a1 = 4.0f * (1.0f + cr) / d;
        a2 = -4.0f / d;
        break;
    case GX_SP_RING2:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = 1.0f - 2.0f * cr * cr / d;
        a1 = 4.0f * cr / d;
        a2 = -2.0f / d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        break;
    }

    lt_obj->a[0] = a0;
    lt_obj->a[1] = a1;
    lt_obj->a[2] = a2;
}
